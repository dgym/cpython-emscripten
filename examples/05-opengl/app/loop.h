#include <stdbool.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif


static void main_loop(void (*loop_thunk)(void)) {
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop_thunk, 0, true);
#else
    for (;;) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                return;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    return;
                }
                break;
            default:
                break;
            }
        }

        loop_thunk();
    }
#endif
}
