#include "epalace.h"

#include "engine/egameboard.h"
#include "textures/egametextures.h"
#include "epalacetile.h"

ePalace::ePalace(eGameBoard& board, const bool r) :
    eBuilding(board, eBuildingType::palace,
              r ? 4 : 8, r ? 8 : 4),
    mRotated(r) {
    setEnabled(true);
    board.registerPalace(this);
}

ePalace::~ePalace() {
    auto& b = getBoard();
    b.unregisterPalace();
}

void ePalace::erase() {
    for(const auto& t : mTiles) {
        t->eBuilding::erase();
    }
    eBuilding::erase();
}

eTextureSpace ePalace::getTextureSpace(const int tx, const int ty,
                                       const eTileSize size) const {
    const SDL_Point p{tx, ty};
    const auto r = tileRect();
    if(!SDL_PointInRect(&p, &r)) return {nullptr};
    const auto& blds = eGameTextures::buildings();
    const int sizeId = static_cast<int>(size);
    const auto& plcs = blds[sizeId];
    if(mRotated) {
        if(ty - r.y > 3) return {plcs.fPalace2H, SDL_Rect{r.x, r.y + 4, 4, 4}};
        else return {plcs.fPalace1H, SDL_Rect{r.x, r.y, 4, 4}};
    } else {
        if(tx - r.x > 3) return {plcs.fPalace2W, SDL_Rect{r.x + 4, r.y, 4, 4}};
        else return {plcs.fPalace1W, SDL_Rect{r.x, r.y, 4, 4}};
    }
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
        a0.fX = 1.15;
        a0.fY = -3.25;
        const int ttt = tt % coll.size();
        a0.fTex = coll.getTexture(ttt);
        os.push_back(a0);
    }
    return os;
}

void ePalace::addTile(ePalaceTile* const tile) {
    mTiles.push_back(tile);
}

void ePalace::read(eReadStream& src) {
    eBuilding::read(src);

    int tiles;
    src >> tiles;
    for(int i = 0; i < tiles; i++) {
        src.readBuilding(&getBoard(), [this](eBuilding* const b) {
            const auto pt = static_cast<ePalaceTile*>(b);
            addTile(pt);
        });
    }
}

void ePalace::write(eWriteStream& dst) const {
    eBuilding::write(dst);

    dst << mTiles.size();
    for(const auto t : mTiles) {
        dst.writeBuilding(t);
    }
}
