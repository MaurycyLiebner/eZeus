#include "eeditorsettingsmenu.h"

#include "eframedbutton.h"
#include "elanguage.h"

#include "characters/gods/egod.h"
#include "emultipleselectionwidget.h"

#include "engine/egameboard.h"
#include "emainwindow.h"

void eEditorSettingsMenu::initialize(eGameBoard& board) {
    setType(eFrameType::message);

    const auto boardPtr = &board;
    const auto mythologyAct = [this, boardPtr]() {
        const auto mythMenu = new eFramedWidget(window());
        mythMenu->setType(eFrameType::message);
        mythMenu->resize(width(), height());

        std::vector<eGodType> gods;
        const int iMin = static_cast<int>(eGodType::aphrodite);
        const int iMax = static_cast<int>(eGodType::zeus);
        for(int i = iMin; i <= iMax; i++) {
            const auto mi = static_cast<eGodType>(i);
            gods.push_back(mi);
        }

        std::vector<std::string> godNames;
        for(const auto g : gods) {
            godNames.push_back(eGod::sGodName(g));
        }

        const auto friendGodsAct = [this, gods, godNames, boardPtr]() {
            const auto choose = new eMultipleSelectionWidget(window());
            const auto act = [gods, boardPtr](const std::vector<int>& ns) {
                std::vector<eGodType> godNs;
                for(const int n : ns) {
                    godNs.push_back(gods[n]);
                }
                boardPtr->setFriendlyGods(godNs);
            };

            const auto& iniG = boardPtr->friendlyGods();
            std::vector<int> ini;
            for(const auto g : iniG) {
                const int i = static_cast<int>(g);
                ini.push_back(i);
            }
            choose->resize(width(), height());
            choose->initialize(godNames, act, ini);

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

        const auto hostileGodsAct = [this, gods, godNames, boardPtr]() {
            const auto choose = new eMultipleSelectionWidget(window());
            const auto act = [gods, boardPtr](const std::vector<int>& ns) {
                std::vector<eGodType> godNs;
                for(const int n : ns) {
                    godNs.push_back(gods[n]);
                }
                boardPtr->setHostileGods(godNs);
            };

            const auto& iniG = boardPtr->hostileGods();
            std::vector<int> ini;
            for(const auto g : iniG) {
                const int i = static_cast<int>(g);
                ini.push_back(i);
            }
            choose->resize(width(), height());
            choose->initialize(godNames, act, ini);

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
            std::vector<eMonsterType> monsters;
            const int iMin = static_cast<int>(eMonsterType::calydonianBoar);
            const int iMax = static_cast<int>(eMonsterType::talos);
            for(int i = iMin; i <= iMax; i++) {
                const auto mi = static_cast<eMonsterType>(i);
                monsters.push_back(mi);
            }

            const std::vector<std::string> monsterGods {
                eLanguage::text("artemis"),
                eLanguage::text("hades"),
                eLanguage::text("atlas"),
                eLanguage::text("zeus"),
                eLanguage::text("ares"),
                "-",
                "-",
                eLanguage::text("aphrodite"),
                eLanguage::text("athena"),
                eLanguage::text("poseidon"),
                eLanguage::text("dionysus"),
                eLanguage::text("demeter"),
                eLanguage::text("hermes"),
                eLanguage::text("apollo"),
                eLanguage::text("hera"),
                eLanguage::text("hephaestus")
            };
            const std::vector<std::string> monsterHeroes {
                eLanguage::text("theseus"),
                eLanguage::text("hercules"),
                eLanguage::text("bellerophon"),
                eLanguage::text("odysseus"),
                eLanguage::text("jason"),
                eLanguage::text("bellerophon"),
                eLanguage::text("atalanta"),
                eLanguage::text("achilles"),
                eLanguage::text("hercules"),
                eLanguage::text("perseus"),
                eLanguage::text("achilles"),
                eLanguage::text("perseus"),
                eLanguage::text("theseus"),
                eLanguage::text("odysseus"),
                eLanguage::text("atalanta"),
                eLanguage::text("jason")
            };

            std::vector<std::string> monsterNames;
            const int iMax2 = monsters.size();
            for(int i = 0; i < iMax2; i++) {
                const auto& m = monsters[i];
                const auto& g = monsterGods[i];
                const auto& h = monsterHeroes[i];
                monsterNames.push_back(eMonster::sMonsterName(m) + " (" +
                                       g + ", " + h + ")");
            }

            const auto choose = new eMultipleSelectionWidget(window());
            const auto act = [monsters, boardPtr](const std::vector<int>& ns) {
                std::vector<eMonsterType> godNs;
                for(const int n : ns) {
                    godNs.push_back(monsters[n]);
                }
                boardPtr->setHostileMonsters(godNs);
            };

            const auto& iniG = boardPtr->hostileMonsters();
            std::vector<int> ini;
            for(const auto g : iniG) {
                const int i = static_cast<int>(g);
                ini.push_back(i);
            }
            choose->resize(width(), height());
            choose->initialize(monsterNames, act, ini);

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

    const auto eventsAct = []() {
    };

    const auto eventsButt = new eFramedButton(window());
    eventsButt->setUnderline(false);
    eventsButt->setText(eLanguage::text("events"));
    eventsButt->fitContent();
    eventsButt->setPressAction(eventsAct);
    addWidget(eventsButt);
    eventsButt->align(eAlignment::hcenter);

    layoutVertically();
}
