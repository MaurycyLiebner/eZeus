#include "egamewidget.h"

#include "eterraineditmenu.h"
#include "etilepainter.h"

#include "emainmenu.h"
#include "egamemenu.h"
#include "eminimap.h"

#include "textures/etiletotexture.h"
#include "textures/egametextures.h"

#include "textures/eparktexture.h"
#include "textures/evaryingsizetex.h"

#include "buildings/ebuildingrenderer.h"

#include "buildings/esmallhouse.h"
#include "buildings/egymnasium.h"
#include "buildings/eroad.h"
#include "buildings/epodium.h"
#include "buildings/ecollege.h"
#include "buildings/efountain.h"
#include "buildings/ewatchpost.h"
#include "buildings/ehospital.h"
#include "buildings/etheater.h"
#include "buildings/edramaschool.h"
#include "buildings/estadium.h"
#include "buildings/estadiumrenderer.h"
#include "buildings/epalace.h"
#include "buildings/epalacerenderer.h"
#include "buildings/emint.h"
#include "buildings/efoundry.h"
#include "buildings/etimbermill.h"
#include "buildings/emasonryshop.h"
#include "buildings/etaxoffice.h"
#include "buildings/eresourcebuilding.h"
#include "buildings/ehuntinglodge.h"
#include "buildings/emaintenanceoffice.h"

#include "buildings/egranary.h"
#include "buildings/ewarehouse.h"

#include "buildings/etradepost.h"

#include "buildings/egrowerslodge.h"

#include "buildings/ewinery.h"
#include "buildings/eolivepress.h"
#include "buildings/esculpturestudio.h"
#include "buildings/earmory.h"

#include "buildings/eartisansguild.h"

#include "buildings/ewall.h"
#include "buildings/etower.h"
#include "buildings/egatehouse.h"
#include "buildings/egatehouserenderer.h"

#include "buildings/ewheatfarm.h"
#include "buildings/eonionfarm.h"
#include "buildings/ecarrotfarm.h"

#include "buildings/edairy.h"
#include "buildings/ecardingshed.h"

#include "buildings/efoodvendor.h"
#include "buildings/efleecevendor.h"
#include "buildings/eoilvendor.h"
#include "buildings/ewinevendor.h"
#include "buildings/earmsvendor.h"
#include "buildings/ehorsevendor.h"

#include "buildings/epark.h"
#include "buildings/ecolumn.h"
#include "buildings/eavenue.h"

#include "buildings/eanimalbuilding.h"

#include "buildings/eelitehousing.h"
#include "buildings/eelitehousingrenderer.h"

#include "buildings/sanctuaries/ehephaestussanctuary.h"
#include "buildings/sanctuaries/estairsrenderer.h"
#include "buildings/sanctuaries/etempletilebuilding.h"
#include "buildings/sanctuaries/etemplestatuebuilding.h"
#include "buildings/sanctuaries/etemplemonumentbuilding.h"
#include "buildings/sanctuaries/etemplealtarbuilding.h"
#include "buildings/sanctuaries/etemplebuilding.h"

#include "characters/esheep.h"
#include "characters/egoat.h"
#include "characters/actions/eanimalaction.h"

#include "characters/esoldier.h"
#include "characters/actions/esoldieraction.h"

#include "spawners/eboarspawner.h"
#include "spawners/edeerspawner.h"
#include "spawners/esettlerspawner.h"

#include "echeckbox.h"

#include "esounds.h"

#include "engine/emapgenerator.h"

#include "infowidgets/estorageinfowidget.h"
#include "infowidgets/etradepostinfowidget.h"

#include "engine/boardData/eappealupdatetask.h"
#include "engine/epathfinder.h"

#include "emainwindow.h"

#include "emessagebox.h"
#include "emessages.h"

#include "buildings/sanctuaries/esanctuaryblueprint.h"

#include "widgets/eworldwidget.h"

#include "epathdatafindtask.h"

#include "missiles/emissile.h"

#include "characters/esoldierbanner.h"

#include "eiteratesquare.h"

eGameWidget::eGameWidget(eMainWindow* const window) :
    eWidget(window) {}


void eGameWidget::setBoard(eGameBoard* const board) {
    if(mBoard == board) return;
    mBoard = board;
    mBoard->setEventHandler([this](const eEvent e, eTile* const tile) {
        handleEvent(e, tile);
    });
    mBoard->setVisibilityChecker([this](eTile* const tile) {
        return tileVisible(tile);
    });
}

void eGameWidget::initialize() {
    mGm = new eGameMenu(window());
    mGm->initialize();
    addWidget(mGm);
    mGm->align(eAlignment::right | eAlignment::top);
    mGm->setBoard(mBoard);
    mGm->setGameWidget(this);

    mGm->setViewTileHandler([this](eTile* const tile) {
        if(!tile) return;
        viewTile(tile);
    });

    const auto mm = mGm->miniMap();
    mm->setChangeAction([this, mm]() {
        double fx;
        double fy;
        mm->viewedFraction(fx, fy);
        viewFraction(fx, fy);
    });

    mTopBar = new eTopBarWidget(window());
    mTopBar->initialize();
    addWidget(mTopBar);
    mTopBar->align(eAlignment::top);
    const int gw = width() - mGm->width();
    mTopBar->setX(gw/2 - mTopBar->width()/2);
    mTopBar->setBoard(mBoard);

    mTem = new eTerrainEditMenu(window());
    mTem->initialize();
    addWidget(mTem);
    mTem->align(eAlignment::right | eAlignment::top);
    mTem->hide();


    const auto swtch = new eCheckBox(window());
    swtch->move(mGm->x(), 0);
    swtch->setCheckAction([this](const bool c) {
        mTem->setVisible(c);
        mGm->setVisible(!c);
    });
    addWidget(swtch);

    const auto& setts = window()->settings();
    const auto sizes = setts.availableSizes();
    setTileSize(sizes.front());

    showMessage(nullptr, eMessages::instance.fFire);
}

void drawXY(const int tx, const int ty,
            double& rx, double& ry,
            const int wSpan, const int hSpan,
            const int a) {
    rx = tx + 0.5;
    ry = ty + 1.5;

    if(wSpan == 2 && hSpan == 2) {
        rx += 0.5;
        ry += 0.5;
    } else if(wSpan == 3 && hSpan == 3) {
        rx += 0.0;
        ry += 2.0;
    } else if(wSpan == 4 && hSpan == 4) {
        rx += 0.5;
        ry += 2.5;
    } else if(wSpan == 5 && hSpan == 5) {
        rx += 0.0;
        ry += 4.0;
    }
    rx -= a;
    ry -= a;
}

void eGameWidget::pixToId(const int pixX, const int pixY,
                          int& idX, int& idY) const {
    const double w = mTileW;
    const double h = mTileH;
    idX = std::round((pixX - mDX)/w + (pixY - mDY)/h - 0.5);
    idY = std::round(-(pixX - mDX)/w + (pixY - mDY)/h - 0.5);

    for(int x = idX + 4; x >= idX - 4; x--) {
        for(int y = idY + 4; y >= idY - 4; y--) {
            const auto t = mBoard->tile(x, y);
            if(!t) continue;
            const int a = t->altitude();
            const int dx = 0;
            const int dy = -a*2 + 2;
            const int tpx = std::round(0.5 * (x - y + dx) * mTileW) + mDX;
            const int tpy = std::round(0.5 * (x + y + dy) * mTileH) + mDY;
            const int dist = std::sqrt((tpx - pixX)*(tpx - pixX) +
                                       (tpy - pixY)*(tpy - pixY));
            if(dist < mTileH) {
                idX = x;
                idY = y;
                return;
            }
        }
    }
}

void eGameWidget::setViewMode(const eViewMode m) {
    if(m == eViewMode::appeal) updateAppealMap();
    mViewMode = m;
}

void eGameWidget::mapDimensions(int& mdx, int& mdy) const {
    const int w = mBoard->width();
    const int h = mBoard->height();
    mdx = mTileW*(w + h)/2;
    mdy = mTileH*(w + h)/2;
}

void eGameWidget::viewBoxSize(double& fx, double& fy) const {
    int mdx;
    int mdy;
    mapDimensions(mdx, mdy);
    fx = width()/double(mdx);
    fy = height()/double(mdy);
}

void eGameWidget::viewedFraction(double& fx, double& fy) const {
    int mdx;
    int mdy;
    mapDimensions(mdx, mdy);

    fx = (double(mdx)/2 + width()/2 - mDX)/mdx;
    fy = (double(height())/2 - mDY)/mdy;
}

void eGameWidget::tileViewFraction(eTile* const tile,
                                   double& xf, double& yf) const {
    int mdx;
    int mdy;
    mapDimensions(mdx, mdy);

    const int tx = tile->x();
    const int ty = tile->y();
    xf = mTileW*(tx - ty)/2. + mdx/2.;
    yf = mTileH*(tx + ty)/2.;

    xf /= mdx;
    yf /= mdy;
}

void eGameWidget::viewFraction(const double fx, const double fy) {
    int mdx;
    int mdy;
    mapDimensions(mdx, mdy);

    mDX = -fx*mdx + mdx/2 + width()/2;
    mDY = -fy*mdy + height()/2;
}

void eGameWidget::viewTile(eTile* const tile) {
    double x;
    double y;
    tileViewFraction(tile, x, y);
    viewFraction(x, y);
}

bool eGameWidget::tileVisible(eTile* const tile) const {
    if(!tile) return false;

    double fx;
    double fy;
    viewBoxSize(fx, fy);

    double ffx;
    double ffy;
    viewedFraction(ffx, ffy);

    double txf;
    double tyf;
    tileViewFraction(tile, txf, tyf);

    const double top = ffy - fy/2;
    const double left = ffx - fx/2;
    const double bottom = top + fy;
    const double right = left + fx;

    if(txf > right) return false;
    if(txf < left) return false;
    if(tyf > bottom) return false;
    if(tyf < top) return false;
    return true;
}

void eGameWidget::iterateOverVisibleTiles(const eTileAction& a) {
    const int w = mBoard->width();
    const int h = mBoard->height();
    const int nRows = w + h - 1;

    int minRow = -2*mDY/mTileH - 5;
    int maxRow = minRow + 2*height()/mTileH + 10;
    minRow = std::clamp(minRow, 0, nRows);
    maxRow = std::clamp(maxRow, 0, nRows);

    const int minXYDiff = -2*mDX/mTileW - 5;
    const int maxXYDiff = minXYDiff + 2*width()/mTileW + 10;

    const int soundRow = (minRow + maxRow)/2 + (rand() % 7 - 3);
    const int soundXmy = (minXYDiff + maxXYDiff)/2 + (rand() % 7 - 3);
    const bool play = Mix_Playing(-1) == 0 && (rand() % 250) == 0;

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
        if(play && xmy == soundXmy && it.row() == soundRow) {
            eSounds::playSoundForTile(tile);
        }
        a(tile);
        ++it;
    }
}

void eGameWidget::sClearScrub(const int x, const int y,
                             const int sw, const int sh,
                             eGameBoard& board) {
    for(int xx = x; xx < x + sw; xx++) {
        for(int yy = y; yy < y + sh; yy++) {
            for(int i = -6; i < 7; i++) {
                for(int j = -6; j < 7; j++) {
                    const int tx = xx + i;
                    const int ty = yy + j;
                    const auto t = board.tile(tx, ty);
                    if(!t) continue;
                    const int dx = xx - tx;
                    const int dy = yy - ty;
                    const int dist = sqrt(dx*dx + dy*dy);
                    const double max = dist*0.15;
                    t->setScrub(std::min(max, t->scrub()));
                }
            }
        }
    }
}

void eGameWidget::sClearForest(const int x, const int y,
                               const int sw, const int sh,
                               eGameBoard& board) {
    return;
    for(int xx = x; xx < x + sw; xx++) {
        for(int yy = y; yy < y + sh; yy++) {
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 2; j++) {
                    const int tx = xx + i;
                    const int ty = yy + j;
                    const auto t = board.tile(tx, ty);
                    if(!t) continue;
                    if(t->terrain() == eTerrain::forest ||
                       t->terrain() == eTerrain::choppedForest) {
                        t->setTerrain(eTerrain::dry);
                    }
                }
            }
        }
    }
}

void buildTiles(int& minX, int& minY,
                int& maxX, int& maxY,
                const int tx, const int ty,
                const int sw, const int sh) {
    minX = tx;
    minY = ty;

    if(sw == 2 && sh == 2) {
        minY -= 1;
    } else if(sw == 3 && sh == 3) {
        minX -= 1;
        minY -= 1;
    } else if(sw == 4 || sh == 4) {
        minX -= 1;
        minY -= 2;
    } else if(sw == 5 || sh == 5) {
        minX -= 2;
        minY -= 2;
    }

    maxX = minX + sw;
    maxY = minY + sh;
}

bool eGameWidget::canBuildBase(const int minX, const int maxX,
                               const int minY, const int maxY,
                               const eSpecialRequirement& specReq) {
    for(int x = minX; x < maxX; x++) {
        for(int y = minY; y < maxY; y++) {
            const auto t = mBoard->tile(x, y);
            if(!t || t->underBuilding()) return false;
            if(specReq && !specReq(t)) return false;

            const auto ttt = t->terrain();
            const auto ttta = ttt & eTerrain::buildable;
            if(!static_cast<bool>(ttta)) return false;

            const int a = t->altitude();
            const auto tr = t->topRight();
            if(tr && tr->altitude() > a) return false;
            const auto r = t->right();
            if(r && r->altitude() > a) return false;
            const auto br = t->bottomRight();
            if(br && br->altitude() > a) return false;
            const auto b = t->bottom();
            if(b && b->altitude() > a) return false;
            const auto bl = t->bottomLeft();
            if(bl && bl->altitude() > a) return false;
            const auto l = t->left();
            if(l && l->altitude() > a) return false;
            const auto tl = t->topLeft();
            if(tl && tl->altitude() > a) return false;
            const auto tt = t->top();
            if(tt && tt->altitude() > a) return false;
        }
    }
    return true;
}

bool eGameWidget::canBuild(const int tx, const int ty,
                           const int sw, const int sh,
                           const eSpecialRequirement& specReq) {
    int minX;
    int minY;
    int maxX;
    int maxY;
    buildTiles(minX, minY, maxX, maxY, tx, ty, sw, sh);
    return canBuildBase(minX, maxX, minY, maxY, specReq);
}

bool eGameWidget::erase(eTile* const tile) {
    if(!tile) return false;
    if(const auto b = tile->underBuilding()) {
        if(!b->isOnFire()) b->erase();
    }
    const auto t = tile->terrain();
    if(t == eTerrain::forest || t == eTerrain::choppedForest) {
        tile->setTerrain(eTerrain::dry);
    }
    return true;
}

std::vector<ePatrolGuide>::iterator
    eGameWidget::findGuide(const int tx, const int ty) {
    const auto pgs = mPatrolBuilding->patrolGuides();
    const int iMax = pgs->size();
    for(int i = 0; i < iMax; i++) {
        auto& pg = (*pgs)[i];
        if(pg.fX == tx && pg.fY == ty) {
            return pgs->begin() + i;
        }
    }
    return pgs->end();
}

void eGameWidget::updateMinimap() {
    double fx;
    double fy;
    viewedFraction(fx, fy);
    const auto mm = mGm->miniMap();
    mm->viewFraction(fx, fy);
}

int eGameWidget::waterParkId() const {
    return mTime/(mSpeed*150);
}

void eGameWidget::updateAppealMap() {
    if(!mBoard) return;
    mBoard->updateAppealMap();
}

void eGameWidget::showMessage(eTile* const tile, const eMessageType& msg) {
    showMessage(tile, msg.fFull);
}

void eGameWidget::showMessage(eTile* const tile, const eMessage& msg) {
    const auto msgb = new eMessageBox(window());
    msgb->setHeight(height()/3);
    msgb->setWidth(width()/2);
    eAction a;
    if(tile) {
        a = [this, tile]() {
            viewTile(tile);
        };
    }
    const auto& d = mBoard->date();
    msgb->initialize(a, d, msg, mBoard->playerName());
    addWidget(msgb);
    msgb->align(eAlignment::bottom | eAlignment::hcenter);
    msgb->setY(msgb->y() - mGm->width()/10);
    msgb->setX(msgb->x() - mGm->width()/2);
}

bool eGameWidget::roadPath(std::vector<eOrientation>& path) {
    ePathFinder p([](eTileBase* const t) {
        const auto terr = t->terrain();
        const bool tr = static_cast<bool>(eTerrain::buildable & terr);
        if(!tr) return false;
        const auto bt = t->underBuildingType();
        const bool r = bt == eBuildingType::road ||
                       bt == eBuildingType::none;
        if(!r) return false;
        if(!t->walkableElev() && t->isElevationTile()) return false;
        return true;
    }, [&](eTileBase* const t) {
        return t->x() == mPressedTX && t->y() == mPressedTY;
    });
    const auto startTile = mBoard->tile(mHoverTX, mHoverTY);
    const int w = mBoard->width();
    const int h = mBoard->height();
    const bool r = p.findPath(startTile, 100, true, w, h);
    if(!r) return false;
    return p.extractPath(path);
}

bool eGameWidget::build(const int tx, const int ty,
                        const int sw, const int sh,
                        const eBuildingCreator& bc,
                        const eSpecialRequirement& specReq,
                        const eRendererCreator& rc) {
    if(!bc) return false;
    const auto tile = mBoard->tile(tx, ty);
    if(!tile) return false;
    const bool cb = canBuild(tx, ty, sw, sh, specReq);
    if(!cb) return false;
    const auto b = bc();
    if(!b) return false;
    const auto rend = rc ? rc() : e::make_shared<eBuildingRenderer>(b);
    tile->setBuilding(rend);
    int minX;
    int minY;
    int maxX;
    int maxY;
    buildTiles(minX, minY, maxX, maxY,
               tx, ty, sw, sh);
    b->setTileRect({minX, minY, sw, sh});
    for(int x = minX; x < maxX; x++) {
        for(int y = minY; y < maxY; y++) {
            const auto t = mBoard->tile(x, y);
            if(t) {
                t->setUnderBuilding(b);
                b->addUnderBuilding(t);
            }
        }
    }

    if(b->type() != eBuildingType::road) {
        sClearScrub(minX, minY, sw, sh, *mBoard);
        sClearForest(minX, minY, sw, sh, *mBoard);
    }

    const auto diff = mBoard->difficulty();
    const int cost = eDifficultyHelpers::buildingCost(diff, b->type());
    mBoard->incDrachmas(-cost);
    return true;
}

bool eGameWidget::sTileFertile(eTile* const tile) {
    return tile->terrain() == eTerrain::fertile;
}

void eGameWidget::buildAnimal(eTile* const tile,
                              const eBuildingType type,
                              const eAnimalCreator& creator) {
    const int tx = tile->x();
    const int ty = tile->y();
    const bool cb = canBuild(tx, ty, 1, 2, sTileFertile);
    if(!cb) return;
    const auto sh = creator(*mBoard);
    sh->changeTile(tile);
    const auto e = []() {};
    sh->setAction(e::make_shared<eAnimalAction>(
                     sh.get(), e, e, tx, ty,
                     eMoveAroundAction::sFertileWalkable));

    const auto diff = mBoard->difficulty();
    const int cost = eDifficultyHelpers::buildingCost(
                         diff, type);
    mBoard->incDrachmas(-cost);

    build(tx, ty, 1, 2, [this, sh, type]() {
        return e::make_shared<eAnimalBuilding>(
                    *mBoard, sh.get(), type);
    }, sTileFertile);
}

stdsptr<eTexture> getBasementTexture(
        eTile* const tile, eBuilding* const d,
        const eTerrainTextures& trrTexs) {
    const int tx = tile->x();
    const int ty = tile->y();

    const auto tr = d->tileRect();
    const int right = tr.x + tr.w - 1;
    const int bottom = tr.y + tr.h - 1;
    int id = 0;
    if(tr.w == 1 && tr.h == 1) {
        id = 0;
    } else if(tx == tr.x) {
        if(ty == tr.y) {
            id = 2;
        } else if(ty == bottom) {
            id = 8;
        } else {
            id = 9;
        }
    } else if(tx == right) {
        if(ty == tr.y) {
            id = 4;
        } else if(ty == bottom) {
            id = 6;
        } else {
            id = 5;
        }
    } else if(ty == tr.y) {
        id = 3;
    } else if(ty == bottom) {
        id = 7;
    } else {
        id = 1;
    }
    const eTextureCollection* coll = nullptr;
    if(d->type() == eBuildingType::commonHouse) {
        coll = &trrTexs.fBuildingBase3;
    } else {
        coll = &trrTexs.fBuildingBase2;
    }
    return coll->getTexture(id);
}

void drawColumn(eTilePainter& tp, const int n,
                const double rx, const double ry,
                const eTextureCollection& coll) {
    double y = 0;
    const auto top = coll.getTexture(0);
    const auto mid = coll.getTexture(1);
    const auto btm = coll.getTexture(2);

    tp.drawTexture(rx + 1 - y, ry - y, btm,
                   eAlignment::hcenter | eAlignment::top);
    y += 0.75;
    for(int i = 0; i < n; i++) {
        tp.drawTexture(rx + 1 - y, ry - y, mid,
                       eAlignment::hcenter | eAlignment::top);
        y += 0.33;
    }
    tp.drawTexture(rx + 1 - y, ry - y, top,
                   eAlignment::hcenter | eAlignment::top);
}

void eGameWidget::paintEvent(ePainter& p) {
    mFrame++;
    if(!mPaused && !mMenu) {
        mTime += mSpeed;
        mBoard->incTime(mSpeed);
    }

    const int uam = mViewMode == eViewMode::appeal ? mFrame % 200 :
                                                     mFrame % 600;
    if(uam == 0) updateAppealMap();

    p.setFont(eFonts::defaultFont(resolution()));
    p.translate(mDX, mDY);
    eTilePainter tp(p, mTileSize, mTileW, mTileH);

    const int tid = static_cast<int>(mTileSize);
    const auto& trrTexs = eGameTextures::terrain().at(tid);
    const auto& builTexs = eGameTextures::buildings().at(tid);
    const auto& intrTexs = eGameTextures::interface().at(tid);
    const auto& destTexs = eGameTextures::destrution().at(tid);
    const auto& charTexs = eGameTextures::characters().at(tid);

    const auto mode = mGm->mode();

    const int sMinX = std::min(mPressedTX, mHoverTX);
    const int sMinY = std::min(mPressedTY, mHoverTY);
    const int sMaxX = std::max(mPressedTX, mHoverTX);
    const int sMaxY = std::max(mPressedTY, mHoverTY);

    const auto drawTerrain = [&](eTile* const tile) {
        const int tx = tile->x();
        const int ty = tile->y();

        int futureDim;
        int drawDim;
        const auto tex = eTileToTexture::get(tile, trrTexs, builTexs,
                                             mTileSize, mDrawElevation,
                                             futureDim, drawDim);
        tile->setFutureDimension(futureDim);

        double rx;
        double ry;
        const int a = mDrawElevation ? tile->altitude() : 0;
        drawXY(tx, ty, rx, ry, drawDim, drawDim, a);

        if(tex) {
            if(drawDim == 3) {
                rx += 1;
                ry -= 1;
            }
            bool s = false;
            if(mPressedTX >= 0 && mPressedTY >= 0) {
                if(tx >= sMinX && tx <= sMaxX &&
                   ty >= sMinY && ty <= sMaxY) {
                    s = true;
                }
            }
            const bool h = tx == mHoverTX && ty == mHoverTY;
            const bool e = mode == eBuildingMode::erase;
            const bool cm = (h || s) && (mTem->visible() || e);
            if(cm) tex->setColorMod(255, 175, 255);
            tp.drawTexture(rx, ry, tex, eAlignment::top);
            if(cm) tex->clearColorMod();
        }
    };

    mBoard->updateTileRenderingOrderIfNeeded();
    iterateOverVisibleTiles([&](eTile* const tile) {
        const int tx = tile->x();
        const int ty = tile->y();
        const int a = mDrawElevation ? tile->altitude() : 0;

        const auto mode = mGm->mode();

        const auto ub = tile->underBuilding();
        const auto bt = tile->underBuildingType();

        const auto tbr = tile->building();

        const bool bv = eViewModeHelpers::buildingVisible(mViewMode, ub);
        const bool v = ub && bv;

        bool bd = false;

        double rx;
        double ry;
        drawXY(tx, ty, rx, ry, 1, 1, a);

        const auto drawSheepGoat = [&]() {
            if(mode == eBuildingMode::sheep ||
               mode == eBuildingMode::goat ||
               mode == eBuildingMode::erase) {
                if(bt == eBuildingType::sheep ||
                   bt == eBuildingType::goat) {
                    const auto tex = trrTexs.fBuildingBase;
                    tp.drawTexture(rx, ry, tex, eAlignment::top);
                    bd = true;
                }
            }
        };

        const auto drawPatrol = [&]() {
            if(mViewMode == eViewMode::patrolBuilding) {
                if(mPatrolBuilding && ub && !tile->hasRoad()) {
                    std::shared_ptr<eTexture> tex;
                    if(ub == mPatrolBuilding) {
                        tex = trrTexs.fSelectedBuildingBase;
                    } else {
                        tex = getBasementTexture(tile, ub, trrTexs);
                    }
                    tp.drawTexture(rx, ry, tex, eAlignment::top);
                    bd = true;
                }
            }
        };

        const auto drawAppeal = [&]() {
            if(!v && mViewMode == eViewMode::appeal) {
                const auto& am = mBoard->appealMap();
                const auto ae = am.enabled(tx, ty);
                const bool ch = bt == eBuildingType::commonHouse;
                if(ae || ch) {
                    const eTextureCollection* coll;
                    if(ch) {
                        coll = &builTexs.fHouseAppeal;
                    } else {
                        coll = &builTexs.fAppeal;
                    }
                    const double app = am.appeal(tx, ty);
                    const double mult = app > 0 ? 1 : -1;
                    const double appS = mult*pow(abs(app), 0.75);
                    int appId = (int)std::round(appS + 2.);
                    appId = std::clamp(appId, 0, 9);
                    const auto tex = coll->getTexture(appId);
                    tp.drawTexture(rx, ry, tex, eAlignment::top);
                    bd = true;
                }
            }
        };

        const auto drawBuilding = [&]() {
            if(bt == eBuildingType::park) {
                int futureDim = 1;
                int drawDim = 1;
                const auto tex = eVaryingSizeTex::getVaryingTexture(
                                     eParkTexture::get, tile,
                                     builTexs.fPark,
                                     builTexs.fLargePark,
                                     builTexs.fHugePark,
                                     futureDim, drawDim);
                tile->setFutureDimension(futureDim);
                if(drawDim > 0) {
                    double rx0 = rx;
                    double ry0 = ry;
                    if(drawDim == 2) {
                        rx0 += 0.5;
                        ry0 += 0.5;
                    } else if(drawDim == 3) {
                        rx0 += 1.0;
                        ry0 += 1.0;
                    }
                    tp.drawTexture(rx0, ry0, tex, eAlignment::top);
                }
            } else {
                double rx;
                double ry;
                drawXY(tx, ty, rx, ry, tbr->spanW(), tbr->spanH(), a);
                tbr->draw(tp, rx, ry);

//                drawXY(tx, ty, rx, ry, 1, 1, a);
//                tp.drawTexture(rx, ry, trrTexs.fSelectedBuildingBase, eAlignment::top);
            }
        };

        const auto drawBuildingModes = [&]() {
            if(mViewMode == eViewMode::hazards) {
                const auto diff = mBoard->difficulty();
                const int fr = eDifficultyHelpers::fireRisk(diff, bt);
                const int dr = eDifficultyHelpers::damageRisk(diff, bt);

                const int h = 100 - ub->maintenance();
                if((fr || dr) && h > 5) {
                    const int n = h/15;
                    const eTextureCollection* coll = nullptr;
                    if(n < 2) {
                        coll = &intrTexs.fColumn1;
                    } else if(n < 3) {
                        coll = &intrTexs.fColumn2;
                    } else if(n < 4) {
                        coll = &intrTexs.fColumn3;
                    } else {
                        coll = &intrTexs.fColumn4;
                    }

                    drawColumn(tp, n, rx, ry, *coll);
                }
            } else if(mViewMode == eViewMode::water) {
                if(bt == eBuildingType::commonHouse) {
                    const auto ch = static_cast<eSmallHouse*>(ub);
                    const int w = ch->water()/2;
                    drawColumn(tp, w, rx, ry, intrTexs.fColumn5);
                }
            } else if(mViewMode == eViewMode::actors) {
                if(bt == eBuildingType::commonHouse) {
                    const auto ch = static_cast<eSmallHouse*>(ub);
                    const int a = ch->actors()/2;
                    drawColumn(tp, a, rx, ry, intrTexs.fColumn1);
                } else if(bt == eBuildingType::eliteHousing) {
                    const auto ch = static_cast<eEliteHousing*>(ub);
                    const int a = ch->actors()/2;
                    drawColumn(tp, a, rx, ry, intrTexs.fColumn1);
                }
            } else if(mViewMode == eViewMode::philosophers) {
                if(bt == eBuildingType::commonHouse) {
                    const auto ch = static_cast<eSmallHouse*>(ub);
                    const int a = ch->philosophers()/2;
                    drawColumn(tp, a, rx, ry, intrTexs.fColumn1);
                } else if(bt == eBuildingType::eliteHousing) {
                    const auto ch = static_cast<eEliteHousing*>(ub);
                    const int a = ch->philosophers()/2;
                    drawColumn(tp, a, rx, ry, intrTexs.fColumn1);
                }
            } else if(mViewMode == eViewMode::athletes) {
                if(bt == eBuildingType::commonHouse) {
                    const auto ch = static_cast<eSmallHouse*>(ub);
                    const int a = ch->athletes()/2;
                    drawColumn(tp, a, rx, ry, intrTexs.fColumn1);
                } else if(bt == eBuildingType::eliteHousing) {
                    const auto ch = static_cast<eEliteHousing*>(ub);
                    const int a = ch->athletes()/2;
                    drawColumn(tp, a, rx, ry, intrTexs.fColumn1);
                }
            } else if(mViewMode == eViewMode::supplies) {
                if(bt == eBuildingType::commonHouse) {
                    const auto ch = static_cast<eSmallHouse*>(ub);
                    double rxx = rx - 2.5;
                    double ryy = ry - 2;
                    tp.drawTexture(rxx, ryy, intrTexs.fSuppliesBg);
                    rxx += 0.32;
                    ryy += 0.32;
                    tp.drawTexture(rxx + 0.17, ryy - 0.17,
                                   ch->lowFood() ?
                                       intrTexs.fNHasFood :
                                       intrTexs.fHasFood);
                    tp.drawTexture(rxx + 0.62, ryy - 0.62,
                                   ch->lowFleece() ?
                                       intrTexs.fNHasFleece :
                                       intrTexs.fHasFleece);
                    tp.drawTexture(rxx + 1.08, ryy - 1.08,
                                   ch->lowOil() ?
                                       intrTexs.fNHasOil :
                                       intrTexs.fHasOil);
                } else if(bt == eBuildingType::eliteHousing) {
                    const auto ch = static_cast<eEliteHousing*>(ub);
                    double rxx = rx - 3.5;
                    double ryy = ry - 1.5;
                    tp.drawTexture(rxx, ryy, intrTexs.fEliteSuppliesBg);
                    rxx += 0.32;
                    ryy += 0.32;
                    tp.drawTexture(rxx + 0.17, ryy - 0.17,
                                   ch->lowFood() ?
                                       intrTexs.fNHasFood :
                                       intrTexs.fHasFood);
                    tp.drawTexture(rxx + 0.62, ryy - 0.62,
                                   ch->lowFleece() ?
                                       intrTexs.fNHasFleece :
                                       intrTexs.fHasFleece);
                    tp.drawTexture(rxx + 1.08, ryy - 1.08,
                                   ch->lowOil() ?
                                       intrTexs.fNHasOil :
                                       intrTexs.fHasOil);
                    tp.drawTexture(rxx + 1.54, ryy - 1.54,
                                   ch->lowWine() ?
                                       intrTexs.fNHasWine :
                                       intrTexs.fHasWine);
                    tp.drawTexture(rxx + 2.00, ryy - 2.00,
                                   ch->lowArms() ?
                                       intrTexs.fNHasArms :
                                       intrTexs.fHasArms);
                    tp.drawTexture(rxx + 2.46, ryy - 2.46,
                                   ch->lowHorses() ?
                                       intrTexs.fNHasHorses :
                                       intrTexs.fHasHorses);
                }
            }
        };

        const auto drawCharacters = [&]() {
            const int dtx = 0; // -1
            const int dty = 0;

            eTile* tt;
            if(dtx == 0 && dty == 0) {
                tt = tile;
            } else {
                tt = mBoard->tile(tx + dtx, ty + dty);
            }
            if(!tt) return;
            const int min = static_cast<int>(eBuildingType::templeAphrodite);
            const int max = static_cast<int>(eBuildingType::templeZeus);
            const auto bt = tt->underBuildingType();
            const int bi = static_cast<int>(bt);
            const bool r = bi >= min && bi <= max;
            if(r ||
               bt == eBuildingType::none ||
               bt == eBuildingType::road ||
               bt == eBuildingType::templeTile ||
               bt == eBuildingType::vine ||
               bt == eBuildingType::oliveTree ||
               bt == eBuildingType::orangeTree ||
               bt == eBuildingType::sheep ||
               bt == eBuildingType::goat ||
               bt == eBuildingType::ruins ||
               bt == eBuildingType::wall) {
                const auto& chars = tt->characters();
                for(const auto& c : chars) {
                    if(!c->visible()) continue;
                    const bool v = eViewModeHelpers::characterVisible(
                                       mViewMode, c->type());
                    if(!v) continue;
                    const double x = tx - a + c->x() + 0.25 + dtx;
                    const double y = ty - a + c->y() + 0.25 + dty;
                    if(c->isSoldier()) {
                        const auto s = static_cast<eSoldier*>(c.get());
                        if(s->selected()) {
                            tp.drawTexture(x - 0.55, y - 0.20, charTexs.fSelected);
                        }
                    }
                    const auto tex = c->getTexture(mTileSize);
                    tp.drawTexture(x, y, tex);
                    if(!c->hasSecondaryTexture()) continue;
                    const auto stex = c->getSecondaryTexture(mTileSize);
                    if(stex.fTex) {
                        tp.drawTexture(x + stex.fX, y + stex.fY, stex.fTex);
                    }
                }
            }
        };

        const auto drawFire = [&]() {
            if(tile->onFire()) {
                const int f = (tx + ty) % destTexs.fFire.size();
                const auto& ff = destTexs.fFire[f];
                const int dt = mTime/8 + tx*ty;
                const auto tex = ff.getTexture(dt % ff.size());
                tp.drawTexture(rx - 2, ry - 3, tex, eAlignment::hcenter);
            }
        };

        const auto drawPatrolGuides = [&]() {
            if(mPatrolBuilding) {
                const auto pgs = mPatrolBuilding->patrolGuides();
                for(const auto& pg : *pgs) {
                    if(pg.fX == tx && pg.fY == ty) {
                        const auto& coll = builTexs.fPatrolGuides;
                        const auto tex = coll.getTexture(14);
                        tp.drawTexture(rx, ry, tex, eAlignment::top);
                        tp.drawTexture(rx, ry - 1, intrTexs.fSpawner,
                                       eAlignment::hcenter | eAlignment::top);
                        break;
                    }
                }
            }
        };

        const auto drawSpawner = [&]() {
            if(mTem->visible() && tile->spawner()) {
                tp.drawTexture(rx, ry - 1, intrTexs.fSpawner,
                               eAlignment::hcenter | eAlignment::top);
            }
        };

        const auto drawClouds = [&]() {
            const bool tr = tile->topRight();
            const bool br = tile->bottomRight();
            const bool bl = tile->bottomLeft();
            const bool tl = tile->topLeft();
            if(!tr || !br || !bl || !tl) {
                const auto& clouds = builTexs.fClouds;
                const int id = tile->seed() % clouds.size();
                const auto tex = builTexs.fClouds.getTexture(id);
                double dx = 0;
                double dy = 0;
                eAlignment align = eAlignment::bottom | eAlignment::right;
                if((!tr && !tl) || (!tr && !br) || (!br && !bl) || (!bl && !tl)) {
                    align = eAlignment::center;
                    dx = -0.25;
                    dy = -1.0;
                } else if(!tile->topRight()) {
                    dx = 1.25;
                    dy = -1.5;
                    align = eAlignment::top | eAlignment::left;
                } else if(!tile->bottomRight()) {
                    dx = -1.5;
                    dy = -1.5;
                } else if(!tile->bottomLeft()) {
                    dx = -2.0;
                    dy = -0.5;
                } else if(!tile->topLeft()) {
                    dx = 1.5;
                    dy = -1.5;
                    align = eAlignment::top | eAlignment::left;
                }
                tp.drawTexture(rx + dx, ry + dy, tex, align);
            }
        };

        const auto drawMissiles = [&]() {
            const auto& mss = tile->missiles();
            for(const auto& m : mss) {
                const double h = m->height();
                const double x = tx - a + m->x() + 0.25 - h;
                const double y = ty - a + m->y() + 0.25 - h;
                const auto tex = m->getTexture(mTileSize);
                tp.drawTexture(x, y, tex);
            }
        };

        const auto drawBanners = [&]() {
            const auto b = tile->banner();
            if(!b) return;
            {
                const auto& rods = charTexs.fBannerRod;
                const auto rod = rods.getTexture(0);
                tp.drawTexture(rx, ry - 1, rod,
                               eAlignment::hcenter | eAlignment::top);
            }
            {
                const int id = b->id();
                const auto& bnrs = charTexs.fBanners;
                const auto& bnr = bnrs[id % bnrs.size()];
                int texId;
                if(b->selected()) {
                    texId = (mFrame/10) % 6;
                } else {
                    texId = 6;
                }
                const auto tex = bnr.getTexture(texId);
                tp.drawTexture(rx - 1, ry - 2.6, tex,
                               eAlignment::hcenter | eAlignment::top);
            }
            {
                const auto type = b->type();
                const auto& tps = charTexs.fBannerTops;
                const int itype = static_cast<int>(type);
                const auto top = tps.getTexture(itype);
                tp.drawTexture(rx - 2.5, ry -  3.5, top,
                               eAlignment::hcenter | eAlignment::top);
            }
        };

        drawSheepGoat();
        drawPatrol();
        drawAppeal();

        if(bd) {
        } else if(ub && !v) {
            const auto tex = getBasementTexture(tile, ub, trrTexs);
            tp.drawTexture(rx, ry, tex, eAlignment::top);
        } else if(tbr && bt != eBuildingType::road) {
            drawBuilding();
            if(ub && tbr && tbr->isMain()) {
                drawBuildingModes();
            }
        }
        drawCharacters();
        drawFire();

        drawPatrolGuides();
        drawSpawner();
        drawBanners();

        drawClouds();

        for(const auto t : tile->terrainTiles()) {
            drawTerrain(t);
        }

        drawMissiles();

        if(mLeftPressed && mMovedSincePress &&
           mGm->mode() == eBuildingMode::none) {
            const int x = mPressedX > mHoverX ? mHoverX : mPressedX;
            const int y = mPressedY > mHoverY ? mHoverY : mPressedY;
            const int w = abs(mPressedX - mHoverX);
            const int h = abs(mPressedY - mHoverY);
            SDL_Rect selRect{x - mDX, y - mDY, w, h};
            p.drawRect(selRect, SDL_Color{0, 255, 0, 255}, 1);
        }
    });

    if(mPatrolBuilding) {
        const auto pgs = mPatrolBuilding->patrolGuides();
        if(!pgs->empty()) {
            const auto t = mPatrolBuilding->centerTile();
            const int tx = t->x();
            const int ty = t->y();
            std::vector<SDL_Point> polygon;
            polygon.reserve(pgs->size() + 2);
            polygon.push_back({tx, ty});
            for(const auto& pg : *pgs) {
                polygon.push_back({pg.fX, pg.fY});
            }
            polygon.push_back({tx, ty});
            tp.drawPolygon(polygon, {0, 0, 0, 255});
        }
    }

    if(mode == eBuildingMode::road && mLeftPressed) {
        const auto startTile = mBoard->tile(mHoverTX, mHoverTY);
        std::vector<eOrientation> path;
        const bool r = roadPath(path);
        if(r) {
            const auto drawRoad = [&](eTile* const t) {
                const auto& tex = trrTexs.fBuildingBase;
                double rx;
                double ry;
                drawXY(t->x(), t->y(), rx, ry, 1, 1, t->altitude());
                tp.drawTexture(rx, ry, tex, eAlignment::top);
            };
            eTile* t = startTile;
            for(int i = path.size() - 1; i >= 0; i--) {
                if(!t) break;
                const auto b1 = e::make_shared<eRoad>(*mBoard);
                drawRoad(t);
                t = t->neighbour<eTile>(path[i]);
            }
            if(t) drawRoad(t);
            return;
        }
    }

    if(mLeftPressed) {
        if(mode == eBuildingMode::vine ||
           mode == eBuildingMode::oliveTree ||
           mode == eBuildingMode::orangeTree) {
            std::shared_ptr<eTexture> tex;
            if(mode == eBuildingMode::vine) {
                tex = builTexs.fVine.getTexture(0);
                tex->setColorMod(0, 255, 0);
            } else if(mode == eBuildingMode::oliveTree) {
                tex = builTexs.fOliveTree.getTexture(0);
                tex->setColorMod(0, 255, 0);
            } else if(mode == eBuildingMode::orangeTree) {
                tex = builTexs.fOrangeTree.getTexture(0);
                tex->setColorMod(0, 255, 0);
            } else {
                tex = trrTexs.fBuildingBase;
            }
            for(int x = sMinX; x <= sMaxX; x++) {
                for(int y = sMinY; y <= sMaxY; y++) {
                    double rx;
                    double ry;
                    const auto t = mBoard->tile(x, y);
                    if(!t) continue;
                    if(t->terrain() != eTerrain::fertile) continue;
                    if(t->underBuilding()) continue;
                    drawXY(x, y, rx, ry, 1, 1, t->altitude());
                    tp.drawTexture(rx, ry, tex, eAlignment::top);
                }
            }
            tex->clearColorMod();
            return;
        }

        if(mode == eBuildingMode::sheep ||
           mode == eBuildingMode::goat) {
            const auto tex = trrTexs.fBuildingBase;
            for(int x = sMinX; x <= sMaxX; x++) {
                for(int y = sMinY; y <= sMaxY; y += 2) {
                    double rx;
                    double ry;
                    const auto t = mBoard->tile(x, y);
                    if(!t) continue;
                    if(t->terrain() != eTerrain::fertile) continue;
                    if(t->underBuilding()) continue;
                    const auto t2 = mBoard->tile(x, y + 1);
                    if(!t2) continue;
                    if(t2->terrain() != eTerrain::fertile) continue;
                    if(t2->underBuilding()) continue;
                    drawXY(x, y, rx, ry, 1, 1, t->altitude());
                    tp.drawTexture(rx, ry, tex, eAlignment::top);
                    tp.drawTexture(rx, ry + 1, tex, eAlignment::top);
                }
            }
            return;
        }

        if(mode == eBuildingMode::park ||
           mode == eBuildingMode::avenue ||
           mode == eBuildingMode::wall) {
            const auto& tex = trrTexs.fBuildingBase;
            for(int x = sMinX; x <= sMaxX; x++) {
                for(int y = sMinY; y <= sMaxY; y++) {
                    double rx;
                    double ry;
                    const auto t = mBoard->tile(x, y);
                    if(!t) continue;
                    if(t->underBuilding()) continue;
                    drawXY(x, y, rx, ry, 1, 1, t->altitude());
                    tp.drawTexture(rx, ry, tex, eAlignment::top);
                }
            }
            return;
        }

        if(mode == eBuildingMode::commonHousing) {
            std::vector<SDL_Rect> rects;
            const auto& tex = trrTexs.fBuildingBase;
            for(int x = sMinX; x <= sMaxX; x++) {
                for(int y = sMinY - 1; y <= sMaxY; y++) {
                    const SDL_Rect rect{x, y, 2, 2};
                    bool cbr = true;
                    for(const auto& r : rects) {
                        const bool i = SDL_HasIntersection(&r, &rect);
                        if(i) {
                            cbr = false;
                            break;
                        }
                    }
                    if(!cbr) continue;
                    const bool cb = canBuildBase(x, x + 2, y, y + 2);
                    if(!cb) continue;
                    double rx;
                    double ry;
                    const auto t = mBoard->tile(x, y);
                    if(!t) continue;
                    drawXY(x, y, rx, ry, 1, 1, t->altitude());
                    tp.drawTexture(rx, ry, tex, eAlignment::top);
                    tp.drawTexture(rx + 1, ry, tex, eAlignment::top);
                    tp.drawTexture(rx, ry + 1, tex, eAlignment::top);
                    tp.drawTexture(rx + 1, ry + 1, tex, eAlignment::top);
                    rects.emplace_back(rect);
                }
            }
            return;
        }
    }

    const auto& tex = trrTexs.fBuildingBase;
    switch(mode) {
    case eBuildingMode::templeArtemis:
    case eBuildingMode::templeHephaestus: {
        const auto bt = eBuildingModeHelpers::toBuildingType(mode);
        const auto h = sanctuaryBlueprint(bt, mRotate);
        const int sw = h->fW;
        const int sh = h->fH;
        const int xMin = mHoverTX - sw/2;
        const int yMin = mHoverTY - sh/2;
        const int xMax = xMin + sw;
        const int yMax = yMin + sh;
        const bool cb = canBuildBase(xMin, xMax, yMin, yMax);
        if(!cb) {
            tex->setColorMod(255, 0, 0);
        }
        for(int x = xMin; x < xMax; x++) {
            for(int y = yMin; y < yMax; y++) {
                double rx;
                double ry;
                const auto t = mBoard->tile(x, y);
                if(!t) continue;
                if(t->underBuilding()) continue;
                drawXY(x, y, rx, ry, 1, 1, t->altitude());
                tp.drawTexture(rx, ry, tex, eAlignment::top);
            }
        }
        if(!cb) {
            tex->clearColorMod();
        }
    } break;
    default: break;
    }

    const auto t = mBoard->tile(mHoverTX, mHoverTY);
    const auto& wrld = mBoard->getWorldBoard();
    eSpecialRequirement specReq;
    if(t && mGm->visible()) {
        struct eB {
            eB(const int tx, const int ty,
               const stdsptr<eBuilding>& b) :
                fTx(tx), fTy(ty), fB(b) {}

            int fTx;
            int fTy;
            stdsptr<eBuilding> fB;
            stdsptr<eBuildingRenderer> fBR;
        };

        std::vector<eB> ebs;
        switch(mode) {
        case eBuildingMode::road: {
            const auto b1 = e::make_shared<eRoad>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::commonHousing: {
            const auto b1 = e::make_shared<eSmallHouse>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::gymnasium: {
            const auto b1 = e::make_shared<eGymnasium>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::podium: {
            const auto b1 = e::make_shared<ePodium>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::fountain: {
            const auto b1 = e::make_shared<eFountain>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::watchpost: {
            const auto b1 = e::make_shared<eWatchpost>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::maintenanceOffice: {
            const auto b1 = e::make_shared<eMaintenanceOffice>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::college: {
            const auto b1 = e::make_shared<eCollege>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::dramaSchool: {
            const auto b1 = e::make_shared<eDramaSchool>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::theater: {
            const auto b1 = e::make_shared<eTheater>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::hospital: {
            const auto b1 = e::make_shared<eHospital>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::stadium: {
            const auto b1 = e::make_shared<eStadium>(*mBoard, mRotate);
            auto& ebs1 = ebs.emplace_back(mHoverTX, mHoverTY, b1);
            ebs1.fBR = e::make_shared<eStadium1Renderer>(b1);
            int dx;
            int dy;
            if(mRotate) {
                dx = 0;
                dy = 5;
            } else {
                dx = 5;
                dy = 0;
            }
            auto& ebs2 = ebs.emplace_back(mHoverTX + dx, mHoverTY + dy, b1);
            ebs2.fBR = e::make_shared<eStadium2Renderer>(b1);
        } break;
        case eBuildingMode::palace: {
            const auto b1 = e::make_shared<ePalace>(*mBoard, mRotate);
            auto& ebs1 = ebs.emplace_back(mHoverTX, mHoverTY, b1);
            ebs1.fBR = e::make_shared<ePalace1Renderer>(b1);
            int dx;
            int dy;
            if(mRotate) {
                dx = 0;
                dy = 4;
            } else {
                dx = 4;
                dy = 0;
            }
            auto& ebs2 = ebs.emplace_back(mHoverTX + dx, mHoverTY + dy, b1);
            ebs2.fBR = e::make_shared<ePalace2Renderer>(b1);
        } break;
        case eBuildingMode::eliteHousing: {
            const auto b1 = e::make_shared<eEliteHousing>(*mBoard);
            auto& ebs1 = ebs.emplace_back(mHoverTX, mHoverTY, b1);
            ebs1.fBR = e::make_shared<eEliteHousingRenderer>(
                           eEliteRendererType::top, b1);
            auto& ebs2 = ebs.emplace_back(mHoverTX + 2, mHoverTY, b1);
            ebs2.fBR = e::make_shared<eEliteHousingRenderer>(
                           eEliteRendererType::right, b1);
            auto& ebs3 = ebs.emplace_back(mHoverTX + 2, mHoverTY + 2, b1);
            ebs3.fBR = e::make_shared<eEliteHousingRenderer>(
                           eEliteRendererType::bottom, b1);
            auto& ebs4 = ebs.emplace_back(mHoverTX, mHoverTY + 2, b1);
            ebs4.fBR = e::make_shared<eEliteHousingRenderer>(
                           eEliteRendererType::left, b1);
        } break;
        case eBuildingMode::taxOffice: {
            const auto b1 = e::make_shared<eTaxOffice>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::mint: {
            const auto b1 = e::make_shared<eMint>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::foundry: {
            const auto b1 = e::make_shared<eFoundry>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::timberMill: {
            const auto b1 = e::make_shared<eTimberMill>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::masonryShop: {
            const auto b1 = e::make_shared<eMasonryShop>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;

        case eBuildingMode::oliveTree: {
            const auto b1 = e::make_shared<eResourceBuilding>(
                                *mBoard, eResourceBuildingType::oliveTree);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
            specReq = sTileFertile;
        } break;
        case eBuildingMode::vine: {
            const auto b1 = e::make_shared<eResourceBuilding>(
                                *mBoard, eResourceBuildingType::vine);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
            specReq = sTileFertile;
        } break;
        case eBuildingMode::orangeTree: {
            const auto b1 = e::make_shared<eResourceBuilding>(
                                *mBoard, eResourceBuildingType::orangeTree);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
            specReq = sTileFertile;
        } break;

        case eBuildingMode::huntingLodge: {
            const auto b1 = e::make_shared<eHuntingLodge>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;

        case eBuildingMode::wheatFarm: {
            const auto b1 = e::make_shared<eWheatFarm>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
            specReq = sTileFertile;
        } break;
        case eBuildingMode::onionFarm: {
            const auto b1 = e::make_shared<eOnionFarm>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
            specReq = sTileFertile;
        } break;
        case eBuildingMode::carrotFarm: {
            const auto b1 = e::make_shared<eCarrotFarm>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
            specReq = sTileFertile;
        } break;

        case eBuildingMode::growersLodge: {
            const auto b1 = e::make_shared<eGrowersLodge>(
                                *mBoard, eGrowerType::grapesAndOlives);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::orangeTendersLodge: {
            const auto b1 = e::make_shared<eGrowersLodge>(
                                *mBoard, eGrowerType::oranges);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;

        case eBuildingMode::granary: {
            const auto b1 = e::make_shared<eGranary>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::warehouse: {
            const auto b1 = e::make_shared<eWarehouse>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;

        case eBuildingMode::tradePost: {
            const int ctid = mGm->cityId();
            const auto cts = wrld.cities();
            const auto ct = cts[ctid];
            const auto b1 = e::make_shared<eTradePost>(*mBoard, *ct);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;


        case eBuildingMode::wall: {
            const auto b1 = e::make_shared<eWall>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::tower: {
            const auto b1 = e::make_shared<eTower>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::gatehouse: {
            int dx;
            int dy;
            if(mRotate) {
                dx = 0;
                dy = 3;
            } else {
                dx = 3;
                dy = 0;
            }
            const auto b1 = e::make_shared<eGatehouse>(*mBoard, mRotate);
            auto& ebs1 = ebs.emplace_back(mHoverTX, mHoverTY, b1);
            ebs1.fBR = e::make_shared<eGatehouseRenderer>(
                           eGatehouseRendererType::grt1, b1);
            auto& ebs2 = ebs.emplace_back(mHoverTX + dx, mHoverTY + dy, b1);
            ebs2.fBR = e::make_shared<eGatehouseRenderer>(
                           eGatehouseRendererType::grt2, b1);
        } break;

        case eBuildingMode::armory: {
            const auto b1 = e::make_shared<eArmory>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::olivePress: {
            const auto b1 = e::make_shared<eOlivePress>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::winery: {
            const auto b1 = e::make_shared<eWinery>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::sculptureStudio: {
            const auto b1 = e::make_shared<eSculptureStudio>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;

        case eBuildingMode::artisansGuild: {
            const auto b1 = e::make_shared<eArtisansGuild>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;

        case eBuildingMode::dairy: {
            const auto b1 = e::make_shared<eDairy>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::cardingShed: {
            const auto b1 = e::make_shared<eCardingShed>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;

        case eBuildingMode::foodVendor: {
            const auto b1 = e::make_shared<eFoodVendor>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::fleeceVendor: {
            const auto b1 = e::make_shared<eFleeceVendor>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::oilVendor: {
            const auto b1 = e::make_shared<eOilVendor>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::wineVendor: {
            const auto b1 = e::make_shared<eWineVendor>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::armsVendor: {
            const auto b1 = e::make_shared<eArmsVendor>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::horseTrainer: {
            const auto b1 = e::make_shared<eHorseVendor>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;

        case eBuildingMode::park: {
            const auto b1 = e::make_shared<ePark>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::doricColumn: {
            const auto b1 = e::make_shared<eDoricColumn>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::ionicColumn: {
            const auto b1 = e::make_shared<eIonicColumn>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::corinthianColumn: {
            const auto b1 = e::make_shared<eCorinthianColumn>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::avenue: {
            const auto b1 = e::make_shared<eAvenue>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;

        case eBuildingMode::populationMonument: {
            const auto b1 = e::make_shared<eCommemorative>(0, *mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::commemorative2: {
            const auto b1 = e::make_shared<eCommemorative>(1, *mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::colonyMonument: {
            const auto b1 = e::make_shared<eCommemorative>(2, *mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::athleteMonument: {
            const auto b1 = e::make_shared<eCommemorative>(3, *mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::conquestMonument: {
            const auto b1 = e::make_shared<eCommemorative>(4, *mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::happinessMonument: {
            const auto b1 = e::make_shared<eCommemorative>(5, *mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::commemorative7: {
            const auto b1 = e::make_shared<eCommemorative>(6, *mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::commemorative8: {
            const auto b1 = e::make_shared<eCommemorative>(7, *mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::scholarMonument: {
            const auto b1 = e::make_shared<eCommemorative>(8, *mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;

        case eBuildingMode::bench: {
            const auto b1 = e::make_shared<eBench>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::flowerGarden: {
            const auto b1 = e::make_shared<eFlowerGarden>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::gazebo: {
            const auto b1 = e::make_shared<eGazebo>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::hedgeMaze: {
            const auto b1 = e::make_shared<eHedgeMaze>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::fishPond: {
            const auto b1 = e::make_shared<eFishPond>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;

        case eBuildingMode::waterPark: {
            const auto b1 = e::make_shared<eWaterPark>(*mBoard);
            b1->setId(waterParkId());
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;

        case eBuildingMode::birdBath: {
            const auto b1 = e::make_shared<eBirdBath>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::shortObelisk: {
            const auto b1 = e::make_shared<eShortObelisk>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::tallObelisk: {
            const auto b1 = e::make_shared<eTallObelisk>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::shellGarden: {
            const auto b1 = e::make_shared<eShellGarden>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::sundial: {
            const auto b1 = e::make_shared<eSundial>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::dolphinSculpture: {
            const auto b1 = e::make_shared<eDolphinSculpture>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::spring: {
            const auto b1 = e::make_shared<eSpring>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::topiary: {
            const auto b1 = e::make_shared<eTopiary>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::baths: {
            const auto b1 = e::make_shared<eBaths>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::stoneCircle: {
            const auto b1 = e::make_shared<eStoneCircle>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        default: break;
        }
        bool cbg = true;
        const int a = t->altitude();
        for(auto& eb : ebs) {
            if(!eb.fBR) eb.fBR = e::make_shared<eBuildingRenderer>(eb.fB);
            const auto b = eb.fBR;
            const int sw =  b->spanW();
            const int sh = b->spanH();
            const bool cb = canBuild(eb.fTx, eb.fTy, sw, sh, specReq);
            if(!cb) cbg = false;
        }
        for(auto& eb : ebs) {
            if(!eb.fB) continue;
            const auto b = eb.fB;

            b->setSeed(0);
            b->addUnderBuilding(t);
            double rx;
            double ry;
            const int sw = eb.fBR->spanW();
            const int sh = eb.fBR->spanH();
            drawXY(eb.fTx, eb.fTy, rx, ry, sw, sh, a);
            const auto tex = eb.fBR->getTexture(tp.size());

            if(tex) {
                if(cbg) tex->setColorMod(0, 255, 0);
                else tex->setColorMod(255, 0, 0);
                tp.drawTexture(rx, ry, tex, eAlignment::top);
                tex->clearColorMod();
            }

            const auto overlays = eb.fBR->getOverlays(tp.size());
            for(const auto& o : overlays) {
                const auto& ttex = o.fTex;
                if(cbg) ttex->setColorMod(0, 255, 0);
                else ttex->setColorMod(255, 0, 0);
                if(o.fAlignTop) tp.drawTexture(rx + o.fX, ry + o.fY, ttex,
                                               eAlignment::top);
                else tp.drawTexture(rx + o.fX, ry + o.fY, ttex);
                ttex->clearColorMod();
            }
        }
    }
}

bool eGameWidget::keyPressEvent(const eKeyPressEvent& e) {
    const auto k = e.key();
    if(k == SDL_Scancode::SDL_SCANCODE_KP_PLUS ||
       k == SDL_Scancode::SDL_SCANCODE_RIGHTBRACKET) {
        mSpeedId = std::clamp(mSpeedId + 1, 0, 4);
        mSpeed = sSpeeds[mSpeedId];
    } else if(k == SDL_Scancode::SDL_SCANCODE_KP_MINUS ||
              k == SDL_Scancode::SDL_SCANCODE_LEFTBRACKET) {
        mSpeedId = std::clamp(mSpeedId - 1, 0, 4);
        mSpeed = sSpeeds[mSpeedId];
    } else if(k == SDL_Scancode::SDL_SCANCODE_R) {
        mRotate = !mRotate;
    } else if(k == SDL_Scancode::SDL_SCANCODE_P) {
        mPaused = !mPaused;
        if(mPaused && !mPausedLabel) {
            mPausedLabel = new eFramedLabel("Paused", window());
            mPausedLabel->fitContent();
            addWidget(mPausedLabel);
            mPausedLabel->align(eAlignment::bottom);
            const int vw = width() - mGm->width();
            const int w = mPausedLabel->width();
            mPausedLabel->setX((vw - w)/2);
        } else if(mPausedLabel) {
            mPausedLabel->deleteLater();
            mPausedLabel = nullptr;
        }
    } else if(k == SDL_Scancode::SDL_SCANCODE_LEFT) {
        mDX += 25;
        updateMinimap();
    } else if(k == SDL_Scancode::SDL_SCANCODE_RIGHT) {
        mDX -= 25;
        updateMinimap();
    } else if(k == SDL_Scancode::SDL_SCANCODE_UP) {
        mDY += 25;
        updateMinimap();
    } else if(k == SDL_Scancode::SDL_SCANCODE_DOWN) {
        mDY -= 25;
        updateMinimap();
    } else if(k == SDL_Scancode::SDL_SCANCODE_ESCAPE) {
        if(mMenu) {
            mMenu->deleteLater();
            mMenu = nullptr;
        } else {
            mMenu = new eGameMainMenu(window());
            mMenu->resize(width()/4, height()/2);
            const auto w = window();
            mMenu->initialize([w]() {
                w->closeGame();
            });
            addWidget(mMenu);
            mMenu->align(eAlignment::center);
        }
    }
    return true;
}

bool eGameWidget::mousePressEvent(const eMouseEvent& e) {
    mMovedSincePress = false;
    const auto b = e.button();
    if(b != eMouseButton::middle) {
        eSounds::playButtonSound();
    }
    switch(b) {
    case eMouseButton::middle:
        mLastX = e.x();
        mLastY = e.y();
        return true;
    case eMouseButton::left:
        mLeftPressed = true;
        int tx;
        int ty;
        pixToId(e.x(), e.y(), tx, ty);
        mPressedTX = tx;
        mPressedTY = ty;
        mPressedX = e.x();
        mPressedY = e.y();
        if(mPatrolBuilding) {
            const auto tile = mBoard->tile(tx, ty);
            if(!tile) return true;
            if(tile->underBuilding() == mPatrolBuilding) {
                const auto pgs = mPatrolBuilding->patrolGuides();
                pgs->clear();
            } else {
                const auto pgs = mPatrolBuilding->patrolGuides();
                const auto it = findGuide(tx, ty);
                if(it != pgs->end()) {
                    pgs->erase(it);
                } else {
                    if(tile->hasRoad()) pgs->push_back({tx, ty});
                }
            }
        }
        return true;
    case eMouseButton::right: {
        const auto& solds = mBoard->selectedSoldiers();
        mGm->clearMode();
        if(!solds.empty()) return true;
        int tx;
        int ty;
        pixToId(e.x(), e.y(), tx, ty);
        if(mPatrolBuilding) {
            setViewMode(eViewMode::defaultView);
            mPatrolBuilding = nullptr;
        }
        const auto tile = mBoard->tile(tx, ty);
        if(!tile) return true;
        const auto b = tile->underBuilding();
        if(!b) return true;
        eInfoWidget* wid = nullptr;
        eAction closeAct;
        if(const auto gym = dynamic_cast<eGymnasium*>(b)) {
            const auto gymWid = new eGymInfoWidget(window());
            gymWid->initialize();
            wid = gymWid;
        } else if(const auto stor = dynamic_cast<eTradePost*>(b)) {
            const auto storWid = new eTradePostInfoWidget(window());
            storWid->initialize(stor);
            wid = storWid;
            const stdptr<eTradePost> storptr(stor);
            closeAct = [storptr, storWid]() {
                if(storptr) {
                    std::map<eResourceType, int> maxCount;
                    eResourceType imports;
                    eResourceType exports;
                    storWid->get(imports, exports, maxCount);
                    storptr->setOrders(imports, exports);
                    storptr->setMaxCount(maxCount);
                }
            };
        } else if(const auto stor = dynamic_cast<eStorageBuilding*>(b)) {
            const auto storWid = new eStorageInfoWidget(window());
            storWid->initialize(stor);
            wid = storWid;
            const stdptr<eStorageBuilding> storptr(stor);
            closeAct = [storptr, storWid]() {
                if(storptr) {
                    std::map<eResourceType, int> maxCount;
                    eResourceType get;
                    eResourceType empty;
                    eResourceType accept;
                    eResourceType dontaccept;
                    storWid->get(get, empty, accept, dontaccept, maxCount);
                    storptr->setOrders(get, empty, accept);
                    storptr->setMaxCount(maxCount);
                }
            };
        }
        if(wid) {
            addWidget(wid);
            wid->setX((width() - mGm->width() - wid->width())/2);
            wid->align(eAlignment::vcenter);
            wid->setCloseAction([this, wid, closeAct]() {
                if(closeAct) closeAct();
                removeWidget(wid);
                wid->deleteLater();
            });
        }
    } break;
    default: return true;
    }
    return true;
}

bool eGameWidget::mouseMoveEvent(const eMouseEvent& e) {
    mMovedSincePress = true;
    if(static_cast<bool>(e.buttons() & eMouseButton::middle)) {
        const int dx = e.x() - mLastX;
        const int dy = e.y() - mLastY;
        mDX += dx;
        mDY += dy;
        updateMinimap();
        mLastX = e.x();
        mLastY = e.y();
    } else {
        mHoverX = e.x();
        mHoverY = e.y();
        pixToId(e.x(), e.y(), mHoverTX, mHoverTY);
    }
    return true;
}

bool eGameWidget::mouseReleaseEvent(const eMouseEvent& e) {
    switch(e.button()) {
    case eMouseButton::left: {
        mBoard->clearSoldierSelection();
        mLeftPressed = false;
        const bool r = buildMouseRelease();
        if(!r) {
            if(mMovedSincePress) {
                const int x0 = mPressedX > mHoverX ? mHoverX : mPressedX;
                const int y0 = mPressedY > mHoverY ? mHoverY : mPressedY;
                const int x1 = mPressedX > mHoverX ? mPressedX : mHoverX;
                const int y1 = mPressedY > mHoverY ? mPressedY : mHoverY;
                int t0x;
                int t0y;
                int t1x;
                int t1y;
                pixToId(x0, y0, t0x, t0y);
                pixToId(x1, y1, t1x, t1y);

                const int w = mBoard->width();
                const int h = mBoard->height();
                const int nRows = w + h - 1;
                int minRow = t0x + t0y;
                int maxRow = t1x + t1y;
                minRow = std::clamp(minRow, 0, nRows);
                maxRow = std::clamp(maxRow, 0, nRows);

                const int minXYDiff = t0x - t0y;
                const int maxXYDiff = t1x - t1y;

                const auto iniIt = eGameBoardDiagonalIterator(minRow, 0, mBoard);
                for(auto it = iniIt; it != mBoard->dEnd();) {
                    if(it.row() > maxRow) break;
                    const auto tile = *it;
                    if(!tile) continue;
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
                    const auto b = tile->banner();
                    if(b) {
                        if(!b->selected()) mBoard->selectSoldier(b);
                    }
                    ++it;
                }
            } else {
                const auto tile = mBoard->tile(mHoverTX, mHoverTY);
                if(!mPatrolBuilding && tile) {
                    if(const auto b = tile->underBuilding()) {
                        if(const auto pb = dynamic_cast<ePatrolBuilding*>(b)) {
                            setViewMode(eViewMode::patrolBuilding);
                            mPatrolBuilding = pb;
                        }
                    }
                }
            }
        }
        mPressedTX = -1;
        mPressedTY = -1;
    } break;
    case eMouseButton::right: {
        const int hx = mHoverTX;
        const int hy = mHoverTY;
        const auto& solds = mBoard->selectedSoldiers();

        const int n = solds.size();
        if(n == 1) {
            solds[0]->moveTo(hx, hy);
        } else if(n > 0) {
            int isld = 0;
            const int slds = solds.size();
            const int dist = 5;

            const auto prcsTile = [&](const int i, const int j) {
                if(isld >= slds) return;
                const int tx = hx + i;
                const int ty = hy + j;
                const auto tt = mBoard->tile(tx, ty);
                if(!tt) return;
                if(!tt->walkable()) return;

                const auto s = solds[isld++];
                s->moveTo(tx, ty);
            };

            for(int k = 0; isld < slds; k += dist) {
                eIterateSquare::iterateSquare(k, prcsTile, dist);
            }
        }
    } break;
    default: return false;
    }

    return true;
}

bool eGameWidget::mouseWheelEvent(const eMouseWheelEvent& e) {
    const bool wheel = std::abs(mWheel) > 3;
    if(!wheel) {
        mWheel += e.dy();
        return true;
    }
    mWheel = 0;
    const auto& sett = window()->settings();
    std::vector<eTileSize> sizes;
    int currSize = 0;
    if(sett.fTinyTextures) {
        sizes.push_back(eTileSize::s15);
        if(mTileSize == eTileSize::s15) {
            currSize = sizes.size() - 1;
        }
    }
    if(sett.fSmallTextures) {
        sizes.push_back(eTileSize::s30);
        if(mTileSize == eTileSize::s30) {
            currSize = sizes.size() - 1;
        }
    }
    if(sett.fMediumTextures) {
        sizes.push_back(eTileSize::s45);
        if(mTileSize == eTileSize::s45) {
            currSize = sizes.size() - 1;
        }
    }
    if(sett.fLargeTextures) {
        sizes.push_back(eTileSize::s60);
        if(mTileSize == eTileSize::s60) {
            currSize = sizes.size() - 1;
        }
    }
    const int sizesC = sizes.size();
    if(e.dy() > 0) {
        const int newSize = currSize + 1;
        if(newSize < sizesC) {
            setTileSize(sizes[newSize]);
        }
    } else {
        const int newSize = currSize - 1;
        if(newSize >= 0) {
            setTileSize(sizes[newSize]);
        }
    }
    return true;
}

void eGameWidget::setTileSize(const eTileSize size) {
    mTileSize = size;
    const int tid = static_cast<int>(mTileSize);
    const auto& trrTexs = eGameTextures::terrain().at(tid);
    const int newW = trrTexs.fTileW;
    const int newH = trrTexs.fTileH;

    mDX = std::round((mDX - width()/2) * static_cast<double>(newW)/mTileW + width()/2);
    mDY = std::round((mDY - height()/2) * static_cast<double>(newH)/mTileH + height()/2);

    mTileW = newW;
    mTileH = newH;

    {
        double fx;
        double fy;
        viewBoxSize(fx, fy);
        const auto mm = mGm->miniMap();
        mm->setViewBoxSize(fx, fy);
    }
}

void eGameWidget::actionOnSelectedTiles(const eTileAction& apply) {
    if(!apply) return;
    const int minX = std::min(mPressedTX, mHoverTX);
    const int minY = std::min(mPressedTY, mHoverTY);
    const int maxX = std::max(mPressedTX, mHoverTX);
    const int maxY = std::max(mPressedTY, mHoverTY);

    for(int x = minX; x <= maxX; x++) {
        for(int y = minY; y <= maxY; y++) {
            const auto tile = mBoard->tile(x, y);
            if(!tile) continue;
            apply(tile);
        }
    }
}
