#ifndef EBUILDING_H
#define EBUILDING_H

#include "etexturecollection.h"
#include "widgets/etilepainter.h"
#include "engine/etile.h"

enum class eBuildingType {
    house,
    gymnasium,
    road
};

struct eOverlay {
    double fX;
    double fY;
    eTexture fTex;
};

class eBuilding {
public:
    eBuilding(const eBuildingType type,
              const int sw, const int sh);

    virtual eTexture getTexture(const eTileSize size) const = 0;
    virtual std::vector<eOverlay> getOverlays(const eTileSize size) const {
        (void)size;
        return std::vector<eOverlay>();
    }

    eTile* nearestRoad() const;

    int seed() const { return mSeed; }
    eBuildingType type() const { return mType; }
    eTile* tile() const { return mTile; }
    int spanW() const { return mSpanW; }
    int spanH() const { return mSpanH; }

    void incTime() { mTime++; };
    int time() const { return mTime; }
    void setTile(eTile* const t);

    void draw(eTilePainter& p,
              const double x, const double y,
              const eAlignment align);
private:
    const int mSeed;
    const eBuildingType mType;
    const int mSpanW;
    const int mSpanH;
    int mTime = 0;
    eTile* mTile = nullptr;
};

#endif // EBUILDING_H
