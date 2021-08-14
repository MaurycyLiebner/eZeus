#ifndef ETILE_H
#define ETILE_H

#include <vector>
#include <functional>

#include "etilebase.h"
#include "eterrain.h"
#include "eorientation.h"

enum class eTileSize : int {
    s15, s30, s60
};

class eCharacter;
class eBuilding;
class eSpawner;

class eTile : public eTileBase<eTile> {
public:
    eTile(const int x, const int y);

    int scrubId(const int nLevels) const;

    void addCharacter(eCharacter* const c);
    bool removeCharacter(eCharacter* const c);

    const std::vector<eCharacter*>& characters() const
    { return mCharacters; }

    bool walkable() const;

    void setBuilding(eBuilding* const b);
    eBuilding* building() const { return mBuilding; }
    bool hasRoad() const;
    void setUnderBuilding(eBuilding* const b);
    eBuilding* underBuilding() const { return mUnderBuilding; }

    void setSpawner(eSpawner* const s);
    eSpawner* spawner() const { return mSpawner; }

    // used for stones rendering
    void setDrawnSpan(const int w, const int h);
    int drawSpanW() const { return mDrawnSpanW; }
    int drawSpanH() const { return mDrawnSpanH; }

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
private:
    int mDrawnSpanW = 0;
    int mDrawnSpanH = 0;
private:
    std::vector<eCharacter*> mCharacters;
    eBuilding* mUnderBuilding = nullptr;
    eBuilding* mBuilding = nullptr;
    eSpawner* mSpawner = nullptr;
};

#endif // ETILE_H
