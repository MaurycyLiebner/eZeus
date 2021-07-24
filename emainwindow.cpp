#include "emainwindow.h"

#include "widgets/emainmenu.h"
#include "widgets/esettingsmenu.h"

eMainWindow* eMainWindow::sInstance = nullptr;

eMainWindow* eMainWindow::instance() {
    return sInstance;
}

eMainWindow::eMainWindow() {
    sInstance = this;
}

eMainWindow::~eMainWindow() {
    if(mSdlWindow) SDL_DestroyWindow(mSdlWindow);
    if(mSdlRenderer) SDL_DestroyRenderer(mSdlRenderer);
    setWidget(nullptr);
}

bool eMainWindow::initialize(const eResolution& res) {
    const auto window = SDL_CreateWindow("eZeus",
                                         SDL_WINDOWPOS_UNDEFINED,
                                         SDL_WINDOWPOS_UNDEFINED,
                                         res.width(), res.height(),
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

    if(mSdlWindow) SDL_DestroyWindow(mSdlWindow);
    if(mSdlRenderer) SDL_DestroyRenderer(mSdlRenderer);
    mSdlWindow = window;
    mSdlRenderer = renderer;
    mResolution = res;
    return true;
}

void eMainWindow::setWidget(eWidget* const w) {
    if(mWidget) mWidget->deleteLater();
    mWidget = w;
}

void eMainWindow::addSlot(const eSlot& slot) {
    sInstance->addSlotImpl(slot);
}

void eMainWindow::addSlotImpl(const eSlot& slot) {
    mSlots.push_back(slot);
}

void eMainWindow::showMainMenu() {
    const auto mm = new eMainMenu(mSdlRenderer);
    mm->resize(width(), height());
    setWidget(mm);

    const auto newGameAction = []() {

    };

    const auto loadGameAction = []() {

    };

    const auto settingsAction = [this]() {
        showSettingsMenu();
    };

    const auto quitAction = [this]() {
        mQuit = true;
    };

    mm->initialize(newGameAction,
                   loadGameAction,
                   settingsAction,
                   quitAction);
}

void eMainWindow::showSettingsMenu() {
    eSettings settings{mResolution};
    const auto esm = new eSettingsMenu(settings, mSdlRenderer);
    esm->resize(width(), height());
    const auto backA = [this]() {
        showMainMenu();
    };
    const auto applyA = [this](const eSettings& settings) {
        mResolution = settings.fRes;
        const int w = settings.width();
        const int h = settings.height();
        SDL_SetWindowSize(mSdlWindow, w, h);
        showSettingsMenu();
    };
    esm->initialize(backA, applyA);
    setWidget(esm);
}

int eMainWindow::exec() {
    showMainMenu();

    eMouseButton button{eMouseButton::none};
    eMouseButton buttons{eMouseButton::none};

    SDL_Event e;

    while(!mQuit) {
        while(SDL_PollEvent(&e)) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(e.type == SDL_QUIT) {
                mQuit = true;
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

        for(const auto& s : mSlots) {
            s();
        }
        mSlots.clear();
    }

    return 0;
}
