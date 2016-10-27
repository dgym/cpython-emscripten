# Serving a pure Python application

This example demonstrates how a Python application can be run without having to
recompile/relink the main Python files for every update. This can be very
helpful during development as the linking step is very slow.

The Makefile still produces the these two files:

 * python.asm.js - Python compiled to asm.js
 * python.asm.data - A root filesystem required to initialize Python

The Makefile also bundles everything in the app/ directory into a third file
called app.zip. The main program fetches app.zip from the server and adds it to
Python's path, then executes it like a module. This is equivalent to running
```python -m app``` on the command line.

Because zipping up the app directory is typically much faster than linking this
process helps reduce the development cycle.

# Building

Run ```make```.

# Running

Run ```make serve``` to start a web server on local port 8062 (this requires
Python) and then visit the test page
[http://localhost:8062/](http://localhost:8062/).