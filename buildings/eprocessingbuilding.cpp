#include "eprocessingbuilding.h"

#include "characters/actions/ecarttransporteraction.h"
#include "textures/egametextures.h"

eProcessingBuilding::eProcessingBuilding(
        eGameBoard& board,
        const eBaseTex baseTex,
        const double overlayX,
        const double overlayY,
        const eOverlays overlays,
        const eBuildingType type,
        const int sw, const int sh,
        const int maxEmployees,
        const eResourceType rawMaterial,
        const eResourceType product,
        const int rawUse,
        const int time) :
    eResourceBuildingBase(board, type, sw, sh, maxEmployees, product),
    mTextures(eGameTextures::buildings()),
    mBaseTex(baseTex), mOverlays(overlays),
    mOverlayX(overlayX), mOverlayY(overlayY),
    mRawMaterial(rawMaterial), mRawUse(rawUse),
    mProcessWaitTime(5000*time) {

}

eTexture eProcessingBuilding::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].*mBaseTex;
}

std::vector<eOverlay> eProcessingBuilding::getOverlays(
        const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& coll = mTextures[sizeId].*mOverlays;
    const int texId = textureTime() % coll.size();
    eOverlay o;
    o.fTex = coll.getTexture(texId);
    o.fX = mOverlayX;
    o.fY = mOverlayY;
    return std::vector<eOverlay>({o});
}

void eProcessingBuilding::timeChanged() {
    if(!mRawCart && mRawCount < mMaxRaw && time() > mSpawnTime) {
        spawnRawGetter();
        mSpawnTime = time() + mSpawnWaitTime;
    }
    if(time() > mProcessTime) {
        if(mRawCount >= mRawUse) {
            const int c = add(resourceType(), 1);
            mRawCount -= c*mRawUse;
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
        const int result = r - mRawCount;
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
    if(!mRawCart) mRawCart = e::make_shared<eCartTransporter>(getBoard());
    mRawCart->changeTile(t);
    const eStdPointer<eProcessingBuilding> tptr(this);
    const eStdPointer<eProcessingBuilding> rcptr(this);
    const auto failAct = [tptr, this] {
        if(!tptr) return;
        if(mRawCart && mRawCart->dead()) {
            mSpawnTime = time() + mSpawnWaitTime;
            mRawCart.reset();
        } else {
            killCart();
        }
    };
    const auto finishAct = [tptr, this]() {
        if(tptr) depositRaw();
    };
    const auto a = e::make_shared<eCartTransporterAction>(
                       tileRect(), mRawCart.get(),
                       eCartActionType::take,
                       mRawMaterial,
                       failAct, finishAct);
    mRawCart->setAction(a);
    return true;
}

void eProcessingBuilding::depositRaw() {
    if(!mRawCart) return;
    if(mRawCount >= mMaxRaw) return;
    const auto type = mRawCart->resourceType();
    const int count = mRawCart->resourceCount();
    const int added = add(type, count);
    mRawCart->setResource(type, count - added);
    const int newCount = mRawCart->resourceCount();
    if(newCount <= 0) {
        killCart();
    } else {
        mRawCart->setActionType(eCharacterActionType::stand);
    }
}

void eProcessingBuilding::killCart() {
    mSpawnTime = time() + mSpawnWaitTime;
    mRawCart->changeTile(nullptr);
    mRawCart.reset();
}
