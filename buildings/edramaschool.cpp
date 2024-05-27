#include "edramaschool.h"

#include "characters/egymnast.h"
#include "textures/egametextures.h"

eDramaSchool::eDramaSchool(eGameBoard& board) :
    eEmployingBuilding(board, eBuildingType::dramaSchool, 3, 3, 10),
    mTextures(eGameTextures::buildings()) {
    eGameTextures::loadDramaSchool();
}

std::shared_ptr<eTexture> eDramaSchool::getTexture(const eTileSize size) const {
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
