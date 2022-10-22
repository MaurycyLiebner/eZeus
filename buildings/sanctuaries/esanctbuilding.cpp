#include "esanctbuilding.h"

#include "textures/egametextures.h"
#include "esanctuary.h"

eSanctBuilding::eSanctBuilding(const eSanctCost& cost,
                               const int maxProgress,
                               eGameBoard& board,
                               const eBuildingType type,
                               const int sw, const int sh) :
    eBuilding(board, type, sw, sh),
    mMaxProgress(maxProgress),
    mCost(cost) {
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

void eSanctBuilding::setSanctuary(eSanctuary* const s) {
    mSanctuary = s;
}

void eSanctBuilding::read(eReadStream& src) {
    eBuilding::read(src);

    src >> mCost.fMarble;
    src >> mCost.fSculpture;
    src >> mCost.fWood;

    src >> mStored.fMarble;
    src >> mStored.fSculpture;
    src >> mStored.fWood;

    src >> mProgress;
}

void eSanctBuilding::write(eWriteStream& dst) const {
    eBuilding::write(dst);

    dst << mCost.fMarble;
    dst << mCost.fSculpture;
    dst << mCost.fWood;

    dst << mStored.fMarble;
    dst << mStored.fSculpture;
    dst << mStored.fWood;

    dst << mProgress;
}
