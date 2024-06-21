#ifndef EEVENTSELECTIONWIDGET_H
#define EEVENTSELECTIONWIDGET_H

#include "escrollbuttonslist.h"

#include "pointers/estdselfref.h"

class eGameEvent;
class eGameBoard;

enum class eGameEventBranch;

class eEventSelectionWidget : public eScrollButtonsList {
public:
    eEventSelectionWidget(const eGameEventBranch branch,
                          eMainWindow* const window);

    using eEventsGetter = std::function<std::vector<stdsptr<eGameEvent>>()>;
    using eEventAdder = std::function<void(const stdsptr<eGameEvent>&)>;
    using eEventRemover = std::function<void(const stdsptr<eGameEvent>&)>;
    void initialize(const eEventsGetter& get,
                    const eEventAdder& add,
                    const eEventRemover& remove);
private:
    const eGameEventBranch mBranch;
};

#endif // EEVENTSELECTIONWIDGET_H
