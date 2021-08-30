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
    const auto rx = x + mX;
    const auto ry = y + mY;
    const double dx = mTileH*tex->offsetX()/30.;
    const double dy = mTileH*tex->offsetY()/30.;
    mP.drawTexture(std::round(0.5 * (rx - ry) * mTileW - dx),
                   std::round(0.5 * (rx + ry) * mTileH - dy),
                   tex, align);
}

void eTilePainter::drawTexture(const double x, const double y,
                               const std::shared_ptr<eTexture>& tex) const {
    const auto rx = x + mX;
    const auto ry = y + mY;
    const double dx = mTileH*tex->offsetX()/30.;
    const double dy = mTileH*tex->offsetY()/30.;
    mP.drawTexture(std::round(0.5 * (rx - ry) * mTileW - dx),
                   std::round(0.5 * (rx + ry) * mTileH - dy),
                   tex);
}
