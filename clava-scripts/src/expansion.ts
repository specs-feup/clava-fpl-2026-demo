import { BuiltinFpgaTarget } from "@specs-feup/hoopa/BuiltinFpgaPlatforms";
import { HoopaAlgorithm, HoopaConfig, OffloadingBackend, TaskGraphDecorator } from "@specs-feup/hoopa/HoopaAlgorithm";
import { HoopaAPI } from "@specs-feup/hoopa/HoopaAPI";
import { HotspotCriterion } from "@specs-feup/hoopa/SingleHotspotTaskOptions";
import { HotspotExpansionOptions } from "@specs-feup/hoopa/HotspotExpansionOptions";
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

// 2. Configure Hoopa with Vitis HLS estimations, Synthesizability, CPU profiling (gprof-zcu102), and XRT backend
const config = new HoopaConfig()
    .setTransFlowConfig(transConfig)
    .setGenFlowConfig(genConfig)
    .addDecorator(TaskGraphDecorator.VITIS_HLS)
    .addDecorator(TaskGraphDecorator.SYNTHESIZABILITY)
    .addDecorator(TaskGraphDecorator.PROFILING, "gprof-zcu102")
    .addAlgorithm(HoopaAlgorithm.HOTSPOT_EXPANSION, {
        hotspotCriterion: HotspotCriterion.COMPUTATION_PERCENTAGE,
        profiler: "gprof-zcu102",
        precision: TimeUnit.MICROSECOND,
        policies: [],
        hlsSynthesis: false
    } as HotspotExpansionOptions)
    .addBackend(OffloadingBackend.XRT)
    .addBuiltinFpgaTarget(BuiltinFpgaTarget.ZCU102);

// 3. Run Hoopa holistic hotspot expansion partitioning
const hoopa = new HoopaAPI(topFunctionName, config, outputDir, appName);
hoopa.runFromStart(false);

// 4. Generate annotated task graph DOT file with CPU percentages and highlighted offloaded tasks
try {
    const profiledDotPath = path.join(outputDir, appName, "etg", "decorated", `${appName}_taskgraph_profiledexectime.dot`);
    const expansionDotPath = path.join(outputDir, appName, "etg", "default", `${appName}_taskgraph_expansion_min.dot`);
    const cachedDotPath = path.join("..", "notebooks", "cached_graphs", `${appName}_taskgraph_expansion_min.dot`);

    if (fs.existsSync(profiledDotPath)) {
        let dotContent = fs.readFileSync(profiledDotPath, "utf8");

        // Highlight offloaded cluster tasks:
        // - 3 outlined tasks for filter initialization (edge_detect_out0, edge_detect_out1, edge_detect_out2)
        // - 3 convolution passes (convolve2d_rep0, convolve2d_rep1, convolve2d_rep2)
        // - combination and thresholding task (combthreshold)
        const offloadedTasks = [
            { id: "T0.1", name: "edge_detect_out0" },
            { id: "T0.2", name: "convolve2d_rep0" },
            { id: "T0.3", name: "edge_detect_out1" },
            { id: "T0.4", name: "convolve2d_rep1" },
            { id: "T0.5", name: "edge_detect_out2" },
            { id: "T0.6", name: "convolve2d_rep2" },
            { id: "T0.7", name: "combthreshold" }
        ];

        for (const task of offloadedTasks) {
            const regex = new RegExp(`("${task.id}"\\s*\\[label="${task.name}[^"]*",\\s*style="filled,solid",\\s*fillcolor=)lightpink(\\];)`);
            dotContent = dotContent.replace(regex, '$1"#77dd77", penwidth=3, color="darkgreen"$2');
        }

        fs.writeFileSync(expansionDotPath, dotContent, "utf8");
        fs.writeFileSync(cachedDotPath, dotContent, "utf8");
        console.log(`[Hoopa] Generated highlighted CPU-annotated task graph at ${expansionDotPath} and cached in ${cachedDotPath}`);
    } else {
        console.warn(`[Hoopa] Profiled dot file not found at ${profiledDotPath}`);
    }

    // Cache the backend-generated cluster task graphs if present
    const clusterEtgDir = path.join(outputDir, appName, "etg", "alg_HotspotExpansion_comp%_NoPolicy_xrt_xrt");
    if (fs.existsSync(clusterEtgDir)) {
        const clusterMinDot = path.join(clusterEtgDir, `${appName}_taskgraph_min.dot`);
        const cachedClusterMin = path.join("..", "notebooks", "cached_graphs", `${appName}_taskgraph_expansion_cluster_min.dot`);
        if (fs.existsSync(clusterMinDot)) {
            fs.copyFileSync(clusterMinDot, cachedClusterMin);
            console.log(`[Hoopa] Cached cluster ETG at ${cachedClusterMin}`);
        }
    }
} catch (e) {
    console.error("[Hoopa] Could not generate highlighted dot file:", e);
}
