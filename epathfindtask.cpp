#include "epathfindtask.h"

#include "engine/epathfinder.h"
#include "engine/eknownendpathfinder.h"
#include "characters/actions/walkable/ewalkableobject.h"
#include "ewalkablehelpers.h"

using eTileDistance = std::function<int(eTileBase* const)>;
eTileDistance tileDist(const stdsptr<eWalkableObject>& w,
                       const eTileDistance& d) {
    if(!d && w && w->rootType() == eWalkableObjectType::roadAvenue) {
        return eWalkableHelpers::sRoadAvenueTileDistance;
    } else {
        return d;
    }
}

ePathFindTask::ePathFindTask(const eTileGetter& startTile,
                             const stdsptr<eWalkableObject>& tileWalkable,
                             const eTileChecker& endTileFunc,
                             const eFinishFunc& finishFunc,
                             const eFailFunc& failFunc,
                             const bool onlyDiagonal,
                             const int range,
                             const eTileDistance& distance,
                             const eTileGetter& endTile,
                             const bool findAll) :
    mStartTile(startTile),
    mEndTile(endTile),
    mTileWalkable(tileWalkable),
    mEndTileFunc(endTileFunc),
    mFinish(finishFunc),
    mFailFunc(failFunc),
    mOnlyDiagonal(onlyDiagonal),
    mRange(range),
    mDistance(tileDist(tileWalkable, distance)),
    mFindAll(findAll) {}

void ePathFindTask::run(eThreadBoard& data) {
    if(mEndTile) {
        const auto startT = mStartTile(data);
        const auto endT = mEndTile(data);
        eKnownEndPathFinder pf0(
        [&](eTileBase* const t) {
            return mTileWalkable->walkable(t);
        }, endT);
        if(mFindAll) pf0.setMode(ePathFinderMode::findAll);
        const bool r = pf0.findPath(startT, mRange, mOnlyDiagonal,
                                    data.width(), data.height(),
                                    mDistance);
        if(r) {
            mR = pf0.extractPath(mPath);
        } else {
            mR = false;
        }
    } else if(mEndTileFunc) {
        const auto t = mStartTile(data);
        ePathFinder pf0(
        [&](eTileBase* const t) {
            return mTileWalkable->walkable(t);
        },
        [&](eTileBase* const t) {
           return mEndTileFunc(static_cast<eThreadTile*>(t));
        });
        if(mFindAll) pf0.setMode(ePathFinderMode::findAll);
        const bool r = pf0.findPath(t, mRange, mOnlyDiagonal,
                                    data.width(), data.height(),
                                    mDistance);
        if(r) {
            mR = pf0.extractPath(mPath);
        } else {
            mR = false;
        }
    }
}

void ePathFindTask::finish() {
    if(mR) mFinish(mPath);
    else mFailFunc();
}
