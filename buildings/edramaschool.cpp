#include "edramaschool.h"

#include "characters/egymnast.h"
#include "characters/actions/epatrolaction.h"
#include "textures/egametextures.h"

eDramaSchool::eDramaSchool() :
    eBuilding(eBuildingType::dramaSchool, 3, 3),
    mTextures(eGameTextures::buildings()) {

}

eTexture eDramaSchool::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].fDramaSchool;
}

std::vector<eOverlay> eDramaSchool::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& coll = mTextures[sizeId].fDramaSchoolOverlay;
    const int texId = textureTime() % coll.size();
    eOverlay o;
    o.fTex = coll.getTexture(texId);
    o.fX = -3.08;
    o.fY = -4.51;
    return std::vector<eOverlay>({o});
}
