#include "eepisodegoalselectionwidget.h"

#include "widgets/echoosebutton.h"
#include "emainwindow.h"
#include "engine/eepisodegoal.h"
#include "eepisodegoalwidget.h"

void eEpisodeGoalSelectionWidget::initialize(
        const eEventsGetter& get,
        const eEventAdder& add,
        const eEventRemover& remove,
        eWorldBoard* const board) {

    eScrollButtonsList::initialize();

    const auto iniEs = get();
    for(const auto& e : iniEs) {
        const auto eStr = e->text(false, false);
        addButton(eStr);
    }

    const auto editEvent = [this, board](const stdsptr<eEpisodeGoal>& e) {
        const auto settings = new eEpisodeGoalWidget(window());
        settings->resize(2*width()/3, height()/3);
        settings->initialize(e, board);

        window()->execDialog(settings);
        settings->align(eAlignment::center);
    };

    setButtonPressEvent([get, editEvent](const int id) {
        const auto es = get();
        const auto& e = es[id];
        editEvent(e);
    });

    setButtonCreateEvent([this, add, editEvent]() {
        const std::vector<eEpisodeGoalType> types = {
            eEpisodeGoalType::population,
            eEpisodeGoalType::treasury,
            eEpisodeGoalType::sanctuary,
            eEpisodeGoalType::support,
            eEpisodeGoalType::quest,
            eEpisodeGoalType::slay,
            eEpisodeGoalType::rule,
            eEpisodeGoalType::housing,
            eEpisodeGoalType::setAsideGoods,
            eEpisodeGoalType::surviveUntil,
            eEpisodeGoalType::completeBefore,
            eEpisodeGoalType::tradingPartners
        };
        std::vector<std::string> labels;
        for(const auto t : types) {
            labels.push_back(eEpisodeGoal::sText(t));
        }
        const auto echoose = new eChooseButton(window());
        const auto act = [this, add, types, labels, editEvent](const int val) {
            const auto type = types[val];
            const auto e = std::make_shared<eEpisodeGoal>();
            e->fType = type;

            if(e) {
                add(e);
                editEvent(e);
                addButton(e->text(false, false));
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
