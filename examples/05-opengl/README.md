# SDL2 and OpenGLESv2

This example uses enscripten's SDL2 support to render to a canvas using
OpenGL calls.

Only a minimal set of bindings have been written, complete Cython bindings
can probably be found in other projects, e.g.
[sdl2_cython](https://pypi.python.org/pypi/sdl2_cython/).

One important aspect of this example is that it was developed and tested on
a native host first. The app can be run on a Linux desktop machine as long
as the required SDL2 and GL libraries are installed. Once the example was
working natively it was then built with emscripten to work in the browser.

# Building

Run ```make```.

# Running

Run ```make serve``` to start a web server on local port 8062 (this requires
Python) and then visit the test page
[http://localhost:8062/](http://localhost:8062/).
