#include "egamewidget.h"

#include "eterraineditmenu.h"

#include "textures/etiletotexture.h"
#include "textures/egametextures.h"

#include "textures/eparktexture.h"
#include "textures/evaryingsizetex.h"

#include "buildings/allbuildings.h"

#include "missiles/emissile.h"
#include "characters/esoldierbanner.h"

#include "spawners/elandinvasionpoint.h"

#include "characters/esoldier.h"
#include "characters/actions/esoldieraction.h"

#include "evectorhelpers.h"

bool sDontDrawAppeal(const eTerrain terr) {
    return terr == eTerrain::stones ||
           terr == eTerrain::flatStones ||
           terr == eTerrain::tallStones ||
           terr == eTerrain::copper ||
           terr == eTerrain::silver ||
           terr == eTerrain::water;
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

class eGameBoardRegisterLock {
public:
    eGameBoardRegisterLock(eGameBoard& board) :
        mBoard(board) {
        mBoard.setRegisterBuildingsEnabled(false);
    }
    ~eGameBoardRegisterLock() {
        mBoard.setRegisterBuildingsEnabled(true);
    }
private:
    eGameBoard& mBoard;
};

void eGameWidget::setArmyMenuVisible(const bool v) {
    if(mAm->visible() == v) return;
    mAm->setVisible(v);
    if(v) {
        mGm->show();
        mTem->hide();
    } else {
        mTem->setVisible(mEditorMode);
        mGm->setVisible(!mEditorMode);
    }
}

void eGameWidget::updateTerrainTextures(eTile* const tile,
                                        const eTerrainTextures& trrTexs,
                                        const eBuildingTextures& builTexs) {
    auto& painter = tile->terrainPainter();

    painter.fColl = nullptr;
    painter.fTex = eTileToTexture::get(tile, trrTexs, builTexs,
                                       mTileSize, mDrawElevation,
                                       painter.fFutureDim,
                                       painter.fDrawDim,
                                       &painter.fColl);
}

void eGameWidget::updateTerrainTextures() {
    const int tid = static_cast<int>(mTileSize);
    const auto& trrTexs = eGameTextures::terrain().at(tid);
    const auto& builTexs = eGameTextures::buildings().at(tid);

    mBoard->iterateOverAllTiles([&](eTile* const tile) {
        updateTerrainTextures(tile, trrTexs, builTexs);
    });
}

void eGameWidget::paintEvent(ePainter& p) {
    {
        const auto& ss = mBoard->selectedSoldiers();
        const bool v = !ss.empty();
        setArmyMenuVisible(v);
    }
    {
        const auto pbv = eViewMode::patrolBuilding;
        if(!mPatrolBuilding && (mViewMode == pbv || mPatrolPathWid)) {
            setPatrolBuilding(nullptr);
        }
    }
    mFrame++;

    bool updateTips = false;
    for(int i = 0; i < int(mTips.size()); i++) {
        const auto& tip = mTips[i];
        if(mFrame > tip.fLastFrame) {
            tip.fWid->deleteLater();
            mTips.erase(mTips.begin() + i);
            updateTips = true;
            i--;
        }
    }
    if(updateTips) updateTipPositions();
    mBoard->scheduleDataUpdate();
    mBoard->updateAppealMapIfNeeded();
    mBoard->handleFinishedTasks();
    if(!mPaused && !mLocked && !mMenu && !mMsgBox && !mInfoWidget) {
        mTime += mSpeed;
        mBoard->incTime(mSpeed);
    }
    mBoard->emptyRubbish();
    if(mHoverX == 0) {
        setDX(mDX + 35);
    } else if(mHoverX == width() - 1) {
        setDX(mDX - 35);
    }
    if(mHoverY == 0) {
        setDY(mDY + 35);
    } else if(mHoverY == height() - 1) {
        setDY(mDY - 35);
    }
    eGameBoardRegisterLock lock(*mBoard);

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

    const bool terrUpdated = mUpdateTerrain;
    if(mUpdateTerrain) {
        updateTerrainTextures();
        mUpdateTerrain = false;
    }

    const auto drawTerrain = [&](eTile* const tile) {
        const int tx = tile->x();
        const int ty = tile->y();

        if(tile->updateTerrain() || tile->hasRoad()) {
            if(!terrUpdated) {
                updateTerrainTextures(tile, trrTexs, builTexs);
            }
            tile->terrainUpdated();
        }
        auto& painter = tile->terrainPainter();

        const int drawDim = painter.fDrawDim;
        stdsptr<eTexture> tex;
        if(const auto coll = painter.fColl) {
            const int ff = mFrame/20;
            const int id = ff % coll->size();
            tex = coll->getTexture(id);
        } else {
            tex = painter.fTex;
        }

        double rx;
        double ry;
        const int a = mDrawElevation ? tile->altitude() : 0;
        drawXY(tx, ty, rx, ry, drawDim, drawDim, a);

        if(tex) {
            if(drawDim == 3) {
                rx += 1;
                ry -= 1;
            }
            bool eraseCm = false;
            bool patrolCm = false;
            if(mPatrolBuilding && (!mPatrolPath.empty() || !mPatrolPath1.empty())) {
                patrolCm = eVectorHelpers::contains(mPatrolPath, tile) ||
                           eVectorHelpers::contains(mPatrolPath1, tile);
                if(patrolCm) {
                    tex->setColorMod(175, 255, 175);
                } else {
                    patrolCm = eVectorHelpers::contains(mExcessPatrolPath, tile) ||
                               eVectorHelpers::contains(mExcessPatrolPath1, tile);
                    if(patrolCm) {
                        tex->setColorMod(255, 175, 175);
                    }
                }
            } else {
                const auto ub = tile->underBuilding();
                if(ub) {
                    eraseCm = inErase(ub);
                } else {
                    eraseCm = inErase(tx, ty);
                }
                if(eraseCm) tex->setColorMod(255, 175, 255);
            }
            tp.drawTexture(rx, ry, tex, eAlignment::top);
            if(eraseCm || patrolCm) tex->clearColorMod();
        }
    };


    std::vector<eTile*> bridgetTs;
    bool bridgeValid = false;
    bool bridgeRot;
    if(mode == eBuildingMode::bridge) {
        const auto startTile = mBoard->tile(mHoverTX, mHoverTY);
        bridgeValid = bridgeTiles(startTile, bridgetTs, bridgeRot);
    }

    const auto isPatrolSelected = [&](eBuilding* const ub) {
        bool selected = false;
        if(const auto v = dynamic_cast<eVendor*>(ub)) {
            selected = v->agora() == mPatrolBuilding;
        } else if(const auto s = dynamic_cast<eAgoraSpace*>(ub)) {
            selected = s->agora() == mPatrolBuilding;
        } else {
            selected = ub == mPatrolBuilding;
        }
        return selected;
    };

    const auto buildingDrawer = [&](eTile* const tile) {
        const int tx = tile->x();
        const int ty = tile->y();
        const int a = mDrawElevation ? tile->altitude() : 0;

        const auto ub = tile->underBuilding();
        const auto bt = tile->underBuildingType();

        const bool bv = eViewModeHelpers::buildingVisible(mViewMode, ub);
        const bool v = ub && bv;

        double rx;
        double ry;
        drawXY(tx, ty, rx, ry, 1, 1, a);

        const auto drawFire = [&](eTile* const ubt) {
            const int tx = ubt->x();
            const int ty = ubt->y();
            double frx;
            double fry;
            drawXY(tx, ty, frx, fry, 1, 1, a);
            eGameTextures::loadFire();
            const int f = (tx + ty) % destTexs.fFire.size();
            const auto& ff = destTexs.fFire[f];
            const int dt = mTime/8 + std::abs(tx*ty);
            const auto tex = ff.getTexture(dt % ff.size());
            tp.drawTexture(frx + 1, fry, tex, eAlignment::hcenter | eAlignment::top);
        };

        const auto drawBuildingModes = [&]() {
            if(!ub) return;
            const double cdx = -0.65;
            const double cdy = -0.65;
            if(mViewMode == eViewMode::hazards) {
                const auto diff = mBoard->difficulty();
                const int fr = eDifficultyHelpers::fireRisk(diff, bt);
                const int dr = eDifficultyHelpers::damageRisk(diff, bt);
                if(const auto h = dynamic_cast<eHouseBase*>(ub)) {
                    if(h->people() == 0) return;
                }
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

                    drawColumn(tp, n, rx + cdx, ry + cdy, *coll);
                }
            } else if(mViewMode == eViewMode::taxes) {
                if(const auto h = dynamic_cast<eHouseBase*>(ub)) {
                    if(h->people() == 0) return;
                    const bool paid = h->paidTaxes();
                    const int n = paid ? 4 : 0;
                    drawColumn(tp, n, rx + cdx, ry + cdy, intrTexs.fColumn1);
                }
            } else if(mViewMode == eViewMode::water) {
                if(bt == eBuildingType::commonHouse) {
                    const auto ch = static_cast<eSmallHouse*>(ub);
                    if(ch->people() == 0) return;
                    const int w = ch->water()/2;
                    drawColumn(tp, w, rx + cdx, ry + cdy, intrTexs.fColumn5);
                }
            } else if(mViewMode == eViewMode::hygiene) {
                if(bt == eBuildingType::commonHouse) {
                    const auto ch = static_cast<eSmallHouse*>(ub);
                    if(ch->people() == 0) return;
                    const int h = ch->hygiene();
                    const int n = h/15;
                    const eTextureCollection* coll = nullptr;
                    if(n < 2) {
                        coll = &intrTexs.fColumn4;
                    } else if(n < 3) {
                        coll = &intrTexs.fColumn3;
                    } else if(n < 4) {
                        coll = &intrTexs.fColumn2;
                    } else {
                        coll = &intrTexs.fColumn1;
                    }

                    drawColumn(tp, n, rx + cdx, ry + cdy, *coll);
                }
            } else if(mViewMode == eViewMode::unrest) {
                if(bt == eBuildingType::commonHouse) {
                    const auto ch = static_cast<eSmallHouse*>(ub);
                    if(ch->people() == 0) return;
                    const int h = 100 - ch->satisfaction();
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

                    drawColumn(tp, n, rx + cdx, ry + cdy, *coll);
                }
            } else if(mViewMode == eViewMode::actors) {
                if(bt == eBuildingType::commonHouse) {
                    const auto ch = static_cast<eSmallHouse*>(ub);
                    if(ch->people() == 0) return;
                    const int a = ch->actors()/2;
                    drawColumn(tp, a, rx + cdx, ry + cdy, intrTexs.fColumn1);
                } else if(bt == eBuildingType::eliteHousing) {
                    const auto ch = static_cast<eEliteHousing*>(ub);
                    if(ch->people() == 0) return;
                    const int a = ch->actors()/2;
                    drawColumn(tp, a, rx + cdx, ry + cdy, intrTexs.fColumn1);
                }
            } else if(mViewMode == eViewMode::philosophers) {
                if(bt == eBuildingType::commonHouse) {
                    const auto ch = static_cast<eSmallHouse*>(ub);
                    if(ch->people() == 0) return;
                    const int a = ch->philosophers()/2;
                    drawColumn(tp, a, rx + cdx, ry + cdy, intrTexs.fColumn1);
                } else if(bt == eBuildingType::eliteHousing) {
                    const auto ch = static_cast<eEliteHousing*>(ub);
                    if(ch->people() == 0) return;
                    const int a = ch->philosophers()/2;
                    drawColumn(tp, a, rx + cdx, ry + cdy, intrTexs.fColumn1);
                }
            } else if(mViewMode == eViewMode::athletes) {
                if(bt == eBuildingType::commonHouse) {
                    const auto ch = static_cast<eSmallHouse*>(ub);
                    if(ch->people() == 0) return;
                    const int a = ch->athletes()/2;
                    drawColumn(tp, a, rx + cdx, ry + cdy, intrTexs.fColumn1);
                } else if(bt == eBuildingType::eliteHousing) {
                    const auto ch = static_cast<eEliteHousing*>(ub);
                    if(ch->people() == 0) return;
                    const int a = ch->athletes()/2;
                    drawColumn(tp, a, rx + cdx, ry + cdy, intrTexs.fColumn1);
                }
            } else if(mViewMode == eViewMode::supplies) {
                if(bt == eBuildingType::commonHouse) {
                    const auto ch = static_cast<eSmallHouse*>(ub);
                    if(ch->people() == 0) return;
                    double rxx = rx - 2.5;
                    double ryy = ry - 2;
                    tp.drawTexture(rxx, ryy, intrTexs.fSuppliesBg);
                    rxx += 0.49;
                    ryy += 0.15;
                    const double inc = 0.43;
                    tp.drawTexture(rxx, ryy,
                                   ch->lowFood() ?
                                       intrTexs.fNHasFood :
                                       intrTexs.fHasFood);
                    rxx += inc;
                    ryy -= inc;
                    tp.drawTexture(rxx, ryy,
                                   ch->lowFleece() ?
                                       intrTexs.fNHasFleece :
                                       intrTexs.fHasFleece);
                    rxx += inc;
                    ryy -= inc;
                    tp.drawTexture(rxx, ryy,
                                   ch->lowOil() ?
                                       intrTexs.fNHasOil :
                                       intrTexs.fHasOil);
                } else if(bt == eBuildingType::eliteHousing) {
                    const auto ch = static_cast<eEliteHousing*>(ub);
                    if(ch->people() == 0) return;
                    double rxx = rx - 3.5;
                    double ryy = ry - 1.5;
                    tp.drawTexture(rxx, ryy, intrTexs.fEliteSuppliesBg);
                    rxx += 0.49;
                    ryy += 0.15;
                    const double inc = 0.43;
                    tp.drawTexture(rxx, ryy,
                                   ch->lowFood() ?
                                       intrTexs.fNHasFood :
                                       intrTexs.fHasFood);
                    rxx += inc;
                    ryy -= inc;
                    tp.drawTexture(rxx, ryy,
                                   ch->lowFleece() ?
                                       intrTexs.fNHasFleece :
                                       intrTexs.fHasFleece);
                    rxx += inc;
                    ryy -= inc;
                    tp.drawTexture(rxx, ryy,
                                   ch->lowOil() ?
                                       intrTexs.fNHasOil :
                                       intrTexs.fHasOil);
                    rxx += inc;
                    ryy -= inc;
                    tp.drawTexture(rxx, ryy,
                                   ch->lowWine() ?
                                       intrTexs.fNHasWine :
                                       intrTexs.fHasWine);
                    rxx += inc;
                    ryy -= inc;
                    tp.drawTexture(rxx, ryy,
                                   ch->lowArms() ?
                                       intrTexs.fNHasArms :
                                       intrTexs.fHasArms);
                    rxx += inc;
                    ryy -= inc;
                    tp.drawTexture(rxx, ryy,
                                   ch->lowHorses() ?
                                       intrTexs.fNHasHorses :
                                       intrTexs.fHasHorses);
                }
            }
        };

        if(ub && !v) {
            if(!isPatrolSelected(ub) && mViewMode != eViewMode::appeal) {
                const auto tex = getBasementTexture(tile, ub, trrTexs);
                tp.drawTexture(rx, ry, tex, eAlignment::top);
            }
        } else if(ub && !eBuilding::sFlatBuilding(bt)) {
            const auto getDisplacement =
            [](const int w, const int h,
               double& dx, double& dy) {
                if(w == 1 && h == 1) {
                    dx = -0.5;
                    dy = 0.5;
                } else if(w == 2 && h == 2) {
                    dx = -1.;
                    dy = 1.;
                } else if(w == 3 && h == 3) {
                    dx = -1.5;
                    dy = 1.5;
                } else if(w == 4 && h == 4) {
                    dx = -2.;
                    dy = 2.;
                } else if(w == 5 && h == 5) {
                    dx = -2.5;
                    dy = 2.5;
                } else {
                    dx = 0.;
                    dy = 0.;
                }
            };
            const auto size = tp.size();
            const auto ts = ub->getTextureSpace(tx, ty, size);
            const auto tsRect = ts.fRect;
            const int fitY = tsRect.y + tsRect.h - 1;
            const int fitX = tsRect.x + tsRect.w - 1;
            double dx;
            double dy;
            getDisplacement(tsRect.w, tsRect.h, dx, dy);
            const double drawX = fitX + dx + 1 - a;
            const double drawY = fitY + dy + 1 - a;
            if(ty == fitY || tx == fitX) {
                const auto bRender = [&](const int tx, const int ty,
                                         const bool last) {
                    SDL_Rect clipRect;
                    clipRect.y = -10000;
                    clipRect.h = 20000;
                    const int d = ty == fitY ? 1 : 0;
                    clipRect.x = mDX + (tx - ty - d)*mTileW/2;
                    clipRect.w = mTileW/2;
                    SDL_RenderSetClipRect(p.renderer(), &clipRect);

                    const bool erase = inErase(ub);
                    const auto tex = ts.fTex;
                    if(tex) {
                        if(erase) tex->setColorMod(255, 175, 255);
                        tp.drawTexture(drawX, drawY, tex, eAlignment::top);
                        if(erase) tex->clearColorMod();
                    }
                    if(ub->overlayEnabled() && ts.fOvelays) {
                        const auto overlays = ub->getOverlays(size);
                        for(const auto& o : overlays) {
                            const auto& tex = o.fTex;

                            if(erase) tex->setColorMod(255, 175, 255);
                            if(o.fAlignTop) {
                                tp.drawTexture(drawX + o.fX, drawY + o.fY,
                                               tex, eAlignment::top);
                            } else {
                                tp.drawTexture(drawX + o.fX, drawY + o.fY, tex);
                            }
                            if(erase) tex->clearColorMod();
                        }
                    }
                    SDL_RenderSetClipRect(p.renderer(), nullptr);

                    if(last) {
                        if(const auto ch = dynamic_cast<eSmallHouse*>(ub)) {
                            const bool p = ch->plague();
                            if(p && ch->people()) {
                                eGameTextures::loadPlague();
                                const auto& blsd = destTexs.fPlague;
                                const int texId = ub->textureTime() % blsd.size();
                                const auto tex = blsd.getTexture(texId);

                                tp.drawTexture(drawX + 3, drawY + 1, tex, eAlignment::top);
                            }
                        }
                        if(ub->isOnFire()) {
                            const auto& ubts = ub->tilesUnder();
                            for(const auto& ubt : ubts) {
                                drawFire(ubt);
                            }
                        }
                        if(ts.fOvelays && tex) {
                            const int bx = drawX;
                            const int by = drawY - tsRect.h;
                            if(ub->blessed()) {
                                eGameTextures::loadBlessed();
                                const auto& blsd = destTexs.fBlessed;
                                const auto tex = blsd.getTexture(ub->textureTime() % blsd.size());
                                tp.drawTexture(bx, by, tex, eAlignment::bottom);
                            } else if(ub->cursed()) {
                                eGameTextures::loadCursed();
                                const auto& blsd = destTexs.fCursed;
                                const auto tex = blsd.getTexture(ub->textureTime() % blsd.size());
                                tp.drawTexture(bx, by, tex, eAlignment::bottom);
                            }
                        }
                        drawBuildingModes();
                    }
                };
                bRender(tx, ty, false);
                if(tx == fitX && ty == fitY) {
                    bRender(tx + 1, ty + 1, true);
                }
            }
        } else if(ub) {
            if(ub->isOnFire()) {
                const auto& ubts = ub->tilesUnder();
                for(const auto& ubt : ubts) {
                    drawFire(ubt);
                }
            }
        }
    };
    iterateOverVisibleTiles([&](eTile* const tile) {
        const int tx = tile->x();
        const int ty = tile->y();
        const int dtx = tile->dx();
        const int dty = tile->dy();
        const int a = mDrawElevation ? tile->altitude() : 0;

        const auto mode = mGm->mode();

        const auto ub = tile->underBuilding();
        const auto bt = tile->underBuildingType();

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
                if(!ub || !mPatrolBuilding) return;
                const auto ubt = ub->type();
                if(eBuilding::sFlatBuilding(ubt)) return;
                std::shared_ptr<eTexture> tex;
                if(isPatrolSelected(ub)) {
                    tex = trrTexs.fSelectedBuildingBase;
                } else {
                    tex = getBasementTexture(tile, ub, trrTexs);
                }
                tp.drawTexture(rx, ry, tex, eAlignment::top);
                bd = true;
            }
        };

        const auto drawAppeal = [&]() {
            const auto terr = tile->terrain();
            if(sDontDrawAppeal(terr)) return;
            if(!v && mViewMode == eViewMode::appeal) {
                const auto& am = mBoard->appealMap();
                const auto ae = am.enabled(dtx, dty);
                const bool ch = bt == eBuildingType::commonHouse;
                if(ae || ch || tile->underBuilding()) {
                    const eTextureCollection* coll;
                    if(ch) {
                        coll = &trrTexs.fHouseAppeal;
                    } else {
                        coll = &trrTexs.fAppeal;
                    }
                    const double app = am.heat(dtx, dty);
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

        const auto drawCharacters = [&](eTile* const tile,
                                        const bool big) {
            if(!tile) return;
            const int tx = tile->x();
            const int ty = tile->y();
            const int a = tile->altitude();
            const auto bttt = tile->underBuildingType();
            const bool flat = eBuilding::sFlatBuilding(bttt);
            if(flat || bttt == eBuildingType::wall) {
                const auto r = p.renderer();
                const auto& chars = tile->characters();
                for(const auto& c : chars) {
                    if(!c->visible()) continue;
                    const auto ct = c->type();
                    if(ct == eCharacterType::cartTransporter ||
                       ct == eCharacterType::ox ||
                       ct == eCharacterType::trailer) {
                        if(eBuilding::sSanctuaryBuilding(bttt)) {
                            continue;
                        }
                    }
                    const bool cbig = ct == eCharacterType::scylla ||
                                      ct == eCharacterType::kraken;
                    if(big != cbig) continue;
                    const bool v = eViewModeHelpers::characterVisible(
                                       mViewMode, c->type());
                    if(!v) continue;
                    const double cx = c->x();
                    const double cy = c->y();
                    double x = tx - a + cx + 0.25;
                    double y = ty - a + cy + 0.25;
                    {
                        const auto t = tile->top<eTile>();
                        const auto l = tile->left<eTile>();
                        const auto r = tile->right<eTile>();
                        const auto b = tile->bottom<eTile>();
                        const auto tl = tile->topLeft<eTile>();
                        const auto tr = tile->topRight<eTile>();
                        const auto bl = tile->bottomLeft<eTile>();
                        const auto br = tile->bottomRight<eTile>();
                        if(tl && tl->altitude() > a) {
                            const double mult = 1 - cx;
                            const int tla = tl->altitude();
                            const double da = mult*(tla - a);
                            x -= da;
                            y -= da;
                        } else if(tr && tr->altitude() > a) {
                            const double mult = 1 - cy;
                            const int tra = tr->altitude();
                            const double da = mult*(tra - a);
                            x -= da;
                            y -= da;
                        } else if(bl && bl->altitude() > a) {
                            const double mult = cy;
                            const int bla = bl->altitude();
                            const double da = mult*(bla - a);
                            x -= da;
                            y -= da;
                        } else if(br && br->altitude() > a) {
                            const double mult = cx;
                            const int bra = br->altitude();
                            const double da = mult*(bra - a);
                            x -= da;
                            y -= da;
                        } else if(t && t->altitude() > a) {
                            const double mult = (1 - cx)*(1 - cy);
                            const int ta = t->altitude();
                            const double da = mult*(ta - a);
                            x -= da;
                            y -= da;
                        } else if(l && l->altitude() > a) {
                            const double mult = (1 - cx)*cy;
                            const int la = l->altitude();
                            const double da = mult*(la - a);
                            x -= da;
                            y -= da;
                        } else if(r && r->altitude() > a) {
                            const double mult = cx*(1 - cy);
                            const int ra = r->altitude();
                            const double da = mult*(ra - a);
                            x -= da;
                            y -= da;
                        } else if(b && b->altitude() > a) {
                            const double mult = cx*cy;
                            const int ba = b->altitude();
                            const double da = mult*(ba - a);
                            x -= da;
                            y -= da;
                        }
                    }
                    const auto tex = c->getTexture(mTileSize);
                    if(tex) {
                        const double offX = mTileH*tex->offsetX()/30.;
                        const double offY = mTileH*tex->offsetY()/30.;
                        const double dstXf = 0.5*(x - y)*mTileW - offX;
                        const double dstYf = 0.5*(x + y)*mTileH - offY;
                        const int ddstXf = mDX + dstXf;
                        const int ddstYf = mDY + dstYf;
                        const int ddstX = std::round(ddstXf);
                        const int ddstY = std::round(ddstYf);

                        tex->render(r, ddstX, ddstY, false);
                    }
                    if(c->hasSecondaryTexture()) {
                        const auto stex = c->getSecondaryTexture(mTileSize);
                        const auto stexTex = stex.fTex;
                        if(stexTex) {
                            const double offX = mTileH*stexTex->offsetX()/30.;
                            const double offY = mTileH*stexTex->offsetY()/30.;
                            const double sdstXf = 0.5*(x + stex.fX - y - stex.fY)*mTileW - offX;
                            const double sdstYf = 0.5*(x + stex.fX + y + stex.fY)*mTileH - offY;
                            const double sddstXf = mDX + sdstXf;
                            const double sddstYf = mDY + sdstYf;
                            const int sddstX = std::round(sddstXf);
                            const int sddstY = std::round(sddstYf);
                            stexTex->render(r, sddstX, sddstY, false);
                        }
                    }
//                        tex->clearColorMod();
//                      tp.drawTexture(x, y, tex);
                }
            }
        };

        const auto drawNumber = [&](const int id) {
            const auto tex = mNumbers[id % 10];
            tp.drawTexture(rx - 1.65, ry - 2.60, tex,
                           eAlignment::hcenter | eAlignment::top);
        };

        const auto drawPatrolGuides = [&]() {
            if(mPatrolBuilding) {
                using ePatrolGuides = std::vector<ePatrolGuide>;
                const auto drawPGS = [&](const ePatrolGuides& pgs) {
                    int i = 0;
                    for(const auto& pg : pgs) {
                        if(pg.fX == tx && pg.fY == ty) {
                            const bool invalid = !eVectorHelpers::contains(mPatrolPath, tile) &&
                                                 !eVectorHelpers::contains(mPatrolPath1, tile);
                            const auto& tex = intrTexs.fSpawner;
                            if(invalid) tex->setColorMod(255, 125, 125);
                            //const auto& coll = builTexs.fPatrolGuides;
                            //const auto tex = coll.getTexture(14);
                            //tp.drawTexture(rx, ry, tex, eAlignment::top);
                            tp.drawTexture(rx, ry - 1, tex,
                                           eAlignment::hcenter | eAlignment::top);
                            drawNumber(i + 1);
                            if(invalid) tex->clearColorMod();
                            break;
                        }
                        i++;
                    }
                };
                const auto& pgs = mPatrolBuilding->patrolGuides();
                drawPGS(pgs);
            }
        };

        const auto drawSpawner = [&]() {
            const auto b = tile->banner();
            if(mTem->visible() && b) {
                tp.drawTexture(rx, ry - 1, intrTexs.fSpawner,
                               eAlignment::hcenter | eAlignment::top);
                const int id = b->id();
                drawNumber(id);
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
            const auto b = tile->soldierBanner();
            if(!b) return;
            {
                eGameTextures::loadBanners();
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
                int itype;
                if(type == eBannerType::aresWarrior) {
                    itype = 0;
                } else if(type == eBannerType::amazon) {
                    itype = -1;
                } else {
                    itype = static_cast<int>(type);
                }
                if(itype != -1) {
                    const auto top = tps.getTexture(itype);
                    tp.drawTexture(rx - 2.5, ry -  3.5, top,
                                   eAlignment::hcenter | eAlignment::top);
                }
            }
        };


        const auto terrTile = mBoard->tile(tx, ty);
        if(terrTile) {
            const auto terrUb = terrTile->underBuilding();
            const auto terrBt = terrTile->underBuildingType();
            bool flatSanct = false;
            if(terrUb) {
                if(const auto sb = dynamic_cast<eSanctBuilding*>(terrUb)) {
                    flatSanct = sb->progress() <= 0;
                }
            }
            const auto terr = terrTile->terrain();
            if(!terrUb || flatSanct ||
               eBuilding::sFlatBuilding(terrBt)) {
                if(mViewMode == eViewMode::appeal && !terrUb &&
                   !sDontDrawAppeal(terr)) {
                    const auto& am = mBoard->appealMap();
                    const int ttdx = terrTile->dx();
                    const int ttdy = terrTile->dy();
                    const auto ae = am.enabled(ttdx, ttdy);
                    if(!ae) drawTerrain(terrTile);
                } else {
                    drawTerrain(terrTile);
                }
            }
        }
        //drawTerrain(tile);

        drawSheepGoat();
        drawPatrol();
        drawAppeal();

        if(tile->hasFish()) {
            const auto& fh = builTexs.fFish;
            const int t = mTime/30;
            const auto tex = fh.getTexture(t % fh.size());
            const auto a = eAlignment::right | eAlignment::top;
            tp.drawTexture(rx + 1, ry, tex, a);
        }
        if(tile->hasUrchin()) {
            const auto& fh = builTexs.fUrchin;
            const int t = mTime/30;
            const auto tex = fh.getTexture(t % fh.size());
            const auto a = eAlignment::bottom;
            tp.drawTexture(rx + 0.5, ry - 0.5, tex, a);
        }

        const auto drawBridge = [&]() {
            if(mode == eBuildingMode::bridge) {
                eGameTextures::loadBridge();
                const bool r = eVectorHelpers::contains(bridgetTs, tile);
                if(r) {
                    const int texId = bridgeRot ? 11 : 10;
                    const auto& tex = builTexs.fBridge.getTexture(texId);
                    if(bridgeValid) tex->setColorMod(0, 255, 0);
                    else tex->setColorMod(255, 0, 0);
                    tp.drawTexture(rx + 0.5, ry - 0.5, tex,
                                   eAlignment::hcenter | eAlignment::top);
                    tex->clearColorMod();
                }
            }
        };

        drawBridge();
        drawPatrolGuides();
        drawSpawner();

        if(bt == eBuildingType::templeTile) {
            const auto t = static_cast<eTempleTileBuilding*>(ub);
            const int tid = t ? t->id() : 0;
            if(tid >= 10) {
                const auto s = t ? t->sanctuary() : nullptr;
                const int f = s && s->finished();
                if(f) {
                    const auto& coll = builTexs.fSanctuaryFire;
                    const int textureTime = mFrame/4;
                    const int texId = textureTime % coll.size();
                    const auto& tex = coll.getTexture(texId);
                    tp.drawTexture(rx + 0.5, ry - 0.5, tex, eAlignment::bottom);
                }
            }
        }

        const auto r = p.renderer();
        enum class eTileClipSide {
            left, right
        };

        const auto clipTileRect = [&](const eTileClipSide side) {
            SDL_Rect clipRect;
            clipRect.y = -10000;
            clipRect.h = 20000;
            switch(side) {
            case eTileClipSide::left: {
                clipRect.x = mDX + (tile->x() - tile->y() - 1)*mTileW/2;
                clipRect.w = 10000;
            } break;
            case eTileClipSide::right: {
                clipRect.x = mDX + (tile->x() - tile->y() - 1)*mTileW/2 - 10000;
                clipRect.w = mTileW + 10000;
            } break;
            }
            SDL_RenderSetClipRect(r, &clipRect);
        };

        enum class eCharRenderOrder {
            x0y1x1y0,
            x1y1
        };

        const auto tileCharRenderOrder = [](const eTile* tile) {
            const auto tileFlat = [](const eTile* const tile) {
                const auto bt = tile->underBuildingType();
                const bool flat = eBuilding::sFlatBuilding(bt);
                return flat;
            };
            {
                const auto t_x0y1 = tile->bottomLeft<eTile>();
                if(t_x0y1) {
                    const bool flat = tileFlat(t_x0y1);
                    if(!flat) return eCharRenderOrder::x0y1x1y0;
                }
            }
            {
                const auto t_x1y0 = tile->bottomLeft<eTile>();
                if(t_x1y0) {
                    const bool flat = tileFlat(t_x1y0);
                    if(!flat) return eCharRenderOrder::x0y1x1y0;
                }
            }
            return eCharRenderOrder::x1y1;
        };
        {
            const auto tt = tile->tileRel<eTile>(-3, -3);
            if(tt) {
                drawCharacters(tt, true);
            }
        }
        {
            const auto t = tile->top<eTile>();
            if(t) {
                const auto order = tileCharRenderOrder(t);
                if(order == eCharRenderOrder::x1y1) {
                    drawCharacters(t, false);
                }
            }
        }
        {
            const auto tl = tile->topLeft<eTile>();
            if(tl) {
                const auto order = tileCharRenderOrder(tl);
                if(order == eCharRenderOrder::x0y1x1y0) {
                    clipTileRect(eTileClipSide::left);
                    drawCharacters(tl, false);
                    SDL_RenderSetClipRect(r, nullptr);
                }
            }
        }
        {
            const auto tr = tile->topRight<eTile>();
            if(tr) {
                const auto order = tileCharRenderOrder(tr);
                if(order == eCharRenderOrder::x0y1x1y0) {
                    clipTileRect(eTileClipSide::right);
                    drawCharacters(tr, false);
                    SDL_RenderSetClipRect(r, nullptr);
                }
            }
        }

        drawBanners();

        buildingDrawer(tile);

        drawMissiles();

        if(mLeftPressed && mMovedSincePress &&
           mGm->visible() && mGm->mode() == eBuildingMode::none) {
            const int x = mPressedX > mHoverX ? mHoverX : mPressedX;
            const int y = mPressedY > mHoverY ? mHoverY : mPressedY;
            const int w = abs(mPressedX - mHoverX);
            const int h = abs(mPressedY - mHoverY);
            SDL_Rect selRect{x - mDX, y - mDY, w, h};
            p.drawRect(selRect, SDL_Color{0, 255, 0, 255}, 1);
        }
    });

    if(mPatrolBuilding) {
        const auto& pgs = mPatrolBuilding->patrolGuides();
        if(!pgs.empty()) {
            const auto t = mPatrolBuilding->centerTile();
            const int tx = t->x();
            const int ty = t->y();
            const int ta = t->altitude();
            std::vector<SDL_Point> polygon;
            polygon.reserve(pgs.size() + 2);
            polygon.push_back({tx - ta, ty - ta});
            for(const auto& pg : pgs) {
                const int tx = pg.fX;
                const int ty = pg.fY;
                const auto t = mBoard->tile(tx, ty);
                const int ta = t->altitude();
                polygon.push_back({pg.fX - ta, pg.fY - ta});
            }
            polygon.push_back({tx - ta, ty - ta});
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
                drawRoad(t);
                t = t->neighbour<eTile>(path[i]);
            }
            if(t) drawRoad(t);
            return;
        }
    }

    if(mode == eBuildingMode::bridge) {
        if(!bridgeValid && bridgetTs.empty()) {
            eGameTextures::loadBridge();
            const auto hoverTile = mBoard->tile(mHoverTX, mHoverTY);
            const auto& tex = builTexs.fBridge.getTexture(10);
            tex->setColorMod(255, 0, 0);
            double rx;
            double ry;
            const int hx = hoverTile->x();
            const int hy = hoverTile->y();
            const int ha = hoverTile->altitude();
            drawXY(hx, hy, rx, ry, 1, 1, ha);
            tp.drawTexture(rx, ry, tex, eAlignment::top);
            tex->clearColorMod();
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
                    const int a = t->altitude();
                    drawXY(x, y, rx, ry, 1, 1, a);
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
                for(int y = sMinY; y <= sMaxY; y++) {
                    const auto t = mBoard->tile(x, y);
                    if(!t) continue;
                    if(t->terrain() != eTerrain::fertile) continue;
                    if(t->underBuilding()) continue;
                    const auto t2 = mBoard->tile(x, y + 1);
                    if(!t2) continue;
                    if(t2->terrain() != eTerrain::fertile) continue;
                    if(t2->underBuilding()) continue;
                    double rx;
                    double ry;
                    const int a = t->altitude();
                    drawXY(x, y, rx, ry, 1, 1, a);
                    tp.drawTexture(rx, ry, tex, eAlignment::top);
                    tp.drawTexture(rx, ry + 1, tex, eAlignment::top);
                    y++;
                }
            }
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
                    const int a = t->altitude();
                    drawXY(x, y, rx, ry, 1, 1, a);
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
                    const int a = t->altitude();
                    drawXY(x, y, rx, ry, 1, 1, a);
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


    if(mode == eBuildingMode::sheep ||
       mode == eBuildingMode::goat) {
        if(mLeftPressed) return;
        double rx;
        double ry;
        const auto t = mBoard->tile(mHoverTX, mHoverTY);
        if(!t) return;
        const int tx = t->x();
        const int ty = t->y();
        const bool cb = canBuild(tx, ty, 1, 2, true, true);
        const auto& tex = trrTexs.fBuildingBase;
        tex->setColorMod(cb ? 0 : 255, cb ? 255 : 0, 0);
        const int a = t->altitude();
        drawXY(mHoverTX, mHoverTY, rx, ry, 1, 1, a);
        tp.drawTexture(rx, ry, tex, eAlignment::top);
        tp.drawTexture(rx, ry + 1, tex, eAlignment::top);
        tex->clearColorMod();
        return;
    }

    const auto t = mBoard->tile(mHoverTX, mHoverTY);

    switch(mode) {
    case eBuildingMode::commonAgora: {
        eGameTextures::loadAgora();
        const auto& agr = builTexs.fAgora;
        const auto& agrr = builTexs.fAgoraRoad;

        eAgoraOrientation bt;
        const auto p = agoraBuildPlaceIter(t, false, bt);
        if(p.empty()) {
            const auto& tex = trrTexs.fBuildingBase;
            tex->setColorMod(255, 0, 0);
            for(int i = t->x() - 1; i < t->x() + 2; i++) {
                for(int j = t->y() - 3; j < t->y() + 3; j++) {
                    double rx;
                    double ry;
                    const int a = t->altitude();
                    drawXY(i, j, rx, ry, 1, 1, a);
                    tp.drawTexture(rx, ry, tex, eAlignment::top);
                }
            }
            tex->clearColorMod();
            const auto& road = trrTexs.fRoad.getTexture(0);
            road->setColorMod(255, 0, 0);
            for(int j = t->y() - 3; j < t->y() + 3; j++) {
                double rx;
                double ry;
                const int a = t->altitude();
                drawXY(t->x() - 1, j, rx, ry, 1, 1, a);
                tp.drawTexture(rx, ry, road, eAlignment::top);
            }
            road->clearColorMod();
        } else {
            if(bt == eAgoraOrientation::bottomRight) {
                const int iMax = p.size();
                for(int i = 0; i < iMax; i++) {
                    const auto t = p[i];
                    stdsptr<eTexture> tex;
                    int dim;
                    if(i < 6) {
                        const int texId = t->seed() % agrr.size();
                        tex = agrr.getTexture(texId);
                        dim = 1;
                        if(i == 5) i++;
                    } else if(i < 12) {
                        const int texId = t->seed() % agr.size();
                        tex = agr.getTexture(texId);
                        dim = 2;
                        i++;
                    } else {
                        continue;
                    }
                    double rx;
                    double ry;
                    const int tx = t->x();
                    const int ty = t->y();
                    const int a = t->altitude();
                    drawXY(tx, ty, rx, ry, dim, dim, a);
                    tex->setColorMod(0, 255, 0);
                    tp.drawTexture(rx, ry, tex, eAlignment::top);
                    tex->clearColorMod();
                }
            } else if(bt == eAgoraOrientation::topLeft) {
                const int iMax = p.size();
                for(int i = 0; i < iMax; i++) {
                    const auto t = p[i];
                    stdsptr<eTexture> tex;
                    int dim;
                    if(i < 6) {
                        const int texId = t->seed() % agrr.size();
                        tex = agrr.getTexture(texId);
                        dim = 1;
                    } else if(i > 12) {
                        const int texId = t->seed() % agr.size();
                        tex = agr.getTexture(texId);
                        dim = 2;
                        i++;
                    } else {
                        continue;
                    }
                    double rx;
                    double ry;
                    const int tx = t->x();
                    const int ty = t->y();
                    const int a = t->altitude();
                    drawXY(tx, ty, rx, ry, dim, dim, a);
                    tex->setColorMod(0, 255, 0);
                    tp.drawTexture(rx, ry, tex, eAlignment::top);
                    tex->clearColorMod();
                }
            } else if(bt == eAgoraOrientation::bottomLeft) {
                const int iMax = p.size();
                for(int i = 0; i < iMax; i++) {
                    const auto t = p[i];
                    stdsptr<eTexture> tex;
                    int dim;
                    if(i < 6) {
                        const int texId = t->seed() % agrr.size();
                        tex = agrr.getTexture(texId);
                        dim = 1;
                    } else if(i > 11) {
                        const int texId = t->seed() % agr.size();
                        tex = agr.getTexture(texId);
                        dim = 2;
                        i++;
                    } else {
                        continue;
                    }
                    double rx;
                    double ry;
                    const int tx = t->x();
                    const int ty = t->y();
                    const int a = t->altitude();
                    drawXY(tx, ty, rx, ry, dim, dim, a);
                    tex->setColorMod(0, 255, 0);
                    tp.drawTexture(rx, ry, tex, eAlignment::top);
                    tex->clearColorMod();
                }
            } else if(bt == eAgoraOrientation::topRight) {
                const int iMax = p.size();
                for(int i = 0; i < iMax; i++) {
                    const auto t = p[i];
                    stdsptr<eTexture> tex;
                    int dim;
                    if(i < 6) {
                        const int texId = t->seed() % agrr.size();
                        tex = agrr.getTexture(texId);
                        dim = 1;
                    } else if(i < 12) {
                        const int texId = t->seed() % agr.size();
                        tex = agr.getTexture(texId);
                        dim = 2;
                        i++;
                    } else {
                        continue;
                    }
                    double rx;
                    double ry;
                    const int tx = t->x();
                    const int ty = t->y();
                    const int a = t->altitude();
                    drawXY(tx, ty, rx, ry, dim, dim, a);
                    tex->setColorMod(0, 255, 0);
                    tp.drawTexture(rx, ry, tex, eAlignment::top);
                    tex->clearColorMod();
                }
            }
        }
    } break;
    case eBuildingMode::grandAgora: {
        eGameTextures::loadAgora();
        const auto& agr = builTexs.fAgora;
        const auto& agrr = builTexs.fAgoraRoad;

        eAgoraOrientation bt;
        const auto p = agoraBuildPlaceIter(t, true, bt);
        const int tx = t->x();
        const int ty = t->y();
        const int a = t->altitude();
        if(p.empty()) {
            const auto& tex = trrTexs.fBuildingBase;
            tex->setColorMod(255, 0, 0);
            for(int i = tx - 2; i < tx + 3; i++) {
                for(int j = ty - 3; j < ty + 3; j++) {
                    double rx;
                    double ry;
                    drawXY(i, j, rx, ry, 1, 1, a);
                    tp.drawTexture(rx, ry, tex, eAlignment::top);
                }
            }
            tex->clearColorMod();
            const auto& road = trrTexs.fRoad.getTexture(0);
            road->setColorMod(255, 0, 0);
            for(int j = ty - 3; j < ty + 3; j++) {
                double rx;
                double ry;
                drawXY(tx, j, rx, ry, 1, 1, a);
                tp.drawTexture(rx, ry, road, eAlignment::top);
            }
            road->clearColorMod();
        } else {
            if(bt == eAgoraOrientation::bottomRight) {
                const int iMax = p.size();
                for(int i = 0; i < iMax; i++) {
                    const auto t = p[i];
                    stdsptr<eTexture> tex;
                    int dim;
                    if(i < 6) {
                        const int texId = t->seed() % agrr.size();
                        tex = agrr.getTexture(texId);
                        dim = 1;
                    } else if((i > 12 && i < 18) || (i > 24 && i < 30)) {
                        const int texId = t->seed() % agr.size();
                        tex = agr.getTexture(texId);
                        dim = 2;
                        i++;
                    } else {
                        continue;
                    }
                    double rx;
                    double ry;
                    drawXY(tx, ty, rx, ry, dim, dim, a);
                    tex->setColorMod(0, 255, 0);
                    tp.drawTexture(rx, ry, tex, eAlignment::top);
                    tex->clearColorMod();
                }
            } else if(bt == eAgoraOrientation::bottomLeft) {
                const int iMax = p.size();
                for(int i = 0; i < iMax; i++) {
                    const auto t = p[i];
                    stdsptr<eTexture> tex;
                    int dim;
                    if(i < 6) {
                        const int texId = t->seed() % agrr.size();
                        tex = agrr.getTexture(texId);
                        dim = 1;
                    } else if((i < 12) || (i > 29 && i < 35)) {
                        const int texId = t->seed() % agr.size();
                        tex = agr.getTexture(texId);
                        dim = 2;
                        i++;
                    } else {
                        continue;
                    }
                    double rx;
                    double ry;
                    drawXY(tx, ty, rx, ry, dim, dim, a);
                    tex->setColorMod(0, 255, 0);
                    tp.drawTexture(rx, ry, tex, eAlignment::top);
                    tex->clearColorMod();
                }
            }
        }
    } break;
    default: break;
    }

    const auto& wrld = mBoard->getWorldBoard();
    if(t && mGm->visible()) {
        bool fertile = false;
        std::function<bool(const int tx, const int ty,
                           const int sw, const int sh)> canBuildFunc;
        switch(mode) {
        case eBuildingMode::urchinQuay:
        case eBuildingMode::fishery: {
            canBuildFunc = [&](const int tx, const int ty,
                               const int sw, const int sh) {
                (void)sw;
                (void)sh;
                eOrientation o;
                return canBuildFishery(tx, ty, o);
            };
        } break;
        case eBuildingMode::pier: {
            canBuildFunc = [&](const int tx, const int ty,
                               const int sw, const int sh) {
                if(sw > 2 || sh > 2) return true;
                eOrientation o;
                return canBuildPier(tx, ty, o);
            };
        } break;
        case eBuildingMode::palace: {
            canBuildFunc = [&](const int tx, const int ty,
                               const int sw, const int sh) {
                if(mBoard->hasPalace()) return false;
                return canBuild(tx, ty, sw, sh, fertile);
            };
        } break;
        case eBuildingMode::stadium: {
            canBuildFunc = [&](const int tx, const int ty,
                               const int sw, const int sh) {
                if(mBoard->hasStadium()) return false;
                return canBuild(tx, ty, sw, sh, fertile);
            };
        } break;
        case eBuildingMode::foodVendor: {
            canBuildFunc = [&](const int tx, const int ty,
                               const int sw, const int sh) {
                (void)sw;
                (void)sh;
                return canBuildVendor(tx, ty, eResourceType::food);
            };
        } break;
        case eBuildingMode::fleeceVendor: {
            canBuildFunc = [&](const int tx, const int ty,
                               const int sw, const int sh) {
                (void)sw;
                (void)sh;
                return canBuildVendor(tx, ty, eResourceType::fleece);
            };
        } break;
        case eBuildingMode::oilVendor: {
            canBuildFunc = [&](const int tx, const int ty,
                               const int sw, const int sh) {
                (void)sw;
                (void)sh;
                return canBuildVendor(tx, ty, eResourceType::oliveOil);
            };
        } break;
        case eBuildingMode::wineVendor: {
            canBuildFunc = [&](const int tx, const int ty,
                               const int sw, const int sh) {
                (void)sw;
                (void)sh;
                return canBuildVendor(tx, ty, eResourceType::wine);
            };
        } break;
        case eBuildingMode::armsVendor: {
            canBuildFunc = [&](const int tx, const int ty,
                               const int sw, const int sh) {
                (void)sw;
                (void)sh;
                return canBuildVendor(tx, ty, eResourceType::armor);
            };
        } break;
        case eBuildingMode::horseTrainer: {
            canBuildFunc = [&](const int tx, const int ty,
                               const int sw, const int sh) {
                (void)sw;
                (void)sh;
                return canBuildVendor(tx, ty, eResourceType::horse);
            };
        } break;
        default: {
            canBuildFunc = [&](const int tx, const int ty,
                               const int sw, const int sh) {
                return canBuild(tx, ty, sw, sh, fertile);
            };
        } break;
        }

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
        case eBuildingMode::templeAphrodite:
        case eBuildingMode::templeApollo:
        case eBuildingMode::templeAres:
        case eBuildingMode::templeArtemis:
        case eBuildingMode::templeAthena:
        case eBuildingMode::templeAtlas:
        case eBuildingMode::templeDemeter:
        case eBuildingMode::templeDionysus:
        case eBuildingMode::templeHades:
        case eBuildingMode::templeHephaestus:
        case eBuildingMode::templeHera:
        case eBuildingMode::templeHermes:
        case eBuildingMode::templePoseidon:
        case eBuildingMode::templeZeus: {
            const auto& tex = trrTexs.fBuildingBase;
            const auto bt = eBuildingModeHelpers::toBuildingType(mode);
            const auto h = eSanctBlueprints::sSanctuaryBlueprint(bt, mRotate);
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
                    const int a = t->altitude();
                    drawXY(x, y, rx, ry, 1, 1, a);
                    tp.drawTexture(rx, ry, tex, eAlignment::top);
                }
            }
           if(!cb) {
               tex->clearColorMod();
            }
//            const auto bt = eBuildingModeHelpers::toBuildingType(mode);
//            const auto h = eSanctBlueprints::sSanctuaryBlueprint(bt, mRotate);
//            const int sw = h->fW;
//            const int sh = h->fH;
//            const int minX = mHoverTX - sw/2;
//            const int maxX = minX + sw;
//            const int minY = mHoverTY - sh/2;
//            const int maxY = minY + sh;
//            const bool cb = canBuildBase(minX, maxX, minY, maxY);
//            const int rmod = cb ? 0 : 255;
//            const int gmod = cb ? 255 : 0;

//            eGodType god;
//            stdsptr<eSanctuary> b;
//            switch(mode) {
//            case eBuildingMode::templeZeus: {
//                god = eGodType::zeus;
//                b = e::make_shared<eZeusSanctuary>(
//                        sw, sh, *mBoard);
//            } break;
//            case eBuildingMode::templeArtemis: {
//                god = eGodType::artemis;
//                b = e::make_shared<eArtemisSanctuary>(
//                        sw, sh, *mBoard);
//            } break;
//            case eBuildingMode::templeHephaestus: {
//                god = eGodType::hephaestus;
//                b = e::make_shared<eHephaestusSanctuary>(
//                        sw, sh, *mBoard);
//            } break;
//            default:
//                break;
//            }

//            const auto mint = mBoard->tile(mHoverTX, mHoverTY);
//            if(!mint) return;
//            const int a = mint->altitude();
//            b->setAltitude(a);

//            b->setTileRect({minX, minY, sw, sh});
//            const auto ct = mBoard->tile((minX + maxX)/2, (minY + maxY)/2);
//            b->setCenterTile(ct);

//            const auto tb = e::make_shared<eTempleBuilding>(*mBoard);
//            tb->setSanctuary(b.get());
//            b->registerElement(tb);

//            for(const auto& tv : h->fTiles) {
//                for(const auto& t : tv) {
//                    const double tx = minX + t.fX + 0.5;
//                    const double ty = minY + t.fY + 1.5;
//                    const int alt = a + t.fA;
//                    switch(t.fType) {
//                    case eSanctEleType::tile: {
//                        const auto tt = e::make_shared<eTempleTileBuilding>(
//                                            t.fId, *mBoard);
//                        tt->setSanctuary(b.get());
//                        b->registerElement(tt);
//                        const auto tex = tt->getTileTexture(tp.size());
//                        tex->setColorMod(rmod, gmod, 0);
//                        tp.drawTexture(tx - alt, ty - alt, tex, eAlignment::top);
//                        tex->clearColorMod();
//                    } break;
//                    case eSanctEleType::stairs: {
//                        const auto s = e::make_shared<eStairsRenderer>(t.fId, b);
//                        const auto tex = s->getTexture(tp.size());
//                        tex->setColorMod(rmod, gmod, 0);
//                        tp.drawTexture(tx - alt, ty - alt, tex, eAlignment::top);
//                        tex->clearColorMod();
//                    } break;
//                    default:
//                        break;
//                    };
//                }
//            }
//            for(const auto& tv : h->fTiles) {
//                for(const auto& t : tv) {
//                    const double tx = minX + t.fX + 0.5;
//                    const double ty = minY + t.fY + 1.5;
//                    const auto tile = mBoard->tile(tx, ty);
//                    if(!tile) continue;
//                    const int alt = a + t.fA;
//                    switch(t.fType) {
//                    case eSanctEleType::copper: {
//                        const int tid = static_cast<int>(mTileSize);
//                        const auto& textures = eGameTextures::terrain().at(tid);
//                        const auto tex = textures.fBronzeTerrainTexs.getTexture(0);
//                        tex->setColorMod(rmod, gmod, 0);
//                        tp.drawTexture(tx - alt, ty - alt, tex, eAlignment::top);
//                        tex->clearColorMod();
//                    } break;
//                    case eSanctEleType::statue: {
//                        const auto tt = e::make_shared<eTempleStatueBuilding>(
//                                           god, t.fId, *mBoard);
//                        tt->setSanctuary(b.get());
//                        b->registerElement(tt);
//                        const auto tex = tt->getTexture(tp.size());
//                        tex->setColorMod(rmod, gmod, 0);
//                        tp.drawTexture(tx - alt, ty - alt, tex, eAlignment::top);
//                        tex->clearColorMod();
//                    } break;
//                    case eSanctEleType::monument: {
//                        const auto tt = e::make_shared<eTempleMonumentBuilding>(
//                                            god, t.fId, *mBoard);
//                        tt->setSanctuary(b.get());
//                        const int d = mRotate ? 1 : 0;
//                        b->registerElement(tt);
//                        const auto tex = tt->getTexture(tp.size());
//                        tex->setColorMod(rmod, gmod, 0);
//                        tp.drawTexture(tx - alt - d + 0.5, ty - alt + d + 0.5,
//                                       tex, eAlignment::top);
//                        tex->clearColorMod();
//                    } break;
//                    case eSanctEleType::altar: {
//                        const auto tt = e::make_shared<eTempleAltarBuilding>(
//                                            *mBoard);
//                        tt->setSanctuary(b.get());
//                        const int d = mRotate ? 1 : 0;
//                        b->registerElement(tt);
//                        const auto tex = tt->getTexture(tp.size());
//                        tex->setColorMod(rmod, gmod, 0);
//                        tp.drawTexture(tx - alt - d + 0.5, ty - alt + d + 0.5,
//                                       tex, eAlignment::top);
//                        tex->clearColorMod();
//                    } break;
//                    case eSanctEleType::sanctuary: {
//                        int dx;
//                        int dy;
//                        if(mRotate) {
//                            dx = -2;
//                            dy = 2;
//                        } else {
//                            dx = 1;
//                            dy = -1;
//                        }
//                        const auto tt = e::make_shared<eTempleRenderer>(t.fId, tb);
//                        const auto tex = tt->getTexture(tp.size());
//                        tex->setColorMod(rmod, gmod, 0);
//                        tp.drawTexture(tx - alt + dx + 0.5, ty - alt + dy + 0.5 + 2, tex, eAlignment::top);
//                        tex->clearColorMod();
//                    } break;
//                    default:
//                        break;
//                    }
//                }
//            }
//            tb->setCost({ts*5, ts*5, 0});
//            for(const auto& tv : h->fTiles) {
//                for(const auto& t : tv) {
//                    const int tx = minX + t.fX;
//                    const int ty = minY + t.fY;
//                    const auto tile = mBoard->tile(tx, ty);
//                    tile->setAltitude(tile->altitude() + t.fA);
//                    const auto trr = tile->terrain();
//                    const bool bldbl = static_cast<bool>(
//                                           trr & eTerrain::buildable);
//                    if(!tile->underBuilding() && bldbl) {
//                        tile->setUnderBuilding(b);
//                        b->addUnderBuilding(tile);
//                    }
//                }
//            }
        } break;
        case eBuildingMode::road: {
            const auto b1 = e::make_shared<eRoad>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::bridge: {

        } break;
        case eBuildingMode::roadblock: {
            const auto b1 = e::make_shared<eRoad>(*mBoard);
            b1->setRoadblock(true);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
            canBuildFunc = [&](const int tx, const int ty,
                               const int sw, const int sh) {
                (void)sw;
                (void)sh;
                const auto t = mBoard->tile(tx, ty);
                if(!t) return false;
                const bool hr = t->hasRoad();
                if(!hr) return false;
                const bool b = t->hasBridge();
                if(b) return false;
                const auto ub = t->underBuilding();
                const auto r = static_cast<eRoad*>(ub);
                return !r->isRoadblock();
            };
        } break;
        case eBuildingMode::achillesHall:
        case eBuildingMode::atalantaHall:
        case eBuildingMode::bellerophonHall:
        case eBuildingMode::herculesHall:
        case eBuildingMode::jasonHall:
        case eBuildingMode::odysseusHall:
        case eBuildingMode::perseusHall:
        case eBuildingMode::theseusHall: {
            const auto hallType = eBuildingModeHelpers::toBuildingType(mode);
            const auto heroType = eHerosHall::sHallTypeToHeroType(hallType);
            const auto b1 = e::make_shared<eHerosHall>(heroType, *mBoard);
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
            const int tx = mHoverTX;
            const int ty = mHoverTY;
            const auto b1 = e::make_shared<ePalace>(*mBoard, mRotate);

            int dx;
            int dy;
            int sw;
            int sh;
            const int tminX = tx - 2;
            const int tminY = ty - 3;
            int tmaxX;
            int tmaxY;
            if(mRotate) {
                dx = 0;
                dy = 4;
                sw = 4;
                sh = 8;
                tmaxX = tminX + 6;
                tmaxY = tminY + 9;
            } else {
                dx = 4;
                dy = 0;
                sw = 8;
                sh = 4;
                tmaxX = tminX + 9;
                tmaxY = tminY + 6;
            }
            const SDL_Rect rect{tminX + 1, tminY + 1, sw, sh};
            for(int x = tminX; x < tmaxX; x++) {
                for(int y = tminY; y < tmaxY; y++) {
                    const SDL_Point pt{x, y};
                    const bool r = SDL_PointInRect(&pt, &rect);
                    if(r) continue;
                    bool other = x == tminX && y == tminY;
                    if(!other) {
                        if(mRotate) {
                            other = x == tmaxX - 1 && y == tminY;
                        } else {
                            other = x == tminX && y == tmaxY - 1;
                        }
                    }
                    const auto b0 = e::make_shared<ePalaceTile>(
                                        *mBoard, other);
                    b0->setPalace(b1.get());
                    ebs.emplace_back(x, y, b0);
                }
            }

            auto& ebs1 = ebs.emplace_back(tx, ty, b1);
            ebs1.fBR = e::make_shared<ePalace1Renderer>(b1);
            auto& ebs2 = ebs.emplace_back(tx + dx, ty + dy, b1);
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
            fertile = true;
        } break;
        case eBuildingMode::vine: {
            const auto b1 = e::make_shared<eResourceBuilding>(
                                *mBoard, eResourceBuildingType::vine);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
            fertile = true;
        } break;
        case eBuildingMode::orangeTree: {
            const auto b1 = e::make_shared<eResourceBuilding>(
                                *mBoard, eResourceBuildingType::orangeTree);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
            fertile = true;
        } break;

        case eBuildingMode::huntingLodge: {
            const auto b1 = e::make_shared<eHuntingLodge>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;

        case eBuildingMode::urchinQuay: {
            eOrientation o = eOrientation::topRight;
            canBuildFishery(mHoverTX, mHoverTY, o);
            const auto b1 = e::make_shared<eUrchinQuay>(*mBoard, o);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;

        case eBuildingMode::fishery: {
            eOrientation o = eOrientation::topRight;
            canBuildFishery(mHoverTX, mHoverTY, o);
            const auto b1 = e::make_shared<eFishery>(*mBoard, o);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;

        case eBuildingMode::pier: {
            eOrientation o = eOrientation::topRight;
            canBuildFishery(mHoverTX, mHoverTY, o);
            const auto b1 = e::make_shared<ePier>(*mBoard, o);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
            const int ctid = mGm->cityId();
            const auto cts = wrld.cities();
            const auto ct = cts[ctid];
            const auto b2 = e::make_shared<eTradePost>(
                                *mBoard, *ct, eTradePostType::pier);
            int tx = mHoverTX;
            int ty = mHoverTY;
            switch(o) {
            case eOrientation::topRight: {
                ty += 3;
            } break;
            case eOrientation::bottomRight: {
                tx -= 3;
            } break;
            case eOrientation::bottomLeft: {
                ty -= 3;
            } break;
            default:
            case eOrientation::topLeft: {
                tx += 3;
            } break;
            }
            switch(o) {
            case eOrientation::bottomRight:
            case eOrientation::bottomLeft:
                ebs.insert(ebs.begin(), eB{tx, ty, b2});
                break;
            default:
            case eOrientation::topRight:
            case eOrientation::topLeft:
                ebs.emplace_back(tx, ty, b2);
                break;
            }
        } break;

        case eBuildingMode::wheatFarm: {
            const auto b1 = e::make_shared<eWheatFarm>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
            fertile = true;
        } break;
        case eBuildingMode::onionFarm: {
            const auto b1 = e::make_shared<eOnionFarm>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
            fertile = true;
        } break;
        case eBuildingMode::carrotFarm: {
            const auto b1 = e::make_shared<eCarrotFarm>(*mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
            fertile = true;
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
        case eBuildingMode::horseRanch: {
            const int tx = mHoverTX;
            const int ty = mHoverTY;
            const auto b1 = e::make_shared<eHorseRanch>(*mBoard);
            ebs.emplace_back(tx, ty, b1);

            int dx = 0;
            int dy = 0;
            bool under = false;
            if(mRotateId == 0) { // bottomRight
                dx = 3;
            } else if(mRotateId == 1) { // topRight
                dy = -3;
                dx = -1;
                under = true;
            } else if(mRotateId == 2) { // topLeft
                dx = -4;
                dy = 1;
                under = true;
            } else if(mRotateId == 3) { // bottomLeft
                dy = 4;
            }
            const auto b2 = e::make_shared<eHorseRanchEnclosure>(*mBoard);
            b2->setRanch(b1.get());
            if(under) {
                ebs.insert(ebs.begin(), eB{tx + dx, ty + dy, b2});
            } else {
                ebs.emplace_back(tx + dx, ty + dy, b2);
            }
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
        case eBuildingMode::victoryMonument: {
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
        case eBuildingMode::heroicFigureMonument: {
            const auto b1 = e::make_shared<eCommemorative>(6, *mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::diplomacyMonument: {
            const auto b1 = e::make_shared<eCommemorative>(7, *mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::scholarMonument: {
            const auto b1 = e::make_shared<eCommemorative>(8, *mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;

        case eBuildingMode::aphroditeMonument:
        case eBuildingMode::apolloMonument:
        case eBuildingMode::aresMonument:
        case eBuildingMode::artemisMonument:
        case eBuildingMode::athenaMonument:
        case eBuildingMode::atlasMonument:
        case eBuildingMode::demeterMonument:
        case eBuildingMode::dionysusMonument:
        case eBuildingMode::hadesMonument:
        case eBuildingMode::hephaestusMonument:
        case eBuildingMode::heraMonument:
        case eBuildingMode::hermesMonument:
        case eBuildingMode::poseidonMonument:
        case eBuildingMode::zeusMonument: {
            const int tx = mHoverTX;
            const int ty = mHoverTY;
            const int tminX = tx - 1;
            const int tminY = ty - 2;
            const int tmaxX = tminX + 4;
            const int tmaxY = tminY + 4;
            const auto am = eBuildingMode::aphroditeMonument;
            const int id = static_cast<int>(mode) -
                           static_cast<int>(am);
            const auto gt = static_cast<eGodType>(id);
            const auto b1 = e::make_shared<eGodMonument>(
                                gt, eGodQuestId::godQuest1, *mBoard);

            for(int x = tminX; x < tmaxX; x++) {
                for(int y = tminY; y < tmaxY; y++) {
                    const auto b0 = e::make_shared<eGodMonumentTile>(
                                        *mBoard);
                    b0->setMonument(b1.get());
                    ebs.emplace_back(x, y, b0);
                }
            }

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
            const int sw = b->spanW();
            const int sh = b->spanH();
            const bool cb = canBuildFunc(eb.fTx, eb.fTy, sw, sh);
            if(!cb) cbg = false;
        }
        for(auto& eb : ebs) {
            if(!eb.fB) continue;
            const auto b = eb.fB;

            b->setSeed(0);
            b->addUnderBuilding(t);
            b->setCenterTile(t);
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
