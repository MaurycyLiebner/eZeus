#include "egodattackeventwidget.h"

#include "widgets/eswitchbutton.h"
#include "elanguage.h"

#include "gameEvents/egodattackevent.h"

void eGodAttackEventWidget::initialize() {
    mRandomButton = new eSwitchButton(window());
    mRandomButton->addValue(eLanguage::text("iterative"));
    mRandomButton->addValue(eLanguage::text("random"));
    mRandomButton->setSwitchAction([this](const int v) {
        mRandom = v;
    });
}

void eGodAttackEventWidget::load(const eGodAttackEvent& e) {
    mTypes = e.types();
    mRandom = e.random();

    mRandomButton->setValue(mRandom ? 1 : 0);
}

void eGodAttackEventWidget::save(eGodAttackEvent& e) const {
    e.setTypes(mTypes);
    e.setRandom(mRandom);
}
