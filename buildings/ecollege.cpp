#include "ecollege.h"

#include "characters/egymnast.h"
#include "characters/actions/epatrolaction.h"
#include "textures/egametextures.h"

eCollege::eCollege() :
    eBuilding(eBuildingType::college, 3, 3),
    mTextures(eGameTextures::buildings()) {

}

eTexture eCollege::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].fCollege;
}

std::vector<eOverlay> eCollege::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& coll = mTextures[sizeId].fCollegeOverlay;
    const int texId = textureTime() % coll.size();
    eOverlay o;
    o.fTex = coll.getTexture(texId);
    o.fX = -2.7;
    o.fY = -4.38;
    return std::vector<eOverlay>({o});
}
