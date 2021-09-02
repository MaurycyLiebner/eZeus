#include "eminimap.h"

#include "textures/egametextures.h"

void eMiniMap::setBoard(eGameBoard* const board) {
    mBoard = board;
    viewTile(mBoard->width()/2, mBoard->height()/2);
}

bool eMiniMap::mousePressEvent(const eMouseEvent& e) {
    if(!mBoard) return false;

    viewPix(e.x(), e.y());

    return true;
}

bool eMiniMap::mouseMoveEvent(const eMouseEvent& e) {
    if(!mBoard) return false;
    const bool pressed = static_cast<bool>(e.buttons() & eMouseButton::left);
    if(!pressed) return false;

    viewPix(e.x(), e.y());

    return true;
}

void eMiniMap::paintEvent(ePainter& p) {
    if(!mBoard) return;

    int viewPixX;
    int viewPixY;
    pixAtTile(mCenterX, mCenterY, viewPixX, viewPixY);

    const int leftX = -viewPixX + width()/2;
    const int topY = -viewPixY + height()/2;

    const int tdim = 2;

    const int w = mBoard->width();
    const int h = mBoard->height();
    const int nRows = w + h - 1;

    int minRow = -2*topY/tdim;
    int maxRow = minRow + 2*height()/tdim;
    minRow = std::clamp(minRow, 0, nRows);
    maxRow = std::clamp(maxRow, 0, nRows);

    const int minXYDiff = -2*leftX/tdim;
    const int maxXYDiff = minXYDiff + 2*width()/tdim;

    const auto& intrfc = eGameTextures::interface();
    const int id = static_cast<int>(resolution().uiScale());
    const auto& coll = intrfc[id];
    const auto& ds = coll.fDiamond;

    p.save();
    p.translate(leftX, topY);
    eTilePainter tp2(p, eTileSize::s15, tdim, tdim);

    const auto iniIt = eGameBoardDiagonalIterator(minRow, 0, mBoard);
    for(auto it = iniIt; it != mBoard->dEnd();) {
        if(it.row() > maxRow) break;
        const auto tile = *it;
        const int tx = tile->x();
        const int ty = tile->y();
        const int xmy = tx - ty;
        if(xmy < minXYDiff) {
            ++it;
            continue;
        }
        if(xmy > maxXYDiff) {
            it.nextRow();
            continue;
        }
        SDL_Color color{255, 255, 255, 255};
        if(const auto b = tile->underBuilding()) {
            if(b->type() == eBuildingType::road) {
                color = {255, 255, 255, 255};
            } else {
                color = {0, 0, 0, 255};
            }
        } else if(!tile->characters().empty()) {
            color = {0, 0, 0, 255};
        } else {
            const SDL_Color dryColor{255, 200, 100, 255};
            switch(tile->terrain()) {
            case eTerrain::dry:
                color = dryColor;
                break;
            case eTerrain::fertile:
                if(xmy % 2) {
                    color = {200, 150, 255, 255};
                } else {
                    color = dryColor;
                }
                break;
            case eTerrain::forest:
            case eTerrain::choppedForest:
                color = {150, 255, 50, 255};
                break;
            case eTerrain::water:
                color = {50, 175, 225, 255};
                break;
            case eTerrain::silver:
                color = {0, 255, 255, 255};
                break;
            case eTerrain::copper:
                color = {255, 200, 100, 255};
                break;
            }
        }
        const auto t = ds.getTexture(tdim/2 - 1);
        t->setColorMod(color.r, color.g, color.b);
        tp2.drawTexture(tile->x(), tile->y(), t);
        ++it;
    }
    p.restore();
    eWidget::paintEvent(p);
}

void eMiniMap::tileAtPix(const int pixX, const int pixY,
                         int& tileX, int& tileY) const {
    const int tdim = 2;

    tileX = (pixX + pixY)/tdim;
    tileY = 2*pixY/tdim - tileX;
}

void eMiniMap::pixAtTile(const int tileX, const int tileY,
                         int& pixX, int& pixY) const {
    const int tdim = 2;

    pixX = tileX*tdim/2 - tileY*tdim/2;
    pixY = tileX*tdim/2 + tileY*tdim/2;
}

void eMiniMap::viewTile(const int tileX, const int tileY) {
    mCenterX = tileX;
    mCenterY = tileY;
}

void eMiniMap::viewPix(const int pixX, const int pixY) {
    int tileX;
    int tileY;
    tileAtPix(pixX, pixY, tileX, tileY);
    viewTile(tileX, tileY);
}
