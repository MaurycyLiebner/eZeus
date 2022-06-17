#include "eminimap.h"

#include "textures/egametextures.h"

#include "etilehelper.h"

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
    p.save();
    p.drawTexture(0, 0, mTexture);
    p.restore();
    const int w = mViewBoxW*mBoard->width()*mTDim;
    const int h = mViewBoxH*mBoard->height()*mTDim/2;
    const SDL_Rect rect{width()/2 - w/2, height()/2 - h/2, w, h};
    p.drawRect(rect, {8, 65, 90, 255}, 2);
    p.drawRect(rect, {125, 235, 255, 255}, 1);
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

    const int xMin = (mCenterX - width()/2)/mTDim;
    const int xMax = (mCenterX + width()/2)/mTDim;

    const int yMin = 2*(mCenterY - height()/2)/mTDim;
    const int yMax = 2*(mCenterY + height()/2)/mTDim;

    const auto& intrfc = eGameTextures::interface();
    const int id = static_cast<int>(resolution().uiScale());
    const auto& coll = intrfc[id];
    const auto& ds = coll.fDiamond;

    for(int x = xMin; x < xMax; x++) {
        for(int y = yMin; y < yMax; y++) {
            const auto tile = mBoard->dtile(x, y);
            if(!tile) continue;
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
                    if((x + y) % 2) {
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
                case eTerrain::marble:
                    color = {125, 235, 255, 255};
                    break;
                default: break;
                }
            }
            const auto t = ds.getTexture(mTDim/2 - 1);
            t->setColorMod(color.r, color.g, color.b);
            const int px = (x - xMin)*mTDim + (y % 2 ? mTDim/2 : 0);
            const int py = (y - yMin)*mTDim/2;
            p.drawTexture(px, py, t);
        }
    }

    SDL_SetRenderTarget(rend, nullptr);
}

void eMiniMap::viewFraction(const double fx, const double fy) {
    const int px = fx*mBoard->width()*mTDim;
    const int py = fy*mBoard->height()*mTDim/2;
    viewAbsPix(px, py);
}

void eMiniMap::viewedFraction(double& fx, double& fy) {
    fx = double(mCenterX)/(mBoard->width()*mTDim);
    fy = double(mCenterY)/(mBoard->height()*mTDim/2);
}

void eMiniMap::viewTile(const int tileX, const int tileY) {
    const int pixX = mTDim*tileX;
    const int pixY = mTDim*tileY/2;
    viewAbsPix(pixX, pixY);
}

void eMiniMap::viewedTile(int& tileX, int& tileY) const {
    tileX = mCenterX/mTDim;
    tileY = 2*mCenterY/mTDim;
}

void eMiniMap::setViewBoxSize(const double fx, const double fy) {
    mViewBoxW = fx;
    mViewBoxH = fy;
}

void eMiniMap::viewRelPix(const int pixX, const int pixY) {
    const int px = mCenterX + pixX - width()/2;
    const int py = mCenterY + pixY - height()/2;
    viewAbsPix(px, py);
}

void eMiniMap::viewAbsPix(const int px, const int py) {
    mCenterX = std::clamp(px, 0, mBoard->width()*mTDim);
    mCenterY = std::clamp(py, 0, mBoard->height()*mTDim/2);
    scheduleUpdate();
}

void eMiniMap::scheduleUpdate() {
    mUpdateScheduled = true;
}
