#include "esanctbuilding.h"

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
    scheduleTerrainUpdate();
    mSanctuary->buildingProgressed();
    return true;
}

void eSanctBuilding::destroy() {
    mProgress = 0;
    scheduleTerrainUpdate();
}

void eSanctBuilding::setSanctuary(eSanctuary* const s) {
    mSanctuary = s;
}

void eSanctBuilding::read(eReadStream& src) {
    eBuilding::read(src);

    src >> mStored.fMarble;
    src >> mStored.fSculpture;
    src >> mStored.fWood;

    src >> mProgress;
}

void eSanctBuilding::write(eWriteStream& dst) const {
    eBuilding::write(dst);

    dst << mStored.fMarble;
    dst << mStored.fSculpture;
    dst << mStored.fWood;

    dst << mProgress;
}

void eSanctBuilding::scheduleTerrainUpdate() {
    const auto bt = type();
    if(bt == eBuildingType::templeTile) {
        const auto t = centerTile();
        if(t) t->scheduleTerrainUpdate();
    }
}
