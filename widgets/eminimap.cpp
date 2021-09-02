#include "eminimap.h"

#include "textures/egametextures.h"

void eMiniMap::setBoard(eGameBoard* const board) {
    mBoard = board;
    viewPix(0, 0);
}

bool eMiniMap::mousePressEvent(const eMouseEvent& e) {
    if(!mBoard) return false;

    mMouseX = e.x();
    mMouseY = e.y();

    viewPix(e.x(), e.y());

    return true;
}

bool eMiniMap::mouseMoveEvent(const eMouseEvent& e) {
    if(!mBoard) return false;
    const bool pressed = static_cast<bool>(e.buttons() & eMouseButton::left);
    if(!pressed) return false;

    const int dx = e.x() - mMouseX;
    const int dy = e.y() - mMouseY;
    setCenterPix(mCenterX + dx, mCenterY + dy);

    mMouseX = e.x();
    mMouseY = e.y();

    return true;
}

void eMiniMap::paintEvent(ePainter& p) {
    if(!mBoard) return;

    const int leftX = -mCenterX;
    const int topY = -mCenterY;

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
            const SDL_Color dryColor{210, 175, 85, 255};
            switch(tile->terrain()) {
            case eTerrain::dry:
                color = dryColor;
                break;
            case eTerrain::fertile:
                if((tx + ty) % 2) {
                    color = {115, 110, 200, 255};
                } else {
                    color = dryColor;
                }
                break;
            case eTerrain::forest:
            case eTerrain::choppedForest:
                color = {100, 120, 60, 255};
                break;
            case eTerrain::water:
                color = {42, 108, 116, 255};
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

int eMiniMap::mapDimension() const {
    if(!mBoard) return 0;
    const int tdim = 2;
    return tdim*(mBoard->width() + mBoard->height())/2;
}

void eMiniMap::viewPix(const int pixX, const int pixY) {
    const int px = mCenterX + pixX - width()/2;
    const int py = mCenterY + pixY - height()/2;
    setCenterPix(px, py);
}

void eMiniMap::setCenterPix(const int px, const int py) {
    const int md = mapDimension();
    mCenterX = std::clamp(px, -md/2, md/2 - width());
    mCenterY = std::clamp(py, 0, md - height());
}
