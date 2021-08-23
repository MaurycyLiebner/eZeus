#include "eprocessingbuilding.h"

#include "characters/actions/ecarttransporteraction.h"

eProcessingBuilding::eProcessingBuilding(
        eGameBoard& board,
        const eBuildingType type,
        const int sw, const int sh,
        const eResourceType rawMaterial,
        const eResourceType product) :
    eResourceBuildingBase(board, type, sw, sh, product),
    mRawMaterial(rawMaterial) {

}

void eProcessingBuilding::timeChanged() {
    if(!mSpawned && mRawCount < mMaxRaw && time() > mSpawnTime) {
        mSpawned = spawnRawGetter();
        mSpawnTime = time() + mSpawnWaitTime;
    }
    if(time() > mProcessTime) {
        if(mRawCount > 0) {
            const int c = add(resourceType(), 1);
            if(c == 1) mRawCount--;
        }
        mProcessTime = time() + mProcessWaitTime;
    }
    eResourceBuildingBase::timeChanged();
}

int eProcessingBuilding::count(const eResourceType type) const {
    if(type == mRawMaterial) return mRawCount;
    return eResourceBuildingBase::count(type);
}

int eProcessingBuilding::add(const eResourceType type, const int count) {
    if(type == mRawMaterial) {
        const int r = std::clamp(mRawCount + count, 0, mMaxRaw);
        const int result = mRawCount - r;
        mRawCount = r;
        return result;
    }
    return eResourceBuildingBase::add(type, count);
}

int eProcessingBuilding::spaceLeft(const eResourceType type) const {
    if(type == mRawMaterial) return mMaxRaw - mRawCount;
    return eResourceBuildingBase::spaceLeft(type);
}

bool eProcessingBuilding::spawnRawGetter() {
    if(mRawCart) depositRaw();
    if(mRawCount >= mMaxRaw) return false;
    const auto t = tile();
    if(!mRawCart) mRawCart = new eCartTransporter(getBoard());
    mRawCart->setTile(t);
    const auto failAct = [this] {
        mSpawned = false;
        if(mRawCart->dead()) {
            mSpawnTime = time() + mSpawnWaitTime;
        } else {
            killCart();
        }
        mRawCart = nullptr;
    };
    const auto finishAct = [this]() {
        depositRaw();
    };
    const auto a = new eCartTransporterAction(
                       tileRect(),
                       mRawCart, eCartActionType::take,
                       mRawMaterial,
                       failAct, finishAct);
    mRawCart->setAction(a);
    t->addCharacter(mRawCart);
    return true;
}

void eProcessingBuilding::depositRaw() {
    if(mRawCount >= mMaxRaw) return;
    const auto type = mRawCart->resourceType();
    const int count = mRawCart->resourceCount();
    const int added = add(type, count);
    mRawCart->setResource(type, count - added);
    const int newCount = mRawCart->resourceCount();
    if(newCount == 0) {
        killCart();
    } else {
        mRawCart->setActionType(eCharacterActionType::stand);
    }
}

void eProcessingBuilding::killCart() {
    mSpawned = false;
    mSpawnTime = time() + mSpawnWaitTime;
    const auto t = mRawCart->tile();
    t->removeCharacter(mRawCart);
    delete mRawCart;
    mRawCart = nullptr;
}
