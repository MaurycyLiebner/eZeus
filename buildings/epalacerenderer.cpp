#include "epalacerenderer.h"

#include "engine/egameboard.h"

ePalace1Renderer::ePalace1Renderer(
        const stdsptr<ePalace>& b) :
    eBuildingRenderer(b, eBuildingRendererType::palace1),
    mPalace(b) {}

std::shared_ptr<eTexture>
ePalace1Renderer::getTexture(const eTileSize size) const {
    auto& board = getBoard();
    const auto dir = board.direction();
    const auto& blds = eGameTextures::buildings();
    const int sizeId = static_cast<int>(size);
    const bool rotated = mPalace->rotated();
    if(dir == eWorldDirection::S) {
        if(rotated) {
            return blds[sizeId].fPalace2H;
        } else {
            return blds[sizeId].fPalace2W;
        }
    } else if(dir == eWorldDirection::E) {
        if(rotated) {
            return blds[sizeId].fPalace1W;
        } else {
            return blds[sizeId].fPalace2H;
        }
    } else if(dir == eWorldDirection::W) {
        if(rotated) {
            return blds[sizeId].fPalace2W;
        } else {
            return blds[sizeId].fPalace1H;
        }
    } else {
        if(rotated) {
            return blds[sizeId].fPalace1H;
        } else {
            return blds[sizeId].fPalace1W;
        }
    }
}

std::vector<eOverlay>
ePalace1Renderer::getOverlays(const eTileSize size) const {
    auto& board = getBoard();
    const auto dir = board.direction();
    const bool rotated = mPalace->rotated();
    const bool o = dir == eWorldDirection::S ||
                   (dir == eWorldDirection::W && rotated) ||
                   (dir == eWorldDirection::E && !rotated);
    if(o) {
        return mPalace->getOverlays(size);
    } else {
        return {};
    }
}

ePalace2Renderer::ePalace2Renderer(
        const stdsptr<ePalace>& b) :
    eBuildingRenderer(b, eBuildingRendererType::palace2),
    mPalace(b) {}

std::shared_ptr<eTexture>
ePalace2Renderer::getTexture(const eTileSize size) const {
    auto& board = getBoard();
    const auto dir = board.direction();
    const auto& blds = eGameTextures::buildings();
    const int sizeId = static_cast<int>(size);
    const bool rotated = mPalace->rotated();
    if(dir == eWorldDirection::S) {
        if(rotated) {
            return blds[sizeId].fPalace1H;
        } else {
            return blds[sizeId].fPalace1W;
        }
    } else if(dir == eWorldDirection::E) {
        if(rotated) {
            return blds[sizeId].fPalace2W;
        } else {
            return blds[sizeId].fPalace1H;
        }
    } else if(dir == eWorldDirection::W) {
        if(rotated) {
            return blds[sizeId].fPalace1W;
        } else {
            return blds[sizeId].fPalace2H;
        }
    } else {
        if(rotated) {
            return blds[sizeId].fPalace2H;
        } else {
            return blds[sizeId].fPalace2W;
        }
    }
}

std::vector<eOverlay>
ePalace2Renderer::getOverlays(const eTileSize size) const {
    auto& board = getBoard();
    const auto dir = board.direction();
    const bool rotated = mPalace->rotated();
    const bool o = dir == eWorldDirection::S ||
                   (dir == eWorldDirection::W && rotated) ||
                   (dir == eWorldDirection::E && !rotated);
    if(o) {
        return {};
    } else {
        return mPalace->getOverlays(size);
    }
}
