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
    if(resource() >= maxResource()) return false;
    auto dirs = gExtractDirections(eMoveDirection::allDirections);
    if(dirs.empty()) return false;
    std::random_shuffle(dirs.begin(), dirs.end());
    eTile* t = nullptr;
    for(const auto dir : dirs) {
        t = tileNeighbour(dir, [](eTile* const tile) {
            return tile->walkable();
        });
        if(t) break;
    }
    if(!t) return false;

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
    const auto a = new eCartTransporterAction(
                       h, eCartActionType::give, mResType,
                       finishAct, finishAct);
    h->setAction(a);
    t->addCharacter(h);
    return true;
}
