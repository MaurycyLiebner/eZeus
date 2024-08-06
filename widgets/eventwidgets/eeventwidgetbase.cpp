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
#include "gameEvents/eeconomicmilitarychangeeventbase.h"
#include "gameEvents/egoddisasterevent.h"
#include "gameEvents/erivalarmyawayevent.h"
#include "gameEvents/eearthquakeevent.h"
#include "gameEvents/ecitybecomesevent.h"
#include "gameEvents/ebasiccityevent.h"

#include "egodattackeventwidget.h"
#include "emonsterattackeventwidget.h"
#include "einvasioneventwidget.h"
#include "egiftfromeventwidget.h"
#include "ereceiverequesteventwidget.h"
#include "egodquesteventwidget.h"
#include "eeconomicmilitarychangeeventwidget.h"
#include "etroopsrequesteventwidget.h"
#include "egoddisastereventwidget.h"
#include "erivalarmyawayeventwidget.h"
#include "eeartquakeeventwidget.h"
#include "ecitybecomeseventwidget.h"
#include "ebasiccityeventwidget.h"

void eEventWidgetBase::initialize(const stdsptr<eGameEvent>& e) {
    setType(eFrameType::message);

    const auto cont = new eWidget(window());
    cont->setNoPadding();
    addWidget(cont);
    const int p = padding();
    cont->move(2*p, 2*p);
    cont->resize(width() - 4*p, height() - 4*p);

    const auto et = e->type();
    switch(et) {
    case eGameEventType::godAttack: {
        const auto eew = new eGodAttackEventWidget(window());
        const auto gaee = static_cast<eGodAttackEvent*>(e.get());
        eew->initialize(this, gaee);
        cont->addWidget(eew);
    } break;
    case eGameEventType::monsterUnleashed:
    case eGameEventType::monsterInvasion: {
        const auto eew = new eMonsterAttackEventWidget(window());
        const auto maee = static_cast<eMonsterInvasionEventBase*>(e.get());
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
    case eGameEventType::troopsRequest: {
        const auto eew = new eTroopsRequestEventWidget(window());
        const auto rree = static_cast<eTroopsRequestEvent*>(e.get());
        eew->initialize(rree);
        cont->addWidget(eew);
    } break;
    case eGameEventType::godQuest:
    case eGameEventType::godQuestFulfilled: {
        const auto eew = new eGodQuestEventWidget(window());
        const auto gqee = static_cast<eGodQuestEventBase*>(e.get());
        eew->initialize(gqee);
        cont->addWidget(eew);
    } break;
    case eGameEventType::militaryChange:
    case eGameEventType::economicChange: {
        const auto eew = new eEconomicMilitaryChangeEventWidget(window());
        const auto emceb = static_cast<eEconomicMilitaryChangeEventBase*>(e.get());
        eew->initialize(emceb);
        cont->addWidget(eew);
    } break;
    case eGameEventType::godDisaster: {
        const auto eew = new eGodDisasterEventWidget(window());
        const auto emceb = static_cast<eGodDisasterEvent*>(e.get());
        eew->initialize(emceb);
        cont->addWidget(eew);
    } break;
    case eGameEventType::rivalArmyAway: {
        const auto eew = new eRivalArmyAwayEventWidget(window());
        const auto emceb = static_cast<eRivalArmyAwayEvent*>(e.get());
        eew->initialize(emceb);
        cont->addWidget(eew);
    } break;
    case eGameEventType::earthquake: {
        const auto eew = new eEartquakeEventWidget(window());
        const auto ee = static_cast<eEarthquakeEvent*>(e.get());
        eew->initialize(ee);
        cont->addWidget(eew);
    } break;
    case eGameEventType::cityBecomes: {
        const auto eew = new eCityBecomesEventWidget(window());
        const auto ee = static_cast<eCityBecomesEvent*>(e.get());
        eew->initialize(ee);
        cont->addWidget(eew);
    } break;
    case eGameEventType::tradeShutdowns:
    case eGameEventType::tradeOpensUp: {
        const auto eew = new eBasicCityEventWidget(window());
        const auto ee = static_cast<eBasicCityEvent*>(e.get());
        eew->initialize(ee);
        cont->addWidget(eew);
    } break;
    default:
        break;
    }

    const auto dateW = new eWidget(window());
    dateW->setNoPadding();

    const auto yearsButtonL = new eLabeledWidget(window());
    const auto yearsButton = new eValueButton(window());
    yearsButton->setValueChangeAction([e, yearsButton](const int y) {
        e->setDatePlusYears(y);
        yearsButton->setText("+" + yearsButton->text());
    });
    yearsButton->initialize(0, 99999);
    yearsButton->setValue(e->datePlusYears());
    yearsButton->setText("+" + yearsButton->text());
    yearsButtonL->setup(eLanguage::text("years:"), yearsButton);
    dateW->addWidget(yearsButtonL);

    const auto monthssButtonL = new eLabeledWidget(window());
    const auto monthsButton = new eValueButton(window());
    monthsButton->setValueChangeAction([e, monthsButton](const int y) {
        e->setDatePlusMonths(y);
        monthsButton->setText("+" + monthsButton->text());
    });
    monthsButton->initialize(0, 99999);
    monthsButton->setValue(e->datePlusMonths());
    monthsButton->setText("+" + monthsButton->text());
    monthssButtonL->setup(eLanguage::text("months:"), monthsButton);
    dateW->addWidget(monthssButtonL);

    const auto daysButtonL = new eLabeledWidget(window());
    const auto daysButton = new eValueButton(window());
    daysButton->setValueChangeAction([e, daysButton](const int y) {
        e->setDatePlusDays(y);
        daysButton->setText("+" + daysButton->text());
    });
    daysButton->initialize(0, 99999);
    daysButton->setValue(e->datePlusDays());
    daysButton->setText("+" + daysButton->text());
    daysButtonL->setup(eLanguage::text("days:"), daysButton);
    dateW->addWidget(daysButtonL);

    const auto periodButtonL = new eLabeledWidget(window());
    const auto periodButton = new eValueButton(window());
    periodButton->setValueChangeAction([e](const int p) {
        e->setPeriod(p);
    });
    periodButton->initialize(31, 99999);
    periodButton->setValue(e->period());
    periodButtonL->setup(eLanguage::text("period:"), periodButton);
    dateW->addWidget(periodButtonL);

    const auto repeatButtonL = new eLabeledWidget(window());
    const auto repeatButton = new eValueButton(window());
    repeatButton->setValueChangeAction([e](const int p) {
        e->setRepeat(p);
    });
    repeatButton->initialize(0, 99999);
    repeatButton->setValue(e->repeat());
    repeatButtonL->setup(eLanguage::text("repeat:"), repeatButton);
    dateW->addWidget(repeatButtonL);

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

                const auto choose = new eEventSelectionWidget(
                                        eGameEventBranch::trigger,
                                        window());

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
                choose->initialize(get, add, remove);

                window()->execDialog(choose);
                choose->align(eAlignment::center);
            };
            choose->initialize(labels, act);

            window()->execDialog(choose);
            choose->align(eAlignment::center);
        });
        dateW->addWidget(triggersButt);
    }

    dateW->stackVertically(p);
    dateW->fitContent();
    cont->addWidget(dateW);
    cont->layoutHorizontallyWithoutSpaces();
}
