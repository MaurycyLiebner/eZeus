#include "etradepost.h"

#include "textures/egametextures.h"

eTradePost::eTradePost(eGameBoard& board, eWorldCity& city) :
    eWarehouseBase(board, eBuildingType::tradePost, 4, 4, 24,
                   eResourceType::warehouse, 15),
    mCity(city) {
    setOverlayEnabledFunc([]() { return true; });
    setOrders(eResourceType::none, eResourceType::none);
}

std::shared_ptr<eTexture> eTradePost::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    return blds[sizeId].fTradingPost;
}

std::vector<eOverlay> eTradePost::getOverlays(const eTileSize size) const {
    std::vector<eOverlay> os;
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    const auto texs = blds[sizeId];
    if(enabled()) {
        const auto& coll = texs.fTradingPostOverlay;
        const int texId = textureTime() % coll.size();
        auto& o = os.emplace_back();
        o.fTex = coll.getTexture(texId);
        o.fX = -3.1;
        o.fY = -7.2;
    }
    const eXY xy = {{-1.5, -3.5},
                    {-1.5, -2.5},
                    {-1.5, -1.5},

                    {-0.5, -4.5},
                    {-0.5, -3.5},
                    {-0.5, -2.5},
                    {-0.5, -1.5},

                    {0.5, -4.5},
                    {0.5, -3.5},
                    {0.5, -2.5},
                    {0.5, -1.5},

                    {1.5, -4.5},
                    {1.5, -3.5},
                    {1.5, -2.5},
                    {1.5, -1.5}};

    getSpaceOverlays(size, os, xy);

    return os;
}

void eTradePost::setOrders(const eResourceType imports,
                           const eResourceType exports) {
    mImports = imports;
    mExports = exports;

    eStorageBuilding::setOrders(mExports, mImports, eResourceType::none);
}

void eTradePost::getOrders(eResourceType& imports,
                           eResourceType& exports) const {
    imports = mImports;
    exports = mExports;
}
