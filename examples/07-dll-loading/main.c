#include <stdlib.h>
#include <stdio.h>
#include <emscripten.h>
#include <Python.h>
#include <dlfcn.h>

int runpython(char *str) {
    printf("%s", str);
    return PyRun_SimpleString(str);
    }

int main(int argc, char** argv) {

    setenv("PYTHONHOME", "/", 0);

    EM_ASM({
      Runtime.loadDynamicLibrary('libpython3.5.js');
    }); 

    printf("Initializing...");

    Py_InitializeEx(0);

    printf("Home directory: %s", Py_GetPythonHome());

    emscripten_exit_with_live_runtime();
    return 0;
}
