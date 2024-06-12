#include "eeventselectionwidget.h"

#include "emainwindow.h"

#include "eventwidgets/eeventwidgetbase.h"
#include "gameEvents/egameevent.h"
#include "elanguage.h"

#include "widgets/echoosebutton.h"

#include "gameEvents/egodattackevent.h"
#include "gameEvents/einvasionevent.h"
#include "gameEvents/egiftfromevent.h"
#include "gameEvents/emakerequestevent.h"
#include "gameEvents/ereceiverequestevent.h"

#include "engine/egameboard.h"

eEventSelectionWidget::eEventSelectionWidget(
        const eGameEventBranch branch,
        eMainWindow* const window) :
    eScrollButtonsList(window),
    mBranch(branch) {}

void eEventSelectionWidget::initialize(
        const eEventsGetter& get,
        const eEventAdder& add,
        const eEventRemover& remove,
        eGameBoard& board) {
    eScrollButtonsList::initialize();
    const auto boardPtr = &board;

    const auto iniEs = get();
    for(const auto& e : iniEs) {
        const auto eStr = e->longDatedName();
        addButton(eStr);
    }

    const auto editEvent = [this](const stdsptr<eGameEvent>& e) {
        const auto settings = new eEventWidgetBase(window());
        settings->resize(width(), height());
        settings->initialize(e);

        window()->execDialog(settings);
        settings->align(eAlignment::center);
    };

    setButtonPressEvent([get, editEvent](const int id) {
        const auto es = get();
        const auto& e = es[id];
        editEvent(e);
    });

    setButtonCreateEvent([this, add, boardPtr, editEvent]() {
        const std::vector<eGameEventType> types = {
            eGameEventType::godVisit,
            eGameEventType::godAttack,
            eGameEventType::monsterUnleashed,
            eGameEventType::monsterInvasion,
            eGameEventType::invasion,
            eGameEventType::payTribute,
            eGameEventType::makeRequest,
            eGameEventType::receiveRequest,
            eGameEventType::giftTo,
            eGameEventType::giftFrom,
            eGameEventType::godQuest,
            eGameEventType::militaryChange,
            eGameEventType::economicChange,
            eGameEventType::troopsRequest
        };
        const std::vector<std::string> labels = {
            eLanguage::text("god_visit"),
            eLanguage::text("god_attack"),
            eLanguage::text("monster_unleash_long_name"),
            eLanguage::text("monster_invasion_long_name"),
            eLanguage::text("invasion"),
            eLanguage::text("pay_tribute"),
            eLanguage::text("make_request"),
            eLanguage::text("receive_request"),
            eLanguage::text("gift_to"),
            eLanguage::text("gift_from"),
            eLanguage::text("god_quest"),
            eLanguage::text("military_change_long_name"),
            eLanguage::text("economic_change_long_name"),
            eLanguage::text("troops_request_short_name")
        };
        const auto echoose = new eChooseButton(window());
        const auto act = [this, add, boardPtr, types, labels, editEvent](const int val) {
            const auto type = types[val];
            const auto e = eGameEvent::sCreate(type, mBranch, boardPtr);

            if(e) {
                const auto boardDate = boardPtr->date();
                const int period = 150;
                const auto date = boardDate + period;
                e->initializeDate(date, period, 1);
                add(e);
                editEvent(e);
                addButton(e->longDatedName());
            }
        };
        echoose->initialize(8, labels, act);

        window()->execDialog(echoose);
        echoose->align(eAlignment::center);
    });

    setButtonRemoveEvent([get, remove](const int id) {
        const auto es = get();
        const auto& e = es[id];
        remove(e);
    });
}
