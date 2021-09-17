#include "epalace.h"

#include "engine/egameboard.h"
#include "textures/egametextures.h"

ePalace::ePalace(eGameBoard& board, const bool r) :
    eBuilding(board, eBuildingType::palace,
              r ? 4 : 8, r ? 8 : 4),
    mRotated(r) {
    board.registerPalace();
}

ePalace::~ePalace() {
    auto& b = getBoard();
    b.unregisterPalace();
}

std::shared_ptr<eTexture> ePalace::getTexture1(const eTileSize size) const {
    const auto& blds = eGameTextures::buildings();
    const int sizeId = static_cast<int>(size);
    if(mRotated) {
        return blds[sizeId].fPalace1H;
    } else {
        return blds[sizeId].fPalace1W;
    }
}

std::shared_ptr<eTexture> ePalace::getTexture2(const eTileSize size) const {
    const auto& blds = eGameTextures::buildings();
    const int sizeId = static_cast<int>(size);
    if(mRotated) {
        return blds[sizeId].fPalace2H;
    } else {
        return blds[sizeId].fPalace2W;
    }
}

std::vector<eOverlay> ePalace::getOverlays2(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings()[sizeId];

    std::vector<eOverlay> os;

    const int tt = textureTime();
    if(mRotated) {
        const auto& coll = texs.fPalaceHOverlay;
        eOverlay a0;
        a0.fX = 1.0;
        a0.fY = -2.75;
        const int ttt = tt % coll.size();
        a0.fTex = coll.getTexture(ttt);
        os.push_back(a0);
    } else {
        const auto& coll = texs.fPalaceWOverlay;
        eOverlay a0;
        a0.fX = -1.0;
        a0.fY = -4.5;
        const int ttt = tt % coll.size();
        a0.fTex = coll.getTexture(ttt);
        os.push_back(a0);
    }
    return os;
}