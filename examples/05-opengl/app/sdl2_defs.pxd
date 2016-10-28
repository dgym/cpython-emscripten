from libc.stdint cimport uint32_t


cdef extern from "SDL2/SDL.h" nogil:
    uint32_t SDL_INIT_VIDEO

    uint32_t SDL_WINDOW_OPENGL
    uint32_t SDL_WINDOW_SHOWN

    ctypedef enum SDL_GLattr:
        SDL_GL_DOUBLEBUFFER
        SDL_GL_DEPTH_SIZE
        SDL_GL_CONTEXT_MAJOR_VERSION
        SDL_GL_CONTEXT_MINOR_VERSION

    ctypedef struct SDL_Window:
        pass

    ctypedef void* SDL_GLContext

    int SDL_Init(uint32_t flags)
    SDL_Window* SDL_CreateWindow(const char* title, int x, int y, int w, int h, uint32_t flags)

    int SDL_GL_SetAttribute(SDL_GLattr attr, int value)
    int SDL_GL_SetSwapInterval(int interval)
    SDL_GLContext SDL_GL_CreateContext(SDL_Window* window)
    void SDL_GL_SwapWindow(SDL_Window* window)


cdef extern from "SDL2/SDL_opengles2.h":
    uint32_t GL_COLOR_BUFFER_BIT

    void glClearColor(float r, float g, float b, float alpha)
    void glClear(uint32_t)


cdef extern from "loop.h":
    ctypedef void (*thunk)()
    void main_loop(thunk callback)
