#ifndef ETILEBASE_H
#define ETILEBASE_H

#include "eterrain.h"

#include <functional>

#include "eorientation.h"

#include "fileIO/estreams.h"

class eCharacterBase;

enum class eBuildingType;

enum class eWorldDirection {
    N,
    W,
    S,
    E
};

class eTileBase {
public:
    eTileBase() {}
    virtual ~eTileBase() {}

    virtual bool hasRoad() const = 0;
    using eHasChar = std::function<bool(const eCharacterBase&)>;
    virtual bool hasCharacter(const eHasChar& func) const = 0;
    virtual eBuildingType underBuildingType() const = 0;

    virtual bool onFire() const = 0;
    virtual void setOnFire(const bool f) = 0;

    bool hasBridge() const;
    bool hasWater() const;

    bool walkable() const;

    int seed() const { return mSeed; }
    int dx() const { return mDX; }
    int dy() const { return mDY; }
    int x() const { return mX; }
    int y() const { return mY; }
    int altitude() const { return mAltitude; }
    bool isElevationTile() const { return mElevation; }
    void updateIsElevationTile();
    bool isShoreTile() const;
    eTerrain terrain() const { return mTerr; }
    double scrub() const { return mScrub; }

    void setRoadblock(const bool rb) { mRoadblock = rb; }
    bool hasRoadblock() const { return mRoadblock; }

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

    template <typename T = eTileBase>
    T* topLeftRotated(const eWorldDirection dir) const;
    template <typename T = eTileBase>
    T* topRightRotated(const eWorldDirection dir) const;
    template <typename T = eTileBase>
    T* bottomRightRotated(const eWorldDirection dir) const;
    template <typename T = eTileBase>
    T* bottomLeftRotated(const eWorldDirection dir) const;

    template <typename T = eTileBase>
    T* leftRotated(const eWorldDirection dir) const;
    template <typename T = eTileBase>
    T* topRotated(const eWorldDirection dir) const;
    template <typename T = eTileBase>
    T* rightRotated(const eWorldDirection dir) const;
    template <typename T = eTileBase>
    T* bottomRotated(const eWorldDirection dir) const;

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

    template <typename T = eTileBase>
    T* tileRelRotated(const int x, const int y,
                      const eWorldDirection dir) const;
    template <typename T = eTileBase>
    T* tileAbsRotated(const int x, const int y,
                      const eWorldDirection dir) const;

    void setAltitude(const int a, const bool update = true);
    virtual void setTerrain(const eTerrain terr);
    void setScrub(const double s);
    void incScrub(const double s);

    void setTopLeft(eTileBase* const tl);
    void setTopRight(eTileBase* const tr);
    void setBottomRight(eTileBase* const br);
    void setBottomLeft(eTileBase* const bl);

    bool walkableElev() const { return mWalkableElev; }
    void setWalkableElev(const bool w);
    void setElevation(const bool e);

    bool hasFish() const { return mHasFish; }
    void setHasFish(const bool f) { mHasFish = f; }

    bool hasUrchin() const { return mHasUrchin; }
    void setHasUrchin(const bool f) { mHasUrchin = f; }

    int resource() const { return mResource; }
    void decResource(const int by);
    void setResource(const int r);

    bool busy() const { return mBusy; }
    void setBusy(const bool b);

    int marbleLevel() const { return mMarbleLevel; };
    virtual void setMarbleLevel(const int l);

    virtual void read(eReadStream& src);
    virtual void write(eWriteStream& dst) const;
private:
    int mSeed;

    int mDX;
    int mDY;

    int mX;
    int mY;

    bool mHasFish{false};
    bool mHasUrchin{false};

    bool mElevation{false};
    bool mWalkableElev{false};

    bool mBusy{false};
    int mMarbleLevel = 0;
    int mResource = 1;

    eTileBase* mTopLeft = nullptr;
    eTileBase* mTopRight = nullptr;
    eTileBase* mBottomRight = nullptr;
    eTileBase* mBottomLeft = nullptr;

    eTerrain mTerr = eTerrain::dry;
    double mScrub = 0;
    int mAltitude = 0;

    bool mRoadblock = false;
};

template<typename T>
T* eTileBase::bottomRotated(const eWorldDirection dir) const {
    if(dir == eWorldDirection::N) {
        return bottom<T>();
    } else if(dir == eWorldDirection::E) {
        return left<T>();
    } else if(dir == eWorldDirection::S) {
        return top<T>();
    } else if(dir == eWorldDirection::W) {
        return right<T>();
    }
}

template<typename T>
T* eTileBase::rightRotated(const eWorldDirection dir) const {
    if(dir == eWorldDirection::N) {
        return right<T>();
    } else if(dir == eWorldDirection::E) {
        return bottom<T>();
    } else if(dir == eWorldDirection::S) {
        return left<T>();
    } else if(dir == eWorldDirection::W) {
        return top<T>();
    }
}

template<typename T>
T* eTileBase::topRotated(const eWorldDirection dir) const {
    if(dir == eWorldDirection::N) {
        return top<T>();
    } else if(dir == eWorldDirection::E) {
        return right<T>();
    } else if(dir == eWorldDirection::S) {
        return bottom<T>();
    } else if(dir == eWorldDirection::W) {
        return left<T>();
    }
}

template<typename T>
T* eTileBase::leftRotated(const eWorldDirection dir) const {
    if(dir == eWorldDirection::N) {
        return left<T>();
    } else if(dir == eWorldDirection::E) {
        return top<T>();
    } else if(dir == eWorldDirection::S) {
        return right<T>();
    } else if(dir == eWorldDirection::W) {
        return bottom<T>();
    }
}

template<typename T>
T* eTileBase::bottomLeftRotated(const eWorldDirection dir) const {
    if(dir == eWorldDirection::N) {
        return bottomLeft<T>();
    } else if(dir == eWorldDirection::E) {
        return topLeft<T>();
    } else if(dir == eWorldDirection::S) {
        return topRight<T>();
    } else if(dir == eWorldDirection::W) {
        return bottomRight<T>();
    }
}

template<typename T>
T* eTileBase::bottomRightRotated(const eWorldDirection dir) const {
    if(dir == eWorldDirection::N) {
        return bottomRight<T>();
    } else if(dir == eWorldDirection::E) {
        return bottomLeft<T>();
    } else if(dir == eWorldDirection::S) {
        return topLeft<T>();
    } else if(dir == eWorldDirection::W) {
        return topRight<T>();
    }
}

template<typename T>
T* eTileBase::topRightRotated(const eWorldDirection dir) const {
    if(dir == eWorldDirection::N) {
        return topRight<T>();
    } else if(dir == eWorldDirection::E) {
        return bottomRight<T>();
    } else if(dir == eWorldDirection::S) {
        return bottomLeft<T>();
    } else if(dir == eWorldDirection::W) {
        return topLeft<T>();
    }
}

template<typename T>
T* eTileBase::topLeftRotated(const eWorldDirection dir) const {
    if(dir == eWorldDirection::N) {
        return topLeft<T>();
    } else if(dir == eWorldDirection::E) {
        return topRight<T>();
    } else if(dir == eWorldDirection::S) {
        return bottomRight<T>();
    } else if(dir == eWorldDirection::W) {
        return bottomLeft<T>();
    }
}

template <typename T>
T* eTileBase::left() const {
    return tileRel<T>(-1, 1);
}

template <typename T>
T* eTileBase::top() const {
    return tileRel<T>(-1, -1);
}

template <typename T>
T* eTileBase::right() const {
    return tileRel<T>(1, -1);
}

template <typename T>
T* eTileBase::bottom() const {
    return tileRel<T>(1, 1);
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
T* eTileBase::tileRelRotated(const int x, const int y,
                             const eWorldDirection dir) const {
    if(x == 0 && y == 0) {
        const auto t = static_cast<const T*>(this);
        return const_cast<T*>(t);
    }
    if(x > 0) {
        const auto br = bottomRightRotated<T>(dir);
        if(!br) {
            if(y != 0) {
                const auto ry = tileRelRotated<T>(x - 1, y, dir);
                if(!ry) return nullptr;
                return ry->template tileRelRotated<T>(1, 0, dir);
            }
            return nullptr;
        }
        return br->template tileRelRotated<T>(x - 1, y, dir);
    } else if(x < 0) {
        const auto tl = topLeftRotated<T>(dir);
        if(!tl)  {
            if(y != 0) {
                const auto ry = tileRelRotated<T>(x + 1, y, dir);
                if(!ry) return nullptr;
                return ry->template tileRelRotated<T>(-1, 0, dir);
            }
            return nullptr;
        }
        return tl->template tileRelRotated<T>(x + 1, y, dir);
    }
    if(y > 0) {
        const auto bl = bottomLeftRotated<T>(dir);
        if(!bl) return nullptr;
        return bl->template tileRelRotated<T>(x, y - 1, dir);
    } else if(y < 0) {
        const auto tr = topRightRotated<T>(dir);
        if(!tr) return nullptr;
        return tr->template tileRelRotated<T>(x, y + 1, dir);
    }
    return nullptr;
}

template <typename T>
T* eTileBase::tileAbsRotated(const int x, const int y,
                             const eWorldDirection dir) const {
    return tileRelRotated<T>(x - mX, y - mY, dir);
}

template <typename T>
T* eTileBase::tileRel(const int x, const int y) const {
    if(x == 0 && y == 0) {
        const auto t = static_cast<const T*>(this);
        return const_cast<T*>(t);
    }
    if(x > 0) {
        const auto br = bottomRight<T>();
        if(!br) {
            if(y != 0) {
                const auto ry = tileRel<T>(x - 1, y);
                if(!ry) return nullptr;
                return ry->template tileRel<T>(1, 0);
            }
            return nullptr;
        }
        return br->template tileRel<T>(x - 1, y);
    } else if(x < 0) {
        const auto tl = topLeft<T>();
        if(!tl)  {
            if(y != 0) {
                const auto ry = tileRel<T>(x + 1, y);
                if(!ry) return nullptr;
                return ry->template tileRel<T>(-1, 0);
            }
            return nullptr;
        }
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
