#include "eresourcecollectbuilding.h"

#include "characters/eresourcecollector.h"
#include "characters/actions/ecollectresourceaction.h"
#include "textures/egametextures.h"

eResourceCollectBuilding::eResourceCollectBuilding(eGameBoard& board,
        const eBaseTex baseTex,
        const double overlayX,
        const double overlayY,
        const eOverlays overlays,
        const eCharGenerator& charGen,
        const eBuildingType type,
        const eHasResource& hr,
        const eTranformFunc& tf,
        const int sw, const int sh,
        const eResourceType resType) :
    eResourceBuildingBase(board, type, sw, sh, resType),
    mCharGenerator(charGen),
    mTextures(eGameTextures::buildings()),
    mBaseTex(baseTex), mOverlays(overlays),
    mOverlayX(overlayX), mOverlayY(overlayY),
    mHasRes(hr), mTransFunc(tf) {

}

eTexture eResourceCollectBuilding::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].*mBaseTex;
}

std::vector<eOverlay> eResourceCollectBuilding::
    getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& coll = mTextures[sizeId].*mOverlays;
    const int texId = textureTime() % coll.size();
    eOverlay o;
    o.fTex = coll.getTexture(texId);
    o.fX = mOverlayX;
    o.fY = mOverlayY;
    return std::vector<eOverlay>({o});
}


void eResourceCollectBuilding::timeChanged() {
    eResourceBuildingBase::timeChanged();
    if(!mCollector && time() > mSpawnTime) {
        spawn();
        mSpawnTime = time() + mWaitTime;
    }
}

void eResourceCollectBuilding::spawn() {
    const auto t = tile();
    mCollector = mCharGenerator();
    mCollector->changeTile(t);
    const eStdPointer<eResourceCollectBuilding> tptr(this);
    const auto finishAct = [tptr, this]() {
        if(!tptr) return;
        if(mCollector) {
            add(resourceType(), mCollector->collected());
            mCollector->changeTile(nullptr);
            mCollector.reset();
        }
        mSpawnTime = time() + mWaitTime;
    };

    const auto a = e::make_shared<eCollectResourceAction>(
                       tileRect(), mCollector.get(), mHasRes,
                       mTransFunc, finishAct, finishAct);
    mCollector->setAction(a);
}
