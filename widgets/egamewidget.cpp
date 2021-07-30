#include "egamewidget.h"

#include "eterraineditmenu.h"
#include "etilepainter.h"

#include "textures/etiletotexture.h"
#include "characters/edemeter.h"
#include "characters/emovearoundaction.h"

eGameWidget::eGameWidget(std::vector<eTerrainTextures>&& textures,
                         std::vector<eDemeterTextures>&& demeterTextures,
                         eMainWindow* const window) :
    eWidget(window),
    mTerrainTexturesColl(std::move(textures)),
    mDemeterTextures(std::move(demeterTextures)) {}

eGameWidget::~eGameWidget() {}

void eGameWidget::initialize(const int w, const int h) {
    mTem = new eTerrainEditMenu(window());
    addWidget(mTem);
    mTem->align(eAlignment::hcenter | eAlignment::bottom);

    mBoard.initialize(w, h);

    setTileSize(eTileSize::s30);

    const auto t = mBoard.tile(5, 5);
    const auto d = new eDemeter(mDemeterTextures);
    d->setTile(t);
    d->setX(0.5);
    d->setY(0.5);
    d->setCharAction(new eMoveAroundAction(d));
    t->addDemeter(d);
}

void eGameWidget::pixToId(const int pixX, const int pixY,
                          int& idX, int& idY) const {
    const double w = mTileW;
    const double h = mTileH;
    idX = std::round((pixX - mDX)/w + (pixY - mDY)/h + 0.5);
    idY = std::round(-(pixX - mDX)/w + (pixY - mDY)/h + 0.5);
}

int gHoverX = -1;
int gHoverY = -1;
int gPressedX = -1;
int gPressedY = -1;

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

void eGameWidget::paintEvent(ePainter& p) {
    p.setFont(eFonts::defaultFont(resolution()));
    p.translate(mDX, mDY);
    eTilePainter tp(p, mTileW, mTileH);

    iterateOverTiles([&](eTile* const tile) {
        const int tx = tile->x();
        const int ty = tile->y();

        int wSpan;
        int hSpan;
        const auto tex = eTileToTexture::get(tile, *mTerrainTextures,
                                             wSpan, hSpan);
        if(!tex.isNull()) {
            double rx = tx;
            double ry = ty;
            if((wSpan == 2 && hSpan == 2) ||
               (wSpan == 3 && hSpan == 3)) {
                rx -= 0.5*(wSpan - 1);
                ry += 1;
            }
            if(wSpan == 2 && hSpan == 2) {
                gDelayedTextures.emplace_back(eDelayedTexture{rx, ry, tex});
                return;
            } else {
                tp.drawTexture(rx, ry, tex, eAlignment::top);
            }
        }
        gDrawDelayed(tp);

        if(const auto d = tile->demeter()) {
            const auto tex = d->getTexture(mTileSize);
            tp.drawTexture(tx + d->x() + 0.5, ty + d->y(), tex,
                           eAlignment::top | eAlignment::hcenter);
            d->incTime();
        }

        const auto& selectedTex = mTerrainTextures->fSelectedTex;

        if(tile->x() == gHoverX && tile->y() == gHoverY) {
            tp.drawTexture(tx, ty, selectedTex, eAlignment::top);
        }

        if(gPressedX >= 0 && gPressedY >= 0) {
            const int minX = std::min(gPressedX, gHoverX);
            const int minY = std::min(gPressedY, gHoverY);
            const int maxX = std::max(gPressedX, gHoverX);
            const int maxY = std::max(gPressedY, gHoverY);
            if(tile->x() >= minX && tile->x() <= maxX &&
               tile->y() >= minY && tile->y() <= maxY) {
                tp.drawTexture(tx, ty, selectedTex, eAlignment::top);
            }
        }
    });
    iterateOverTiles([&](eTile* const tile) {
        const int tx = tile->x();
        const int ty = tile->y();

        if(const auto d = tile->demeter()) {
            const auto tex = d->getTexture(mTileSize);
            tp.drawTexture(tx + d->x() + 0.5,
                           ty + d->y(), tex,
                           eAlignment::top | eAlignment::hcenter);
            d->incTime();
        }
    });
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
    default: return false;
    }
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
    mTerrainTextures = &mTerrainTexturesColl.at(static_cast<int>(mTileSize));
    const int newW = mTerrainTextures->fTileW;
    const int newH = mTerrainTextures->fTileH;

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
