#ifndef ETILEBASE_H
#define ETILEBASE_H

#include "eterrain.h"

#include <functional>

#include "eorientation.h"

class eCharacterBase;

enum class eBuildingType;

class eTileBase {
public:
    eTileBase() {}
    virtual ~eTileBase() {}

    virtual bool hasRoad() const = 0;
    using eHasChar = std::function<bool(const eCharacterBase&)>;
    virtual bool hasCharacter(const eHasChar& func) const = 0;
    virtual eBuildingType underBuildingType() const = 0;

    bool walkable() const;

    int seed() const { return mSeed; }
    int dx() const { return mDX; }
    int dy() const { return mDY; }
    int x() const { return mX; }
    int y() const { return mY; }
    int altitude() const { return mAltitude; }
    bool isElevationTile() const;
    eTerrain terrain() const { return mTerr; }
    double scrub() const { return mScrub; }

    static double sDistance(eTileBase* const t1,
                            eTileBase* const t2);

    void setSeed(const int s);
    void setDX(const int x);
    void setDY(const int y);
    void setX(const int x);
    void setY(const int y);

    template <typename T = eTileBase>
    T* topLeft() const { return static_cast<T*>(mTopLeft); }
    template <typename T = eTileBase>
    T* topRight() const { return static_cast<T*>(mTopRight); }
    template <typename T = eTileBase>
    T* bottomRight() const { return static_cast<T*>(mBottomRight); }
    template <typename T = eTileBase>
    T* bottomLeft() const { return static_cast<T*>(mBottomLeft); }

    template <typename T = eTileBase>
    T* left() const;
    template <typename T = eTileBase>
    T* top() const;
    template <typename T = eTileBase>
    T* right() const;
    template <typename T = eTileBase>
    T* bottom() const;

    using eTO = std::pair<eOrientation, eTileBase*>;
    using eTileVerifier = std::function<bool(eTileBase* const)>;

    std::vector<eTO> neighbours(const eTileVerifier& v) const;
    eTO randomNeighbour(const eTileVerifier& v) const;

    std::vector<eTO> diagonalNeighbours(const eTileVerifier& v) const;
    eTO randomDiagonalNeighbour(const eTileVerifier& v) const;


    template <typename T = eTileBase>
    T* neighbour(const eOrientation o) const;

    template <typename T = eTileBase>
    T* tileRel(const int x, const int y) const;
    template <typename T = eTileBase>
    T* tileAbs(const int x, const int y) const;

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

    bool onFire() const { return mOnFire; }
    void setOnFire(const bool of);

    int marbleLevel() const { return mMarbleLevel; };
    void setMarbleLevel(const int l);
private:
    int mSeed;

    int mDX;
    int mDY;

    int mX;
    int mY;

    bool mWalkableElev{false};

    bool mOnFire{false};
    bool mBusy{false};
    int mMarbleLevel = 0;
    int mResource = 100;

    eTileBase* mTopLeft = nullptr;
    eTileBase* mTopRight = nullptr;
    eTileBase* mBottomRight = nullptr;
    eTileBase* mBottomLeft = nullptr;

    eTerrain mTerr = eTerrain::dry;
    double mScrub = 0;
    int mAltitude = 0;
};

template <typename T>
T* eTileBase::left() const {
    if(!mBottomLeft) return nullptr;
    return mBottomLeft->topLeft<T>();
}

template <typename T>
T* eTileBase::top() const {
    if(!mTopLeft) return nullptr;
    return mTopLeft->topRight<T>();
}

template <typename T>
T* eTileBase::right() const {
    if(!mTopRight) return nullptr;
    return mTopRight->bottomRight<T>();
}

template <typename T>
T* eTileBase::bottom() const {
    if(!mBottomLeft) return nullptr;
    return mBottomLeft->bottomRight<T>();
}

template <typename T>
T* eTileBase::neighbour(const eOrientation o) const {
    switch(o) {
    case eOrientation::topRight: {
        return topRight<T>();
    } break;
    case eOrientation::right: {
        return right<T>();
    } break;
    case eOrientation::bottomRight: {
        return bottomRight<T>();
    } break;
    case eOrientation::bottom: {
        return bottom<T>();
    } break;
    case eOrientation::bottomLeft: {
        return bottomLeft<T>();
    } break;
    case eOrientation::left: {
        return left<T>();
    } break;
    case eOrientation::topLeft: {
        return topLeft<T>();
    } break;
    case eOrientation::top: {
        return top<T>();
    } break;
    }
    return nullptr;
}

template <typename T>
T* eTileBase::tileRel(const int x, const int y) const {
    if(x == 0 && y == 0) {
        const auto t = static_cast<const T*>(this);
        return const_cast<T*>(t);
    }
    if(x > 0) {
        const auto br = bottomRight<T>();
        if(!br) return nullptr;
        return br->template tileRel<T>(x - 1, y);
    } else if(x < 0) {
        const auto tl = topLeft<T>();
        if(!tl) return nullptr;
        return tl->template tileRel<T>(x + 1, y);
    }
    if(y > 0) {
        const auto bl = bottomLeft<T>();
        if(!bl) return nullptr;
        return bl->template tileRel<T>(x, y - 1);
    } else if(y < 0) {
        const auto tr = topRight<T>();
        if(!tr) return nullptr;
        return tr->template tileRel<T>(x, y + 1);
    }
    return nullptr;
}

template <typename T>
T* eTileBase::tileAbs(const int x, const int y) const {
    return tileRel<T>(x - mX, y - mY);
}

#endif // ETILEBASE_H
