#include "ewindow.h"

SDL_Window* eWindow::sInstance = nullptr;

SDL_Window* eWindow::initialize(const int width, const int height) {
    sInstance = SDL_CreateWindow("SDL Tutorial",
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED,
                                 width, height,
                                 SDL_WINDOW_SHOWN);
    return sInstance;
}

void eWindow::destroy() {
    if(!sInstance) return;
    SDL_DestroyWindow(sInstance);
    sInstance = nullptr;
}
