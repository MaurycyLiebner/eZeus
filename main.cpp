#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

#include "emainwindow.h"

bool init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n",
               SDL_GetError());
        return false;
    }

    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Warning: Linear texture filtering not enabled!");
    }

    const int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n",
               IMG_GetError());
        return false;
    }

    if(TTF_Init()) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n",
               TTF_GetError());
        return false;
    }

    return true;
}

void close() {
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main() {
    if(!init()) {
        printf("Failed to initialize!\n");
        close();
        return 1;
    }

    eMainWindow w;
    const bool i = w.initialize(eRes::p720);
    if(!i) return 1;

    const int r = w.exec();

    close();

    return r;
}
