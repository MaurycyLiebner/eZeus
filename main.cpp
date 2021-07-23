#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

#include "ewindow.h"
#include "ewindowrenderer.h"
#include "widgets/emainmenu.h"

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

    if(TTF_Init()) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n",
               TTF_GetError());
        return false;
    }

    return true;
}

void close() {
    eWindowRenderer::destroy();
    eWindow::destroy();

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

    const auto window = eWindow::instance();
    const auto renderer = eWindowRenderer::instance();

    int w;
    int h;
    SDL_GetWindowSize(window, &w, &h);
    eMainMenu mm(renderer);
    mm.resize(w, h);
    mm.initialize();

    eMouseButton button{eMouseButton::none};
    eMouseButton buttons{eMouseButton::none};

    bool quit = false;
    SDL_Event e;

    while(!quit) {
        while(SDL_PollEvent(&e)) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(e.type == SDL_QUIT) {
                quit = true;
            } else if(e.type == SDL_MOUSEMOTION) {
                const eMouseEvent me(x, y, buttons, button);
                mm.mouseMove(me);
            } else if(e.type == SDL_MOUSEBUTTONDOWN) {
                const eMouseEvent me(x, y, buttons, button);
                mm.mousePress(me);
            } else if(e.type == SDL_MOUSEBUTTONUP) {
                const eMouseEvent me(x, y, buttons, button);
                mm.mouseRelease(me);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        ePainter p(renderer);
        mm.paint(p);

        SDL_RenderPresent(renderer);
    }

    close();

    return 0;
}
