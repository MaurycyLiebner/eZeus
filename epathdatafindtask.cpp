#include "epathdatafindtask.h"

ePathDataFindTask::ePathDataFindTask(
        const eTileGetter& startTile,
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
    mRange(range) {}

void ePathDataFindTask::run(eThreadBoard& data) {
    const auto t = mStartTile(data);
    ePathFinder pf0(
    [&](eTileBase* const t) {
        return mTileWalkable(static_cast<eThreadTile*>(t));
    },
    [&](eTileBase* const t) {
        return mEndTile(static_cast<eThreadTile*>(t));
    });
    const bool r = pf0.findPath(t, mRange, mOnlyDiagonal,
                                data.width(), data.height());
    if(r) {
        mR = pf0.extractData(mData);
    } else {
        mR = false;
    }
}

void ePathDataFindTask::finish() {
    if(mR) mFinish(mData);
    else mFailFunc();
}
