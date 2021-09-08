#ifndef EAPPEALUPDATETASK_H
#define EAPPEALUPDATETASK_H

#include "../etask.h"

#include <functional>

#include "eappealmap.h"

class eAppealUpdateTask : public eTask {
public:
    using eFunc = std::function<void(eAppealMap&)>;
    eAppealUpdateTask(const eFunc& finish);

    void run(eThreadBoard& board);
    void finish();
private:
    const eFunc mFinish;

    eAppealMap mMap;
};

#endif // EAPPEALUPDATETASK_H
