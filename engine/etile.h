#ifndef ETILE_H
#define ETILE_H

#include <vector>

enum class eTerrain {
    dry = 1 << 0,
    beach = 1 << 1,
    water = 1 << 2,
    fertile = 1 << 3,
    forest = 1 << 4,

    dryBased = eTerrain::dry |
               eTerrain::fertile |
               eTerrain::forest
};

inline eTerrain operator|(const eTerrain a, const eTerrain b) {
    return static_cast<eTerrain>(static_cast<int>(a) | static_cast<int>(b));
}

inline eTerrain operator&(const eTerrain a, const eTerrain b) {
    return static_cast<eTerrain>(static_cast<int>(a) & static_cast<int>(b));
}

class eTile {
public:
    eTile(const int x, const int y);
    int id() const { return mId; }
    int x() const { return mX; }
    int y() const { return mY; }
    int altitude() const { return mAltitude; }
    eTerrain terrain() const { return mTerr; }
    double scrub() const { return mScrub; }
    int scrubId(const int nLevels) const;

    eTile* topLeft() const { return mTopLeft; }
    eTile* topRight() const { return mTopRight; }
    eTile* bottomRight() const { return mBottomRight; }
    eTile* bottomLeft() const { return mBottomLeft; }

    eTile* left() const;
    eTile* top() const;
    eTile* right() const;
    eTile* bottom() const;

    void setTerrain(const eTerrain terr);
    void setScrub(const double s);
    void incScrub(const double s);

    void setTopLeft(eTile* const tl);
    void setTopRight(eTile* const tr);
    void setBottomRight(eTile* const br);
    void setBottomLeft(eTile* const bl);

    void surroundingTerrain(eTerrain& tlTerr,
                          eTerrain& trTerr,
                          eTerrain& brTerr,
                          eTerrain& blTerr,
                          eTerrain& tTerr,
                          eTerrain& rTerr,
                          eTerrain& bTerr,
                          eTerrain& lTerr) const;
    void neighboursWithTerrain(const eTerrain terr,
                               bool& tl, bool& tr,
                               bool& br, bool& bl,
                               bool& t, bool& r,
                               bool& b, bool& l) const;
    void neighbourTerrainTypes(std::vector<eTerrain>& neighTerrs) const;
    void majorNeighbourTerrainTypes(std::vector<eTerrain>& neighTerrs) const;
private:
    const int mId;
    const int mX;
    const int mY;

    eTile* mTopLeft = nullptr;
    eTile* mTopRight = nullptr;
    eTile* mBottomRight = nullptr;
    eTile* mBottomLeft = nullptr;

    eTerrain mTerr = eTerrain::dry;
    double mScrub = 0;
    int mAltitude = 0;
};

#endif // ETILE_H
