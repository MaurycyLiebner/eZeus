#include "esanctbuilding.h"

#include "textures/egametextures.h"

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

bool eSanctBuilding::incProgress() {
    if(mProgress >= mMaxProgress) return false;
    mProgress++;
    return true;
}

void eSanctBuilding::setCost(const eSanctCost& c) {
    mCost = c;
}
