#include <stdlib.h>

#include <emscripten.h>
#include <Python.h>


EMSCRIPTEN_KEEPALIVE
int main(int argc, char** argv) {
    setenv("PYTHONHOME", "/", 0);
    setenv("_PYTHON_SYSCONFIGDATA_NAME", "_sysconfigdata", 0);

    Py_InitializeEx(0);
    PyRun_SimpleString("print('Success - Python has printed to the browser console.')");

    return 0;
}
