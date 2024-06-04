#include "euniversity.h"

#include "textures/egametextures.h"

eUniversity::eUniversity(eGameBoard& board) :
    eEmployingBuilding(board, eBuildingType::university, 3, 3, 12) {
    eGameTextures::loadUniversity();
}

std::shared_ptr<eTexture> eUniversity::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    return blds[sizeId].fUniversity;
}

std::vector<eOverlay> eUniversity::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    const auto& coll = blds[sizeId].fUniversityOverlay;
    const int texId = textureTime() % coll.size();
    eOverlay o;
    o.fTex = coll.getTexture(texId);
    o.fX = -3.25;
    o.fY = -4.00;
    return std::vector<eOverlay>({o});
}
