#include "egatehouserenderer.h"

#include "egatehouse.h"

eGatehouseRenderer::eGatehouseRenderer(
        const eGatehouseRendererType type,
        const stdsptr<eGatehouse>& b) :
    eBuildingRenderer(b),
    mType(type),
    mBuilding(b) {

}

std::shared_ptr<eTexture>
eGatehouseRenderer::getTexture(const eTileSize size) const {
    switch(mType) {
    case eGatehouseRendererType::grt1: {
        return mBuilding->getTextureSides(size);
    } break;
    case eGatehouseRendererType::grt2: {
        return nullptr;
    } break;
    }
}

std::vector<eOverlay>
eGatehouseRenderer::getOverlays(const eTileSize size) const {
    switch(mType) {
    case eGatehouseRendererType::grt1: {
        const auto ebo = mBuilding->getTextureEntranceBack(size);
        const auto eo = mBuilding->getTextureEntrance(size);
        return {ebo, eo};
    } break;
    case eGatehouseRendererType::grt2: {
        eOverlay so;
        so.fTex = mBuilding->getTextureSides(size);
        so.fX = 0.0;
        so.fY = 0.0;
        so.fAlignTop = true;

        const auto eo = mBuilding->getTextureEntranceOverlay(size);

        return {eo, so};
    } break;
    }
    return {};
}
