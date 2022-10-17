#ifndef EHEATMAP_H
#define EHEATMAP_H

#include <vector>
#include <SDL2/SDL_rect.h>

struct eHeat {
    int fValue;
    int fRange;
};

class eHeatMap {
public:
    struct eHeatTile {
        bool fEnabled = false;
        double fAppeal = 0;
    };

    void reset();
    void initialize(const int w, const int h);

    void addHeat(const eHeat& a,
                 const SDL_Rect& tileRect);

    void addHeat(const eHeat& a,
                 const int ax, const int ay,
                 const int sw, const int sh);

    void addHeat(const int x, const int y,
                 const double a);

    bool enabled(const int x, const int y) const;
    double heat(const int x, const int y) const;
private:
    int mWidth = 0;
    int mHeight = 0;
    std::vector<std::vector<eHeatTile>> mMap;
};

#endif // EHEATMAP_H
