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
    if(!mTexture || mTime % 60 == 0 || mUpdateScheduled) {
        updateTexture();
        mUpdateScheduled = false;
    }
    p.save();
    p.drawTexture(0, 0, mTexture);
    p.restore();
    const int w = mViewBoxW*mBoard->width()*mTDim;
    const int h = mViewBoxH*mBoard->height()*mTDim/2;
    const int x = width()/2 - w/2 + mDrawX;
    const int y = height()/2 - h/2 + mDrawY;
    const SDL_Rect rect{x, y, w, h};
    p.drawRect(rect, {0, 0, 0, 255}, 2);
    p.drawRect(rect, {255, 255, 255, 255}, 1);
}

SDL_Color colorForTile(eTile* const tile) {
    if(!tile) return {0, 0, 0, 255};
    if(const auto b = tile->underBuilding()) {
        const auto bt = b->type();
        const int min = static_cast<int>(eBuildingType::templeAphrodite);
        const int max = static_cast<int>(eBuildingType::templeAltar);
        const int bi = static_cast<int>(bt);
        if(bi >= min && bi <= max) return {238, 65, 16, 255};
        switch(bt) {
        case eBuildingType::road:
            return {225, 225, 225, 255};
        case eBuildingType::eliteHousing:
            return {238, 65, 16, 255};
        case eBuildingType::commonHouse:
            return {164, 65, 49, 255};
        case eBuildingType::tradePost:
        case eBuildingType::warehouse:
        case eBuildingType::granary:
            return {115, 186, 247, 255};
        case eBuildingType::podium:
        case eBuildingType::college:
        case eBuildingType::stadium:
        case eBuildingType::gymnasium:
            return {33, 129, 115, 255};
        case eBuildingType::oliveTree:
        case eBuildingType::vine:
        case eBuildingType::orangeTree:

        case eBuildingType::wheatFarm:
        case eBuildingType::carrotsFarm:
        case eBuildingType::onionsFarm:

        case eBuildingType::huntingLodge:
        case eBuildingType::fishery:
        case eBuildingType::urchinQuay:
        case eBuildingType::cardingShed:
        case eBuildingType::dairy:
        case eBuildingType::growersLodge:
        case eBuildingType::orangeTendersLodge:
            return {123, 113, 49, 255};

        case eBuildingType::palace:
            return {230, 162, 0, 255};
        default:
            return {0, 0, 0, 255};
        }
    } else if(!tile->characters().empty()) {
        return {0, 0, 0, 255};
    } else {
        if(tile->isElevationTile()) {
            return {123, 146, 164, 255};
        }
        switch(tile->terrain()) {
        case eTerrain::dry:
            if(tile->scrub() < 0.2) {
                return {214, 170, 99, 255};
            } else if(tile->scrub() < 0.4) {
                return {185, 170, 99, 255};
            } else if(tile->scrub() < 0.6) {
                return {155, 170, 99, 255};
            } else if(tile->scrub() < 0.8) {
                return {125, 170, 99, 255};
            } else {
                return {95, 170, 99, 255};
            }
        case eTerrain::beach:
            return {238, 202, 164, 255};
        case eTerrain::fertile:
            return {155, 110, 110, 255};
        case eTerrain::forest:
        case eTerrain::choppedForest:
            return {90, 129, 41, 255};
        case eTerrain::water:
            return {25, 105, 115, 255};
        case eTerrain::copper:
            return {206, 105, 8, 255};
        case eTerrain::silver:
        case eTerrain::marble:
            return {125, 235, 255, 255};
        default: break;
        }
    }
    return {66, 89, 148, 255};
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

    const int xMin = (mCenterX - mDrawX - width()/2)/mTDim;
    const int xMax = (mCenterX - mDrawX + width()/2)/mTDim;

    const int yMin = 2*(mCenterY - mDrawY - height()/2)/mTDim;
    const int yMax = 2*(mCenterY - mDrawY + height()/2)/mTDim;

    const auto& intrfc = eGameTextures::interface();
    const int id = static_cast<int>(resolution().uiScale());
    const auto& coll = intrfc[id];
    const auto& ds = coll.fDiamond;

    for(int x = xMin; x < xMax; x++) {
        for(int y = yMin; y < yMax; y++) {
            const auto tile = mBoard->dtile(x, y);
            if(!tile) continue;
            const auto color = colorForTile(tile);
            const auto t = ds.getTexture(0);
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
    const int px = mCenterX - mDrawX + pixX - width()/2;
    const int py = mCenterY - mDrawY + pixY - height()/2;
    viewAbsPix(px, py);
}

void eMiniMap::viewAbsPix(const int px, const int py) {
    const int w = mBoard->width()*mTDim;
    const int h = mBoard->height()*mTDim/2;
    mCenterX = std::clamp(px, 0, w);
    mCenterY = std::clamp(py, 0, h);
    if(mCenterX < width()/2) {
        mDrawX = mCenterX - width()/2;
    } else if(mCenterX > w - width()/2) {
        mDrawX = mCenterX - w + width()/2;
    } else {
        mDrawX = 0;
    }
    if(mCenterY < height()/2) {
        mDrawY = mCenterY - height()/2;
    } else if(mCenterY > h - height()/2) {
        mDrawY = mCenterY - h + height()/2;
    } else {
        mDrawY = 0;
    }
    scheduleUpdate();
}

void eMiniMap::scheduleUpdate() {
    mUpdateScheduled = true;
}
