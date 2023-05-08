#include "emonsterattackeventwidget.h"

#include "widgets/eframedbutton.h"
#include "widgets/echoosebutton.h"

#include "widgets/elabeledwidget.h"
#include "widgets/emonsterbutton.h"
#include "elanguage.h"

#include "emainwindow.h"

void eMonsterAttackEventWidget::initialize(
        eMonsterAttackEvent* const e) {
    const auto iniT = e->type();
    const auto monsterButtonL = new eLabeledWidget(window());
    const auto act = [e](const eMonsterType type) {
        e->setType(type);
    };
    const auto monsterButton = new eMonsterButton(window());
    monsterButton->initialize(act);
    monsterButton->setType(iniT);
    monsterButtonL->setup(eLanguage::text("monster:"), monsterButton);
    addWidget(monsterButtonL);

    const int p = padding();
    stackVertically(p);
    setNoPadding();
    fitContent();
}
