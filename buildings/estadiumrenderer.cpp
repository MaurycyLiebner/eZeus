#include "estadiumrenderer.h"

#include "engine/egameboard.h"

eStadium1Renderer::eStadium1Renderer(
        const stdsptr<eStadium>& b) :
    eBuildingRenderer(b, eBuildingRendererType::stadium1),
    mStadium(b) {}

std::shared_ptr<eTexture>
eStadium1Renderer::getTexture(const eTileSize size) const {
    auto& board = getBoard();
    const auto dir = board.direction();
    const auto& blds = eGameTextures::buildings();
    const int sizeId = static_cast<int>(size);
    const bool rotated = mStadium->rotated();
    if(dir == eWorldDirection::S) {
        if(rotated) {
            return blds[sizeId].fStadium2H;
        } else {
            return blds[sizeId].fStadium2W;
        }
    } else if(dir == eWorldDirection::E) {
        if(rotated) {
            return blds[sizeId].fStadium1W;
        } else {
            return blds[sizeId].fStadium2H;
        }
    } else if(dir == eWorldDirection::W) {
        if(rotated) {
            return blds[sizeId].fStadium2W;
        } else {
            return blds[sizeId].fStadium1H;
        }
    } else {
        if(rotated) {
            return blds[sizeId].fStadium1H;
        } else {
            return blds[sizeId].fStadium1W;
        }
    }
}

std::vector<eOverlay>
eStadium1Renderer::getOverlays(const eTileSize size) const {
//    auto& board = getBoard();
//    const auto dir = board.direction();
//    const bool rotated = mStadium->rotated();
//    const bool o = dir == eWorldDirection::S ||
//                   (dir == eWorldDirection::W && rotated) ||
//                   (dir == eWorldDirection::E && !rotated);
//    if(o) {
//        return mStadium->getOverlays(size);
//    } else {
//        return {};
//    }
    (void)size;
    return {};
}

eStadium2Renderer::eStadium2Renderer(
        const stdsptr<eStadium>& b) :
    eBuildingRenderer(b, eBuildingRendererType::stadium2),
    mStadium(b) {}

std::shared_ptr<eTexture>
eStadium2Renderer::getTexture(const eTileSize size) const {
    auto& board = getBoard();
    const auto dir = board.direction();
    const auto& blds = eGameTextures::buildings();
    const int sizeId = static_cast<int>(size);
    const bool rotated = mStadium->rotated();
    if(dir == eWorldDirection::S) {
        if(rotated) {
            return blds[sizeId].fStadium1H;
        } else {
            return blds[sizeId].fStadium1W;
        }
    } else if(dir == eWorldDirection::E) {
        if(rotated) {
            return blds[sizeId].fStadium2W;
        } else {
            return blds[sizeId].fStadium1H;
        }
    } else if(dir == eWorldDirection::W) {
        if(rotated) {
            return blds[sizeId].fStadium1W;
        } else {
            return blds[sizeId].fStadium2H;
        }
    } else {
        if(rotated) {
            return blds[sizeId].fStadium2H;
        } else {
            return blds[sizeId].fStadium2W;
        }
    }
}

std::vector<eOverlay>
eStadium2Renderer::getOverlays(const eTileSize size) const {
//    auto& board = getBoard();
//    const auto dir = board.direction();
//    const bool rotated = mStadium->rotated();
//    const bool o = dir == eWorldDirection::S ||
//                   (dir == eWorldDirection::W && rotated) ||
//                   (dir == eWorldDirection::E && !rotated);
//    if(o) {
//        return {};
//    } else {
//        return mStadium->getOverlays(size);
//    }
    (void)size;
    return {};
}
