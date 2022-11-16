#include "epathfindtask.h"

#include "engine/epathfinder.h"
#include "characters/actions/walkable/ewalkableobject.h"

ePathFindTask::ePathFindTask(const eTileGetter& startTile,
                             const stdsptr<eWalkableObject>& tileWalkable,
                             const eTileChecker& endTile,
                             const eFinishFunc& finishFunc,
                             const eFailFunc& failFunc,
                             const bool onlyDiagonal,
                             const int range,
                             const eTileDistance& distance) :
    mStartTile(startTile),
    mTileWalkable(tileWalkable),
    mEndTile(endTile),
    mFinish(finishFunc),
    mFailFunc(failFunc),
    mOnlyDiagonal(onlyDiagonal),
    mRange(range),
    mDistance(distance) {}

void ePathFindTask::run(eThreadBoard& data) {
    const auto t = mStartTile(data);
    ePathFinder pf0(
    [&](eTileBase* const t) {
        return mTileWalkable->walkable(t);
    },
    [&](eTileBase* const t) {
        return mEndTile(static_cast<eThreadTile*>(t));
    });
    const bool r = pf0.findPath(t, mRange, mOnlyDiagonal,
                                data.width(), data.height(),
                                mDistance);
    if(r) {
        mR = pf0.extractPath(mPath);
    } else {
        mR = false;
    }
}

void ePathFindTask::finish() {
    if(mR) mFinish(mPath);
    else mFailFunc();
}
