#include "eheatmapdivisor.h"

#include <algorithm>

eHeatMapRectangle::eHeatMapRectangle(const double maxHeat,
                                     const int maxHeatX,
                                     const int maxHeatY,
                                     const int x, const int y,
                                     const int w, const int h) :
    mMaxHeat(maxHeat),
    mMaxHeatX(maxHeatX),
    mMaxHeatY(maxHeatY) {
    SDL_Rect::x = x;
    SDL_Rect::y = y;
    SDL_Rect::w = w;
    SDL_Rect::h = h;
}

eHeatMapDivisor::eHeatMapDivisor(const eHeatMap& map) :
    mMap(map) {

}

void eHeatMapDivisor::divide(const int dim) {
    for(int x = 0; x < mMap.width(); x += dim) {
        for(int y = 0; y < mMap.height(); y += dim) {
            const int w = std::min(mMap.width() - x, dim);
            const int h = std::min(mMap.height() - y, dim);
            double maxHeat = -DBL_MAX;
            int maxHeatX = x;
            int maxHeatY = y;
            for(int xx = x; xx < x + w; xx++) {
                for(int yy = y; yy < y + h; yy++) {
                    const double h = mMap.heat(xx, yy);
                    if(h > maxHeat) {
                        maxHeat = h;
                        maxHeatX = xx;
                        maxHeatY = yy;
                    }
                }
            }
            eHeatMapRectangle div(maxHeat,
                                  maxHeatX,
                                  maxHeatY,
                                  x, y, w, h);
            mDivs.push_back(div);
        }
    }
}

const eHeatMapRectangle* eHeatMapDivisor::maxHeatDiv() const {
    double maxHeat = -DBL_MAX;
    const eHeatMapRectangle* maxHeatDiv = nullptr;
    for(const auto& div : mDivs) {
        const double h = div.maxHeat();
        const int x = div.maxHeatX();
        const int y = div.maxHeatY();
        const bool e = mMap.enabled(x, y);
        if(e && h > maxHeat) {
            maxHeat = h;
            maxHeatDiv = &div;
        }
    }
    return maxHeatDiv;
}

bool eHeatMapDivisor::maxHeatTile(int& x, int& y) const {
    const auto div = maxHeatDiv();
    if(!div) return false;
    x = div->maxHeatX();
    y = div->maxHeatY();
    return true;
}

const eHeatMapRectangle* eHeatMapDivisor::randomHeatDiv() const {
    if(mDivs.empty()) return nullptr;
    double totalHeat = 0;
    for(const auto& div : mDivs) {
        const double h = div.maxHeat();
        totalHeat += h;
    }
    const int rdMax = 100*totalHeat;
    if(rdMax == 0) return nullptr;
    const double rd = 0.01*(rand() % rdMax);

    double acc = 0;
    for(const auto& div : mDivs) {
        const double h = div.maxHeat();
        acc += h;
        if(acc > rd) {
            return &div;
        }
    }

    return &mDivs.back();
}

bool eHeatMapDivisor::randomHeatTile(int& x, int& y) const {
    const auto div = randomHeatDiv();
    if(!div) return false;
    x = div->maxHeatX();
    y = div->maxHeatY();
    return true;
}
