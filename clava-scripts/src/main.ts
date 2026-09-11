import { ExtendedTaskGraphAPI } from "@specs-feup/extended-task-graph/ExtendedTaskGraphAPI";
import { GenFlowConfig } from "@specs-feup/extended-task-graph/GenFlowConfig";
import { SubsetTransform } from "@specs-feup/extended-task-graph/SubsetTransforms";
import { TransFlowConfig } from "@specs-feup/extended-task-graph/TransFlowConfig";

const topFunctionName = "edge_detect";
const outputDir = "outputs";
const appName = "edgedetect";
const api = new ExtendedTaskGraphAPI(topFunctionName, outputDir, appName);

// Run code transformation flow
const config1 = new TransFlowConfig();
config1.transformRecipe = [
    SubsetTransform.ArrayFlattener,
    SubsetTransform.ConstantFoldingPropagation,
    SubsetTransform.StructDecomposition,
    SubsetTransform.ConstantFoldingPropagation
];
api.runCodeTransformationFlow(config1);

// Run ETG generation flow
const config2 = new GenFlowConfig();
const etg = api.runTaskGraphGenerationFlow(config2);

// Cache the generated ETG dot file for the notebook
try {
    const fs = await import("fs");
    const path = await import("path");
    const dotPath = path.join(outputDir, appName, "etg", "default", `${appName}_taskgraph_min.dot`);
    const cachedPath = path.join("..", "notebooks", "cached_graphs", `${appName}_taskgraph_min.dot`);
    if (fs.existsSync(dotPath)) {
        fs.copyFileSync(dotPath, cachedPath);
        console.log(`[Clava] Cached ETG dot file to ${cachedPath}`);
    }
} catch (e) {
    // Ignore cache copy error if path doesn't exist
}
