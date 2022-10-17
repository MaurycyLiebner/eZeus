#ifndef EAPPEALUPDATETASK_H
#define EAPPEALUPDATETASK_H

#include "../etask.h"

#include <functional>

#include "eheatmap.h"

enum class eBuildingType;

class eAppealUpdateTask : public eTask {
public:
    using eFunc = std::function<void(eHeatMap&)>;
    using eHeatGetter = std::function<eHeat(eBuildingType)>;
    eAppealUpdateTask(const eHeatGetter& heatGetter,
                      const eFunc& finish);

    void run(eThreadBoard& board);
    void finish();
private:
    const eHeatGetter mHeatGetter;
    const eFunc mFinish;
    eHeatMap mMap;
};

#endif // EAPPEALUPDATETASK_H
