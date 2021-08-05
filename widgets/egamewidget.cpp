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

#include "echeckbox.h"

eGameWidget::eGameWidget(eMainWindow* const window) :
    eWidget(window) {}

eGameWidget::~eGameWidget() {}

void eGameWidget::initialize(const int w, const int h) {
    const auto gm = new eGameMenu(window());
    addWidget(gm);
    gm->align(eAlignment::right | eAlignment::top);

    const auto swtch = new eCheckBox(window());
    swtch->move(gm->x(), 0);
    addWidget(swtch);

    mTem = new eTerrainEditMenu(window());
    addWidget(mTem);
    mTem->align(eAlignment::hcenter | eAlignment::bottom);

    mBoard.initialize(w, h);

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
        rx += 0;
        ry += 2;
    }
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
//            {

//                const int tx = tile->x();
//                const int ty = tile->y();

//                int wSpan;
//                int hSpan;
//                const auto tex = eTileToTexture::get(tile, trrTexs,
//                                                     wSpan, hSpan);
//                tile->setDrawnSpan(wSpan, hSpan);

//                double rx;
//                double ry;
//                drawXY(tx, ty, rx, ry, wSpan, hSpan);
//                const auto& selectedTex = trrTexs.fSelectedTex;

//                tp.drawTexture(rx, ry, selectedTex, eAlignment::top);
//            }
            const auto tex = c->getTexture(mTileSize);
            tp.drawTexture(tx + c->x() + 0.25, ty + c->y() + 0.25, tex);
            c->incTime(mSpeed);
        }
    });
}

bool eGameWidget::keyPressEvent(const eKeyPressEvent& e) {
    if(e.key() == SDL_Scancode::SDL_SCANCODE_KP_PLUS) {
        mSpeed = std::clamp(mSpeed + 1, 1, 10);
    } else if(e.key() == SDL_Scancode::SDL_SCANCODE_KP_MINUS) {
        mSpeed = std::clamp(mSpeed - 1, 1, 10);
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
        const auto mode = mTem->mode();
        if(mode == eTerrainEditMode::scrub) {
            apply = [](eTile* const tile) {
                tile->incScrub(0.1);
            };
        } else if(mode == eTerrainEditMode::smallHouse) {
            apply = [](eTile* const tile) {
                const auto house = new eSmallHouse();
                tile->addBuilding(house);
            };
        } else if(mode == eTerrainEditMode::gymnasium) {
            apply = [](eTile* const tile) {
                const auto gym = new eGymnasium();
                tile->addBuilding(gym);
            };
        } else if(mode == eTerrainEditMode::road) {
            apply = [](eTile* const tile) {
                const auto road = new eRoad();
                tile->addBuilding(road);
            };
        } else {
            apply = [mode](eTile* const tile) {
                const auto terr = static_cast<eTerrain>(mode);
                tile->setTerrain(terr);
            };
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
