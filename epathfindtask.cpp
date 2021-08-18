#include "epathfindtask.h"

#include "engine/epathfinder.h"

ePathFindTask::ePathFindTask(const eTileGetter& startTile,
                             const eTileChecker& tileWalkable,
                             const eTileChecker& endTile,
                             const eFinishFunc& finishFunc,
                             const eFailFunc& failFunc,
                             const int range) :
    mStartTile(startTile),
    mTileWalkable(tileWalkable),
    mEndTile(endTile),
    mFinish(finishFunc),
    mFailFunc(failFunc),
    mRange(range) {

}

void ePathFindTask::run(eThreadBoard& data) {
    const auto t = mStartTile(data);
    const auto pf0 = ePathFinder(t, mTileWalkable, mEndTile);
    mR = pf0.findPath(mRange, mPath, false);
}

void ePathFindTask::finish() {
    if(mR) mFinish(mPath);
    else mFailFunc();
}