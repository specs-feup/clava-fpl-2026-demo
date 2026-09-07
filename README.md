# clava-fpl-2026-demo

This repository now contains two workspaces:

- `clava-scripts/`: the original npm/TypeScript Clava project.
- `notebooks/`: Jupyter workspace for running Python notebooks that can call the npm project.

## clava-scripts

```bash
cd clava-scripts
npm install
npm run build
npm run run
```

## notebooks

```bash
cd notebooks
python -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
jupyter lab
```

Inside notebooks, use `../clava-scripts` as the working directory for npm commands so generated files remain directly accessible from the notebook.
