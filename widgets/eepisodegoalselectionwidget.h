#ifndef EEPISODEGOALSELECTIONWIDGET_H
#define EEPISODEGOALSELECTIONWIDGET_H

#include "escrollbuttonslist.h"

#include "pointers/estdselfref.h"

class eEpisodeGoal;
class eWorldBoard;

enum class eGameEventBranch;
class eEpisodeGoalSelectionWidget : public eScrollButtonsList {
public:
    using eScrollButtonsList::eScrollButtonsList;

    using eEventsGetter = std::function<std::vector<stdsptr<eEpisodeGoal>>()>;
    using eEventAdder = std::function<void(const stdsptr<eEpisodeGoal>&)>;
    using eEventRemover = std::function<void(const stdsptr<eEpisodeGoal>&)>;
    void initialize(const eEventsGetter& get,
                    const eEventAdder& add,
                    const eEventRemover& remove,
                    eWorldBoard* const board);
};

#endif // EEPISODEGOALSELECTIONWIDGET_H
