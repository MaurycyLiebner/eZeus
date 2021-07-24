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

bool eMainWindow::initialize(const eRes& res) {
    const int w = eResolution::width(res);
    const int h = eResolution::width(res);
    const auto window = SDL_CreateWindow("eZeus",
                                         SDL_WINDOWPOS_UNDEFINED,
                                         SDL_WINDOWPOS_UNDEFINED,
                                         w, h, SDL_WINDOW_SHOWN);

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
    setResolution(res);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
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

void eMainWindow::setResolution(const eRes res) {
    mResolution = res;
    const int w = eResolution::width(res);
    const int h = eResolution::height(res);
    SDL_SetWindowSize(mSdlWindow, w, h);
}

void eMainWindow::setFullscreen(const bool f) {
    if(mFullscreen == f) return;
    mFullscreen = f;
    SDL_SetWindowFullscreen(mSdlWindow, f ? SDL_WINDOW_FULLSCREEN : 0);
}

void eMainWindow::showMainMenu() {
    const auto mm = new eMainMenu(this);
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
    eSettings settings{mFullscreen, mResolution};
    const auto esm = new eSettingsMenu(settings, this);
    esm->resize(width(), height());
    const auto backA = [this]() {
        showMainMenu();
    };
    const auto applyA = [this](const eSettings& settings) {
        setResolution(settings.fRes);
        setFullscreen(settings.fFullscreen);
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
