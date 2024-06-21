#include "emonsterbutton.h"

#include "echoosebutton.h"
#include "emainwindow.h"

void eMonsterButton::initialize(const eMonsterAction& mact,
                                const bool withGodsOnly,
                                const bool showGodNames) {
    setUnderline(false);
    setPressAction([this, mact, withGodsOnly, showGodNames]() {
        const auto choose = new eChooseButton(window());
        std::vector<eMonsterType> monsters;
        std::vector<std::string> monsterNames;
        eMonster::sMonsterStrings(monsters, monsterNames,
                                  withGodsOnly, showGodNames);
        const auto act = [this, monsters, mact](const int val) {
            const auto t = monsters[val];
            setType(t);
            if(mact) mact(t);
        };
        choose->initialize(8, monsterNames, act);

        window()->execDialog(choose);
        choose->align(eAlignment::center);
    });
    setType(eMonsterType::calydonianBoar);
    fitContent();
}

void eMonsterButton::setType(const eMonsterType type) {
    setText(eMonster::sMonsterName(type));
    mType = type;
}
