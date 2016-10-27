# Compiling, linking and using Cython modules

This example uses a Cython module to expose the emscripten_run_script()
function.

The Cython file is compiled to a c file which is compiled and linked in with
the interpreter.

The c file has an init function that must be called before it can be imported.
The main file calls this init function after initializing the Python
interpreter.

# Building

Run ```make```.

# Running

Run ```make serve``` to start a web server on local port 8062 (this requires
Python) and then visit the test page
[http://localhost:8062/](http://localhost:8062/).
