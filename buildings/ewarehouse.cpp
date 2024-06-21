#include "ewarehouse.h"

#include "textures/egametextures.h"

eWarehouse::eWarehouse(eGameBoard& board) :
    eWarehouseBase(board, eBuildingType::warehouse, 3, 3, 12,
                   eResourceType::warehouse) {
    setOverlayEnabledFunc([]() { return true; });
}

std::shared_ptr<eTexture> eWarehouse::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    return blds[sizeId].fWarehouse;
}

std::vector<eOverlay> eWarehouse::getOverlays(const eTileSize size) const {
    std::vector<eOverlay> os;
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    const auto& texs = blds[sizeId];
    if(enabled()) {
        const auto& coll = texs.fWarehouseOverlay;
        const int texId = textureTime() % coll.size();
        auto& o = os.emplace_back();
        o.fTex = coll.getTexture(texId);
        o.fX = -1.24;
        o.fY = -4.32;
    }
    const eXY xy = {{-1, -2},
                    {-1, -1},

                    {0, -3},
                    {0, -2},
                    {0, -1},

                    {1, -3},
                    {1, -2},
                    {1, -1}};

    getSpaceOverlays(size, os, xy);

    return os;
}
