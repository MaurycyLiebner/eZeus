#include "esanctbuilding.h"

#include "textures/egametextures.h"
#include "esanctuary.h"

eSanctBuilding::eSanctBuilding(eSanctuary* const s,
                               const eSanctCost& cost,
                               const int maxProgress,
                               eGameBoard& board,
                               const eBuildingType type,
                               const int sw, const int sh) :
    eBuilding(board, type, sw, sh),
    mMaxProgress(maxProgress),
    mSanctuary(s), mCost(cost) {
    setOverlayEnabledFunc([]() { return true; });
}

void eSanctBuilding::erase() {
    mSanctuary->erase();
}

bool eSanctBuilding::resourcesAvailable() const {
    if(finished()) return false;
    const auto s = mSanctuary->stored();
    if(s.fMarble < mCost.fMarble - mStored.fMarble) return false;
    if(s.fWood < mCost.fWood - mStored.fWood) return false;
    if(s.fSculpture < mCost.fSculpture - mStored.fSculpture) return false;
    return true;
}

bool eSanctBuilding::finished() const {
    return mProgress >= mMaxProgress;
}

bool eSanctBuilding::incProgress() {
    if(mProgress >= mMaxProgress) return false;
    if(mProgress == 0) {
        mSanctuary->useResources(mCost);
        mStored = mCost;
    }
    mProgress++;
    return true;
}

void eSanctBuilding::setCost(const eSanctCost& c) {
    mCost = c;
}
