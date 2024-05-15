#include "eeventwidgetbase.h"

#include "gameEvents/egameevent.h"

#include "widgets/edatebutton.h"
#include "widgets/evaluebutton.h"
#include "engine/egameboard.h"
#include "widgets/elabeledwidget.h"
#include "elanguage.h"
#include "emainwindow.h"
#include "widgets/etriggerselectionwidget.h"
#include "widgets/eeventselectionwidget.h"

#include "egodattackeventwidget.h"
#include "emonsterattackeventwidget.h"
#include "einvasioneventwidget.h"
#include "egiftfromeventwidget.h"
#include "ereceiverequesteventwidget.h"
#include "egodquesteventwidget.h"

void eEventWidgetBase::initialize(const stdsptr<eGameEvent>& e) {
    setType(eFrameType::message);

    const auto cont = new eWidget(window());
    cont->setNoPadding();
    addWidget(cont);
    const int p = padding();
    cont->move(2*p, 2*p);
    cont->resize(width() - 4*p, height() - 4*p);

    const auto dateButtonL = new eLabeledWidget(window());
    const auto dateButton = new eDateButton(window());
    dateButton->setDateChangeAction([e](const eDate& d) {
        e->setStartDate(d);
    });
    dateButton->initialize();
    dateButton->setDate(e->startDate());
    dateButtonL->setup(eLanguage::text("date:"), dateButton);
    cont->addWidget(dateButtonL);

    const auto periodButtonL = new eLabeledWidget(window());
    const auto periodButton = new eValueButton(window());
    periodButton->setValueChangeAction([e](const int p) {
        e->setPeriod(p);
    });
    periodButton->initialize(31, 99999);
    periodButton->setValue(e->period());
    periodButtonL->setup(eLanguage::text("period:"), periodButton);
    cont->addWidget(periodButtonL);

    const auto repeatButtonL = new eLabeledWidget(window());
    const auto repeatButton = new eValueButton(window());
    repeatButton->setValueChangeAction([e](const int p) {
        e->setRepeat(p);
    });
    repeatButton->initialize(0, 99999);
    repeatButton->setValue(e->repeat());
    repeatButtonL->setup(eLanguage::text("repeat:"), repeatButton);
    cont->addWidget(repeatButtonL);

    const auto et = e->type();
    switch(et) {
    case eGameEventType::godAttack: {
        const auto eew = new eGodAttackEventWidget(window());
        const auto gaee = static_cast<eGodAttackEvent*>(e.get());
        eew->initialize(this, gaee);
        cont->addWidget(eew);
    } break;
    case eGameEventType::monsterAttack: {
        const auto eew = new eMonsterAttackEventWidget(window());
        const auto maee = static_cast<eMonsterAttackEvent*>(e.get());
        eew->initialize(maee);
        cont->addWidget(eew);
    } break;
    case eGameEventType::invasion: {
        const auto eew = new eInvasionEventWidget(window());
        const auto iee = static_cast<eInvasionEvent*>(e.get());
        eew->initialize(iee);
        cont->addWidget(eew);
    } break;
    case eGameEventType::giftFrom: {
        const auto eew = new eGiftFromEventWidget(window());
        const auto gfee = static_cast<eGiftFromEvent*>(e.get());
        eew->initialize(gfee);
        cont->addWidget(eew);
    } break;
    case eGameEventType::receiveRequest: {
        const auto eew = new eReceiveRequestEventWidget(window());
        const auto rree = static_cast<eReceiveRequestEvent*>(e.get());
        eew->initialize(rree);
        cont->addWidget(eew);
    } break;
    case eGameEventType::godQuest:
    case eGameEventType::godQuestFulfilled:{
        const auto eew = new eGodQuestEventWidget(window());
        const auto gqee = static_cast<eGodQuestEventBase*>(e.get());
        eew->initialize(gqee);
        cont->addWidget(eew);
    } break;
    default:
        break;
    }

    const auto& ts = e->triggers();
    if(!ts.empty()) {
        const int ec = e->triggerEventsCount();
        const auto ecStr = std::to_string(ec);
        const auto str = eLanguage::text("triggers") + " (" + ecStr + ")";
        const auto triggersButt = new eFramedButton(str, window());
        triggersButt->setUnderline(false);
        triggersButt->fitContent();
        triggersButt->setPressAction([this, e]() {
            const auto choose = new eTriggerSelectionWidget(window());

            choose->resize(width(), height());
            std::vector<std::string> labels;
            const auto& ts = e->triggers();
            for(const auto& t : ts) {
                const int ec = t->eventCount();
                const auto ecStr = std::to_string(ec);
                labels.push_back("(" + ecStr + ") " + t->name());
            }
            const auto act = [this, e](const int id) {
                const auto& ts = e->triggers();
                const auto& t = ts[id];
                const auto boardPtr = &e->getBoard();

                const auto choose = new eEventSelectionWidget(window());

                choose->resize(width(), height());
                const auto get = [t]() {
                    return t->events();
                };
                const auto add = [t](const stdsptr<eGameEvent>& e) {
                    t->addEvent(e);
                };
                const auto remove = [t](const stdsptr<eGameEvent>& e) {
                    t->removeEvent(e);
                };
                choose->initialize(get, add, remove, *boardPtr);

                window()->execDialog(choose);
                choose->align(eAlignment::center);
            };
            choose->initialize(labels, act);

            window()->execDialog(choose);
            choose->align(eAlignment::center);
        });
        cont->addWidget(triggersButt);
    }

    cont->stackVertically(p);
}
