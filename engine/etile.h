#ifndef ETILE_H
#define ETILE_H

#include <vector>
#include <functional>

#include "eterrain.h"
#include "eorientation.h"

enum class eTileSize {
    s15, s30, s60
};

class eCharacter;
class eBuilding;

class eTile {
public:
    eTile(const int x, const int y);
    int seed() const { return mSeed; }
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

    using eTO = std::pair<eOrientation, eTile*>;
    using eTileVerifier = std::function<bool(eTile* const)>;

    std::vector<eTO> neighbours(const eTileVerifier& v) const;
    eTO randomNeighbour(const eTileVerifier& v) const;

    std::vector<eTO> diagonalNeighbours(const eTileVerifier& v) const;
    eTO randomDiagonalNeighbour(const eTileVerifier& v) const;

    eTile* neighbour(const eOrientation o) const;

    eTile* tileRel(const int x, const int y);
    eTile* tileAbs(const int x, const int y);

    void setTerrain(const eTerrain terr);
    void setScrub(const double s);
    void incScrub(const double s);

    void setTopLeft(eTile* const tl);
    void setTopRight(eTile* const tr);
    void setBottomRight(eTile* const br);
    void setBottomLeft(eTile* const bl);

    std::vector<eTile*> surroundingRoads() const;
    eTile* nearestRoad() const;

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

    void addCharacter(eCharacter* const c);
    bool removeCharacter(eCharacter* const c);

    const std::vector<eCharacter*>& characters() const
    { return mCharacters; }

    void addBuilding(eBuilding* const b);
    eBuilding* building() const { return mBuilding; }
    bool hasRoad() const;

    // used for stones rendering
    void setDrawnSpan(const int w, const int h);
    int drawSpanW() const { return mDrawnSpanW; }
    int drawSpanH() const { return mDrawnSpanH; }
private:
    int mDrawnSpanW = 0;
    int mDrawnSpanH = 0;
private:
    const int mSeed;
    const int mX;
    const int mY;

    std::vector<eCharacter*> mCharacters;
    eBuilding* mBuilding = nullptr;

    eTile* mTopLeft = nullptr;
    eTile* mTopRight = nullptr;
    eTile* mBottomRight = nullptr;
    eTile* mBottomLeft = nullptr;

    eTerrain mTerr = eTerrain::dry;
    double mScrub = 0;
    int mAltitude = 0;
};

#endif // ETILE_H
