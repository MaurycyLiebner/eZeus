#include "eeventwidgetbase.h"

#include "gameEvents/egameeventcycle.h"

#include "widgets/edatebutton.h"
#include "engine/egameboard.h"
#include "egodattackeventwidget.h"
#include "widgets/elabeledwidget.h"
#include "elanguage.h"

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

    const auto ee = e->event();
    const auto eet = ee->type();
    switch(eet) {
    case eGameEventType::godAttack: {
        const auto eew = new eGodAttackEventWidget(window());
        const auto gaee = static_cast<eGodAttackEvent*>(ee.get());
        eew->initialize(this, gaee);
        cont->addWidget(eew);
    } break;
    default:
        break;
    }

    cont->stackVertically(p);
}
