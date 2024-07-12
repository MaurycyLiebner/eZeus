#include "eheatmap.h"

#include "etilehelper.h"

#include <algorithm>

void eHeatMap::reset() {
    initialize(mWidth, mHeight);
}

void eHeatMap::initialize(const int w, const int h) {
    mMap.clear();
    mWidth = w;
    mHeight = h;
    if(w > 0) mMap.reserve(w);
    for(int i = 0; i < w; i++) {
        auto& row = mMap.emplace_back();
        if(h > 0) row.reserve(h);
        for(int j = 0; j < h; j++) {
            row.emplace_back();
        }
    }
}

void eHeatMap::addHeat(const eHeat& a,
                       const SDL_Rect& tileRect) {
    addHeat(a, tileRect.x, tileRect.y,
              tileRect.w, tileRect.h);
}

void eHeatMap::addHeat(const eHeat& a,
                       const int ax, const int ay,
                       const int sw, const int sh) {
    const int r = a.fRange;
    if(r <= 0) return;
    const double v = a.fValue;
    for(int x = ax - r; x <= ax + sw + r; x++) {
        for(int y = ay - r; y <= ay + sh + r; y++) {
            const double cx = ax + 0.5*sw;
            const double cy = ay + 0.5*sh;
            const double dx = std::max(abs(x - cx) - 0.5*sw, 0.);
            const double dy = std::max(abs(y - cy) - 0.5*sh, 0.);
            const double dist = std::sqrt(dx * dx + dy * dy);
            if(dist > r) continue;
            const double mult = (r - dist)/r;
            int dtx;
            int dty;
            eTileHelper::tileIdToDTileId(x, y, dtx, dty);
            addHeat(dtx, dty, mult*v);
        }
    }
}

void eHeatMap::addHeat(const int x, const int y,
                       const double a) {
    if(x < 0 || y < 0 ||
       x >= mWidth || y >= mHeight) return;
    auto& tile = mMap[x][y];
    tile.fEnabled = true;
    tile.fAppeal += a/2;
}

bool eHeatMap::enabled(const int x, const int y) const {
    return mMap[x][y].fEnabled;
}

double eHeatMap::heat(const int x, const int y) const {
    return mMap[x][y].fAppeal;
}
