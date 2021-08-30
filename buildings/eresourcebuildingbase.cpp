#include "eresourcebuildingbase.h"

#include "characters/actions/ecarttransporteraction.h"

eResourceBuildingBase::eResourceBuildingBase(
        eGameBoard& board,
        const eBuildingType type,
        const int sw, const int sh,
        const int maxEmployees,
        const eResourceType resType) :
    eBuildingWithResource(board, type, sw, sh, maxEmployees),
    mResType(resType) {

}

int eResourceBuildingBase::add(const eResourceType type,
                               const int count) {
    if(type != mResType) return 0;

    const int r = std::clamp(mResource + count, 0, mMaxResource);
    const int result = r - mResource;
    mResource = r;
    return result;
}

int eResourceBuildingBase::take(const eResourceType type,
                                const int count) {
    if(type != mResType) return 0;

    const int result = std::clamp(count, 0, mResource);
    mResource -= result;
    return result;
}

int eResourceBuildingBase::count(const eResourceType type) const {
    if(type != mResType) return 0;
    return mResource;
}

int eResourceBuildingBase::spaceLeft(const eResourceType type) const {
    if(type != mResType) return 0;
    return mMaxResource - mResource;
}

void eResourceBuildingBase::timeChanged() {
    if(!mCart && mResource > 0 && time() > mCartSpawnTime) {
        mCartSpawnTime = time() + mCartWaitTime;
        spawnCart();
    }
}

bool eResourceBuildingBase::spawnCart() {
    return spawnGiveCart(mCart, mCartSpawnTime, mCartWaitTime, mResType);
}
