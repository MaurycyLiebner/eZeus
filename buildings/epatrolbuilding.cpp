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
                                 const int sw, const int sh,
                                 const int maxEmployees) :
    eEmployingBuilding(board, type, sw, sh, maxEmployees),
    mCharGenerator(charGen),
    mActGenerator(actGen),
    mTextures(eGameTextures::buildings()),
    mBaseTex(baseTex), mOverlays(overlays),
    mOverlayX(overlayX), mOverlayY(overlayY) {

}

stdsptr<eCharacterAction> gDefaultActGenerator(
           eCharacter* const c,
           const std::vector<ePatrolGuide>& guides,
           const eAction& failAction,
           const eAction& finishActio) {
    return e::make_shared<ePatrolAction>(
                c, guides, failAction, finishActio);
}

ePatrolBuilding::ePatrolBuilding(eGameBoard& board,
                                 const eBaseTex baseTex,
                                 const double overlayX,
                                 const double overlayY,
                                 const eOverlays overlays,
                                 const eCharGenerator& charGen,
                                 const eBuildingType type,
                                 const int sw, const int sh,
                                 const int maxEmployees) :
    ePatrolBuilding(board, baseTex, overlayX, overlayY,
                    overlays, charGen, gDefaultActGenerator,
                    type, sw, sh, maxEmployees) {

}

eTexture ePatrolBuilding::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].*mBaseTex;
}

std::vector<eOverlay> ePatrolBuilding::getOverlays(const eTileSize size) const {
    if(!mOverlays) return {};
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
    if(!mChar && t >= mSpawnTime) {
        spawn();
        mSpawnTime = time() + mWaitTime;
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

    mChar = mCharGenerator();
    if(!mChar) return false;
    mChar->changeTile(t);
    const eStdPointer<ePatrolBuilding> tptr(this);
    const eStdPointer<eCharacter> cptr(mChar);
    const auto finishAct = [tptr, this, cptr]() {
        if(cptr) cptr->changeTile(nullptr);
        if(tptr) {
            mChar.reset();
            mSpawnTime = time() + mWaitTime;
        }
    };
    const auto a = mActGenerator(mChar.get(), mPatrolGuides,
                                 finishAct, finishAct);
    mChar->setAction(a);
    return true;
}
