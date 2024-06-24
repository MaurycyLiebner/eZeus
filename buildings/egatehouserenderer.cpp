#include "egatehouserenderer.h"

#include "egatehouse.h"

#include "engine/egameboard.h"

eGatehouseRenderer::eGatehouseRenderer(
        const bool rotated,
        const eGatehouseRendererType type,
        const stdsptr<eGatehouse>& b) :
    eBuildingRenderer(b, eBuildingRendererType::gatehouse),
    mRotated(rotated),
    mType(type),
    mBuilding(b) {

}

std::shared_ptr<eTexture>
eGatehouseRenderer::getTexture(const eTileSize size) const {
    return mBuilding->getTextureSides(size);
}

std::vector<eOverlay>
eGatehouseRenderer::getOverlays(const eTileSize size) const {
    auto& board = getBoard();
    const auto dir = board.direction();
    const bool s = dir == eWorldDirection::S;
    const bool w = dir == eWorldDirection::W;
    const bool e = dir == eWorldDirection::E;
    switch(mType) {
    case eGatehouseRendererType::grt1: {
        auto ebo = mBuilding->getTextureEntranceBack(size);
        auto eo = mBuilding->getTextureEntrance(size);
        if(s) {
            std::swap(ebo.fTex, eo.fTex);
        } else if(w) {
            if(mRotated) {
                ebo.fX += 2;
                ebo.fY -= 2;
                eo.fX += 1;
                eo.fY -= 1;
            } else {
                ebo.fX -= 1;
                ebo.fY += 2;
                eo.fX -= 2;
                eo.fY += 1;
                std::swap(ebo, eo);
            }
        } else if(e) {
            if(mRotated) {
                ebo.fX += 2;
                ebo.fY -= 1;
                eo.fX += 1;
                eo.fY -= 2;
                std::swap(ebo, eo);
            } else {
                ebo.fX -= 2;
                ebo.fY += 2;
                eo.fX -= 1;
                eo.fY += 1;
            }
        }
        return {ebo, eo};
    } break;
    case eGatehouseRendererType::grt2: {
        eOverlay so;
        so.fTex = mBuilding->getTextureSides(size);
        so.fX = 0.0;
        so.fY = 0.0;
        so.fAlignTop = true;

//        const auto eo = mBuilding->getTextureEntranceOverlay(size);

        return {so};
    } break;
    }
    return {};
}
