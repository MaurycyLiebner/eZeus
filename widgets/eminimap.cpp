#include "eminimap.h"

#include "textures/egametextures.h"

void eMiniMap::setBoard(eGameBoard* const board) {
    mBoard = board;
    if(mBoard) viewTile(board->width()/2, board->height()/2);
    scheduleUpdate();
}

void eMiniMap::setChangeAction(const eAction& act) {
    mChangeAction = act;
}

bool eMiniMap::mousePressEvent(const eMouseEvent& e) {
    if(!mBoard) return false;

    mMouseX = e.x();
    mMouseY = e.y();

    viewRelPix(e.x(), e.y());

    if(mChangeAction) mChangeAction();

    return true;
}

bool eMiniMap::mouseMoveEvent(const eMouseEvent& e) {
    if(!mBoard) return false;
    const bool pressed = static_cast<bool>(e.buttons() & eMouseButton::left);
    if(!pressed) return false;

    const int dx = e.x() - mMouseX;
    const int dy = e.y() - mMouseY;
    viewAbsPix(mCenterX + dx, mCenterY + dy);

    mMouseX = e.x();
    mMouseY = e.y();

    if(mChangeAction) mChangeAction();

    return true;
}

void eMiniMap::paintEvent(ePainter& p) {
    mTime++;
    if(!mTexture || mTime % 60 == 0 ||
       (mUpdateScheduled && mTime % 10 == 0)) {
        updateTexture();
        mUpdateScheduled = false;
    }
    p.drawTexture(0, 0, mTexture);
}

void eMiniMap::updateTexture() {
    if(!mBoard) return;
    const auto rend = renderer();
    mTexture = std::make_shared<eTexture>();
    mTexture->create(rend, width(), height());
    mTexture->setAsRenderTarget(rend);
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
    SDL_RenderClear(rend);
    ePainter p(rend);

    const int md = mapDimension();
    const int leftX = -(mCenterX - width()/2 - md/2);
    const int topY = -(mCenterY - height()/2);

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
        ++it;
        SDL_Color color{75, 180, 225, 255};
        if(const auto b = tile->underBuilding()) {
            if(b->type() == eBuildingType::road) {
                color = {85, 197, 245, 255};
            } else {
                color = {8, 65, 90, 255};
            }
        } else if(!tile->characters().empty()) {
            color = {8, 65, 90, 255};
        } else {
            switch(tile->terrain()) {
            case eTerrain::dry:
                continue;
                break;
            case eTerrain::fertile:
                if((tx + ty) % 2) {
                    color = {85, 197, 245, 255};
                } else {
                    continue;
                }
                break;
            case eTerrain::forest:
            case eTerrain::choppedForest:
                color = {15, 115, 165, 255};
                break;
            case eTerrain::water:
                color = {8, 65, 90, 255};
                break;
            case eTerrain::copper:
            case eTerrain::silver:
                color = {125, 235, 255, 255};
                break;
            default: break;
            }
        }
        const auto t = ds.getTexture(tdim/2 - 1);
        t->setColorMod(color.r, color.g, color.b);
        tp2.drawTexture(tile->x(), tile->y(), t);
    }

    SDL_SetRenderTarget(rend, nullptr);
}

int eMiniMap::mapDimension() const {
    if(!mBoard) return 0;
    const int tdim = 2;
    return tdim*(mBoard->width() + mBoard->height())/2;
}

void eMiniMap::viewFraction(const double fx, const double fy) {
    const int md = mapDimension();
    viewAbsPix(fx*md, fy*md);
}

void eMiniMap::viewedFraction(double& fx, double& fy) {
    const int md = mapDimension();
    if(md <= 0) return;
    fx = double(mCenterX)/md;
    fy = double(mCenterY)/md;
}

void eMiniMap::viewTile(const int tileX, const int tileY) {
    const int tdim = 2;
    const int md = mapDimension();
    const int pixX = tdim*(tileX - tileY)/2 + md/2;
    const int pixY = tdim*(tileX + tileY)/2;
    viewAbsPix(pixX, pixY);
}

void eMiniMap::viewedTile(int& tileX, int& tileY) const {
    const int tdim = 2;
    const int md = mapDimension();
    tileX = (mCenterX + mCenterY - md/2)/tdim;
    tileY = (mCenterY - mCenterX + md/2)/tdim;
}

void eMiniMap::viewRelPix(const int pixX, const int pixY) {
    const int px = mCenterX + pixX - width()/2;
    const int py = mCenterY + pixY - height()/2;
    viewAbsPix(px, py);
}

void eMiniMap::viewAbsPix(const int px, const int py) {
    const int md = mapDimension();
    mCenterX = std::clamp(px, 0, md);
    mCenterY = std::clamp(py, 0, md);
    scheduleUpdate();
}

void eMiniMap::scheduleUpdate() {
    mUpdateScheduled = true;
}
