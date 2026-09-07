# Jupyter workspace

This folder is meant for notebooks that orchestrate both Python and npm commands.

The `clava-workbench.ipynb` notebook includes an example flow that:

1. Resolves the sibling `../clava-scripts` project path.
2. Runs npm commands inside `clava-scripts` from Python.
3. Reads generated files from that same project folder.

This keeps notebook analysis and generated Clava outputs close and easy to access.
