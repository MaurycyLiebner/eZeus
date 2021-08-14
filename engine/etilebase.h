#ifndef ETILEBASE_H
#define ETILEBASE_H

#include "eterrain.h"

#include <functional>

#include "eorientation.h"

template <typename T>
class eTileBase {
public:
    eTileBase() {}

    int seed() const { return mSeed; }
    int x() const { return mX; }
    int y() const { return mY; }
    int altitude() const { return mAltitude; }
    eTerrain terrain() const { return mTerr; }
    double scrub() const { return mScrub; }

    void setSeed(const int s);
    void setX(const int x);
    void setY(const int y);

    T* topLeft() const { return mTopLeft; }
    T* topRight() const { return mTopRight; }
    T* bottomRight() const { return mBottomRight; }
    T* bottomLeft() const { return mBottomLeft; }

    T* left() const;
    T* top() const;
    T* right() const;
    T* bottom() const;

    using eTO = std::pair<eOrientation, T*>;
    using eTileVerifier = std::function<bool(T* const)>;

    std::vector<eTO> neighbours(const eTileVerifier& v) const;
    eTO randomNeighbour(const eTileVerifier& v) const;

    std::vector<eTO> diagonalNeighbours(const eTileVerifier& v) const;
    eTO randomDiagonalNeighbour(const eTileVerifier& v) const;

    T* neighbour(const eOrientation o) const;

    T* tileRel(const int x, const int y);
    T* tileAbs(const int x, const int y);

    void setAltitude(const int a);
    void setTerrain(const eTerrain terr);
    void setScrub(const double s);
    void incScrub(const double s);

    void setTopLeft(T* const tl);
    void setTopRight(T* const tr);
    void setBottomRight(T* const br);
    void setBottomLeft(T* const bl);

    bool walkableElev() const { return mWalkableElev; }
    void setWalkableElev(const bool w);

    int resource() { return mResource; }
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

    T* mTopLeft = nullptr;
    T* mTopRight = nullptr;
    T* mBottomRight = nullptr;
    T* mBottomLeft = nullptr;

    eTerrain mTerr = eTerrain::dry;
    double mScrub = 0;
    int mAltitude = 0;
};

template <typename T>
void eTileBase<T>::setWalkableElev(const bool w) {
    mWalkableElev = w;
}

template <typename T>
void eTileBase<T>::decResource(const int by) {
    mResource -= by;
}

template<typename T>
void eTileBase<T>::setResource(const int r) {
    mResource = r;
}

template <typename T>
void eTileBase<T>::setBusy(const bool b) {
    mBusy = b;
}

template<typename T>
void eTileBase<T>::setSeed(const int s) {
    mSeed = s;
}

template<typename T>
void eTileBase<T>::setX(const int x) {
    mX = x;
}

template<typename T>
void eTileBase<T>::setY(const int y) {
    mY = y;
}

template <typename T>
T* eTileBase<T>::left() const {
    if(!mBottomLeft) return nullptr;
    return mBottomLeft->topLeft();
}

template <typename T>
T* eTileBase<T>::top() const {
    if(!mTopLeft) return nullptr;
    return mTopLeft->topRight();
}

template <typename T>
T* eTileBase<T>::right() const {
    if(!mTopRight) return nullptr;
    return mTopRight->bottomRight();
}

template <typename T>
T* eTileBase<T>::bottom() const {
    if(!mBottomLeft) return nullptr;
    return mBottomLeft->bottomRight();
}

template <typename T>
std::vector<typename eTileBase<T>::eTO> eTileBase<T>::neighbours(const eTileVerifier& v) const {
    std::vector<eTileBase<T>::eTO> result;
    for(int i = 0; i < 8; i++) {
        const auto o = static_cast<eOrientation>(i);
        const auto t = neighbour(o);
        if(!t) continue;
        if(v(t)) result.push_back({o, t});
    }
    return result;
}

template <typename T>
typename eTileBase<T>::eTO eTileBase<T>::randomNeighbour(const eTileVerifier& v) const {
    const auto ts = neighbours(v);
    if(ts.empty()) return {eOrientation::top, nullptr};
    return ts[rand() % ts.size()];
}

template <typename T>
std::vector<typename eTileBase<T>::eTO> eTileBase<T>::diagonalNeighbours(const eTileVerifier& v) const {
    std::vector<eTileBase<T>::eTO> result;
    for(int i = 0; i < 8; i += 2) {
        const auto o = static_cast<eOrientation>(i);
        const auto t = neighbour(o);
        if(!t) continue;
        if(v(t)) result.push_back({o, t});
    }
    return result;
}

template <typename T>
typename eTileBase<T>::eTO eTileBase<T>::randomDiagonalNeighbour(const eTileVerifier& v) const {
    const auto ts = diagonalNeighbours(v);
    if(ts.empty()) return {eOrientation::top, nullptr};
    return ts[rand() % ts.size()];
}

template <typename T>
T* eTileBase<T>::neighbour(const eOrientation o) const {
    switch(o) {
    case eOrientation::topRight: {
        return topRight();
    } break;
    case eOrientation::right: {
        return right();
    } break;
    case eOrientation::bottomRight: {
        return bottomRight();
    } break;
    case eOrientation::bottom: {
        return bottom();
    } break;
    case eOrientation::bottomLeft: {
        return bottomLeft();
    } break;
    case eOrientation::left: {
        return left();
    } break;
    case eOrientation::topLeft: {
        return topLeft();
    } break;
    case eOrientation::top: {
        return top();
    } break;
    }
    return nullptr;
}

template <typename T>
T* eTileBase<T>::tileRel(const int x, const int y) {
    if(x == 0 && y == 0) return static_cast<T*>(this);
    if(x > 0) {
        const auto br = bottomRight();
        if(!br) return nullptr;
        return br->tileRel(x - 1, y);
    } else if(x < 0) {
        const auto tl = topLeft();
        if(!tl) return nullptr;
        return tl->tileRel(x + 1, y);
    }
    if(y > 0) {
        const auto bl = bottomLeft();
        if(!bl) return nullptr;
        return bl->tileRel(x, y - 1);
    } else if(y < 0) {
        const auto tl = topRight();
        if(!tl) return nullptr;
        return tl->tileRel(x, y + 1);
    }
    return nullptr;
}

template <typename T>
T* eTileBase<T>::tileAbs(const int x, const int y) {
    return tileRel(x - mX, y - mY);
}

template <typename T>
void eTileBase<T>::setAltitude(const int a) {
    mAltitude = a;
}

template <typename T>
void eTileBase<T>::setTerrain(const eTerrain terr) {
    mTerr = terr;
}

template <typename T>
void eTileBase<T>::setScrub(const double s) {
    mScrub = std::clamp(s, 0., 1.);
}

template <typename T>
void eTileBase<T>::incScrub(const double s) {
    setScrub(mScrub + s);
}

template <typename T>
void eTileBase<T>::setTopLeft(T* const tl) {
    mTopLeft = tl;
}

template <typename T>
void eTileBase<T>::setTopRight(T* const tr) {
    mTopRight = tr;
}

template <typename T>
void eTileBase<T>::setBottomRight(T* const br) {
    mBottomRight = br;
}

template <typename T>
void eTileBase<T>::setBottomLeft(T* const bl) {
    mBottomLeft = bl;
}

#endif // ETILEBASE_H
