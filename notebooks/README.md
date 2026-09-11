# Jupyter workspace

This folder contains the interactive demo notebook and support utilities for the FPL 2026 demonstration.

## Contents

- `demo.ipynb`: The main interactive notebook demonstrating ETG generation, Hoopa HW/SW partitioning, holistic hotspot expansion, and trade-off/resource analysis.
- `utils.py`: Helper functions to invoke Clava/Hoopa workflows from Python, render Graphviz task graphs, and plot the interactive latency/resource dashboard.
- `cached_graphs/`: Pre-synthesized DOT graphs for instant offline exploration without rerunning Clava.
- `data/`: CSV data with hardware synthesis results (latency and resource utilization on Xilinx ZCU102).
- `requirements.txt`: Python dependencies required by the notebook.

## Setup & Execution

```bash
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
jupyter lab demo.ipynb
```
