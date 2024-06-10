#include "eeditorsettingsmenu.h"

#include "eframedbutton.h"
#include "elanguage.h"

#include "characters/gods/egod.h"
#include "egodselectionwidget.h"
#include "emonsterselectionwidget.h"

#include "engine/egameboard.h"
#include "emainwindow.h"

#include "widgets/eeventselectionwidget.h"
#include "gameEvents/egameevent.h"
#include "widgets/echeckablebutton.h"
#include "engine/emapgenerator.h"

#include "eacceptbutton.h"
#include "ecancelbutton.h"
#include "enumlineedit.h"

void eEditorSettingsMenu::initialize(eGameBoard& board) {
    setType(eFrameType::message);

    const auto boardPtr = &board;
    const auto mythologyAct = [this, boardPtr]() {
        const auto mythMenu = new eFramedWidget(window());
        mythMenu->setType(eFrameType::message);
        mythMenu->resize(width(), height());

        const auto friendGodsAct = [this, boardPtr]() {
            const auto choose = new eGodSelectionWidget(window());
            const auto act = [boardPtr](const std::vector<eGodType>& godNs) {
                boardPtr->setFriendlyGods(godNs);
            };

            const auto& iniG = boardPtr->friendlyGods();
            choose->resize(width(), height());
            choose->initialize(act, iniG);

            window()->execDialog(choose);
            choose->align(eAlignment::center);
        };

        const auto friendGodsButt = new eFramedButton(window());
        friendGodsButt->setUnderline(false);
        friendGodsButt->setText(eLanguage::text("friendly_gods"));
        friendGodsButt->fitContent();
        friendGodsButt->setPressAction(friendGodsAct);
        mythMenu->addWidget(friendGodsButt);
        friendGodsButt->align(eAlignment::hcenter);

        const auto hostileGodsAct = [this, boardPtr]() {
            const auto choose = new eGodSelectionWidget(window());
            const auto act = [boardPtr](const std::vector<eGodType>& godNs) {
                boardPtr->setHostileGods(godNs);
            };

            const auto& iniG = boardPtr->hostileGods();
            choose->resize(width(), height());
            choose->initialize(act, iniG);

            window()->execDialog(choose);
            choose->align(eAlignment::center);
        };

        const auto hostileGodsButt = new eFramedButton(window());
        hostileGodsButt->setUnderline(false);
        hostileGodsButt->setText(eLanguage::text("hostile_gods"));
        hostileGodsButt->fitContent();
        hostileGodsButt->setPressAction(hostileGodsAct);
        mythMenu->addWidget(hostileGodsButt);
        hostileGodsButt->align(eAlignment::hcenter);

        const auto monstersAct = [this, boardPtr]() {
            const auto choose = new eMonsterSelectionWidget(window());
            const auto act = [boardPtr](const std::vector<eMonsterType>& monsters) {
                boardPtr->setHostileMonsters(monsters);
            };

            const auto& iniM = boardPtr->hostileMonsters();
            choose->resize(width(), height());
            choose->initialize(act, iniM);

            window()->execDialog(choose);
            choose->align(eAlignment::center);
        };

        const auto monstersButt = new eFramedButton(window());
        monstersButt->setUnderline(false);
        monstersButt->setText(eLanguage::text("monsters"));
        monstersButt->fitContent();
        monstersButt->setPressAction(monstersAct);
        mythMenu->addWidget(monstersButt);
        monstersButt->align(eAlignment::hcenter);

        window()->execDialog(mythMenu);
        mythMenu->align(eAlignment::center);
        mythMenu->layoutVertically();
    };

    const auto modeButt = new eFramedButton(window());
    modeButt->setUnderline(false);
    modeButt->setText(board.poseidonMode() ? eLanguage::text("poseidon") :
                                             eLanguage::text("zeus"));
    modeButt->fitContent();
    modeButt->setPressAction([modeButt, boardPtr]() {
        boardPtr->setPoseidonMode(!boardPtr->poseidonMode());
        modeButt->setText(boardPtr->poseidonMode() ? eLanguage::text("poseidon") :
                                                     eLanguage::text("zeus"));
        boardPtr->showTip(eLanguage::text("save_and_reset"));
        boardPtr->scheduleTerrainUpdate();
    });
    addWidget(modeButt);
    modeButt->align(eAlignment::hcenter);

    const auto resizeButt = new eFramedButton(window());
    resizeButt->setUnderline(false);
    resizeButt->setText(eLanguage::text("resize"));
    resizeButt->fitContent();
    resizeButt->setPressAction([this, boardPtr]() {
        const auto resizeMenu = new eFramedWidget(window());
        resizeMenu->setType(eFrameType::message);
        resizeMenu->resize(width(), height());

        const auto res = resolution();
        const int p = res.largePadding();

        const auto iw = new eWidget(window());
        iw->setNoPadding();
        resizeMenu->addWidget(iw);
        iw->move(p, p);

        const auto editW = new eWidget(window());
        editW->setNoPadding();
        iw->addWidget(editW);

        const auto widthL = new eLabel(window());
        widthL->setText(eLanguage::text("width"));
        widthL->fitContent();
        editW->addWidget(widthL);

        const auto width = new eNumLineEdit(window());
        width->setRenderBg(true);
        width->setRange(10, 999);
        width->setValue(999);
        width->fitContent();
        width->setValue(boardPtr->width());
        editW->addWidget(width);

        const auto heightL = new eLabel(window());
        heightL->setText(eLanguage::text("height"));
        heightL->fitContent();
        editW->addWidget(heightL);

        const auto height = new eNumLineEdit(window());
        height->setRenderBg(true);
        height->setRange(10, 999);
        height->setValue(999);
        height->fitContent();
        height->setValue(boardPtr->height());
        editW->addWidget(height);

        editW->stackHorizontally();
        editW->fitContent();

        widthL->align(eAlignment::vcenter);
        width->align(eAlignment::vcenter);
        heightL->align(eAlignment::vcenter);
        height->align(eAlignment::vcenter);

        const auto buttonsW = new eWidget(window());
        buttonsW->setNoPadding();

        const auto accept = new eAcceptButton(window());
        const auto cancel = new eCancelButton(window());
        accept->setPressAction([resizeMenu, width, height, boardPtr]() {
            const int w = width->value();
            const int h = height->value();
            boardPtr->resize(w, h);
            resizeMenu->deleteLater();
        });
        cancel->setPressAction([resizeMenu]() {
            resizeMenu->deleteLater();
        });

        buttonsW->addWidget(accept);
        buttonsW->addWidget(cancel);
        buttonsW->fitHeight();
        buttonsW->setWidth(editW->width());
        buttonsW->layoutHorizontallyWithoutSpaces();
        iw->addWidget(buttonsW);

        iw->stackVertically();
        iw->fitContent();
        resizeMenu->resize(2*p + iw->width(), 2*p + iw->height());

        window()->execDialog(resizeMenu);
        resizeMenu->align(eAlignment::center);
    });
    addWidget(resizeButt);
    resizeButt->align(eAlignment::hcenter);

    const auto generateButt = new eFramedButton(window());
    generateButt->setUnderline(false);
    generateButt->setText(eLanguage::text("generate"));
    generateButt->fitContent();
    generateButt->setPressAction([boardPtr]() {
        eMapGenerator g(*boardPtr);
        eMapGeneratorSettings sett;

        g.generate(sett);
    });
    addWidget(generateButt);
    generateButt->align(eAlignment::hcenter);

    const auto mythButt = new eFramedButton(window());
    mythButt->setUnderline(false);
    mythButt->setText(eLanguage::text("mythology"));
    mythButt->fitContent();
    mythButt->setPressAction(mythologyAct);
    addWidget(mythButt);
    mythButt->align(eAlignment::hcenter);

    const auto eventsAct = [this, boardPtr]() {
        const auto choose = new eEventSelectionWidget(
                                eGameEventBranch::root,
                                window());

        choose->resize(width(), height());
        const auto get = [boardPtr]() {
            return boardPtr->gameEvents();
        };
        const auto add = [boardPtr](const stdsptr<eGameEvent>& e) {
            boardPtr->addRootGameEvent(e);
        };
        const auto remove = [boardPtr](const stdsptr<eGameEvent>& e) {
            boardPtr->removeRootGameEvent(e);
        };
        choose->initialize(get, add, remove, *boardPtr);

        window()->execDialog(choose);
        choose->align(eAlignment::center);
    };

    const auto eventsButt = new eFramedButton(window());
    eventsButt->setUnderline(false);
    eventsButt->setText(eLanguage::text("events"));
    eventsButt->fitContent();
    eventsButt->setPressAction(eventsAct);
    addWidget(eventsButt);
    eventsButt->align(eAlignment::hcenter);

    const auto buildingsAct = [this, boardPtr]() {
        const auto buildMenu = new eFramedWidget(window());
        buildMenu->setType(eFrameType::message);
        buildMenu->resize(width(), height());

        const std::vector<eBuildingType> bv {
            eBuildingType::wheatFarm,
            eBuildingType::carrotsFarm,
            eBuildingType::onionsFarm,

            eBuildingType::vine,
            eBuildingType::oliveTree,
            eBuildingType::orangeTree,

            eBuildingType::dairy,
            eBuildingType::cardingShed,

            eBuildingType::fishery,
            eBuildingType::urchinQuay,
            eBuildingType::huntingLodge,
            eBuildingType::corral,

            eBuildingType::mint,
            eBuildingType::foundry,
            eBuildingType::timberMill,
            eBuildingType::masonryShop,

            eBuildingType::winery,
            eBuildingType::olivePress,
            eBuildingType::sculptureStudio,

            eBuildingType::armory
        };

        int w = 0;
        std::vector<eCheckableButton*> buttons;
        for(const auto& type : bv) {
            const auto bb = new eCheckableButton(window());
            bb->setSmallFontSize();
            bb->setSmallPadding();
            bb->setText(eBuilding::sNameForBuilding(type));
            bb->fitContent();
            w = std::max(w, bb->width());
            bb->setChecked(boardPtr->availableBuilding(type));
            bb->setCheckAction([type, boardPtr](const bool b) {
                if(b) {
                    boardPtr->allow(type);
                } else {
                    boardPtr->disallow(type);
                }
            });
            buttons.push_back(bb);
            buildMenu->addWidget(bb);
        }
        const int p = padding();
        int x = 2*p;
        int y = 2*p;
        for(const auto b : buttons) {
            b->setWidth(w);
            const int bh = b->height();
            if(y + bh + 2*p > buildMenu->height()) {
                x += w;
                y = 2*p;
            }
            b->move(x, y);
            y += bh + p;
        }

        window()->execDialog(buildMenu);
        buildMenu->align(eAlignment::center);
    };

    const auto buildingsButt = new eFramedButton(window());
    buildingsButt->setUnderline(false);
    buildingsButt->setText(eLanguage::text("buildings"));
    buildingsButt->fitContent();
    buildingsButt->setPressAction(buildingsAct);
    addWidget(buildingsButt);
    buildingsButt->align(eAlignment::hcenter);

    layoutVertically();
}
