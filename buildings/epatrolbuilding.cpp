#include "epatrolbuilding.h"

#include "characters/echaracter.h"
#include "characters/actions/epatrolaction.h"
#include "textures/egametextures.h"

ePatrolBuilding::ePatrolBuilding(const eBaseTex baseTex,
                                 const double overlayX,
                                 const double overlayY,
                                 const eOverlays overlays,
                                 const eCharGenerator& charGen,
                                 const eBuildingType type,
                                 const int sw, const int sh) :
    eBuilding(type, sw, sh), mCharGenerator(charGen),
    mTextures(eGameTextures::buildings()),
    mBaseTex(baseTex), mOverlays(overlays),
    mOverlayX(overlayX), mOverlayY(overlayY) {

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
    const int spawnFreq = 5000;
    if(time() % spawnFreq == 0) spawn();
}

void ePatrolBuilding::setPatrolGuides(const ePatrolGuides &g) {
    mPatrolGuides = g;
}

void ePatrolBuilding::spawn() const {
    const auto o = directionToOrientation(mSpawnDirection);
    const auto t = road(o);
    if(!t) return;

    const auto d = mCharGenerator();
    d->setTile(t);
    d->setX(0.5);
    d->setY(0.5);
    const auto finishAct = [d]() {
        const auto t = d->tile();
        t->removeCharacter(d);
        delete d;
    };
    d->setCharAction(new ePatrolAction(d, finishAct, finishAct));
    t->addCharacter(d);
}
