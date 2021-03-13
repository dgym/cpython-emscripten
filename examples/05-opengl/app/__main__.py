try:
    import pyximport
    pyximport.install()
except ImportError:
    pass

import math
import time

from . import sdl2


sdl2.SDL_Init(sdl2.SDL_INIT_VIDEO)
window = sdl2.SDL_CreateWindow(
    bytes('test', 'utf8'), 0, 0, 800, 600,
    sdl2.SDL_WINDOW_OPENGL | sdl2.SDL_WINDOW_SHOWN,
)

sdl2.SDL_GL_SetAttribute(sdl2.SDL_GL_CONTEXT_MAJOR_VERSION, 2)
sdl2.SDL_GL_SetAttribute(sdl2.SDL_GL_CONTEXT_MINOR_VERSION, 0)
sdl2.SDL_GL_SetSwapInterval(0)
sdl2.SDL_GL_SetAttribute(sdl2.SDL_GL_DOUBLEBUFFER, 1)
sdl2.SDL_GL_SetAttribute(sdl2.SDL_GL_DEPTH_SIZE, 24)

sdl2.SDL_GL_CreateContext(window)


counter = 0.0


def loop():
    start = time.time()

    global counter
    sdl2.glClearColor(math.sin(counter), 0.5, 0.6, 1.0)
    sdl2.glClear(sdl2.GL_COLOR_BUFFER_BIT)
    sdl2.SDL_GL_SwapWindow(window)
    counter += 0.01
    if counter > math.pi:
        counter = 0

    elapsed = time.time() - start
    remaining = 0.030 - elapsed
    if remaining > 0:
        time.sleep(remaining)


sdl2.main_loop(loop)
