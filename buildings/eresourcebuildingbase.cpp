#include "eresourcebuildingbase.h"

#include "characters/actions/ecarttransporteraction.h"

eResourceBuildingBase::eResourceBuildingBase(
        eGameBoard& board,
        const eBuildingType type,
        const int sw, const int sh,
        const eResourceType resType) :
    eBuildingWithResource(board, type, sw, sh),
    mResType(resType) {

}

int eResourceBuildingBase::add(const eResourceType type,
                               const int count) {
    if(type != mResType) return 0;

    const int r = std::clamp(mResource + count, 0, mMaxResource);
    const int result = mResource - r;
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
    if(!mSpawned && mResource > 0 && time() > mSpawnTime) {
        mSpawned = spawn();
        mSpawnTime = time() + mWaitTime;
    }
}

bool eResourceBuildingBase::spawn() {
    if(mResource <= 0) return false;
    const auto t = tile();
    const auto h = new eCartTransporter(getBoard());
    const int took = take(mResType, 8);
    h->setResource(mResType, took);
    h->setTile(t);
    const auto finishAct = [this, h]() {
        const auto t = h->tile();
        t->removeCharacter(h);
        mSpawned = false;
        mSpawnTime = time() + mWaitTime;
        delete h;
    };
    const auto failAct = [this, finishAct, took]() {
        add(mResType, took);
        finishAct();
    };
    const auto a = new eCartTransporterAction(
                       tileRect(),
                       h, eCartActionType::give, mResType,
                       failAct, finishAct);
    h->setAction(a);
    t->addCharacter(h);
    return true;
}
