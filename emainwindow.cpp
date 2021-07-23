#include "emainwindow.h"

#include "widgets/emainmenu.h"

eMainWindow::eMainWindow() {

}

eMainWindow::~eMainWindow() {
    if(mSdlWindow) {
        SDL_DestroyWindow(mSdlWindow);
    }
    setWidget(nullptr);
}

bool eMainWindow::initialize(const int width, const int height) {
    const auto window = SDL_CreateWindow("eZeus",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  width, height,
                                  SDL_WINDOW_SHOWN);

    if(!window) {
        printf("Window could not be created! SDL Error: %s\n",
               SDL_GetError());
        return false;
    }
    const Uint32 flags = SDL_RENDERER_ACCELERATED |
                         SDL_RENDERER_PRESENTVSYNC;
    const auto renderer = SDL_CreateRenderer(window, -1, flags);
    if(!renderer) {
        printf("Renderer could not be created! SDL Error: %s\n",
               SDL_GetError());
        SDL_DestroyWindow(window);
        return false;
    }
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    mSdlWindow = window;
    mSdlRenderer = renderer;
    mWidth = width;
    mHeight = height;
    return true;
}

void eMainWindow::setWidget(eWidget* const w) {
    if(mWidget) delete mWidget;
    mWidget = w;
}

int eMainWindow::exec() {
    const auto mm = new eMainMenu(mSdlRenderer);
    mm->resize(mWidth, mHeight);
    setWidget(mm);

    const auto newGameAction = []() {

    };

    const auto loadGameAction = []() {

    };

    const auto settingsAction = [this]() {
    };

    bool quit = false;
    const auto quitAction = [&quit]() {
        quit = true;
    };

    mm->initialize(newGameAction,
                   loadGameAction,
                   settingsAction,
                   quitAction);

    eMouseButton button{eMouseButton::none};
    eMouseButton buttons{eMouseButton::none};

    SDL_Event e;

    while(!quit) {
        while(SDL_PollEvent(&e)) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(e.type == SDL_QUIT) {
                quit = true;
            } else if(e.type == SDL_MOUSEMOTION) {
                const eMouseEvent me(x, y, buttons, button);
                if(mWidget) mWidget->mouseMove(me);
            } else if(e.type == SDL_MOUSEBUTTONDOWN) {
                const eMouseEvent me(x, y, buttons, button);
                if(mWidget) mWidget->mousePress(me);
            } else if(e.type == SDL_MOUSEBUTTONUP) {
                const eMouseEvent me(x, y, buttons, button);
                if(mWidget) mWidget->mouseRelease(me);
            }
        }

        SDL_SetRenderDrawColor(mSdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mSdlRenderer);

        ePainter p(mSdlRenderer);
        if(mWidget) mWidget->paint(p);

        SDL_RenderPresent(mSdlRenderer);
    }

    return 0;
}
