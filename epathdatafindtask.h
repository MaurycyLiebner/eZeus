#ifndef EPATHDATAFINDTASK_H
#define EPATHDATAFINDTASK_H

#include "engine/etask.h"
#include "engine/thread/ethreadtile.h"
#include "engine/thread/ethreaddata.h"
#include "engine/epathfinder.h"

class ePathDataFindTask : public eTask {
public:
    using eTileGetter = std::function<eThreadTile*(eThreadBoard&)>;
    using eTileChecker = std::function<bool(eThreadTile*)>;
    using eFinishFunc = std::function<void(const ePathFindData&)>;
    using eFailFunc = std::function<void()>;
    ePathDataFindTask(const eTileGetter& startTile,
                      const eTileChecker& tileWalkable,
                      const eTileChecker& endTile,
                      const eFinishFunc& finishFunc,
                      const eFailFunc& failFunc,
                      const bool onlyDiagonal,
                      const int range);
protected:
    void run(eThreadBoard& data);
    void finish();
private:
    const eTileGetter mStartTile;
    const eTileChecker mTileWalkable;
    const eTileChecker mEndTile;
    const eFinishFunc mFinish;
    const eFailFunc mFailFunc;
    const bool mOnlyDiagonal;
    const int mRange;

    bool mR{false};
    ePathFindData mData;
};


#endif // EPATHDATAFINDTASK_H
