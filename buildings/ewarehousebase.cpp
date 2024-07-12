#include "ewarehousebase.h"

#include "textures/egametextures.h"

#include <algorithm>

void eWarehouseBase::getSpaceOverlays(const eTileSize size,
                                      std::vector<eOverlay>& os,
                                      const eXY& xy) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings();
    const auto& texs = blds[sizeId];
    const int iMax = xy.size();
    for(int i = 0; i < iMax; i++) {
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
        case eResourceType::oranges:
            o.fTex = texs.fWarehouseOranges.getTexture(texId);
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
        case eResourceType::sculpture:
            o.fTex = texs.fWarehouseSculpture;
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

}
