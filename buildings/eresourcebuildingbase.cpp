#include "eresourcebuildingbase.h"

eResourceBuildingBase::eResourceBuildingBase(
        eGameBoard& board,
        const eBuildingType type,
        const int sw, const int sh,
        const eResourceType resType) :
    eBuilding(board, type, sw, sh), mResType(resType) {

}

int eResourceBuildingBase::incResource(const int by) {
    const int r = std::clamp(mResource + by, 0, mMaxResource);
    const int result = mResource - r;
    mResource = r;
    return result;
}

void eResourceBuildingBase::timeChanged() {
    if(!mSpawned && mResource > 0 && time() > mSpawnTime) {
        mSpawned = spawn();
        mSpawnTime = time() + mWaitTime;
    }
}

bool eResourceBuildingBase::spawn() {

}
