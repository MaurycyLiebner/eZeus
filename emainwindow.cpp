#include "emainwindow.h"

#include "widgets/emainmenu.h"
#include "widgets/esettingsmenu.h"
#include "widgets/egamewidget.h"
#include "widgets/egameloadingwidget.h"
#include "widgets/egamemenu.h"
#include "widgets/emenuloadingwidget.h"
#include "widgets/eworldwidget.h"

#include "audio/emusic.h"

#include "engine/ethreadpool.h"

#include "engine/emapgenerator.h"

#include "egamedir.h"

#include "fileIO/ereadstream.h"

#include <chrono>
#include <filesystem>

#include "widgets/efilewidget.h"
#include "elanguage.h"

#include "evectorhelpers.h"

#include "widgets/eeventbackground.h"

eMainWindow::eMainWindow() {}

eMainWindow::~eMainWindow() {
    if(mSdlWindow) SDL_DestroyWindow(mSdlWindow);
    if(mSdlRenderer) SDL_DestroyRenderer(mSdlRenderer);
    setWidget(nullptr);
}

bool eMainWindow::initialize(const eResolution& res) {
    const int w = res.width();
    const int h = res.height();
    const auto window = SDL_CreateWindow("eZeus",
                                         SDL_WINDOWPOS_UNDEFINED,
                                         SDL_WINDOWPOS_UNDEFINED,
                                         w, h, SDL_WINDOW_SHOWN);

    if(!window) {
        printf("Window could not be created! SDL Error: %s\n",
               SDL_GetError());
        return false;
    }
    const Uint32 flags = SDL_RENDERER_ACCELERATED/* |
                         SDL_RENDERER_PRESENTVSYNC*/;
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

    const std::string icoPath = eGameDir::path("zeus.ico");
    const auto icon = IMG_Load(icoPath.c_str());
    SDL_SetWindowIcon(window, icon);
    eGameTextures::setSettings(mSettings);
    return true;
}

void eMainWindow::setWidget(eWidget* const w) {
    if(mWidget) {
        if(mWidget != mGW && mWidget != mWW) {
            mWidget->deleteLater();
        }
    }
    mWidget = w;
}

eWidget* eMainWindow::takeWidget() {
    const auto w = mWidget;
    mWidget = nullptr;
    return w;
}

void eMainWindow::addSlot(const eSlot& slot) {
    mSlots.push_back(slot);
}

void eMainWindow::setResolution(const eResolution& res) {
    mSettings.fRes = res;
    const int w = res.width();
    const int h = res.height();
    SDL_SetWindowSize(mSdlWindow, w, h);
}

void eMainWindow::setFullscreen(const bool f) {
    if(mSettings.fFullscreen == f) return;
    mSettings.fFullscreen = f;
    SDL_SetWindowFullscreen(mSdlWindow, f ? SDL_WINDOW_FULLSCREEN : 0);
}

void eMainWindow::startGameAction(eGameBoard* const board,
                                  const eGameWidgetSettings& settings) {
    const auto l = new eGameLoadingWidget(this);
    l->resize(width(), height());
    const auto show = [this, board, settings]() {
        showGame(board, settings);
    };
    l->setDoneAction(show);
    setWidget(l);
    l->initialize();
}

bool eMainWindow::saveGame(const std::string& path) {
    const auto fsp = std::filesystem::path(path);
    const auto fspd = fsp.parent_path();
    std::filesystem::create_directories(fspd);
    const auto file = SDL_RWFromFile(path.c_str(), "w+b");
    if(!file) return false;
    eWriteStream dst(file);
    const auto s = mGW->settings();
    s.write(dst);
    mBoard->write(dst);
    SDL_RWclose(file);
    return true;
}

bool eMainWindow::loadGame(const std::string& path) {
    const auto file = SDL_RWFromFile(path.c_str(), "r+b");
    if(!file) return false;
    eReadStream src(file);
    eGameWidgetSettings s;
    s.read(src);
    const auto board = new eGameBoard();
    board->read(src);
    SDL_RWclose(file);

    startGameAction(board, s);
    return true;
}

void eMainWindow::closeGame() {
    if(!mGW) return;
    if(mGW) {
        mGW->deleteLater();
        mGW = nullptr;
    }
    if(mWW) {
        mWW->deleteLater();
        mWW = nullptr;
    }
    showMainMenu();
}

void eMainWindow::showMenuLoading() {
    const auto mlw = new eMenuLoadingWidget(this);
    mlw->setDoneAction([this]() {
        eMusic::playMenuMusic();
        showMainMenu();
    });
    mlw->initialize();
    mlw->resize(width(), height());
    setWidget(mlw);
}

void eMainWindow::showMainMenu() {
    const auto mm = new eMainMenu(this);
    mm->resize(width(), height());
    setWidget(mm);

    const auto newGameAction = [this]() {
        const auto board = new eGameBoard();
        board->initialize(100, 200);

        std::vector<eResourceType> missingPos{eResourceType::oliveOil,
                                              eResourceType::wine,
                                              eResourceType::bronze,
                                              eResourceType::marble,
                                              eResourceType::food};
        std::random_shuffle(missingPos.begin(), missingPos.end());

        std::vector<eGodType> friendlyGods;
        std::vector<eResourceType> missing;
        for(int i = 0; i < 2; i++) {
            const auto ms = missingPos[i];
            switch(ms) {
            case eResourceType::oliveOil:
                friendlyGods.push_back(eGodType::athena);
                break;
            case eResourceType::wine:
                friendlyGods.push_back(eGodType::dionysus);
                break;
            case eResourceType::bronze:
                friendlyGods.push_back(eGodType::hephaestus);
                break;
            case eResourceType::marble:
                friendlyGods.push_back(eGodType::atlas);
                break;
            case eResourceType::food:
                friendlyGods.push_back(eGodType::demeter);
                break;
            default:
                break;
            }

            missing.push_back(ms);
        }


        eMapGenerator g(*board);
        eMapGeneratorSettings sett;

        g.generate(sett);

        const int iMax = static_cast<int>(eGodType::zeus) + 1;
        std::vector<eGodType> gods;
        for(int i = 0; i < iMax; i++) {
            const auto t = static_cast<eGodType>(i);
            const bool r =  eVectorHelpers::contains(friendlyGods, t);
            if(r) continue;
            gods.push_back(t);
        }

        std::random_shuffle(gods.begin(), gods.end());

        for(int i = 0; i < 2; i++) {
            const auto g = gods[i];
            eVectorHelpers::remove(gods, g);
            friendlyGods.push_back(g);
        }
        friendlyGods.push_back(eGodType::apollo);
        friendlyGods.push_back(eGodType::hephaestus);

        std::vector<eGodType> hostileGods;
        std::vector<eMonsterType> monsters;
        for(int i = 0; i < 2; i++) {
            const auto g = gods[i];
            eVectorHelpers::remove(gods, g);
            hostileGods.push_back(g);
            monsters.push_back(eMonster::sGodsMinion(g));
        }

        board->setFriendlyGods(friendlyGods);
        board->setHostileGods(hostileGods);
        board->setHostileMonsters(monsters);

        auto& wb = board->getWorldBoard();

        const auto hc = eWorldCity::sCreateSparta(eWorldCityType::mainCity);
        hc->setIsCurrentCity(true);
        wb.setHomeCity(hc);

        const auto c1 = eWorldCity::sCreateAthens();
        c1->setArmy(3);
        c1->setWealth(4);
        c1->setRelationship(eWorldCityRelationship::ally);
        c1->addBuys(eResourceTrade{eResourceType::marble, 0, 12, 120});
        c1->addBuys(eResourceTrade{eResourceType::wood, 0, 12, 80});
        c1->addSells(eResourceTrade{eResourceType::fleece, 0, 12, 60});
        wb.addCity(c1);

        const auto c2 = eWorldCity::sCreateTroy();
        c2->setArmy(5);
        c2->setWealth(3);
        c2->setRelationship(eWorldCityRelationship::rival);
        c2->setWaterTrade(true);
        c2->addBuys(eResourceTrade{eResourceType::armor, 0, 12, 120});
        c2->addBuys(eResourceTrade{eResourceType::wheat, 0, 12, 80});
        c2->addSells(eResourceTrade{eResourceType::sculpture, 0, 12, 200});
        c2->addSells(eResourceTrade{eResourceType::bronze, 0, 12, 80});
        wb.addCity(c2);

        const auto c3 = eWorldCity::sCreateMtPelion();
        c3->setRelationship(eWorldCityRelationship::ally);
        c3->setWaterTrade(true);
        c3->addBuys(eResourceTrade{eResourceType::armor, 0, 12, 120});
        c3->addBuys(eResourceTrade{eResourceType::wheat, 0, 12, 80});
        c3->addSells(eResourceTrade{eResourceType::sculpture, 0, 12, 200});
        c3->addSells(eResourceTrade{eResourceType::bronze, 0, 12, 80});
        wb.addCity(c3);

        startGameAction(board, eGameWidgetSettings());
    };

    const auto loadGameAction = [this, mm]() {
        const auto fw = new eFileWidget(this);
        const auto func = [this](const std::string& path) {
            return loadGame(path);
        };
        const auto closeAct = [mm, fw]() {
            mm->removeWidget(fw);
            fw->deleteLater();
        };
        fw->intialize(eLanguage::zeusText(1, 3),
                      "../saves/", func, closeAct);
        mm->addWidget(fw);
        fw->align(eAlignment::center);
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
    const auto esm = new eSettingsMenu(mSettings, this);
    esm->resize(width(), height());

    const auto applyA = [this](const eSettings& settings) {
        const bool loadNeeded = settings.fRes != mSettings.fRes;
        setResolution(settings.fRes);
        setFullscreen(settings.fFullscreen);
        mSettings = settings;
        if(!mSettings.fTinyTextures &&
           !mSettings.fSmallTextures &&
           !mSettings.fMediumTextures &&
           !mSettings.fLargeTextures) {
            mSettings.fSmallTextures = true;
        }
        eGameTextures::setSettings(mSettings);
        if(loadNeeded) showMenuLoading();
        else showMainMenu();
    };
    const auto fullscrennA = [this](const bool f) {
        setFullscreen(f);
    };
    esm->initialize(applyA, fullscrennA);
    setWidget(esm);
}
#include "characters/ehoplite.h"
#include "characters/erockthrower.h"
#include "characters/egreekhoplite.h"
#include "characters/esoldierbanner.h"
#include "characters/actions/esoldieraction.h"
void eMainWindow::showGame(eGameBoard* board,
                           const eGameWidgetSettings& settings) {
    if(!board) board = mBoard;

    if(mBoard == board && mGW) {
        return setWidget(mGW);
    }

    if(mGW) {
        mGW->deleteLater();
        mGW = nullptr;
    }

    mBoard = board;

//    const auto spawnHoplite = [&](const int x, const int y,
//                                  const int pid) {
//        stdsptr<eSoldier> h;
////            if(pid == 1) {
//            h = e::make_shared<eRockThrower>(*mBoard);
////            } else {
////                h = e::make_shared<eGreekHoplite>(*mBoard);
////            }
//        h->setPlayerId(pid);
//        const auto a = e::make_shared<eSoldierAction>(h.get());
//        h->setAction(a);
//        h->changeTile(mBoard->tile(x, y));
//        h->setActionType(eCharacterActionType::stand);
//        return h;
//    };

//    stdsptr<eSoldierBanner> b;
//    int bi = 8;
//    for(int i = 20; i < 30; i += 1) {
//        for(int j = -10; j < 0; j += 1) {
//            const auto s = spawnHoplite(i, j, 1);
//            if(bi >= 8) {
//                b = e::make_shared<eSoldierBanner>(eBannerType::rockThrower, *mBoard);
//                b->setPlayerId(1);
//                const auto n = new stdsptr<eSoldierBanner>(b);
//                b->moveTo(i, j);
//                bi = 0;
//            }
//            s->setBanner(b.get());
//            b->incCount();
//            bi++;
//        }
//    }

//    bi = 8;
//    for(int i = 40; i < 50; i += 1) {
//        for(int j = -20; j < -10; j += 1) {
//            const auto s = spawnHoplite(i, j, 2);
//            if(bi >= 8) {
//                b = e::make_shared<eSoldierBanner>(eBannerType::hoplite, *mBoard);
//                b->setPlayerId(2);
//                const auto n = new stdsptr<eSoldierBanner>(b);
//                b->moveTo(i, j);
//                bi = 0;
//            }
//            s->setBanner(b.get());
//            b->incCount();
//            bi++;
//        }
//    }

    eMusic::playRandomMusic();
    mGW = new eGameWidget(this);
    mGW->setBoard(mBoard);
    mGW->resize(width(), height());
    mGW->initialize();
    mGW->setSettings(settings);

//    board->planInvasion(board->date() + 37*31, 10, 10, 10);

    setWidget(mGW);
}

void eMainWindow::showWorld() {
    if(mWidget == mWW) return;
    if(!mWW) {
        mWW = new eWorldWidget(this);
        mWW->resize(width(), height());
        mWW->initialize();
        mWW->setBoard(mBoard);
    } else {
        mWW->update();
    }
    setWidget(mWW);
}

void eMainWindow::execDialog(
        eWidget* const d, const bool closable,
        const eAction &closeFunc,
        eWidget* const parent) {
    if(!mWidget) return;
    const auto bg = new eEventBackground(this);
    if(closeFunc) {
        bg->initialize(parent ? parent : mWidget, d, closable, closeFunc);
    } else {
        const auto closeFunc = [d]() {
            d->deleteLater();
        };
        bg->initialize(parent ? parent : mWidget, d, closable, closeFunc);
    }
}

class eTooltip {
public:
    eTooltip(eMainWindow& w) : mWindow(w) {}

    void update() {
        const auto txt = eWidget::sTooltip();
        const bool updateTxt = mText != txt;
        if(updateTxt) {
            mText = txt;
        }

        const auto& res = mWindow.resolution();
        const int fontSize = res.verySmallFontSize();
        const bool updateFont = mFontSize != fontSize;
        if(updateFont) {
            mFontSize = fontSize;
            mFont = eFonts::defaultFont(mFontSize);
        }

        const bool updateTexture = updateTxt || updateFont;
        if(updateTexture) {
            const auto r = mWindow.renderer();
            if(mText.empty()) {
                mTexture->reset();
            } else {
                mTexture->loadText(r, mText, eFontColor::light, *mFont, 50*fontSize);
            }
        }
    }

    void paint(const int x, const int y, ePainter& p) {
        const int pp = padding();
        SDL_Rect rect{x, y, width(), height()};
        p.fillRect(rect, SDL_Color{16, 108, 144, 255});
        p.drawRect(rect, SDL_Color{0, 32, 32, 255}, 1);
        p.drawTexture(x + pp, y + pp, mTexture);
    }

    int width() const { return mTexture->width() + 2*padding(); }
    int height() const { return mTexture->height() + 2*padding(); }

    bool empty() const { return mText.empty(); }
private:
    int padding() const { return mFontSize/2; }

    eMainWindow& mWindow;
    int mFontSize = -1;
    TTF_Font* mFont = nullptr;
    std::string mText;
    stdsptr<eTexture> mTexture = std::make_shared<eTexture>();
};

int eMainWindow::exec() {
    using namespace std::chrono;
    using namespace std::chrono_literals;

    showMenuLoading();

    eMouseButton button{eMouseButton::none};
    eMouseButton buttons{eMouseButton::none};

    SDL_Event e;
    eTooltip tooltip(*this);

    int c = 0;
    int fpsVal = 0;
    while(!mQuit) {
        const auto fpsStart = high_resolution_clock::now();

        while(SDL_PollEvent(&e)) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            const bool shift = mShiftPressed > 0;
            if(e.type == SDL_QUIT) {
                mQuit = true;
            } else if(e.type == SDL_MOUSEMOTION) {
                const eMouseEvent me(x, y, shift, buttons, button);
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

                const eMouseEvent me(x, y, shift, buttons, button);
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
                const eMouseEvent me(x, y, shift, buttons, button);
                if(mWidget) mWidget->mouseRelease(me);
            } else if(e.type == SDL_MOUSEWHEEL) {
                const eMouseWheelEvent me(x, y, shift, buttons, e.wheel.y);
                if(mWidget) mWidget->mouseWheel(me);
            } else if(e.type == SDL_KEYDOWN) {
                const auto k = e.key.keysym.scancode;
                if(k == SDL_Scancode::SDL_SCANCODE_LSHIFT ||
                   k == SDL_Scancode::SDL_SCANCODE_RSHIFT) {
                    mShiftPressed++;
                }
                const eKeyPressEvent ke(x, y, shift, buttons, k);
                if(mWidget) mWidget->keyPress(ke);
            } else if(e.type == SDL_KEYUP) {
                const auto k = e.key.keysym.scancode;
                if(k == SDL_Scancode::SDL_SCANCODE_LSHIFT ||
                   k == SDL_Scancode::SDL_SCANCODE_RSHIFT) {
                    mShiftPressed--;
                }
            }
        }

        SDL_SetRenderDrawColor(mSdlRenderer, 0x0, 0x0, 0x0, 0xFF);
        SDL_RenderClear(mSdlRenderer);

        ePainter p(mSdlRenderer);

        eMusic::incTime();
        if(mWidget) {
            mWidget->paint(p);
            tooltip.update();
            if(!tooltip.empty()) {
                const auto& res = resolution();
                const int pp = 25*res.multiplier();
                const int wtt = tooltip.width();
                const int htt = tooltip.height();
                int mx, my;
                SDL_GetMouseState(&mx, &my);
                int xtt;
                int ytt;
                if(mx > width()/2) {
                    xtt = mx - wtt;
                } else {
                    xtt = mx;
                }
                if(my > height()/2) {
                    ytt = my - htt - pp;
                } else {
                    ytt = my + pp;
                }
                tooltip.paint(xtt, ytt, p);
            }
        }

        p.setFont(eFonts::defaultFont(resolution()));
        p.drawText(0, 0, std::to_string(fpsVal), eFontColor::dark);

        SDL_RenderPresent(mSdlRenderer);

        for(const auto& s : mSlots) {
            s();
        }
        mSlots.clear();

        const auto fpsEnd = high_resolution_clock::now();
        const duration<double, std::milli> fpsElapsed = fpsEnd - fpsStart;
        const duration<double, std::milli> fpsDuration(1000./20);
        const duration<double, std::milli> fpsSleep(fpsDuration - fpsElapsed);
        std::this_thread::sleep_for(fpsSleep);

        c++;
        if(c % 25 == 0) {
            const auto fpsEnd = high_resolution_clock::now();
            const duration<double, std::milli> fpsElapsed = fpsEnd - fpsStart;
            fpsVal = (int)std::round(1000./fpsElapsed.count());
        }
    }

    return 0;
}
