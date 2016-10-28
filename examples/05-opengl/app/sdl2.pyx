cimport sdl2_defs as defs


SDL_INIT_VIDEO = defs.SDL_INIT_VIDEO

SDL_WINDOW_OPENGL = defs.SDL_WINDOW_OPENGL
SDL_WINDOW_SHOWN = defs.SDL_WINDOW_SHOWN

SDL_GL_DOUBLEBUFFER = defs.SDL_GL_DOUBLEBUFFER
SDL_GL_DEPTH_SIZE = defs.SDL_GL_DEPTH_SIZE
SDL_GL_CONTEXT_MAJOR_VERSION = defs.SDL_GL_CONTEXT_MAJOR_VERSION
SDL_GL_CONTEXT_MINOR_VERSION = defs.SDL_GL_CONTEXT_MINOR_VERSION


cdef class SDL_Window(object):
    cdef defs.SDL_Window *inst


cdef class SDL_GLContext(object):
    cdef defs.SDL_GLContext inst


def SDL_Init(flags):
    return defs.SDL_Init(flags)


cpdef SDL_CreateWindow(title, x, y, w, h, flags):
    cdef SDL_Window result = SDL_Window()
    result.inst = defs.SDL_CreateWindow(title, x, y, w, h, flags)
    return result


def SDL_GL_SetAttribute(attr, value):
    return defs.SDL_GL_SetAttribute(attr, value)


def SDL_GL_SetSwapInterval(interval):
    return defs.SDL_GL_SetSwapInterval(interval)


def SDL_GL_CreateContext(window):
    cdef SDL_GLContext result = SDL_GLContext()
    result.inst = defs.SDL_GL_CreateContext((<SDL_Window?>window).inst)
    return result


def SDL_GL_SwapWindow(window):
    defs.SDL_GL_SwapWindow((<SDL_Window?>window).inst)


GL_COLOR_BUFFER_BIT = defs.GL_COLOR_BUFFER_BIT


def glClearColor(r, g, b, a):
    defs.glClearColor(r, g, b, a)


def glClear(bits):
    defs.glClear(bits)


loop_callback = None


cdef void loop_thunk():
    loop_callback()


def main_loop(callback):
    global loop_callback
    loop_callback = callback
    defs.main_loop(loop_thunk)
