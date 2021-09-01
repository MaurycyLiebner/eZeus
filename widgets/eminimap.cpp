#include "eminimap.h"

#include "textures/egametextures.h"

void eMiniMap::setBoard(eGameBoard* const board) {
    mBoard = board;
    mViewRect = {0, 0, 50, 50};
}

int gMX = 0;
int gMY = 0;

bool eMiniMap::mousePressEvent(const eMouseEvent& e) {
    if(!mBoard) return false;
    gMX = e.x();
    gMY = e.y();
    return true;
}

bool eMiniMap::mouseMoveEvent(const eMouseEvent& e) {
    if(!mBoard) return false;
    const bool pressed = static_cast<bool>(e.buttons() & eMouseButton::left);
    if(!pressed) return false;
    mViewRect.x -= e.x() - gMX;
    mViewRect.y -= e.y() - gMY;
    gMX = e.x();
    gMY = e.y();
    return true;
}

void eMiniMap::paintEvent(ePainter& p) {
    if(!mBoard) return;

    const int tdim = 1;

    const int w = mBoard->width();
    const int h = mBoard->height();
    const int nRows = w + h - 1;

    int minRow = -2*mViewRect.y/tdim;
    int maxRow = minRow + 2*height()/tdim;
    minRow = std::clamp(minRow, 0, nRows);
    maxRow = std::clamp(maxRow, 0, nRows);

    const int minXYDiff = -2*mViewRect.x/tdim;
    const int maxXYDiff = minXYDiff + 2*width()/tdim;


    const auto& intrfc = eGameTextures::interface();
    const int id = static_cast<int>(resolution().uiScale());
    const auto& coll = intrfc[id];
    const auto& ds = coll.fDiamond;

    p.translate(mViewRect.x, mViewRect.y);
    eTilePainter tp2(p, eTileSize::s15, 2, 2);

    const auto iniIt = eGameBoardDiagonalIterator(minRow, 0, mBoard);
    for(auto it = iniIt; it != mBoard->dEnd(); ++it) {
        if(it.row() > maxRow) break;
        const auto tile = *it;
        const int tx = tile->x();
        const int ty = tile->y();
        const int xmy = tx - ty;
        if(xmy < minXYDiff) continue;
        if(xmy > maxXYDiff) continue;
        SDL_Color color{255, 255, 255, 255};
        int dim = 1;
        if(const auto b = tile->underBuilding()) {
            if(b->type() == eBuildingType::road) {
                color = {255, 255, 255, 255};
            } else {
                color = {0, 0, 0, 255};
            }
        } else {
            switch(tile->terrain()) {
            case eTerrain::dry:
                color = {255, 200, 100, 255};
                break;
            case eTerrain::fertile:
                color = {200, 120, 255, 255};
                break;
            case eTerrain::forest:
            case eTerrain::choppedForest:
                color = {0, 255, 0, 255};
                break;
            case eTerrain::water:
                color = {0, 180, 255, 255};
                break;
            }
        }
        const auto t = ds.getTexture(dim - 1);
        t->setColorMod(color.r, color.g, color.b);
        tp2.drawTexture(tile->x(), tile->y(), t);
        t->clearColorMod();
    }
}
