#include "egymnasium.h"

#include "characters/egymnast.h"
#include "characters/actions/epatrolaction.h"
#include "textures/egametextures.h"

eGymnasium::eGymnasium() :
    eBuilding(eBuildingType::gymnasium, 3, 3),
    mTextures(eGameTextures::buildings()) {

}

eTexture eGymnasium::getTexture(const eTileSize size) const {
    const int spawnFreq = 5000;
    if(time() % spawnFreq == 0) spawn();
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].fGymnasium;
}

std::vector<eOverlay> eGymnasium::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& coll = mTextures[sizeId].fGymnasiumOverlay;
    const int texId = (time()/4) % coll.size();
    eOverlay o;
    o.fTex = coll.getTexture(texId);
    o.fX = 0.30;
    o.fY = -1.7;
    return std::vector<eOverlay>({o});
}

void eGymnasium::setPatrolGuides(const ePatrolGuides &g) {
    mPatrolGuides = g;
}

void eGymnasium::spawn() const {
    const auto o = directionToOrientation(mSpawnDirection);
    const auto t = road(o);
    if(!t) return;

    const auto d = new eGymnast();
    d->setTile(t);
    d->setX(0.5);
    d->setY(0.5);
    d->setCharAction(new ePatrolAction(d, []() {}, []() {}));
    t->addCharacter(d);
}
