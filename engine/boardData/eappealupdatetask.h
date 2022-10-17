#ifndef EAPPEALUPDATETASK_H
#define EAPPEALUPDATETASK_H

#include "../etask.h"

#include <functional>

#include "eheatmap.h"

class eAppealUpdateTask : public eTask {
public:
    using eFunc = std::function<void(eHeatMap&)>;
    eAppealUpdateTask(const eFunc& finish);

    void run(eThreadBoard& board);
    void finish();
private:
    const eFunc mFinish;

    eHeatMap mMap;
};

#endif // EAPPEALUPDATETASK_H
