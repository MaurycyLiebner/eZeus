#ifndef EEVENTSELECTIONWIDGET_H
#define EEVENTSELECTIONWIDGET_H

#include "escrollbuttonslist.h"

#include "pointers/estdselfref.h"

class eGameEvent;
class eGameBoard;

class eEventSelectionWidget : public eScrollButtonsList {
public:
    using eScrollButtonsList::eScrollButtonsList;

    using eEventsGetter = std::function<std::vector<stdsptr<eGameEvent>>()>;
    using eEventAdder = std::function<void(const stdsptr<eGameEvent>&)>;
    void initialize(const eEventsGetter& get,
                    const eEventAdder& add,
                    eGameBoard& board);
};

#endif // EEVENTSELECTIONWIDGET_H
