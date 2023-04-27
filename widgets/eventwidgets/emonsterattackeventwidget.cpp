#include "emonsterattackeventwidget.h"

#include "widgets/eframedbutton.h"
#include "widgets/echoosebutton.h"

#include "emainwindow.h"

void eMonsterAttackEventWidget::initialize(
        eMonsterAttackEvent* const e) {
    const auto iniT = e->type();
    const auto iniStr = eMonster::sMonsterName(iniT);
    const auto monsterButton = new eFramedButton(iniStr, window());
    monsterButton->fitContent();
    monsterButton->setUnderline(false);
    monsterButton->setPressAction([this, e, monsterButton]() {
        const auto choose = new eChooseButton(window());
        std::vector<eMonsterType> monsters;
        std::vector<std::string> monsterNames;
        eMonster::sMonsterStrings(monsters, monsterNames);
        const auto act = [e, monsterButton, monsters, monsterNames](const int val) {
            monsterButton->setText(monsterNames[val]);
            e->setType(monsters[val]);
        };
        choose->initialize(8, monsterNames, act);

        window()->execDialog(choose);
        choose->align(eAlignment::center);
    });
    addWidget(monsterButton);

    const int p = padding();
    stackVertically(p);
    setNoPadding();
    fitContent();
}
