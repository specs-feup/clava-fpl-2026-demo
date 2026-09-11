import { BuiltinFpgaTarget } from "@specs-feup/hoopa/BuiltinFpgaPlatforms";
import { HoopaAlgorithm, HoopaConfig, OffloadingBackend, TaskGraphDecorator } from "@specs-feup/hoopa/HoopaAlgorithm";
import { HoopaAPI } from "@specs-feup/hoopa/HoopaAPI";
import { HotspotCriterion, SingleHotspotTaskOptions } from "@specs-feup/hoopa/SingleHotspotTaskOptions";
import { TimeUnit } from "@specs-feup/clava-vitis-integration/VitisReports";
import { SubsetTransform } from "@specs-feup/extended-task-graph/SubsetTransforms";
import { TransFlowConfig } from "@specs-feup/extended-task-graph/TransFlowConfig";
import { GenFlowConfig } from "@specs-feup/extended-task-graph/GenFlowConfig";
import fs from "fs";
import path from "path";

const topFunctionName = "edge_detect";
const outputDir = "outputs";
const appName = "edgedetect";

// 1. Configure code transformation recipe for the C/C++ AST
const transConfig = new TransFlowConfig();
transConfig.transformRecipe = [
    SubsetTransform.ArrayFlattener,
    SubsetTransform.ConstantFoldingPropagation,
    SubsetTransform.StructDecomposition,
    SubsetTransform.ConstantFoldingPropagation
];

const genConfig = new GenFlowConfig();

// 2. Configure Hoopa with Vitis HLS latency decorators, Single Hotspot algorithm, and XRT backend
const config = new HoopaConfig()
    .setTransFlowConfig(transConfig)
    .setGenFlowConfig(genConfig)
    .addDecorator(TaskGraphDecorator.VITIS_HLS)
    .addDecorator(TaskGraphDecorator.SYNTHESIZABILITY)
    .addAlgorithm(HoopaAlgorithm.SINGLE_HOTSPOT, {
        criterion: HotspotCriterion.LATENCY,
        precision: TimeUnit.MICROSECOND
    } as SingleHotspotTaskOptions)
    .addBackend(OffloadingBackend.XRT)
    .addBuiltinFpgaTarget(BuiltinFpgaTarget.ZCU102);

// 3. Run Hoopa partitioning
const hoopa = new HoopaAPI(topFunctionName, config, outputDir, appName);
hoopa.runFromStart(false);

// 4. Generate an annotated task graph DOT file highlighting the offloaded task in green
try {
    const defaultDotPath = path.join(outputDir, appName, "etg", "default", `${appName}_taskgraph_min.dot`);
    const highlightedDotPath = path.join(outputDir, appName, "etg", "default", `${appName}_taskgraph_offloaded_min.dot`);
    const cachedDotPath = path.join("..", "notebooks", "cached_graphs", `${appName}_taskgraph_offloaded_min.dot`);

    if (fs.existsSync(defaultDotPath)) {
        let dotContent = fs.readFileSync(defaultDotPath, "utf8");
        // Highlight convolve2d_rep0 (highest latency task selected by SingleHotspot) in green
        dotContent = dotContent.replace(
            /("T0\.2"\s*\[label="T0\.2:\s*convolve2d_rep0",\s*style="filled,solid",\s*fillcolor=)lightpink(\];)/,
            '$1"#77dd77", penwidth=3, color="darkgreen"$2'
        );
        fs.writeFileSync(highlightedDotPath, dotContent, "utf8");
        fs.writeFileSync(cachedDotPath, dotContent, "utf8");
        console.log(`[Hoopa] Generated highlighted task graph at ${highlightedDotPath} and cached in ${cachedDotPath}`);
    }
} catch (e) {
    console.error("[Hoopa] Could not generate highlighted dot file:", e);
}
