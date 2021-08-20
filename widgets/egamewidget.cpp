#include "egamewidget.h"

#include "eterraineditmenu.h"
#include "etilepainter.h"

#include "emainmenu.h"
#include "egamemenu.h"

#include "textures/etiletotexture.h"
#include "textures/egametextures.h"

#include "characters/edemeter.h"
#include "characters/egymnast.h"
#include "characters/actions/emovearoundaction.h"
#include "characters/actions/emovepathaction.h"
#include "engine/epathfinder.h"

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
#include "buildings/estadium1.h"
#include "buildings/estadium2.h"
#include "buildings/epalace1.h"
#include "buildings/epalace2.h"
#include "buildings/emint.h"
#include "buildings/efoundry.h"
#include "buildings/etimbermill.h"
#include "buildings/etaxoffice.h"
#include "buildings/eresourcebuilding.h"
#include "buildings/ehuntinglodge.h"
#include "buildings/emaintenanceoffice.h"

#include "spawners/eboarspawner.h"
#include "spawners/esettlerspawner.h"

#include "echeckbox.h"

eGameWidget::eGameWidget(eMainWindow* const window) :
    eWidget(window), mBoard(&mThreadPool) {}

eGameWidget::~eGameWidget() {}

void eGameWidget::initialize(const int w, const int h) {
    mThreadPool.initialize(w, h);

    const int dim = 25;
    for(int x = 0; x < w; x += dim) {
        const int ww = std::clamp(w - x, 0, dim);
        for(int y = 0; y < h; y += dim) {
            const int hh = std::clamp(h - y, 0, dim);
            mUpdateRects.emplace_back(SDL_Rect{x, y, ww, hh});
        }
    }

    mGm = new eGameMenu(window());
    mGm->initialize();
    addWidget(mGm);
    mGm->align(eAlignment::right | eAlignment::top);
    mGm->setBoard(&mBoard);

    mTem = new eTerrainEditMenu(window());
    mTem->initialize();
    addWidget(mTem);
    mTem->align(eAlignment::right | eAlignment::top);
    mTem->hide();
    mBoard.initialize(w, h);

    const auto swtch = new eCheckBox(window());
    swtch->move(mGm->x(), 0);
    swtch->setCheckAction([this](const bool c) {
        mTem->setVisible(c);
        mGm->setVisible(!c);
    });
    addWidget(swtch);

    setTileSize(eTileSize::s30);

    const auto t = mBoard.tile(0, 0);
    const auto d = new eDemeter(mBoard);
    d->setTile(t);
    d->setAction(new eMoveAroundAction(d));
    t->addCharacter(d);
}

void drawXY(const int tx, const int ty,
            double& rx, double& ry,
            const int wSpan, const int hSpan,
            const int a) {
    rx = tx + 0.5;
    ry = ty + 1.5;

    if(wSpan == 2 && hSpan == 2) {
        rx += 0.5;
        ry += 1.5;
    } else if(wSpan == 3 && hSpan == 3) {
        rx += 0.0;
        ry += 2.0;
    } else if(wSpan == 4 && hSpan == 4) {
        rx += 0.5;
        ry += 3.5;
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
            const auto t = mBoard.tile(x, y);
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

struct eDelayedTexture {
    double fX;
    double fY;
    eTexture fTex;
};

std::vector<eDelayedTexture> gDelayedTextures;

void gDrawDelayed(eTilePainter& p) {
    if(gDelayedTextures.empty()) return;
    const auto& dell = gDelayedTextures.front();
    p.drawTexture(dell.fX, dell.fY, dell.fTex, eAlignment::top);
    gDelayedTextures.erase(gDelayedTextures.begin());
}

void eGameWidget::iterateOverTiles(const eTileAction& a) {
    const int w = mBoard.width();
    const int h = mBoard.height();
    const int nRows = w + h - 1;

    int minRow = -2*mDY/mTileH + 2;
    int maxRow = minRow + 2*height()/mTileH - 2;
    minRow = std::clamp(minRow, 0, nRows);
    maxRow = std::clamp(maxRow, 0, nRows);

    const int minXYDiff = -2*mDX/mTileW;
    const int maxXYDiff = minXYDiff + 2*width()/mTileW - 1;

    const auto iniIt = eGameBoardDiagonalIterator(minRow, 0, &mBoard);
    for(auto it = iniIt; it != mBoard.dEnd(); ++it) {
        if(it.row() > maxRow) break;
        const auto tile = *it;
        const int tx = tile->x();
        const int ty = tile->y();
        const int xmy = tx - ty;
        if(xmy < minXYDiff) continue;
        if(xmy > maxXYDiff) continue;
        a(tile);
    }
}

int gHoverX = -1;
int gHoverY = -1;
int gPressedX = -1;
int gPressedY = -1;

void buildTiles(int& minX, int& minY,
                int& maxX, int& maxY,
                const int tx, const int ty,
                const int sw, const int sh) {
    minX = tx;
    minY = ty;

    if(sw == 2 && sh == 2) {
    } else if(sw == 3 && sh == 3) {
        minX -= 1;
        minY -= 1;
    } else if(sw == 4 && sh == 4) {
        minX -= 1;
        minY -= 1;
    } else if(sw == 5 && sh == 5) {
        minX -= 2;
        minY -= 2;
    }

    maxX = minX + sw;
    maxY = minY + sh;
}

bool eGameWidget::canBuild(const int tx, const int ty,
                           const int sw, const int sh,
                           const eSpecialRequirement& specReq) {
    int minX;
    int minY;
    int maxX;
    int maxY;
    buildTiles(minX, minY, maxX, maxY, tx, ty, sw, sh);

    for(int x = minX; x < maxX; x++) {
        for(int y = minY; y < maxY; y++) {
            const auto t = mBoard.tile(x, y);
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

bool eGameWidget::erase(eTile* const tile) {
    if(!tile) return false;
    if(const auto b = tile->underBuilding()) {
        b->erase();
        delete b;
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
            const int si = static_cast<int>(pg.fDir);
            int nsi = si + 1;
            if(nsi >= 15) {
                pgs->erase(pgs->begin() + i);
            } else {
                const auto ss = static_cast<eMoveDirection>(nsi);
                pg.fDir = ss;
            }
            break;
        }
    }
    return pgs->end();
}

bool eGameWidget::build(const int tx, const int ty,
                        const int sw, const int sh,
                        const eBuildingCreator& bc,
                        const eSpecialRequirement& specReq) {
    if(!bc) return false;
    const auto tile = mBoard.tile(tx, ty);
    if(!tile) return false;
    const bool cb = canBuild(tx, ty, sw, sh, specReq);
    if(!cb) return false;
    const auto b = bc();
    if(!b) return false;
    b->setTile(tile);
    tile->setBuilding(b);
    int minX;
    int minY;
    int maxX;
    int maxY;
    buildTiles(minX, minY, maxX, maxY,
               tx, ty, sw, sh);
    for(int x = minX; x < maxX; x++) {
        for(int y = minY; y < maxY; y++) {
            const auto t = mBoard.tile(x, y);
            if(t) {
                t->setUnderBuilding(b);
                b->addUnderBuilding(t);
            }
        }
    }
    return true;
}

void eGameWidget::paintEvent(ePainter& p) {
    mThreadPool.handleFinished();
    mTime += mSpeed;
    mBoard.incTime(mSpeed);

    if(mUpdateRects.empty()) {
        const int w = mBoard.width();
        const int h = mBoard.height();
        mThreadPool.scheduleUpdate(mBoard, 0, 0, w, h);
    } else {
        const int i = (mUpdateRect++) % mUpdateRects.size();
        const auto& rect = mUpdateRects[i];
        mThreadPool.scheduleUpdate(mBoard, rect.x, rect.y, rect.w, rect.h);
    }

    p.setFont(eFonts::defaultFont(resolution()));
    p.translate(mDX, mDY);
    eTilePainter tp(p, mTileSize, mTileW, mTileH);

    const int tid = static_cast<int>(mTileSize);
    const auto& trrTexs = eGameTextures::terrain().at(tid);
    const auto& builTexs = eGameTextures::buildings().at(tid);

    const int sMinX = std::min(gPressedX, gHoverX);
    const int sMinY = std::min(gPressedY, gHoverY);
    const int sMaxX = std::max(gPressedX, gHoverX);
    const int sMaxY = std::max(gPressedY, gHoverY);
    iterateOverTiles([&](eTile* const tile) {
        const int tx = tile->x();
        const int ty = tile->y();

        int wSpan;
        int hSpan;
        auto tex = eTileToTexture::get(tile, trrTexs,
                                       wSpan, hSpan,
                                       mTileSize, mDrawElevation);
        tile->setDrawnSpan(wSpan, hSpan);

        double rx;
        double ry;
        const int a = mDrawElevation ? tile->altitude() : 0;
        drawXY(tx, ty, rx, ry, wSpan, hSpan, a);

        if(!tex.isNull()) {
            if(wSpan == 2 && hSpan == 2) {
                gDelayedTextures.emplace_back(eDelayedTexture{rx, ry, tex});
                return;
            } else {
                bool s = false;
                if(gPressedX >= 0 && gPressedY >= 0) {
                    if(tx >= sMinX && tx <= sMaxX &&
                       ty >= sMinY && ty <= sMaxY) {
                        s = true;
                    }
                }
                const bool h = tx == gHoverX && ty == gHoverY;
                if(h || s) tex.setColorMod(255, 175, 255);
                tp.drawTexture(rx, ry, tex, eAlignment::top);
                if(h || s) tex.clearColorMod();
            }
        }
        gDrawDelayed(tp);
    });
    iterateOverTiles([&](eTile* const tile) {
        const int tx = tile->x();
        const int ty = tile->y();
        const int a = mDrawElevation ? tile->altitude() : 0;

        if(mPatrolBuilding && tile->underBuilding() && !tile->hasRoad()) {
            double rx;
            double ry;
            drawXY(tx, ty, rx, ry, 1, 1, a);
            const eTexture* tex;
            if(tile->underBuilding() == mPatrolBuilding) {
                tex = &trrTexs.fSelectedBuildingBase;
            } else {
                tex = &trrTexs.fBuildingBase;
            }
            tp.drawTexture(rx, ry, *tex, eAlignment::top);
        }
        if(const auto d = tile->building()) {
            if(!mPatrolBuilding && d->type() != eBuildingType::road) {
                double rx;
                double ry;
                drawXY(tx, ty, rx, ry, d->spanW(), d->spanH(), a);
                d->draw(tp, rx, ry, eAlignment::top);
            }
        }

        const auto& chars = tile->characters();
        for(const auto c : chars) {
            const auto tex = c->getTexture(mTileSize);
            tp.drawTexture(tx - a + c->x() + 0.25, ty - a + c->y() + 0.25, tex);
        }

        if(tile->onFire()) {
            double rx;
            double ry;
            drawXY(tx, ty, rx, ry, 1, 1, a);
            const int f = (tx + ty) % 2;
            const auto& destr = eGameTextures::destrution().at(tid);
            const auto& ff = destr.fFire[f];
            const int dt = mTime/8 + tx*ty;
            const auto tex = ff.getTexture(dt % ff.size());
            tp.drawTexture(rx - 2, ry - 3, tex, eAlignment::hcenter);
        }

        if(mPatrolBuilding) {
            double rx;
            double ry;
            drawXY(tx, ty, rx, ry, 1, 1, a);
            if(tile->building() == mPatrolBuilding) {
                const auto sd = mPatrolBuilding->spawnDirection();
                const int s = static_cast<int>(sd) - 1;
                const auto& coll = builTexs.fPatrolGuides;
                const auto tex = coll.getTexture(s);
                tp.drawTexture(rx, ry, tex, eAlignment::top);
            }
            const auto pgs = mPatrolBuilding->patrolGuides();
            for(const auto& pg : *pgs) {
                if(pg.fX == tx && pg.fY == ty) {
                    const int s = static_cast<int>(pg.fDir) - 1;
                    const auto& coll = builTexs.fPatrolGuides;
                    const auto tex = coll.getTexture(s);
                    tp.drawTexture(rx, ry, tex, eAlignment::top);
                    break;
                }
            }
        }
        if(mTem->visible() && tile->spawner()) {
            double rx;
            double ry;
            drawXY(tx, ty, rx, ry, 1, 1, a);
            const auto& intrfc = eGameTextures::interface().at(tid);
            tp.drawTexture(rx, ry - 1, intrfc.fSpawner,
                           eAlignment::hcenter | eAlignment::top);
        }
    });

    const auto t = mBoard.tile(gHoverX, gHoverY);
    eSpecialRequirement specReq;
    if(t && mGm->visible()) {
        const int tx = gHoverX;
        const int ty = gHoverY;

        struct eB {
            eB(const int tx, const int ty, eBuilding* const b) :
                fTx(tx), fTy(ty), fB(b) {}

            int fTx = gHoverX;
            int fTy = gHoverY;
            eBuilding* fB = nullptr;
        };

        std::vector<eB> ebs;
        const auto mode = mGm->mode();
        switch(mode) {
        case eBuildingMode::road: {
            const auto b1 = new eRoad(mBoard);
            ebs.emplace_back(gHoverX, gHoverY, b1);
        } break;
        case eBuildingMode::commonHousing: {
            const auto b1 = new eSmallHouse(mBoard);
            ebs.emplace_back(gHoverX, gHoverY, b1);
        } break;
        case eBuildingMode::gymnasium: {
            const auto b1 = new eGymnasium(mBoard);
            ebs.emplace_back(gHoverX, gHoverY, b1);
        } break;
        case eBuildingMode::podium: {
            const auto b1 = new ePodium(mBoard);
            ebs.emplace_back(gHoverX, gHoverY, b1);
        } break;
        case eBuildingMode::fountain: {
            const auto b1 = new eFountain(mBoard);
            ebs.emplace_back(gHoverX, gHoverY, b1);
        } break;
        case eBuildingMode::watchpost: {
            const auto b1 = new eWatchpost(mBoard);
            ebs.emplace_back(gHoverX, gHoverY, b1);
        } break;
        case eBuildingMode::maintenanceOffice: {
            const auto b1 = new eMaintenanceOffice(mBoard);
            ebs.emplace_back(gHoverX, gHoverY, b1);
        } break;
        case eBuildingMode::college: {
            const auto b1 = new eCollege(mBoard);
            ebs.emplace_back(gHoverX, gHoverY, b1);
        } break;
        case eBuildingMode::dramaSchool: {
            const auto b1 = new eDramaSchool(mBoard);
            ebs.emplace_back(gHoverX, gHoverY, b1);
        } break;
        case eBuildingMode::theater: {
            const auto b1 = new eTheater(mBoard);
            ebs.emplace_back(gHoverX, gHoverY, b1);
        } break;
        case eBuildingMode::hospital: {
            const auto b1 = new eHospital(mBoard);
            ebs.emplace_back(gHoverX, gHoverY, b1);
        } break;
        case eBuildingMode::stadium: {
            if(mRotate) {
                const auto b1 = new eStadium1H(mBoard);
                ebs.emplace_back(gHoverX, gHoverY, b1);
                const auto b2 = new eStadium2H(mBoard);
                ebs.emplace_back(gHoverX, gHoverY + 5, b2);
            } else {
                const auto b1 = new eStadium1W(mBoard);
                ebs.emplace_back(gHoverX, gHoverY, b1);
                const auto b2 = new eStadium2W(mBoard);
                ebs.emplace_back(gHoverX + 5, gHoverY, b2);
            }
        } break;
        case eBuildingMode::palace: {
            if(mRotate) {
                const auto b1 = new ePalace1H(mBoard);
                ebs.emplace_back(gHoverX, gHoverY, b1);
                const auto b2 = new ePalace2H(mBoard);
                ebs.emplace_back(gHoverX, gHoverY + 4, b2);
            } else {
                const auto b1 = new ePalace1W(mBoard);
                ebs.emplace_back(gHoverX, gHoverY, b1);
                const auto b2 = new ePalace2W(mBoard);
                ebs.emplace_back(gHoverX + 4, gHoverY, b2);
            }
        } break;
        case eBuildingMode::taxOffice: {
            const auto b1 = new eTaxOffice(mBoard);
            ebs.emplace_back(gHoverX, gHoverY, b1);
        } break;
        case eBuildingMode::mint: {
            const auto b1 = new eMint(mBoard);
            ebs.emplace_back(gHoverX, gHoverY, b1);
        } break;
        case eBuildingMode::foundry: {
            const auto b1 = new eFoundry(mBoard);
            ebs.emplace_back(gHoverX, gHoverY, b1);
        } break;
        case eBuildingMode::timberMill: {
            const auto b1 = new eTimberMill(mBoard);
            ebs.emplace_back(gHoverX, gHoverY, b1);
        } break;

        case eBuildingMode::oliveTree: {
            const auto b1 = new eResourceBuilding(mBoard, eResourceType::oliveTree);
            ebs.emplace_back(gHoverX, gHoverY, b1);
            specReq = [](eTile* const tile) { return tile->terrain() == eTerrain::fertile; };
        } break;
        case eBuildingMode::vine: {
            const auto b1 = new eResourceBuilding(mBoard, eResourceType::vine);
            ebs.emplace_back(gHoverX, gHoverY, b1);
            specReq = [](eTile* const tile) { return tile->terrain() == eTerrain::fertile; };
        } break;

        case eBuildingMode::huntingLodge: {
            const auto b1 = new eHuntingLodge(mBoard);
            ebs.emplace_back(gHoverX, gHoverY, b1);
        } break;
        default: break;
        }
        bool cbg = true;
        const int a = t->altitude();
        for(const auto& eb : ebs) {
            const auto b = eb.fB;
            const int sw =  b->spanW();
            const int sh = b->spanH();
            const bool cb = canBuild(tx, ty, sw, sh, specReq);
            if(!cb) {
                cbg = false;
                break;
            }
        }
        for(const auto& eb : ebs) {
            if(!eb.fB) continue;
            const auto b = eb.fB;
            const int sw = b->spanW();
            const int sh = b->spanH();

            b->setSeed(0);
            b->setTile(t);
            double rx;
            double ry;
            drawXY(eb.fTx, eb.fTy, rx, ry, sw, sh, a);
            auto tex = b->getTexture(tp.size());
            if(cbg) tex.setColorMod(0, 255, 0);
            else tex.setColorMod(255, 0, 0);
            tp.drawTexture(rx, ry, tex, eAlignment::top);
            tex.clearColorMod();
            delete b;
        }
    }
}

bool eGameWidget::keyPressEvent(const eKeyPressEvent& e) {
    if(e.key() == SDL_Scancode::SDL_SCANCODE_KP_PLUS) {
        mSpeed = std::clamp(mSpeed + 1, 1, 20);
    } else if(e.key() == SDL_Scancode::SDL_SCANCODE_KP_MINUS) {
        mSpeed = std::clamp(mSpeed - 1, 1, 20);
    } else if(e.key() == SDL_Scancode::SDL_SCANCODE_R) {
        mRotate = !mRotate;
    } else if(e.key() == SDL_Scancode::SDL_SCANCODE_LEFT) {
        mDX += 25;
    } else if(e.key() == SDL_Scancode::SDL_SCANCODE_RIGHT) {
        mDX -= 25;
    } else if(e.key() == SDL_Scancode::SDL_SCANCODE_UP) {
        mDY += 25;
    } else if(e.key() == SDL_Scancode::SDL_SCANCODE_DOWN) {
        mDY -= 25;
    }
    return true;
}

int gLastX = 0;
int gLastY = 0;

bool eGameWidget::mousePressEvent(const eMouseEvent& e) {
    switch(e.button()) {
    case eMouseButton::middle:
        gLastX = e.x();
        gLastY = e.y();
        return true;
    case eMouseButton::left:
        int tx;
        int ty;
        pixToId(e.x(), e.y(), tx, ty);
        gPressedX = tx;
        gPressedY = ty;
        if(mPatrolBuilding) {
            const auto tile = mBoard.tile(tx, ty);
            if(!tile) return true;
            if(tile->underBuilding() == mPatrolBuilding) {
                const auto s = mPatrolBuilding->spawnDirection();
                const int si = static_cast<int>(s);
                int nsi = si + 1;
                if(nsi > 15) nsi = 1;
                const auto ss = static_cast<eMoveDirection>(nsi);
                mPatrolBuilding->setSpawnDirection(ss);
            } else {
                const auto pgs = mPatrolBuilding->patrolGuides();
                const auto it = findGuide(tx, ty);
                const bool found = it != pgs->end();
                if(found) {
                    auto& pg = *it;
                    const int si = static_cast<int>(pg.fDir);
                    int nsi = si + 1;
                    if(nsi >= 15) {
                        pgs->erase(it);
                    } else {
                        const auto ss = static_cast<eMoveDirection>(nsi);
                        pg.fDir = ss;
                    }
                } else {
                    pgs->push_back({tx, ty, eMoveDirection::topRight});
                }
            }
        }
        return true;
    case eMouseButton::right: {
        int tx;
        int ty;
        pixToId(e.x(), e.y(), tx, ty);
        if(mPatrolBuilding) {
            const auto pgs = mPatrolBuilding->patrolGuides();
            const auto it = findGuide(tx, ty);
            const bool found = it != pgs->end();
            if(found) {
                pgs->erase(it);
                return true;
            }
            const auto t = mBoard.tile(tx, ty);
            if(t && t->underBuilding() == mPatrolBuilding) {
                const auto sd = eMoveDirection::allDirections;
                mPatrolBuilding->setSpawnDirection(sd);
            }
        }
        mPatrolBuilding = nullptr;
        mGm->clearMode();
        const auto tile = mBoard.tile(tx, ty);
        if(!tile) return true;
        const auto b = tile->building();
        if(!b) return true;
        if(const auto gym = dynamic_cast<eGymnasium*>(b)) {
            const auto gymWid = new eGymInfoWidget(window());
            gymWid->initialize([this, gymWid]() {
                removeWidget(gymWid);
                gymWid->deleteLater();
            });
            addWidget(gymWid);
            gymWid->align(eAlignment::center);
        }
    } break;
    default: return true;
    }
    return true;
}

bool eGameWidget::mouseMoveEvent(const eMouseEvent& e) {
    if(static_cast<bool>(e.buttons() & eMouseButton::middle)) {
        const int dx = e.x() - gLastX;
        const int dy = e.y() - gLastY;
        mDX += dx;
        mDY += dy;
        gLastX = e.x();
        gLastY = e.y();
        return true;
    } else {
        pixToId(e.x(), e.y(), gHoverX, gHoverY);
        return true;
    }
    return false;
}

bool eGameWidget::mouseReleaseEvent(const eMouseEvent& e) {
    switch(e.button()) {
    case eMouseButton::left: {
        std::function<void(eTile* const)> apply;
        if(mTem->visible()) {
            const auto mode = mTem->mode();
            if(mode == eTerrainEditMode::scrub) {
                apply = [](eTile* const tile) {
                    tile->incScrub(0.1);
                };
            } else if(mode == eTerrainEditMode::raise) {
                apply = [](eTile* const tile) {
                    tile->setAltitude(tile->altitude() + 1);
                };
            } else if(mode == eTerrainEditMode::lower) {
                apply = [](eTile* const tile) {
                    tile->setAltitude(tile->altitude() - 1);
                };
            } else if(mode == eTerrainEditMode::levelOut) {
                const auto t = mBoard.tile(gHoverX, gHoverY);
                if(t) {
                    const int a = t->altitude();
                    apply = [a](eTile* const tile) {
                        tile->setAltitude(a);
                    };
                }
            } else if(mode == eTerrainEditMode::resetElev) {
                apply = [](eTile* const tile) {
                    tile->setAltitude(0);
                };
            } else if(mode == eTerrainEditMode::makeWalkable) {
                apply = [](eTile* const tile) {
                    tile->setWalkableElev(!tile->walkableElev());
                };
            } else if(mode == eTerrainEditMode::boar) {
                apply = [this](eTile* const tile) {
                    const auto os = tile->spawner();
                    if(os) delete os;
                    new eBoarSpawner(tile, mBoard);
                };
            } else if(mode == eTerrainEditMode::fire) {
                apply = [](eTile* const tile) {
                    tile->setOnFire(true);
                };
            } else if(mode == eTerrainEditMode::settlers) {
                apply = [this](eTile* const tile) {
                    const auto os = tile->spawner();
                    if(os) delete os;
                    new eSettlerSpawner(tile, mBoard);
                };
            } else {
                apply = [mode](eTile* const tile) {
                    const auto terr = static_cast<eTerrain>(mode);
                    tile->setTerrain(terr);
                };
            }
        } else {
            const auto mode = mGm->mode();
            switch(mode) {
            case eBuildingMode::none: {
                const auto tile = mBoard.tile(gHoverX, gHoverY);
                if(!mPatrolBuilding && tile) {
                    if(const auto b = tile->underBuilding()) {
                        if(const auto pb = dynamic_cast<ePatrolBuilding*>(b)) {
                            mPatrolBuilding = pb;
                        }
                    }
                }
            } break;
            case eBuildingMode::erase:
                apply = [this](eTile* const tile) {
                    erase(tile);
                };
                break;
            case eBuildingMode::road:
                apply = [this](eTile* const tile) {
                    build(tile->x(), tile->y(), 1, 1,
                          [this]() { return new eRoad(mBoard); });
                };
                break;
            case eBuildingMode::commonHousing:
                apply = [this](eTile* const tile) {
                    build(tile->x(), tile->y(), 2, 2,
                          [this]() { return new eSmallHouse(mBoard); });
                };
                break;
            case eBuildingMode::gymnasium:
                apply = [this](eTile*) {
                    build(gHoverX, gHoverY, 3, 3,
                          [this]() { return new eGymnasium(mBoard); });
                };
                break;
            case eBuildingMode::podium:
                apply = [this](eTile*) {
                    build(gHoverX, gHoverY, 2, 2,
                          [this]() { return new ePodium(mBoard); });
                };
                break;
            case eBuildingMode::fountain:
                apply = [this](eTile*) {
                    build(gHoverX, gHoverY, 2, 2,
                          [this]() { return new eFountain(mBoard); });
                };
                break;
            case eBuildingMode::watchpost:
                apply = [this](eTile*) {
                    build(gHoverX, gHoverY, 2, 2,
                          [this]() { return new eWatchpost(mBoard); });
                };
                break;
            case eBuildingMode::maintenanceOffice:
                apply = [this](eTile*) {
                    build(gHoverX, gHoverY, 2, 2,
                          [this]() { return new eMaintenanceOffice(mBoard); });
                };
                break;
            case eBuildingMode::college:
                apply = [this](eTile*) {
                    build(gHoverX, gHoverY, 3, 3,
                          [this]() { return new eCollege(mBoard); });
                };
                break;
            case eBuildingMode::dramaSchool:
                apply = [this](eTile*) {
                    build(gHoverX, gHoverY, 3, 3,
                          [this]() { return new eDramaSchool(mBoard); });
                };
                break;
            case eBuildingMode::theater:
                apply = [this](eTile*) {
                    build(gHoverX, gHoverY, 5, 5,
                          [this]() { return new eTheater(mBoard); });
                };
                break;
            case eBuildingMode::hospital:
                apply = [this](eTile*) {
                    build(gHoverX, gHoverY, 4, 4,
                          [this]() { return new eHospital(mBoard); });
                };
                break;
            case eBuildingMode::stadium:
                if(mRotate) {
                    apply = [this](eTile*) {
                        const auto tile = mBoard.tile(gHoverX, gHoverY);
                        if(!tile) return;
                        const bool cb = canBuild(tile->x(), tile->y(), 5, 5);
                        if(!cb) return;
                        const auto t2 = tile->tileRel(0, 5);
                        if(!t2) return;
                        const bool cb2 = canBuild(t2->x(), t2->y(), 5, 5);
                        if(!cb2) return;
                        build(tile->x(), tile->y(), 5, 5,
                              [this]() { return new eStadium1H(mBoard); });
                        build(t2->x(), t2->y(), 5, 5,
                              [this]() { return new eStadium2H(mBoard); });
                    };
                } else {
                    apply = [this](eTile*) {
                        const auto tile = mBoard.tile(gHoverX, gHoverY);
                        if(!tile) return;
                        const bool cb = canBuild(tile->x(), tile->y(), 5, 5);
                        if(!cb) return;
                        const auto t2 = tile->tileRel(5, 0);
                        if(!t2) return;
                        const bool cb2 = canBuild(t2->x(), t2->y(), 5, 5);
                        if(!cb2) return;
                        build(tile->x(), tile->y(), 5, 5,
                              [this]() { return new eStadium1W(mBoard); });
                        build(t2->x(), t2->y(), 5, 5,
                              [this]() { return new eStadium2W(mBoard); });
                    };
                }
                break;
            case eBuildingMode::palace:
                if(mRotate) {
                    apply = [this](eTile*) {
                        const auto tile = mBoard.tile(gHoverX, gHoverY);
                        if(!tile) return;
                        const bool cb = canBuild(tile->x(), tile->y(), 4, 4);
                        if(!cb) return;
                        const auto t2 = tile->tileRel(0, 4);
                        if(!t2) return;
                        const bool cb2 = canBuild(t2->x(), t2->y(), 4, 4);
                        if(!cb2) return;
                        build(tile->x(), tile->y(), 4, 4,
                              [this]() { return new ePalace1H(mBoard); });
                        build(t2->x(), t2->y(), 4, 4,
                              [this]() { return new ePalace2H(mBoard); });
                    };
                } else {
                    apply = [this](eTile*) {
                        const auto tile = mBoard.tile(gHoverX, gHoverY);
                        if(!tile) return;
                        const bool cb = canBuild(tile->x(), tile->y(), 4, 4);
                        if(!cb) return;
                        const auto t2 = tile->tileRel(4, 0);
                        if(!t2) return;
                        const bool cb2 = canBuild(t2->x(), t2->y(), 4, 4);
                        if(!cb2) return;
                        build(tile->x(), tile->y(), 4, 4,
                              [this]() { return new ePalace1W(mBoard); });
                        build(t2->x(), t2->y(), 4, 4,
                              [this]() { return new ePalace2W(mBoard); });
                    };
                }
                break;
            case eBuildingMode::taxOffice:
                apply = [this](eTile*) {
                    build(gHoverX, gHoverY, 2, 2,
                          [this]() { return new eTaxOffice(mBoard); });
                };
                break;
            case eBuildingMode::mint:
                apply = [this](eTile*) {
                    build(gHoverX, gHoverY, 2, 2,
                          [this]() { return new eMint(mBoard); });
                };
                break;
            case eBuildingMode::foundry:
                apply = [this](eTile*) {
                    build(gHoverX, gHoverY, 2, 2,
                          [this]() { return new eFoundry(mBoard); });
                };
                break;
            case eBuildingMode::timberMill:
                apply = [this](eTile*) {
                    build(gHoverX, gHoverY, 2, 2,
                          [this]() { return new eTimberMill(mBoard); });
                };
                break;


            case eBuildingMode::oliveTree:
                apply = [this](eTile*) {
                    build(gHoverX, gHoverY, 1, 1,
                          [this]() { return new eResourceBuilding(mBoard, eResourceType::oliveTree); },
                          [](eTile* const tile) { return tile->terrain() == eTerrain::fertile; });
                };
                break;
            case eBuildingMode::vine:
                apply = [this](eTile*) {
                    build(gHoverX, gHoverY, 1, 1,
                          [this]() { return new eResourceBuilding(mBoard, eResourceType::vine); },
                    [](eTile* const tile) { return tile->terrain() == eTerrain::fertile; });
                };
                break;


            case eBuildingMode::huntingLodge:
                apply = [this](eTile*) {
                    build(gHoverX, gHoverY, 2, 2,
                          [this]() { return new eHuntingLodge(mBoard); });
                };
                break;
            default: break;
            }
        }

        actionOnSelectedTiles(apply);

        gPressedX = -1;
        gPressedY = -1;
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
    if(e.dy() > 0) {
        switch(mTileSize) {
        case eTileSize::s15:
            setTileSize(eTileSize::s30);
            break;
        case eTileSize::s30:
            setTileSize(eTileSize::s60);
            break;
        case eTileSize::s60:
            break;
        }
    } else {
        switch(mTileSize) {
        case eTileSize::s30:
            setTileSize(eTileSize::s15);
            break;
        case eTileSize::s60:
            setTileSize(eTileSize::s30);
            break;
        case eTileSize::s15:
            break;
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
}

void eGameWidget::actionOnSelectedTiles(const eTileAction& apply) {
    if(!apply) return;
    const int minX = std::min(gPressedX, gHoverX);
    const int minY = std::min(gPressedY, gHoverY);
    const int maxX = std::max(gPressedX, gHoverX);
    const int maxY = std::max(gPressedY, gHoverY);

    for(int x = minX; x <= maxX; x++) {
        for(int y = minY; y <= maxY; y++) {
            const auto tile = mBoard.tile(x, y);
            if(!tile) continue;
            apply(tile);
        }
    }
}
