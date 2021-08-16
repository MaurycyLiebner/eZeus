#ifndef ETILEBASE_H
#define ETILEBASE_H

#include "eterrain.h"

#include <functional>

#include "eorientation.h"

class eTileBase {
public:
    eTileBase() {}

    virtual bool hasRoad() = 0;
    virtual bool walkable() = 0;

    int seed() const { return mSeed; }
    int x() const { return mX; }
    int y() const { return mY; }
    int altitude() const { return mAltitude; }
    eTerrain terrain() const { return mTerr; }
    double scrub() const { return mScrub; }

    void setSeed(const int s);
    void setX(const int x);
    void setY(const int y);

    eTileBase* topLeft() const { return mTopLeft; }
    eTileBase* topRight() const { return mTopRight; }
    eTileBase* bottomRight() const { return mBottomRight; }
    eTileBase* bottomLeft() const { return mBottomLeft; }

    eTileBase* left() const;
    eTileBase* top() const;
    eTileBase* right() const;
    eTileBase* bottom() const;

    using eTO = std::pair<eOrientation, eTileBase*>;
    using eTileVerifier = std::function<bool(eTileBase* const)>;

    std::vector<eTO> neighbours(const eTileVerifier& v) const;
    eTO randomNeighbour(const eTileVerifier& v) const;

    std::vector<eTO> diagonalNeighbours(const eTileVerifier& v) const;
    eTO randomDiagonalNeighbour(const eTileVerifier& v) const;

    eTileBase* neighbour(const eOrientation o) const;

    eTileBase* tileRel(const int x, const int y);
    eTileBase* tileAbs(const int x, const int y);

    void setAltitude(const int a);
    void setTerrain(const eTerrain terr);
    void setScrub(const double s);
    void incScrub(const double s);

    void setTopLeft(eTileBase* const tl);
    void setTopRight(eTileBase* const tr);
    void setBottomRight(eTileBase* const br);
    void setBottomLeft(eTileBase* const bl);

    bool walkableElev() const { return mWalkableElev; }
    void setWalkableElev(const bool w);

    int resource() const { return mResource; }
    void decResource(const int by);
    void setResource(const int r);

    bool busy() const { return mBusy; }
    void setBusy(const bool b);
private:
    int mSeed;
    int mX;
    int mY;

    bool mWalkableElev{false};

    bool mBusy = false;
    int mResource = 10000;

    eTileBase* mTopLeft = nullptr;
    eTileBase* mTopRight = nullptr;
    eTileBase* mBottomRight = nullptr;
    eTileBase* mBottomLeft = nullptr;

    eTerrain mTerr = eTerrain::dry;
    double mScrub = 0;
    int mAltitude = 0;
};

#endif // ETILEBASE_H
