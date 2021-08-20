#include "eresourcecollectbuilding.h"

#include "characters/eresourcecollector.h"
#include "characters/actions/ecollectresourceaction.h"
#include "textures/egametextures.h"

eResourceCollectBuilding::eResourceCollectBuilding(
        eGameBoard& board,
        const eBaseTex baseTex,
        const double overlayX,
        const double overlayY,
        const eOverlays overlays,
        const eCharGenerator& charGen,
        const eBuildingType type,
        const eHasResource& hr,
        const eTranformFunc& tf,
        const int sw, const int sh) :
    eResourceBuildingBase(board, type, sw, sh),
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
    if(!mSpawned && time() > mSpawnTime) {
        mSpawned = spawn();
        mSpawnTime = time() + mWaitTime;
    }
}

bool eResourceCollectBuilding::spawn() {
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

    const auto d = mCharGenerator();
    d->setTile(t);
    const auto finishAct = [this, d]() {
        incResource(d->collected());
        const auto t = d->tile();
        t->removeCharacter(d);
        mSpawned = false;
        mSpawnTime = time() + mWaitTime;
        delete d;
    };

    const auto a = new eCollectResourceAction(d, mHasRes,
                                              mTransFunc,
                                              finishAct,
                                              finishAct);
    d->setAction(a);
    t->addCharacter(d);
    return true;
}
