#include <stdlib.h>
#include <stdio.h>

#include <emscripten.h>
#include <Python.h>


#if PY_MAJOR_VERSION < 3
PyMODINIT_FUNC initjs(void);
#else
PyMODINIT_FUNC PyInit_js(void);
#endif


static void onload(const char *filename) {
    printf("Loaded %s.\n", filename);
    PyRun_SimpleString("import sys ; sys.path.insert(0, '/app.zip')");
    PyRun_SimpleString("import runpy ; runpy.run_module('app')");
}


static void onloaderror(const char *filename) {
    printf("Failed to load %s, aborting.\n", filename);
    PyRun_SimpleString("print('fail')");
}


int main(int argc, char** argv) {
    setenv("PYTHONHOME", "/", 0);

    Py_InitializeEx(0);
#if PY_MAJOR_VERSION < 3
    initjs();
#else
    PyInit_js();
#endif

    // Fetch app.zip from the server.
    emscripten_async_wget("app.zip", "/app.zip", onload, onloaderror);

    emscripten_exit_with_live_runtime();
    return 0;
}
