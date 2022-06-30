#include "egamewidget.h"

#include "eterraineditmenu.h"

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
#include "buildings/epalacetile.h"
#include "buildings/emint.h"
#include "buildings/efoundry.h"
#include "buildings/etimbermill.h"
#include "buildings/emasonryshop.h"
#include "buildings/etaxoffice.h"
#include "buildings/eresourcebuilding.h"
#include "buildings/ehuntinglodge.h"
#include "buildings/efishery.h"
#include "buildings/epier.h"
#include "buildings/emaintenanceoffice.h"

#include "buildings/egranary.h"
#include "buildings/ewarehouse.h"

#include "buildings/etradepost.h"

#include "buildings/egrowerslodge.h"

#include "buildings/ewinery.h"
#include "buildings/eolivepress.h"
#include "buildings/esculpturestudio.h"
#include "buildings/earmory.h"
#include "buildings/ehorseranch.h"
#include "buildings/ehorseranchenclosure.h"

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

#include "buildings/eagoraspace.h"

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

#include "missiles/emissile.h"
#include "characters/esoldierbanner.h"

#include "characters/esoldier.h"
#include "characters/actions/esoldieraction.h"

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

void eGameWidget::paintEvent(ePainter& p) {
    mFrame++;
    if(!mPaused && !mLocked && !mMenu) {
        mTime += mSpeed;
        mBoard->incTime(mSpeed);
    }
    eGameBoardRegisterLock lock(*mBoard);

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
            bool cm;
            const auto ub = tile->underBuilding();
            if(ub) {
                cm = inErase(ub);
            } else {
                cm = inErase(tx, ty);
            }
            if(cm) tex->setColorMod(255, 175, 255);
            tp.drawTexture(rx, ry, tex, eAlignment::top);
            if(cm) tex->clearColorMod();
        }
    };

    mBoard->updateTileRenderingOrderIfNeeded();
    iterateOverVisibleTiles([&](eTile* const tile) {
        const int tx = tile->x();
        const int ty = tile->y();
        const int dtx = tile->dx();
        const int dty = tile->dy();
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
                const auto ae = am.enabled(dtx, dty);
                const bool ch = bt == eBuildingType::commonHouse;
                if(ae || ch) {
                    const eTextureCollection* coll;
                    if(ch) {
                        coll = &builTexs.fHouseAppeal;
                    } else {
                        coll = &builTexs.fAppeal;
                    }
                    const double app = am.appeal(dtx, dty);
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
                    const bool cm = inErase(tx, ty);
                    if(cm) tex->setColorMod(255, 175, 255);
                    tp.drawTexture(rx0, ry0, tex, eAlignment::top);
                    if(cm) tex->clearColorMod();
                }
            } else {
                double rx;
                double ry;
                drawXY(tx, ty, rx, ry, tbr->spanW(), tbr->spanH(), a);
                const bool e = inErase(ub);
                tbr->draw(tp, rx, ry, e);

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
            const int dtx = -1; // -1
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
            if(r || eBuilding::sFlatBuilding(bt)) {
                const auto& chars = tt->characters();
                for(const auto& c : chars) {
                    if(!c->visible()) continue;
                    const auto ct = c->type();
                    if(ct == eCharacterType::cartTransporter ||
                       ct == eCharacterType::ox ||
                       ct == eCharacterType::trailer) {
                        if(eBuilding::sSanctuaryBuilding(bt)) {
                            continue;
                        }
                    }
                    const bool v = eViewModeHelpers::characterVisible(
                                       mViewMode, c->type());
                    if(!v) continue;
                    double x = tx - a + c->x() + 0.25 + dtx;
                    double y = ty - a + c->y() + 0.25 + dty;
                    const auto t = tile->top<eTile>();
                    const auto l = tile->left<eTile>();
                    const auto r = tile->right<eTile>();
                    const auto b = tile->bottom<eTile>();
                    const auto tl = tile->topLeft<eTile>();
                    const auto tr = tile->topRight<eTile>();
                    const auto bl = tile->bottomLeft<eTile>();
                    const auto br = tile->bottomRight<eTile>();
                    if(tl && tl->altitude() > a) {
                        const double mult = 1 - c->x();
                        const int tla = tl->altitude();
                        const double da = mult*(tla - a);
                        x -= da;
                        y -= da;
                    } else if(tr && tr->altitude() > a) {
                        const double mult = 1 - c->y();
                        const int tra = tr->altitude();
                        const double da = mult*(tra - a);
                        x -= da;
                        y -= da;
                    } else if(bl && bl->altitude() > a) {
                        const double mult = c->y();
                        const int bla = bl->altitude();
                        const double da = mult*(bla - a);
                        x -= da;
                        y -= da;
                    } else if(br && br->altitude() > a) {
                        const double mult = c->x();
                        const int bra = br->altitude();
                        const double da = mult*(bra - a);
                        x -= da;
                        y -= da;
                    } else if(t && t->altitude() > a) {
                        const double mult = (1 - c->x())*(1 - c->y());
                        const int ta = t->altitude();
                        const double da = mult*(ta - a);
                        x -= da;
                        y -= da;
                    } else if(l && l->altitude() > a) {
                        const double mult = (1 - c->x())*c->y();
                        const int la = l->altitude();
                        const double da = mult*(la - a);
                        x -= da;
                        y -= da;
                    } else if(r && r->altitude() > a) {
                        const double mult = c->x()*(1 - c->y());
                        const int ra = r->altitude();
                        const double da = mult*(ra - a);
                        x -= da;
                        y -= da;
                    } else if(b && b->altitude() > a) {
                        const double mult = c->x()*c->y();
                        const int ba = b->altitude();
                        const double da = mult*(ba - a);
                        x -= da;
                        y -= da;
                    }
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

        //drawTerrain(tile);

        drawSheepGoat();
        drawPatrol();
        drawAppeal();

        if(bd) {
        } else if(ub && !v) {
            const auto tex = getBasementTexture(tile, ub, trrTexs);
            tp.drawTexture(rx, ry, tex, eAlignment::top);
        } else if(tbr && bt != eBuildingType::road &&
                  bt != eBuildingType::oliveTree &&
                  bt != eBuildingType::orangeTree &&
                  bt != eBuildingType::vine &&
                  bt != eBuildingType::ruins) {
            drawBuilding();
            if(ub && tbr && tbr->isMain()) {
                drawBuildingModes();
            }
        }

        if(tile->hasFish()) {
            const auto& fh = builTexs.fFish;
            const int t = mTime/30;
            const auto tex = fh.getTexture(t % fh.size());
            const auto a = eAlignment::right | eAlignment::top;
            tp.drawTexture(rx + 1, ry, tex, a);
        }

        drawCharacters();
        drawFire();

        drawPatrolGuides();
        drawSpawner();
        drawBanners();

        for(const auto t : tile->terrainTiles()) {
            drawTerrain(t);
        }

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

    const auto t = mBoard->tile(mHoverTX, mHoverTY);

    const auto& agr = builTexs.fAgora;
    const auto& agrr = builTexs.fAgoraRoad;

    switch(mode) {
    case eBuildingMode::commonAgora: {
        eAgoraOrientation bt;
        const auto p = agoraBuildPlaceIter(t, false, bt);
        if(p.empty()) {
            const auto& tex = trrTexs.fBuildingBase;
            tex->setColorMod(255, 0, 0);
            for(int i = t->x() - 1; i < t->x() + 2; i++) {
                for(int j = t->y() - 3; j < t->y() + 3; j++) {
                    double rx;
                    double ry;
                    drawXY(i, j, rx, ry, 1, 1, t->altitude());
                    tp.drawTexture(rx, ry, tex, eAlignment::top);
                }
            }
            tex->clearColorMod();
            const auto& road = builTexs.fRoad.getTexture(0);
            road->setColorMod(255, 0, 0);
            for(int j = t->y() - 3; j < t->y() + 3; j++) {
                double rx;
                double ry;
                drawXY(t->x() - 1, j, rx, ry, 1, 1, t->altitude());
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
                    drawXY(t->x(), t->y(), rx, ry, dim, dim, t->altitude());
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
                    drawXY(t->x(), t->y(), rx, ry, dim, dim, t->altitude());
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
                    drawXY(t->x(), t->y(), rx, ry, dim, dim, t->altitude());
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
                    drawXY(t->x(), t->y(), rx, ry, dim, dim, t->altitude());
                    tex->setColorMod(0, 255, 0);
                    tp.drawTexture(rx, ry, tex, eAlignment::top);
                    tex->clearColorMod();
                }
            }
        }
    } break;
    case eBuildingMode::grandAgora: {
        eAgoraOrientation bt;
        const auto p = agoraBuildPlaceIter(t, true, bt);
        if(p.empty()) {
            const auto& tex = trrTexs.fBuildingBase;
            tex->setColorMod(255, 0, 0);
            for(int i = t->x() - 2; i < t->x() + 3; i++) {
                for(int j = t->y() - 3; j < t->y() + 3; j++) {
                    double rx;
                    double ry;
                    drawXY(i, j, rx, ry, 1, 1, t->altitude());
                    tp.drawTexture(rx, ry, tex, eAlignment::top);
                }
            }
            tex->clearColorMod();
            const auto& road = builTexs.fRoad.getTexture(0);
            road->setColorMod(255, 0, 0);
            for(int j = t->y() - 3; j < t->y() + 3; j++) {
                double rx;
                double ry;
                drawXY(t->x(), j, rx, ry, 1, 1, t->altitude());
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
                    drawXY(t->x(), t->y(), rx, ry, dim, dim, t->altitude());
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
                    drawXY(t->x(), t->y(), rx, ry, dim, dim, t->altitude());
                    tex->setColorMod(0, 255, 0);
                    tp.drawTexture(rx, ry, tex, eAlignment::top);
                    tex->clearColorMod();
                }
            }
        }
    } break;
    default: break;
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

    const auto& wrld = mBoard->getWorldBoard();
    if(t && mGm->visible()) {
        eSpecialRequirement specReq;
        std::function<bool(const int tx, const int ty,
                           const int sw, const int sh)> canBuildFunc;
        switch(mode) {
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
                return canBuild(tx, ty, sw, sh, specReq);
            };
        } break;
        case eBuildingMode::stadium: {
            canBuildFunc = [&](const int tx, const int ty,
                               const int sw, const int sh) {
                if(mBoard->hasStadium()) return false;
                return canBuild(tx, ty, sw, sh, specReq);
            };
        } break;
        case eBuildingMode::foodVendor:
        case eBuildingMode::fleeceVendor:
        case eBuildingMode::oilVendor:
        case eBuildingMode::wineVendor:
        case eBuildingMode::armsVendor:
        case eBuildingMode::horseTrainer: {
            canBuildFunc = [&](const int tx, const int ty,
                               const int sw, const int sh) {
                (void)sw;
                (void)sh;
                return canBuildVendor(tx, ty);
            };
        } break;
        default: {
            canBuildFunc = [&](const int tx, const int ty,
                               const int sw, const int sh) {
                return canBuild(tx, ty, sw, sh, specReq);
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
                                        *mBoard, b1.get(), other);
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
            const auto b2 = e::make_shared<eHorseRanchEnclosure>(*mBoard, b1.get());
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
            const auto b1 = e::make_shared<eFoodVendor>(nullptr, *mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::fleeceVendor: {
            const auto b1 = e::make_shared<eFleeceVendor>(nullptr, *mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::oilVendor: {
            const auto b1 = e::make_shared<eOilVendor>(nullptr, *mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::wineVendor: {
            const auto b1 = e::make_shared<eWineVendor>(nullptr, *mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::armsVendor: {
            const auto b1 = e::make_shared<eArmsVendor>(nullptr, *mBoard);
            ebs.emplace_back(mHoverTX, mHoverTY, b1);
        } break;
        case eBuildingMode::horseTrainer: {
            const auto b1 = e::make_shared<eHorseVendor>(nullptr, *mBoard);
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