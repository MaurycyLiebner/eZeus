#ifndef EPATHFINDTASK_H
#define EPATHFINDTASK_H

#include "engine/etask.h"
#include "engine/thread/ethreadtile.h"
#include "engine/thread/ethreaddata.h"

class ePathFindTask : public eTask {
public:
    using ePath = std::vector<eOrientation>;
    using eTileGetter = std::function<eThreadTile*(eThreadBoard&)>;
    using eTileChecker = std::function<bool(eThreadTile*)>;
    using eFinishFunc = std::function<void(const ePath&)>;
    using eFailFunc = std::function<void()>;
    using eTileDistance = std::function<int(eTileBase* const)>;
    ePathFindTask(const eTileGetter& startTile,
                  const stdsptr<eWalkableObject>& tileWalkable,
                  const eTileChecker& endTile,
                  const eFinishFunc& finishFunc,
                  const eFailFunc& failFunc,
                  const bool onlyDiagonal,
                  const int range,
                  const eTileDistance& distance = nullptr);
protected:
    void run(eThreadBoard& data);
    void finish();
private:
    const eTileGetter mStartTile;
    const stdsptr<eWalkableObject> mTileWalkable;
    const eTileChecker mEndTile;
    const eFinishFunc mFinish;
    const eFailFunc mFailFunc;
    const bool mOnlyDiagonal;
    const int mRange;
    const eTileDistance mDistance;

    bool mR{false};
    ePath mPath;
};

#endif // EPATHFINDTASK_H
