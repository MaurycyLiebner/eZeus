#include "eeditorsettingsmenu.h"

#include "eframedbutton.h"
#include "elanguage.h"

#include "characters/gods/egod.h"
#include "egodselectionwidget.h"
#include "emonsterselectionwidget.h"

#include "emainwindow.h"

#include "widgets/eeventselectionwidget.h"
#include "gameEvents/egameevent.h"
#include "widgets/echeckablebutton.h"

#include "engine/ecampaign.h"
#include "evectorhelpers.h"

void eEditorSettingsMenu::initialize(eEpisode* const ep) {
    setType(eFrameType::message);

    const auto mythologyAct = [this, ep]() {
        const auto mythMenu = new eFramedWidget(window());
        mythMenu->setType(eFrameType::message);
        mythMenu->resize(width(), height());

        const auto friendGodsAct = [this, ep]() {
            const auto choose = new eGodSelectionWidget(window());
            const auto act = [ep](const std::vector<eGodType>& godNs) {
                ep->fFriendlyGods = godNs;
            };

            const auto& iniG = ep->fFriendlyGods;
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

        const auto hostileGodsAct = [this, ep]() {
            const auto choose = new eGodSelectionWidget(window());
            const auto act = [ep](const std::vector<eGodType>& godNs) {
                ep->fHostileGods = godNs;
            };

            const auto& iniG = ep->fHostileGods;
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

//        const auto monstersAct = [this, ep]() {
//            const auto choose = new eMonsterSelectionWidget(window());
//            const auto act = [ep](const std::vector<eMonsterType>& monsters) {
//                ep->setHostileMonsters(monsters);
//            };

//            const auto& iniM = ep->hostileMonsters();
//            choose->resize(width(), height());
//            choose->initialize(act, iniM);

//            window()->execDialog(choose);
//            choose->align(eAlignment::center);
//        };

//        const auto monstersButt = new eFramedButton(window());
//        monstersButt->setUnderline(false);
//        monstersButt->setText(eLanguage::text("monsters"));
//        monstersButt->fitContent();
//        monstersButt->setPressAction(monstersAct);
//        mythMenu->addWidget(monstersButt);
//        monstersButt->align(eAlignment::hcenter);

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

    const auto eventsAct = [this, ep]() {
        const auto choose = new eEventSelectionWidget(
                                eGameEventBranch::root,
                                window());

        choose->resize(width(), height());
        const auto get = [ep]() {
            return ep->fEvents;
        };
        const auto add = [ep](const stdsptr<eGameEvent>& e) {
            ep->fEvents.push_back(e);
        };
        const auto remove = [ep](const stdsptr<eGameEvent>& e) {
            eVectorHelpers::remove(ep->fEvents, e);
        };
        choose->initialize(get, add, remove);

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

    const auto buildingsAct = [this, ep]() {
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
            bb->setChecked(ep->availableBuilding(type));
            bb->setCheckAction([type, ep](const bool b) {
                if(b) {
                    ep->fAvailableBuildings.allow(type);
                } else {
                    ep->fAvailableBuildings.disallow(type);
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
