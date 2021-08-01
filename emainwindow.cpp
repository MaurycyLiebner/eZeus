#include "emainwindow.h"

#include "widgets/emainmenu.h"
#include "widgets/esettingsmenu.h"
#include "widgets/egamewidget.h"
#include "widgets/egameloadingwidget.h"

#include "engine/ethreadpool.h"

#include <chrono>

eMainWindow::eMainWindow() {}

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

    const auto newGameAction = [this]() {
        const auto l = new eGameLoadingWidget(this);
        l->resize(width(), height());
        const auto show = [this]() {
            showGame();
        };
        l->setDoneAction(show);
        setWidget(l);
        l->initialize();
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

void eMainWindow::showGame() {
    const auto egw = new eGameWidget(this);
    egw->resize(width(), height());
    egw->initialize(16, 16);
    setWidget(egw);
}

int eMainWindow::exec() {
    using namespace std::chrono;
    using namespace std::chrono_literals;

    showMainMenu();

    eMouseButton button{eMouseButton::none};
    eMouseButton buttons{eMouseButton::none};

    SDL_Event e;

    auto end = high_resolution_clock::now();
    auto start = high_resolution_clock::now();

    int c = 0;

    while(!mQuit) {
        const auto nstart = high_resolution_clock::now();

        while(SDL_PollEvent(&e)) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(e.type == SDL_QUIT) {
                mQuit = true;
            } else if(e.type == SDL_MOUSEMOTION) {
                const eMouseEvent me(x, y, buttons, button);
                if(mWidget) mWidget->mouseMove(me);
            } else if(e.type == SDL_MOUSEBUTTONDOWN) {
                switch(e.button.button) {
                case SDL_BUTTON_LEFT:
                    button = eMouseButton::left;
                    break;
                case SDL_BUTTON_RIGHT:
                    button = eMouseButton::right;
                    break;
                case SDL_BUTTON_MIDDLE:
                    button = eMouseButton::middle;
                    break;
                default: continue;
                }
                buttons = button | buttons;

                const eMouseEvent me(x, y, buttons, button);
                if(mWidget) mWidget->mousePress(me);
            } else if(e.type == SDL_MOUSEBUTTONUP) {
                switch(e.button.button) {
                case SDL_BUTTON_LEFT:
                    button = eMouseButton::left;
                    break;
                case SDL_BUTTON_RIGHT:
                    button = eMouseButton::right;
                    break;
                case SDL_BUTTON_MIDDLE:
                    button = eMouseButton::middle;
                    break;
                default: continue;
                }
                buttons = buttons & ~button;
                const eMouseEvent me(x, y, buttons, button);
                if(mWidget) mWidget->mouseRelease(me);
            } else if(e.type == SDL_MOUSEWHEEL) {
                const eMouseWheelEvent me(x, y, buttons, e.wheel.y);
                if(mWidget) mWidget->mouseWheel(me);
            }
        }

        SDL_SetRenderDrawColor(mSdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mSdlRenderer);

        ePainter p(mSdlRenderer);

        p.setFont(eFonts::defaultFont(resolution()));
        const duration<double> elapsed = end - start;
        const int fps = (int)std::round(1/elapsed.count());
        p.drawText(0, 0, std::to_string(fps), {0, 0, 0, 255});

        if(mWidget) mWidget->paint(p);

        SDL_RenderPresent(mSdlRenderer);

        for(const auto& s : mSlots) {
            s();
        }
        mSlots.clear();

        eThreadPool::handleFinished();

        c++;
        if(c % 25 == 0) {
            start = nstart;
            end = high_resolution_clock::now();
        }
    }

    return 0;
}
