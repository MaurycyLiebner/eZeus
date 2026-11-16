#include "eminimap.h"

#include "textures/egametextures.h"

#include "etilehelper.h"

#include "emainwindow.h"

#include <algorithm>

eMiniMap::eMiniMap(eMainWindow* const window) :
    eWidget(window) {
    mTexture = &mTextures[eWorldDirection::N];
    mTextures[eWorldDirection::E];
    mTextures[eWorldDirection::S];
    mTextures[eWorldDirection::W];
}

void eMiniMap::renderTargetsReset() {
    eWidget::renderTargetsReset();
    scheduleTotalUpdate();
}

void eMiniMap::setBoard(eGameBoard* const board) {
    mBoard = board;
    if(mBoard) viewTile(board->width()/2, board->height()/2);
    scheduleTotalUpdate();
}

void eMiniMap::setDirection(const eWorldDirection dir) {
    if(dir == mDir) return;
    mTexture = &mTextures[dir];
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

    SDL_ShowCursor(SDL_DISABLE);

    return true;
}

bool eMiniMap::mouseMoveEvent(const eMouseEvent& e) {
    if(!mBoard) return false;
    const bool pressed = static_cast<bool>(e.buttons() & eMouseButton::left);
    if(!pressed) return false;

    const int dx = e.x() - mMouseX;
    const int dy = e.y() - mMouseY;
    viewAbsPix(mCenterX + dx, mCenterY + dy);

//    mMouseX = e.x();
//    mMouseY = e.y();

    {
        int cx;
        int cy;
        SDL_GetMouseState(&cx, &cy);
        const auto w = window()->window();
        SDL_WarpMouseInWindow(w, cx - dx, cy - dy);
    }

    if(mChangeAction) mChangeAction();

    return true;
}

bool eMiniMap::mouseReleaseEvent(const eMouseEvent& e) {
    (void)e;
    SDL_ShowCursor(SDL_ENABLE);
    return true;
}

void eMiniMap::paintEvent(ePainter& p) {
    mTime++;
    const auto cities = mBoard->citiesOnBoard();
    const int nc = cities.size();
    const int period = nc > 0 ? 60/nc : 60;

    const bool useTexture = false;

    if(!mTexture->fTexture || mTexture->fTotalUpdateScheduled) {
        updateTexture(eCityId::neutralFriendly, useTexture);
        mTexture->fTotalUpdateScheduled = false;
        mTexture->fUpdateScheduled = false;
        mTexture->fTilesToUpdate.clear();
    } else if(mTexture->fUpdateScheduled) {
        for(const auto cid : cities) {
            updateTexture(cid, useTexture);
        }
        mTexture->fUpdateScheduled = false;
    } else if(nc > 0 && mTime % period == 0) {
        const int id = mCityCounter % nc;
        const auto cid = cities[id];
        updateTexture(cid, useTexture);
        mCityCounter++;
    }
    if(!mTexture->fTilesToUpdate.empty()) {
        updateTexture(eCityId::neutralAggresive, useTexture);
        mTexture->fTilesToUpdate.clear();
    }

    if(!mTexture->fTexture) return;
    const SDL_Rect clip{0, 0, width(), height()};
    p.setClipRect(&clip);
    const int xMin = (mCenterX - mDrawX - width()/2);
    const int yMin = (mCenterY - mDrawY - height()/2);
    p.drawTexture(-xMin, -yMin, mTexture->fTexture);
    p.setClipRect(nullptr);
    const int w = mViewBoxW*mBoard->rotatedWidth()*mTDim;
    const int h = mViewBoxH*mBoard->rotatedHeight()*mTDim/2;
    const int x = width()/2 - w/2 + mDrawX;
    const int y = height()/2 - h/2 + mDrawY;
    const SDL_Rect rect{x, y, w, h};
    p.drawRect(rect, {0, 0, 0, 255}, 2);
    p.drawRect(rect, {255, 255, 255, 255}, 1);
}

SDL_Color gTerrainColor(eTile* const tile) {
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
    case eTerrain::orichalc:
        return {255, 0, 0, 255};
    case eTerrain::silver:
    case eTerrain::marble:
        return {125, 235, 255, 255};
    case eTerrain::blackMarble:
        return {45, 45, 60, 255};
    default:
        return {66, 89, 148, 255};
    }
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
        case eBuildingType::hippodromePiece:
            return {225, 225, 225, 255};
        case eBuildingType::eliteHousing:
            return {238, 65, 16, 255};
        case eBuildingType::commonHouse:
            return {164, 65, 49, 255};
        case eBuildingType::tradePost:
        case eBuildingType::pier:
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
        case eBuildingType::corral:
        case eBuildingType::fishery:
        case eBuildingType::urchinQuay:
        case eBuildingType::cardingShed:
        case eBuildingType::dairy:
        case eBuildingType::growersLodge:
        case eBuildingType::orangeTendersLodge:
            return {123, 113, 49, 255};

        case eBuildingType::palace:
            return {230, 162, 0, 255};

        case eBuildingType::sheep:
        case eBuildingType::cattle:
        case eBuildingType::goat: {
            if(!tile->characters().empty()) {
                return {0, 0, 0, 255};
            } else {
                return gTerrainColor(tile);
            }
        } break;
        default:
            return {0, 0, 0, 255};
        }
    } else if(!tile->characters().empty()) {
        return {0, 0, 0, 255};
    } else {
        if(tile->isElevationTile()) {
            return {123, 146, 164, 255};
        }
        return gTerrainColor(tile);
    }
    return {66, 89, 148, 255};
}

void eMiniMap::updateTexture(const eCityId cid, const bool useTexture) {
    if(!mBoard) return;
    const auto rend = renderer();
    const int w = mBoard->rotatedWidth()*mTDim;
    const int h = mBoard->rotatedHeight()*mTDim/2;
    auto& fTex = mTexture->fTexture;
    const int tw = fTex ? fTex->width() : -1;
    const int th = fTex ? fTex->height() : -1;
    if(tw != w || th != h) {
        fTex = std::make_shared<eTexture>();
        const bool v = fTex->create(rend, w, h);
        if(!v) {
            fTex.reset();
            return;
        }
    }
    fTex->setAsRenderTarget(rend);
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
    ePainter p(rend);

    const auto& intrfc = eGameTextures::interface();
    const int id = static_cast<int>(resolution().uiScale());
    const auto& coll = intrfc[id];
    const auto& ds = coll.fDiamond;
    const auto& dtex = ds.getTexture(0);

    const int xMin = 0;
    const int xMax = mBoard->rotatedWidth();
    const int yMin = 0;
    const int yMax = mBoard->rotatedHeight();

    const bool fogOfWar = mBoard->fogOfWar() && !mBoard->editorMode();

    const auto drawTile = [&](eTile* const tile, const int x, const int y) {
        if(!tile) return;
        auto color = colorForTile(tile);
        const auto cid = tile->cityId();
        if(fogOfWar) {
            const int maxDist = eTile::sMaxDistanceToBorder;
            const int idist = tile->distanceToBorder();
            if(idist != 0) {
                const double dist = idist;
                const double mult = (maxDist - dist)/maxDist;
                color.r *= mult;
                color.g *= mult;
                color.b *= mult;
            }
        } else {
            if(cid == eCityId::neutralFriendly) {
                const int l = 0.2126*color.r + 0.7152*color.g + 0.0722*color.b;
                color.r = l;
                color.g = l;
                color.b = l;
            } else {
                const auto& border = tile->territoryBorder();
                if(border.fTR || border.fR ||
                   border.fBR || border.fB ||
                   border.fBL || border.fL ||
                   border.fTL || border.fT) {
                    color.r = 255;
                    color.g = 255;
                    color.b = 255;
                }
            }
        }
        if(useTexture) dtex->setColorMod(color.r, color.g, color.b);
        const int px = (x - xMin)*mTDim + (y % 2 ? mTDim/2 : 0);
        const int py = (y - yMin)*mTDim/2;
        p.fillRect(SDL_Rect{px, py, mTDim, mTDim}, color);
        if(useTexture) p.drawTexture(px, py, dtex);
    };

    if(cid == eCityId::neutralFriendly) {
        SDL_RenderClear(rend);
        for(int x = xMin; x < xMax; x++) {
            for(int y = yMin; y < yMax; y++) {
                const auto tile = mBoard->rotateddtile(x, y);
                drawTile(tile, x, y);
            }
        }
    } else if(cid == eCityId::neutralAggresive) {
        const auto dir = mBoard->direction();
        const int bw = mBoard->width();
        const int bh = mBoard->height();
        const auto& tiles = mTexture->fTilesToUpdate;
        for(const auto tile : tiles) {
            const int dx = tile->dx();
            const int dy = tile->dy();
            int rdx;
            int rdy;
            eTileHelper::dTileIdToRotatedDTileId(
                        dx, dy, rdx, rdy, dir, bw, bh);
            drawTile(tile, rdx, rdy);
        }
    } else {
        const auto dir = mBoard->direction();
        const int bw = mBoard->width();
        const int bh = mBoard->height();
        const auto c = mBoard->boardCityWithId(cid);
        const auto& tiles = c->tiles();
        for(const auto tile : tiles) {
            const int dx = tile->dx();
            const int dy = tile->dy();
            int rdx;
            int rdy;
            eTileHelper::dTileIdToRotatedDTileId(
                        dx, dy, rdx, rdy, dir, bw, bh);
            drawTile(tile, rdx, rdy);
        }
    }

    SDL_SetRenderTarget(rend, nullptr);
}

void eMiniMap::viewFraction(const double fx, const double fy) {
    const int px = fx*mBoard->rotatedWidth()*mTDim;
    const int py = fy*mBoard->rotatedHeight()*mTDim/2;
    viewAbsPix(px, py);
}

void eMiniMap::viewedFraction(double& fx, double& fy) {
    fx = double(mCenterX)/(mBoard->rotatedWidth()*mTDim);
    fy = double(mCenterY)/(mBoard->rotatedHeight()*mTDim/2);
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
    const int w = mBoard->rotatedWidth()*mTDim;
    const int h = mBoard->rotatedHeight()*mTDim/2;
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
}

void eMiniMap::scheduleUpdate() {
    for(auto& t : mTextures) {
        t.second.fUpdateScheduled = true;
    }
}

void eMiniMap::scheduleTotalUpdate() {
    for(auto& t : mTextures) {
        t.second.fTotalUpdateScheduled = true;
    }
}

void eMiniMap::scheduleTilesUpdate(const std::vector<eTile*>& tiles) {
    for(auto& t : mTextures) {
        auto& ts = t.second.fTilesToUpdate;
        ts.insert(ts.end(), tiles.begin(), tiles.end());
    }
}
