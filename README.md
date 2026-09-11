# Clava FPL 2026 Demo

This repository contains the interactive **Clava** demo presented at **FPL 2026**, matching the paper titled **Ergonomic C/C++ source-to-source analysis and transformations for HLS using Clava**. 

The demonstration explores automated task graph extraction, single-task hotspot offloading, holistic hotspot expansion, and HW/SW co-design trade-off analysis on an image processing application (**Edge Detection** in C++) targeting the **AMD Xilinx Zynq UltraScale+ ZCU102** FPGA.

---

## Repository Structure

```text
clava-fpl-2026-demo/
├── notebooks/                      # Interactive Jupyter workspace
│   ├── demo.ipynb                  # Main demonstration notebook
│   ├── utils.py                    # Python helper module for Clava execution & visualization
│   ├── cached_graphs/              # Pre-synthesized DOT graphs for instant offline exploration
│   ├── data/                       # Hardware synthesis metrics (ZCU102 latency & resources)
│   └── requirements.txt            # Python dependencies (Jupyter, Graphviz, Plotly, Pandas)
├── clava-scripts/                  # Clava & Hoopa TypeScript workspace
│   ├── CxxSources/edge_detect.cpp  # Input C++ application source code
│   ├── src/main.ts                 # Clava ETG generation script
│   ├── src/hoopa.ts                # Hoopa single-hotspot partitioning script
│   ├── src/expansion.ts            # Hoopa holistic hotspot expansion script
│   └── outputs/                    # Generated C++ code, HLS configurations, and reports
└── README.md                       # This guide
```

---

## Prerequisites

### 1. Required for the Demo Notebook
- **Python 3.10+** (with `venv` and `pip`)
- **Graphviz** (system library providing the `dot` executable for task graph rendering):
  - **Ubuntu / Debian**:
    ```bash
    sudo apt update && sudo apt install -y graphviz
    ```
  - **macOS** (via Homebrew):
    ```bash
    brew install graphviz
    ```
  - **Fedora / RHEL**:
    ```bash
    sudo dnf install graphviz
    ```

### 2. Optional (Only for Rerunning Live Clava / Hoopa Passes)
> **Note**: If Node.js or Java are not installed, the notebook **automatically falls back to pre-synthesized graphs** in `notebooks/cached_graphs/` and verified HLS benchmark data, enabling full interactive exploration offline!

If you wish to execute the Clava and Hoopa compiler passes live from the notebook:
- **Node.js** (v18+ or v20+) & **npm**
- **Java OpenJDK 17+ or 21** (`JAVA_HOME` configured)

---

## Setup & Running the Demo Notebook

### Step 1: Clone the Repository
```bash
git clone https://github.com/specs-feup/clava-fpl-2026-demo.git
cd clava-fpl-2026-demo
```

### Step 2: Set Up Python Virtual Environment & Dependencies
```bash
cd notebooks
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
```

### Step 3 (Optional): Build Clava Scripts for Live Execution
If you plan to run live Clava compiler passes:
```bash
cd ../clava-scripts
npm install
npm run build
cd ../notebooks
```

### Step 4: Launch the Demo Notebook
With the virtual environment activated:
```bash
jupyter lab demo.ipynb
```
*(Alternatively, you can run `jupyter notebook demo.ipynb` or open `notebooks/demo.ipynb` in VS Code / Cursor with the `.venv` Python kernel selected).*

---

## Demo Notebook Walkthrough (`demo.ipynb`)

The notebook guides you through four core phases of the automated HW/SW co-design flow:

| Section | Description | Key Functions / Artifacts |
|---|---|---|
| **1. Extended Task Graph (ETG) Generation** | Analyzes `edge_detect.cpp` and extracts an Extended Task Graph displaying task nodes, memory dependencies, and communication channels. | `run_clava()`<br>`show_task_graph()` |
| **2. Single-Task HW/SW Partitioning** | Applies Hoopa's latency-driven partitioning to isolate and offload the single most compute-intensive task (`convolve2d_rep0`, highlighted in green). | `run_hoopa()`<br>`show_offloaded_task_graph()` |
| **3. Holistic HW/SW Partitioning (Hotspot Expansion)** | Applies Hoopa's Holistic Hotspot Expansion algorithm to internalize intermediate image buffers (`filter`, `temp_buf`), eliminating costly host-device DMA round-trips. Shows CPU profiling annotations and expanded cluster. | `run_hotspot_expansion()`<br>`show_expanded_task_graph()` |
| **4. Partitioning Trade-Off & Resource Analysis** | Renders an interactive Plotly dashboard comparing CPU baseline, Single-Task offloading, and Holistic Hotspot Expansion. Breaks down latency (FPGA time, host compute, non-accelerable I/O) and reports FPGA resource utilization on the Xilinx ZCU102. | `plot_partitioning_comparison(interactive=True)` |

### Key Experimental Insights Highlighted in Section 4:
- **Amdahl's Law in Action**: Single-task offloading achieves only a **1.15× speedup** (293.8 ms) because 76% of compute remains on the host CPU. Holistic hotspot expansion offloads 76% of computation, dropping total execution time to 149.9 ms (**2.25× speedup**).
- **Buffer Internalization**: In the expanded hardware cluster, intermediate image frames are kept on-chip in 468 BRAM_18K blocks, avoiding memory transfer bottlenecks while keeping logic utilization low (4.2% LUT, 2.1% FF on ZCU102).

---

## Running Clava Scripts from the Command Line

You can also run each Clava and Hoopa step directly from the terminal without Jupyter:

```bash
cd clava-scripts
npm install
npm run build

# 1. Generate Extended Task Graph (ETG)
npm run run

# 2. Run Hoopa Single Hotspot Partitioning
npm run run:hoopa

# 3. Run Hoopa Holistic Hotspot Expansion
npm run run:expansion
```

Generated C++ code, transformed kernels, Vivado HLS configuration scripts, and synthesis reports will be placed in `clava-scripts/outputs/edgedetect/`.

---

## Troubleshooting

- **Graphviz rendering error (`ExecutableNotFound: failed to execute 'dot'`):**
  Install the Graphviz system package (`sudo apt install graphviz` or `brew install graphviz`) and verify with `which dot`.
- **Plotly figures not rendering in Jupyter:**
  Ensure you are using JupyterLab 4+ or the classic Notebook with modern extension support (installed by `requirements.txt`).
- **Live Clava pass fails:**
  Ensure `java -version` returns Java 17+ or 21, and `node -v` returns Node.js v18+. If unavailable, simply skip the `run_*()` cells; the visualization functions will automatically fall back to the pre-generated graphs in `cached_graphs/`.
