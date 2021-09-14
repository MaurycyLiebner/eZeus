#include "eshepherbuildingbase.h"

#include "textures/egametextures.h"
#include "characters/actions/eshepherdaction.h"

eShepherBuildingBase::eShepherBuildingBase(
        eGameBoard& board,
        const eBaseTex baseTex,
        const double overlayX,
        const double overlayY,
        const eOverlays overlays,
        const eCharGenerator& charGen,
        const eBuildingType type,
        const eResourceType resType,
        const eCharacterType animalType,
        const int sw, const int sh,
        const int maxEmployees) :
    eResourceBuildingBase(board, type, sw, sh,
                          maxEmployees, resType),
    mCharGenerator(charGen),
    mTextures(eGameTextures::buildings()),
    mBaseTex(baseTex), mOverlays(overlays),
    mOverlayX(overlayX), mOverlayY(overlayY),
    mAnimalType(animalType) {

}

std::shared_ptr<eTexture> eShepherBuildingBase::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].*mBaseTex;
}

std::vector<eOverlay> eShepherBuildingBase::getOverlays(
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

void eShepherBuildingBase::timeChanged(const int by) {
    eResourceBuildingBase::timeChanged(by);
    if(enabled() && !mShepherd && time() > mSpawnTime) {
        spawn();
        mSpawnTime = time() + mWaitTime;
    }
}

bool eShepherBuildingBase::spawn() {
    if(resource() >= maxResource()) return false;
    const auto t = centerTile();
    mShepherd = mCharGenerator(getBoard());
    mShepherd->changeTile(t);
    const eStdPointer<eShepherBuildingBase> tptr(this);
    const auto finishAct = [tptr, this]() {
        if(!tptr) return;
        if(mShepherd) {
            add(resourceType(), mShepherd->collected());
            mShepherd->changeTile(nullptr);
            mShepherd.reset();
        }
        mSpawnTime = time() + mWaitTime;
    };
    const auto a = e::make_shared<eShepherdAction>(
                       tileRect(), mShepherd.get(),
                       mAnimalType,
                       finishAct, finishAct);
    mShepherd->setAction(a);
    return true;
}
