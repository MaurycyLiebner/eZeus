#include "einventorsworkshop.h"

#include "textures/egametextures.h"

eInventorsWorkshop::eInventorsWorkshop(eGameBoard& board) :
    eEmployingBuilding(board, eBuildingType::inventorsWorkshop, 3, 3, 12) {
    eGameTextures::loadInventorsWorkshop();
}

std::shared_ptr<eTexture> eInventorsWorkshop::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    return blds[sizeId].fInventorsWorkshop;
}

std::vector<eOverlay> eInventorsWorkshop::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    const auto& coll = blds[sizeId].fInventorsWorkshopOverlay;
    const int texId = textureTime() % coll.size();
    eOverlay o;
    o.fTex = coll.getTexture(texId);
    o.fX = -1.08;
    o.fY = -4.61;
    return std::vector<eOverlay>({o});
}
