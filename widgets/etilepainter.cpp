#include "etilepainter.h"

eTilePainter::eTilePainter(ePainter& p,
                           const eTileSize size,
                           const int tw, const int th) :
    mP(p), mSize(size), mTileW(tw), mTileH(th) {

}

void eTilePainter::save() {
    eTilePainterSave save;
    save.fX = mX;
    save.fY = mY;
    mSaves.emplace(mSaves.end(), save);
}

void eTilePainter::restore() {
    if(mSaves.empty()) return;
    const auto save = mSaves.back();
    mSaves.pop_back();
    mX = save.fX;
    mY = save.fY;
}

void eTilePainter::translate(const double x, const double y) {
    mX += x;
    mY += y;
}

void eTilePainter::drawTexture(const double x, const double y,
                               const std::shared_ptr<eTexture>& tex,
                               const eAlignment align) const {
    if(!tex) return;
    const double dx = mTileH*tex->offsetX()/30.;
    const double dy = mTileH*tex->offsetY()/30.;
    int pixX;
    int pixY;
    drawPositon(x, y, pixX, pixY, dx, dy);
    mP.drawTexture(pixX, pixY, tex, align);
}

void eTilePainter::drawTexture(const double x, const double y,
                               const std::shared_ptr<eTexture>& tex) const {
    if(!tex) return;
    const double dx = mTileH*tex->offsetX()/30.;
    const double dy = mTileH*tex->offsetY()/30.;
    int pixX;
    int pixY;
    drawPositon(x, y, pixX, pixY, dx, dy);
    mP.drawTexture(pixX, pixY, tex);
}

void eTilePainter::drawPolygon(
        std::vector<SDL_Point> pts, const SDL_Color& color) {
    std::vector<SDL_Point> ppts;
    ppts.reserve(pts.size());
    for(const auto& pt : pts) {
        int pixX;
        int pixY;
        drawPositon(pt.x, pt.y, pixX, pixY);
        ppts.push_back({pixX, pixY});
    }
    mP.drawPolygon(ppts, color);
}

void eTilePainter::drawPositon(const double x, const double y,
                               int& pixX, int& pixY,
                               const double dx, const double dy) const {
    const double rx = x + mX;
    const double ry = y + mY;
    pixX = std::round(0.5 * (rx - ry) * mTileW - dx);
    pixY = std::round(0.5 * (rx + ry) * mTileH - dy);
}
