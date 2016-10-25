#include <stdlib.h>

#include <emscripten.h>
#include <Python.h>


int main(int argc, char** argv) {
    setenv("PYTHONHOME", "/", 0);

    Py_InitializeEx(0);
    PyRun_SimpleString("print('Python prints to the browser console.')");
    Py_Finalize();

    emscripten_exit_with_live_runtime();
    return 0;
}
