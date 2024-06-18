#include "emonsterattackeventwidget.h"

#include "widgets/eframedbutton.h"
#include "widgets/echoosebutton.h"

#include "widgets/elabeledwidget.h"
#include "widgets/emonsterbutton.h"
#include "widgets/evaluebutton.h"
#include "elanguage.h"

#include "emainwindow.h"

void eMonsterAttackEventWidget::initialize(eMonsterInvasionEventBase* const e) {
    const auto iniT = e->type();
    const auto monsterButtonL = new eLabeledWidget(window());
    const auto act = [e](const eMonsterType type) {
        e->setType(type);
    };
    const auto et = e->eGameEvent::type();
    const bool withGodsOnly = et == eGameEventType::monsterUnleashed;
    const auto monsterButton = new eMonsterButton(window());
    monsterButton->initialize(act, withGodsOnly, withGodsOnly);
    monsterButton->setType(iniT);
    monsterButtonL->setup(eLanguage::text("monster:"), monsterButton);
    addWidget(monsterButtonL);

    const auto invasionPointButtonL = new eLabeledWidget(window());
    const auto invasionPointButton = new eValueButton(window());
    invasionPointButton->setValueChangeAction([e](const int p) {
        e->setPointId(p);
    });
    invasionPointButton->initialize(0, 999);
    invasionPointButton->setValue(e->pointId());
    invasionPointButtonL->setup(eLanguage::text("invasion_point:"), invasionPointButton);
    addWidget(invasionPointButtonL);

    const int p = padding();
    stackVertically(p);
    setNoPadding();
    fitContent();
}
