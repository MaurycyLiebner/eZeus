#ifndef ETILEPAINTER_H
#define ETILEPAINTER_H

#include "epainter.h"
#include "engine/etile.h"

class eTilePainter {
    struct eTilePainterSave {
        double fX;
        double fY;
    };
public:
    eTilePainter(ePainter& p,
                 const eTileSize size,
                 const int tw, const int th);

    SDL_Renderer* renderer() const { return mP.renderer(); }
    eTileSize size() const { return mSize; }

    void save();
    void restore();

    void translate(const double x, const double y);

    void drawTexture(const double x, const double y,
                     const std::shared_ptr<eTexture>& tex,
                     const eAlignment align) const;
    void drawTexture(const double x, const double y,
                     const std::shared_ptr<eTexture>& tex) const;

    void drawPolygon(std::vector<SDL_Point> pts,
                     const SDL_Color& color);
private:
    void drawPositon(const double x, const double y,
                     int& pixX, int& pixY,
                     const double dx = 0, const double dy = 0) const;

    ePainter& mP;
    const eTileSize mSize;
    const int mTileW;
    const int mTileH;

    std::vector<eTilePainterSave> mSaves;

    double mX = 0;
    double mY = 0;
};

#endif // ETILEPAINTER_H
