#ifndef EWINDOW_H
#define EWINDOW_H

#include <SDL2/SDL.h>

class eWindow {
public:
    static SDL_Window* initialize(const int width, const int height);
    static void destroy();

    static SDL_Window* instance() { return sInstance; }
private:
    static SDL_Window* sInstance;
};

#endif // EWINDOW_H
