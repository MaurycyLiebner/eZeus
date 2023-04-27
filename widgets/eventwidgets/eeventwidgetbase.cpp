#include "eeventwidgetbase.h"

#include "gameEvents/egameeventcycle.h"

#include "widgets/edatebutton.h"
#include "widgets/evaluebutton.h"
#include "engine/egameboard.h"
#include "widgets/elabeledwidget.h"
#include "elanguage.h"

#include "egodattackeventwidget.h"
#include "emonsterattackeventwidget.h"

void eEventWidgetBase::initialize(const stdsptr<eGameEventCycle>& e,
                                  eGameBoard* const boardPtr) {
    setType(eFrameType::message);

    const auto cont = new eWidget(window());
    cont->setNoPadding();
    addWidget(cont);
    const int p = padding();
    cont->move(2*p, 2*p);
    cont->resize(width() - 4*p, height() - 4*p);

    const auto dateButtonL = new eLabeledWidget(window());
    const auto dateButton = new eDateButton(window());
    dateButton->setDateChangeAction([e, boardPtr](const eDate& d) {
        e->setStartDate(d);
        e->rewind(boardPtr->date());
    });
    dateButton->initialize();
    dateButton->setDate(e->startDate());
    dateButtonL->setup(eLanguage::text("date:"), dateButton);
    cont->addWidget(dateButtonL);

    const auto periodButtonL = new eLabeledWidget(window());
    const auto periodButton = new eValueButton(window());
    periodButton->setValueChangeAction([e, boardPtr](const int p) {
        e->setPeriod(p);
        e->rewind(boardPtr->date());
    });
    periodButton->initialize(31, 99999);
    periodButton->setValue(e->period());
    periodButtonL->setup(eLanguage::text("period:"), periodButton);
    cont->addWidget(periodButtonL);

    const auto repeatButtonL = new eLabeledWidget(window());
    const auto repeatButton = new eValueButton(window());
    repeatButton->setValueChangeAction([e, boardPtr](const int p) {
        e->setRepeat(p);
        e->rewind(boardPtr->date());
    });
    repeatButton->initialize(0, 99999);
    repeatButton->setValue(e->repeat());
    repeatButtonL->setup(eLanguage::text("repeat:"), repeatButton);
    cont->addWidget(repeatButtonL);

    const auto ee = e->event();
    const auto eet = ee->type();
    switch(eet) {
    case eGameEventType::godAttack: {
        const auto eew = new eGodAttackEventWidget(window());
        const auto gaee = static_cast<eGodAttackEvent*>(ee.get());
        eew->initialize(this, gaee);
        cont->addWidget(eew);
    } break;
    case eGameEventType::monsterAttack: {
        const auto eew = new eMonsterAttackEventWidget(window());
        const auto maee = static_cast<eMonsterAttackEvent*>(ee.get());
        eew->initialize(maee);
        cont->addWidget(eew);
    } break;
    default:
        break;
    }

    cont->stackVertically(p);
}
