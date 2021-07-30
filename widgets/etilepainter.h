#ifndef ETILEPAINTER_H
#define ETILEPAINTER_H

#include "epainter.h"

class eTilePainter {
    struct eTilePainterSave {
        double fX;
        double fY;
    };
public:
    eTilePainter(ePainter& p, const int tw, const int th);

    void save();
    void restore();

    void translate(const double x, const double y);

    void drawTexture(const double x, const double y,
                     const eTexture& tex,
                     const eAlignment align) const;
    void drawTexture(const double x, const double y,
                     const eTexture& tex) const;
private:
    ePainter& mP;
    const int mTileW;
    const int mTileH;

    std::vector<eTilePainterSave> mSaves;

    double mX = 0;
    double mY = 0;
};

#endif // ETILEPAINTER_H
