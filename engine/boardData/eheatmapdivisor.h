#ifndef EHEATMAPDIVISOR_H
#define EHEATMAPDIVISOR_H

#include "eheatmap.h"

class eHeatMapRectangle : public SDL_Rect {
public:
    eHeatMapRectangle(const double maxHeat,
                      const int maxHeatX,
                      const int maxHeatY,
                      const int x, const int y,
                      const int w, const int h);

    double maxHeat() const { return mMaxHeat; }
    int maxHeatX() const { return mMaxHeatX; }
    int maxHeatY() const { return mMaxHeatY; }
private:
    double mMaxHeat;
    int mMaxHeatX;
    int mMaxHeatY;
};

class eHeatMapDivisor {
public:
    eHeatMapDivisor(const eHeatMap& map);

    void divide(const int dim);

    const eHeatMapRectangle* maxHeatDiv() const;
    bool maxHeatTile(int& x, int& y) const;
    const eHeatMapRectangle* randomHeatDiv() const;
    bool randomHeatTile(int& x, int& y) const;
private:
    const eHeatMap& mMap;
    std::vector<eHeatMapRectangle> mDivs;
};

#endif // EHEATMAPDIVISOR_H
