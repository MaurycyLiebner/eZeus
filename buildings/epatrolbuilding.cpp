#include "epatrolbuilding.h"

#include "characters/echaracter.h"
#include "characters/actions/epatrolaction.h"
#include "textures/egametextures.h"

ePatrolBuilding::ePatrolBuilding(eGameBoard& board,
                                 const eBaseTex baseTex,
                                 const double overlayX,
                                 const double overlayY,
                                 const eOverlays overlays,
                                 const eCharGenerator& charGen,
                                 const eActGenerator& actGen,
                                 const eBuildingType type,
                                 const int sw, const int sh) :
    eBuilding(board, type, sw, sh),
    mCharGenerator(charGen),
    mActGenerator(actGen),
    mTextures(eGameTextures::buildings()),
    mBaseTex(baseTex), mOverlays(overlays),
    mOverlayX(overlayX), mOverlayY(overlayY) {

}

eCharacterAction* gDefaultActGenerator(
           eCharacter* const c,
           const std::vector<ePatrolGuide>& guides,
           const eAction& failAction,
           const eAction& finishActio) {
    return new ePatrolAction(c, guides, failAction, finishActio);
}

ePatrolBuilding::ePatrolBuilding(eGameBoard& board,
                                 const eBaseTex baseTex,
                                 const double overlayX,
                                 const double overlayY,
                                 const eOverlays overlays,
                                 const eCharGenerator& charGen,
                                 const eBuildingType type,
                                 const int sw, const int sh) :
    ePatrolBuilding(board, baseTex, overlayX, overlayY,
                    overlays, charGen, gDefaultActGenerator,
                    type, sw, sh) {

}

eTexture ePatrolBuilding::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].*mBaseTex;
}

std::vector<eOverlay> ePatrolBuilding::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& coll = mTextures[sizeId].*mOverlays;
    const int texId = textureTime() % coll.size();
    eOverlay o;
    o.fTex = coll.getTexture(texId);
    o.fX = mOverlayX;
    o.fY = mOverlayY;
    return std::vector<eOverlay>({o});
}

void ePatrolBuilding::timeChanged() {
    const int t = time();
    if(!mSpawned && t >= mSpawnTime) {
        mSpawned = spawn();
        mSpawnTime = t + mWaitTime;
    }
}

void ePatrolBuilding::setPatrolGuides(const ePatrolGuides &g) {
    mPatrolGuides = g;
}

void ePatrolBuilding::setSpawnDirection(const eMoveDirection d) {
    mSpawnDirection = d;
}

bool ePatrolBuilding::spawn() {
    auto dirs = gExtractDirections(mSpawnDirection);
    if(dirs.empty()) return false;
    std::random_shuffle(dirs.begin(), dirs.end());
    eTile* t = nullptr;
    for(const auto dir : dirs) {
        t = road(dir);
        if(t) break;
    }
    if(!t) return false;

    const auto c = mCharGenerator();
    c->changeTile(t);
    const auto finishAct = [this, c]() {
        const auto t = c->tile();
        t->removeCharacter(c);
        mSpawned = false;
        delete c;
    };
    c->setAction(mActGenerator(c, mPatrolGuides, finishAct, finishAct));
    return true;
}
