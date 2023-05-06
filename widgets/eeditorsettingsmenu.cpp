#include "eeditorsettingsmenu.h"

#include "eframedbutton.h"
#include "elanguage.h"

#include "characters/gods/egod.h"
#include "escrollbuttonslist.h"
#include "egodselectionwidget.h"
#include "emonsterselectionwidget.h"

#include "engine/egameboard.h"
#include "emainwindow.h"

#include "gameEvents/egameevent.h"
#include "widgets/eventwidgets/eeventwidgetbase.h"
#include "widgets/echoosebutton.h"
#include "widgets/echeckablebutton.h"

#include "gameEvents/emonsterattackevent.h"
#include "gameEvents/egodattackevent.h"
#include "gameEvents/einvasionevent.h"
#include "gameEvents/egiftfromevent.h"
#include "gameEvents/emakerequestevent.h"
#include "gameEvents/ereceiverequestevent.h"

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

    const auto mythButt = new eFramedButton(window());
    mythButt->setUnderline(false);
    mythButt->setText(eLanguage::text("mythology"));
    mythButt->fitContent();
    mythButt->setPressAction(mythologyAct);
    addWidget(mythButt);
    mythButt->align(eAlignment::hcenter);

    const auto eventsAct = [this, boardPtr]() {
        const auto choose = new eScrollButtonsList(window());

        choose->resize(width(), height());
        choose->initialize();

        const auto& iniEs = boardPtr->gameEvents();
        for(const auto& e : iniEs) {
            const auto eStr = e->longDatedName();
            choose->addButton(eStr);
        }

        const auto editEvent = [this](const stdsptr<eGameEvent>& e) {
            const auto settings = new eEventWidgetBase(window());
            settings->resize(width(), height());
            settings->initialize(e);

            window()->execDialog(settings);
            settings->align(eAlignment::center);
        };

        choose->setButtonPressEvent([boardPtr, editEvent](const int id) {
            const auto& es = boardPtr->gameEvents();
            const auto& e = es[id];
            editEvent(e);
        });

        choose->setButtonCreateEvent([this, choose, boardPtr, editEvent]() {
            const std::vector<eGameEventType> types = {
                eGameEventType::godVisit,
                eGameEventType::godAttack,
                eGameEventType::monsterAttack,
                eGameEventType::invasion,
                eGameEventType::payTribute,
                eGameEventType::makeRequest,
                eGameEventType::receiveRequest,
                eGameEventType::giftTo,
                eGameEventType::giftFrom
            };
            const std::vector<std::string> labels = {
                eLanguage::text("god_visit"),
                eLanguage::text("god_attack"),
                eLanguage::text("monster_attack"),
                eLanguage::text("invasion"),
                eLanguage::text("pay_tribute"),
                eLanguage::text("make_request"),
                eLanguage::text("receive_request"),
                eLanguage::text("gift_to"),
                eLanguage::text("gift_from")
            };
            const auto echoose = new eChooseButton(window());
            const auto act = [this, choose, boardPtr, types, labels, editEvent](const int val) {
                const auto type = types[val];
                stdsptr<eGameEvent> e;
                switch(type) {
                case eGameEventType::godVisit: {

                } break;
                case eGameEventType::godAttack: {
                    e = e::make_shared<eGodAttackEvent>(*boardPtr);
                } break;
                case eGameEventType::monsterAttack: {
                    e = e::make_shared<eMonsterAttackEvent>(*boardPtr);
                } break;
                case eGameEventType::invasion: {
                    e = e::make_shared<eInvasionEvent>(*boardPtr);
                } break;
                case eGameEventType::payTribute: {

                } break;
                case eGameEventType::makeRequest: {
                    e = e::make_shared<eMakeRequestEvent>(*boardPtr);
                } break;
                case eGameEventType::receiveRequest: {
                    e = e::make_shared<eReceiveRequestEvent>(*boardPtr);
                } break;
                case eGameEventType::giftTo: {

                } break;
                case eGameEventType::giftFrom: {
                    e = e::make_shared<eGiftFromEvent>(*boardPtr);
                } break;
                default:
                    break;
                }
                if(e) {
                    const auto boardDate = boardPtr->date();
                    const int period = 150;
                    const auto date = boardDate + period;
                    e->initializeDate(date, period, 1);
                    boardPtr->addGameEvent(e);
                    editEvent(e);
                    choose->addButton(e->longDatedName());
                }
            };
            echoose->initialize(8, labels, act);

            window()->execDialog(echoose);
            echoose->align(eAlignment::center);
        });

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

        const auto basicAllower = [boardPtr](const eBuildingType type) {
            return [boardPtr, type](const bool b) {
                if(b) {
                    boardPtr->allow(type);
                } else {
                    boardPtr->disallow(type);
                }
            };
        };

        using eBVs = std::vector<std::pair<std::string, eBuildingType>>;
        const eBVs bv {
            {eLanguage::text("wheat_farm"), eBuildingType::wheatFarm},
            {eLanguage::text("carrot_farm"), eBuildingType::carrotsFarm},
            {eLanguage::text("onion_farm"), eBuildingType::onionsFarm},

            {eLanguage::text("vine"), eBuildingType::vine},
            {eLanguage::text("olive_tree"), eBuildingType::oliveTree},
            {eLanguage::text("orange_tree"), eBuildingType::orangeTree},

            {eLanguage::text("dairy"), eBuildingType::dairy},
            {eLanguage::text("carding_shed"), eBuildingType::cardingShed},

            {eLanguage::text("fishery"), eBuildingType::fishery},
            {eLanguage::text("urchin_quay"), eBuildingType::urchinQuay},
            {eLanguage::text("hunting_lodge"), eBuildingType::huntingLodge},

            {eLanguage::text("mint"), eBuildingType::mint},
            {eLanguage::text("foundry"), eBuildingType::foundry},
            {eLanguage::text("timber_mill"), eBuildingType::timberMill},
            {eLanguage::text("masonry_shop"), eBuildingType::masonryShop},

            {eLanguage::text("winery"), eBuildingType::winery},
            {eLanguage::text("olive_press"), eBuildingType::olivePress},
            {eLanguage::text("sculpture_studio"), eBuildingType::sculptureStudio},

            {eLanguage::text("armory"), eBuildingType::armory}
        };

        int w = 0;
        std::vector<eCheckableButton*> buttons;
        for(const auto& b : bv) {
            const auto bb = new eCheckableButton(window());
            bb->setSmallFontSize();
            bb->setSmallPadding();
            bb->setText(b.first);
            bb->fitContent();
            w = std::max(w, bb->width());
            const auto type = b.second;
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
