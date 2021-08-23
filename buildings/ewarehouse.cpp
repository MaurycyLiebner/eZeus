#include "ewarehouse.h"

#include "textures/egametextures.h"

eWarehouse::eWarehouse(eGameBoard& board) :
    eStorageBuilding(board, eBuildingType::warehouse, 3, 3),
    mTextures(eGameTextures::buildings()) {
    setAccepts(eResourceType::allButFood | eResourceType::wheat);
}

eTexture eWarehouse::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].fWarehouse;
}

std::vector<eOverlay> eWarehouse::getOverlays(const eTileSize size) const {
    std::vector<eOverlay> os;
    const int sizeId = static_cast<int>(size);
    const auto texs = mTextures[sizeId];
    const auto& coll = texs.fWarehouseOverlay;
    const int texId = textureTime() % coll.size();
    auto& o = os.emplace_back();
    o.fTex = coll.getTexture(texId);
    o.fX = -1.20;
    o.fY = -4.32;
    const std::pair<int, int> xy[8] = {{-1, -2},
                                       {-1, -1},

                                       {0, -3},
                                       {0, -2},
                                       {0, -1},

                                       {1, -3},
                                       {1, -2},
                                       {1, -1}};
    for(int i = 0; i < 8; i++) {
        const int count = resourceCount(i);
        const auto type = resourceType(i);
        eOverlay& o = os.emplace_back();
        const auto& xxyy = xy[i];
        o.fX = xxyy.first;
        o.fY = xxyy.second;
        o.fAlignTop = true;
        if(type == eResourceType::none || count <= 0) {
            o.fTex = texs.fWarehouseEmpty;
            continue;
        }
        const int texId = std::clamp(count - 1, 0, 3);
        switch(type) {
        case eResourceType::urchin:
            o.fTex = texs.fWarehouseUrchin.getTexture(texId);
            break;
        case eResourceType::fish:
            o.fTex = texs.fWarehouseFish.getTexture(texId);
            break;
        case eResourceType::meat:
            o.fTex = texs.fWarehouseMeat.getTexture(texId);
            break;
        case eResourceType::cheese:
            o.fTex = texs.fWarehouseCheese.getTexture(texId);
            break;
        case eResourceType::carrots:
            o.fTex = texs.fWarehouseCarrots.getTexture(texId);
            break;
        case eResourceType::onions:
            o.fTex = texs.fWarehouseOnions.getTexture(texId);
            break;
        case eResourceType::wheat:
            o.fTex = texs.fWarehouseWheat.getTexture(texId);
            break;


        case eResourceType::wood:
            o.fTex = texs.fWarehouseWood.getTexture(texId);
            break;
        case eResourceType::bronze:
            o.fTex = texs.fWarehouseBronze.getTexture(texId);
            break;
        case eResourceType::marble:
            o.fTex = texs.fWarehouseMarble.getTexture(texId);
            break;
        case eResourceType::grapes:
            o.fTex = texs.fWarehouseGrapes.getTexture(texId);
            break;
        case eResourceType::olives:
            o.fTex = texs.fWarehouseOlives.getTexture(texId);
            break;
        case eResourceType::fleece:
            o.fTex = texs.fWarehouseFleece.getTexture(texId);
            break;
        case eResourceType::statue:
            o.fTex = texs.fWarehouseStatue;
            break;
        case eResourceType::oliveOil:
            o.fTex = texs.fWarehouseOliveOil.getTexture(texId);
            break;
        case eResourceType::wine:
            o.fTex = texs.fWarehouseWine.getTexture(texId);
            break;
        case eResourceType::armor:
            o.fTex = texs.fWarehouseArmor.getTexture(texId);
            break;
        default: continue;
        }
    }
    return os;
}
