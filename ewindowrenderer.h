#ifndef EWINDOWRENDERER_H
#define EWINDOWRENDERER_H

#include <SDL2/SDL.h>

class eWindowRenderer {
public:
    static SDL_Renderer* instance() { return sInstance; }
    static void destroy();

    static SDL_Renderer* initialize(SDL_Window* const w);
private:
    static SDL_Renderer* sInstance;
};

#endif // EWINDOWRENDERER_H
