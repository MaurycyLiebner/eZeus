#include "epathfindtask.h"

#include "engine/epathfinder.h"

ePathFindTask::ePathFindTask(const eTileGetter& startTile,
                             const eTileChecker& tileWalkable,
                             const eTileChecker& endTile,
                             const eFinishFunc& finishFunc,
                             const eFailFunc& failFunc,
                             const bool onlyDiagonal,
                             const int range) :
    mStartTile(startTile),
    mTileWalkable(tileWalkable),
    mEndTile(endTile),
    mFinish(finishFunc),
    mFailFunc(failFunc),
    mOnlyDiagonal(onlyDiagonal),
    mRange(range) {

}

void ePathFindTask::run(eThreadBoard& data) {
    const auto t = mStartTile(data);
    ePathFinder pf0(
    [&](eTileBase* const t) {
        return mTileWalkable(static_cast<eThreadTile*>(t));
    },
    [&](eTileBase* const t) {
        return mEndTile(static_cast<eThreadTile*>(t));
    });
    mR = pf0.findPath(t, mRange, mPath, mOnlyDiagonal);
}

void ePathFindTask::finish() {
    if(mR) mFinish(mPath);
    else mFailFunc();
}
