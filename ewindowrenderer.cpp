#include "ewindowrenderer.h"

SDL_Renderer* eWindowRenderer::sInstance = nullptr;

SDL_Renderer* eWindowRenderer::initialize(SDL_Window* const w) {
    const Uint32 flags = SDL_RENDERER_ACCELERATED |
                         SDL_RENDERER_PRESENTVSYNC;
    sInstance = SDL_CreateRenderer(w, -1, flags);
    return sInstance;
}

void eWindowRenderer::destroy() {
    if(!sInstance) return;
    SDL_DestroyRenderer(sInstance);
    sInstance = nullptr;
}
