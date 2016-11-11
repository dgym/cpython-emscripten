cdef extern from "emscripten.h":
    void emscripten_run_script(const char *)


def run(code):
    emscripten_run_script(code)
