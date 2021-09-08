#ifndef EAPPEALMAP_H
#define EAPPEALMAP_H

#include "buildings/eappeal.h"

class eAppealMap {
public:
    struct eAppealTile {
        bool fEnabled = false;
        double fAppeal = 0;
    };

    void reset();
    void initialize(const int w, const int h);

    void addAppeal(const eAppeal& a,
                   const SDL_Rect& tileRect);

    void addAppeal(const eAppeal& a,
                   const int ax, const int ay,
                   const int sw, const int sh);

    void addAppeal(const int x, const int y,
                   const double a);

    bool enabled(const int x, const int y) const;
    double appeal(const int x, const int y) const;
private:
    int mWidth = 0;
    int mHeight = 0;
    std::vector<std::vector<eAppealTile>> mMap;
};

#endif // EAPPEALMAP_H
