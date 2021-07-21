#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

#include "ewindow.h"
#include "ewindowrenderer.h"
#include "etexturehelper.h"

bool init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n",
               SDL_GetError());
        return false;
    }

    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Warning: Linear texture filtering not enabled!");
    }

    const auto window = eWindow::initialize(800, 600);
    if(!window) {
        printf("Window could not be created! SDL Error: %s\n",
               SDL_GetError());
        return false;
    }

    const auto renderer = eWindowRenderer::initialize(window);
    if(!renderer) {
        printf("Renderer could not be created! SDL Error: %s\n",
               SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    const int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n",
               IMG_GetError());
        return false;
    }

    return true;
}

void close() {
    eWindowRenderer::destroy();
    eWindow::destroy();

    IMG_Quit();
    SDL_Quit();
}

int main() {
    if(!init()) {
        printf("Failed to initialize!\n");
        close();
        return 1;
    }

    const auto renderer = eWindowRenderer::instance();

    bool quit = false;

    SDL_Event e;

    while(!quit) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);



        SDL_RenderPresent(renderer);
    }

    close();

    return 0;
}
