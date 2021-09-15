#include "eelitehousingrenderer.h"

#include "eelitehousing.h"

eEliteHousingRenderer::eEliteHousingRenderer(
        const eEliteRendererType type,
        const stdsptr<eEliteHousing>& b) :
    eBuildingRenderer(b),
    mType(type),
    mBuilding(b) {

}

std::shared_ptr<eTexture>
eEliteHousingRenderer::getTexture(const eTileSize size) const {
    switch(mType) {
    case eEliteRendererType::left:
        return mBuilding->getLeftTexture(size);
    case eEliteRendererType::bottom:
        return mBuilding->getBottomTexture(size);
    case eEliteRendererType::top:
        return mBuilding->getTopTexture(size);
    case eEliteRendererType::right:
        return mBuilding->getRightTexture(size);
    }
}

std::vector<eOverlay>
eEliteHousingRenderer::getOverlays(const eTileSize size) const {
    switch(mType) {
    case eEliteRendererType::left:
    case eEliteRendererType::bottom:
    case eEliteRendererType::right:
        return {};
    case eEliteRendererType::top:
        return mBuilding->getHorseOverlays(size);
    }
}
