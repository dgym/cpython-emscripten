#include <stdlib.h>
#include <stdio.h>

#include <emscripten.h>
#include <Python.h>


#if PY_MAJOR_VERSION < 3
PyMODINIT_FUNC initsdl2(void);
#else
PyMODINIT_FUNC PyInit_sdl2(void);
#endif


static void onload(const char *filename) {
    printf("Loaded %s.\n", filename);
    PyRun_SimpleString(
        "import zipfile;"
        "zipfile.ZipFile('/app.zip').extractall('/');"
    );
    PyRun_SimpleString(
        "import sys;"
        "sys.path.insert(0, '/');"
    );
    PyRun_SimpleString(
        "import runpy;"
        "runpy.run_module('app');"
    );
}


static void onloaderror(const char *filename) {
    printf("Failed to load %s, aborting.\n", filename);
    PyRun_SimpleString("print('fail')");
}


int main(int argc, char** argv) {
    setenv("PYTHONHOME", "/", 0);
    setenv("_PYTHON_SYSCONFIGDATA_NAME", "_sysconfigdata", 0);

    Py_InitializeEx(0);
#if PY_MAJOR_VERSION < 3
    initsdl2();
#else
    PyInit_sdl2();
#endif

    // Fetch app.zip from the server.
    emscripten_async_wget("app.zip", "/app.zip", onload, onloaderror);

    emscripten_exit_with_live_runtime();
    return 0;
}
