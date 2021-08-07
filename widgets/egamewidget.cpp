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
#include "buildings/ehospital.h"
#include "buildings/etheater.h"
#include "buildings/edramaschool.h"
#include "buildings/estadium1.h"
#include "buildings/estadium2.h"
#include "buildings/epalace1.h"
#include "buildings/epalace2.h"

#include "echeckbox.h"

eGameWidget::eGameWidget(eMainWindow* const window) :
    eWidget(window) {}

eGameWidget::~eGameWidget() {}

void eGameWidget::initialize(const int w, const int h) {
    mGm = new eGameMenu(window());
    mGm->initialize();
    addWidget(mGm);
    mGm->align(eAlignment::right | eAlignment::top);

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
    const auto d = new eDemeter();
    d->setTile(t);
    d->setX(0.5);
    d->setY(0.5);
    d->setCharAction(new eMoveAroundAction(d));
    t->addCharacter(d);
}

void eGameWidget::pixToId(const int pixX, const int pixY,
                          int& idX, int& idY) const {
    const double w = mTileW;
    const double h = mTileH;
    idX = std::round((pixX - mDX)/w + (pixY - mDY)/h - 0.5);
    idY = std::round(-(pixX - mDX)/w + (pixY - mDY)/h - 0.5);
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

void drawXY(const int tx, const int ty, double& rx, double& ry,
            const int wSpan, const int hSpan) {
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
}

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
                           const int sw, const int sh) {
    int minX;
    int minY;
    int maxX;
    int maxY;
    buildTiles(minX, minY, maxX, maxY, tx, ty, sw, sh);

    for(int x = minX; x < maxX; x++) {
        for(int y = minY; y < maxY; y++) {
            const auto t = mBoard.tile(x, y);
            if(!t || t->underBuilding()) return false;
        }
    }
    return true;
}


bool eGameWidget::build(const int tx, const int ty,
                        const int sw, const int sh,
                        const eBuildingCreator& bc) {
    if(!bc) return false;
    const auto tile = mBoard.tile(tx, ty);
    if(!tile) return false;
    const bool cb = canBuild(tx, ty, sw, sh);
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
            if(t) t->setUnderBuilding(b);
        }
    }
    return true;
}

void eGameWidget::paintEvent(ePainter& p) {
    p.setFont(eFonts::defaultFont(resolution()));
    p.translate(mDX, mDY);
    eTilePainter tp(p, mTileSize, mTileW, mTileH);

    const int tid = static_cast<int>(mTileSize);
    const auto& trrTexs = eGameTextures::terrain().at(tid);

    iterateOverTiles([&](eTile* const tile) {
        const int tx = tile->x();
        const int ty = tile->y();

        int wSpan;
        int hSpan;
        const auto tex = eTileToTexture::get(tile, trrTexs,
                                             wSpan, hSpan);
        tile->setDrawnSpan(wSpan, hSpan);

        double rx;
        double ry;
        drawXY(tx, ty, rx, ry, wSpan, hSpan);

        if(!tex.isNull()) {
            if(wSpan == 2 && hSpan == 2) {
                gDelayedTextures.emplace_back(eDelayedTexture{rx, ry, tex});
                return;
            } else {
                tp.drawTexture(rx, ry, tex, eAlignment::top);
            }
        }
        gDrawDelayed(tp);


        if(const auto d = tile->building()) {
            if(d->type() == eBuildingType::road) {
                double rx;
                double ry;
                drawXY(tx, ty, rx, ry, d->spanW(), d->spanH());
                d->draw(tp, rx, ry, eAlignment::top);
                d->incTime(mSpeed);
            }
        }

        const auto& selectedTex = trrTexs.fSelectedTex;

        if(tile->x() == gHoverX && tile->y() == gHoverY) {
            tp.drawTexture(rx, ry, selectedTex, eAlignment::top);
        }

        if(gPressedX >= 0 && gPressedY >= 0) {
            const int minX = std::min(gPressedX, gHoverX);
            const int minY = std::min(gPressedY, gHoverY);
            const int maxX = std::max(gPressedX, gHoverX);
            const int maxY = std::max(gPressedY, gHoverY);
            if(tile->x() >= minX && tile->x() <= maxX &&
               tile->y() >= minY && tile->y() <= maxY) {
                tp.drawTexture(rx, ry, selectedTex, eAlignment::top);
            }
        }
    });
    iterateOverTiles([&](eTile* const tile) {
        const int tx = tile->x();
        const int ty = tile->y();

        if(const auto d = tile->building()) {
            if(d->type() != eBuildingType::road) {
                double rx;
                double ry;
                drawXY(tx, ty, rx, ry, d->spanW(), d->spanH());
                d->draw(tp, rx, ry, eAlignment::top);
                d->incTime(mSpeed);
            }
        }

        const auto& chars = tile->characters();
        for(const auto c : chars) {
            const auto tex = c->getTexture(mTileSize);
            tp.drawTexture(tx + c->x() + 0.25, ty + c->y() + 0.25, tex);
            c->incTime(mSpeed);
        }
    });

    const auto t = mBoard.tile(gHoverX, gHoverY);
    if(t && mGm->visible()) {
        const int tx = gHoverX;
        const int ty = gHoverY;
        eBuilding* b1 = nullptr;
        eBuilding* b2 = nullptr;
        int tx2 = tx;
        int ty2 = ty;
        const auto mode = mGm->mode();
        switch(mode) {
        case eBuildingMode::road:
            b1 = new eRoad;
            break;
        case eBuildingMode::commonHousing:
            b1 = new eSmallHouse;
            break;
        case eBuildingMode::gymnasium:
            b1 = new eGymnasium;
            break;
        case eBuildingMode::podium:
            b1 = new ePodium;
            break;
        case eBuildingMode::fountain:
            b1 = new eFountain;
            break;
        case eBuildingMode::college:
            b1 = new eCollege;
            break;
        case eBuildingMode::dramaSchool:
            b1 = new eDramaSchool;
            break;
        case eBuildingMode::theater:
            b1 = new eTheater;
            break;
        case eBuildingMode::hospital:
            b1 = new eHospital;
            break;
        case eBuildingMode::stadium:
            if(mRotate) {
                b1 = new eStadium1H;
                b2 = new eStadium2H;
                ty2 += 5;
            } else {
                b1 = new eStadium1W;
                b2 = new eStadium2W;
                tx2 += 5;
            }
            break;
        case eBuildingMode::palace:
            if(mRotate) {
                b1 = new ePalace1H;
                b2 = new ePalace2H;
                ty2 += 4;
            } else {
                b1 = new ePalace1W;
                b2 = new ePalace2W;
                tx2 += 4;
            }
            break;
        default: break;
        }
        struct eB {
            int fTx;
            int fTy;
            eBuilding* fB;
        };
        bool cbg = true;
        if(b1) {
            const bool cb1 = canBuild(tx, ty, b1->spanW(), b1->spanH());
            cbg = cbg && cb1;
        }
        if(b2) {
            const bool cb2 = canBuild(tx2, ty2, b2->spanW(), b2->spanH());
            cbg = cbg && cb2;
        }
        for(const auto& eb : {eB{tx, ty, b1}, eB{tx2, ty2, b2}}) {
            if(!eb.fB) continue;
            const auto b = eb.fB;
            const int sw = b->spanW();
            const int sh = b->spanH();

            b->setSeed(0);
            b->setTile(t);
            double rx;
            double ry;
            drawXY(eb.fTx, eb.fTy, rx, ry, sw, sh);
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
        mSpeed = std::clamp(mSpeed + 1, 1, 10);
    } else if(e.key() == SDL_Scancode::SDL_SCANCODE_KP_MINUS) {
        mSpeed = std::clamp(mSpeed - 1, 1, 10);
    } else if(e.key() == SDL_Scancode::SDL_SCANCODE_R) {
        mRotate = !mRotate;
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
        pixToId(e.x(), e.y(), gPressedX, gPressedY);
        return true;
    case eMouseButton::right: {
        mGm->clearMode();
        int tx;
        int ty;
        pixToId(e.x(), e.y(), tx, ty);
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
            } else {
                apply = [mode](eTile* const tile) {
                    const auto terr = static_cast<eTerrain>(mode);
                    tile->setTerrain(terr);
                };
            }
        } else {
            const auto mode = mGm->mode();
            switch(mode) {
            case eBuildingMode::road:
                apply = [this](eTile* const tile) {
                    build(tile->x(), tile->y(), 1, 1,
                          []() { return new eRoad; });
                };
                break;
            case eBuildingMode::commonHousing:
                apply = [this](eTile* const tile) {
                    build(tile->x(), tile->y(), 2, 2,
                          []() { return new eSmallHouse; });
                };
                break;
            case eBuildingMode::gymnasium:
                apply = [this](eTile*) {
                    build(gHoverX, gHoverY, 3, 3,
                          []() { return new eGymnasium; });
                };
                break;
            case eBuildingMode::podium:
                apply = [this](eTile*) {
                    build(gHoverX, gHoverY, 2, 2,
                          []() { return new ePodium; });
                };
                break;
            case eBuildingMode::fountain:
                apply = [this](eTile*) {
                    build(gHoverX, gHoverY, 2, 2,
                          []() { return new eFountain; });
                };
                break;
            case eBuildingMode::college:
                apply = [this](eTile*) {
                    build(gHoverX, gHoverY, 3, 3,
                          []() { return new eCollege; });
                };
                break;
            case eBuildingMode::dramaSchool:
                apply = [this](eTile*) {
                    build(gHoverX, gHoverY, 3, 3,
                          []() { return new eDramaSchool; });
                };
                break;
            case eBuildingMode::theater:
                apply = [this](eTile*) {
                    build(gHoverX, gHoverY, 5, 5,
                          []() { return new eTheater; });
                };
                break;
            case eBuildingMode::hospital:
                apply = [this](eTile*) {
                    build(gHoverX, gHoverY, 4, 4,
                          []() { return new eHospital; });
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
                              []() { return new eStadium1H; });
                        build(t2->x(), t2->y(), 5, 5,
                              []() { return new eStadium2H; });
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
                              []() { return new eStadium1W; });
                        build(t2->x(), t2->y(), 5, 5,
                              []() { return new eStadium2W; });
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
                              []() { return new ePalace1H; });
                        build(t2->x(), t2->y(), 4, 4,
                              []() { return new ePalace2H; });
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
                              []() { return new ePalace1W; });
                        build(t2->x(), t2->y(), 4, 4,
                              []() { return new ePalace2W; });
                    };
                }
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
