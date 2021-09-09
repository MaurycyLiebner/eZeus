#ifndef ETILE_H
#define ETILE_H

#include <vector>
#include <functional>

#include "etilebase.h"
#include "eterrain.h"
#include "eorientation.h"

#include "pointers/estdselfref.h"

enum class eTileSize : int {
    s15, s30, s60
};

class eCharacter;
class eBuilding;
class eSpawner;

class eTile : public eTileBase {
public:
    eTile(const int x, const int y);

    int scrubId(const int nLevels) const;

    void addCharacter(const stdsptr<eCharacter>& c);
    bool removeCharacter(const stdsptr<eCharacter>& c);
    bool hasCharacter(const eHasChar& func) const;

    const std::vector<stdsptr<eCharacter>>& characters() const
    { return mCharacters; }

    void setBuilding(const stdsptr<eBuilding>& b);
    eBuilding* building() const { return mBuilding.get(); }
    bool hasRoad() const;
    void setUnderBuilding(eBuilding* const b);
    eBuilding* underBuilding() const { return mUnderBuilding; }
    eBuildingType underBuildingType() const;

    void setSpawner(eSpawner* const s);
    eSpawner* spawner() const { return mSpawner; }

    // used for stones rendering
    void setFutureDimension(const int futureDim);
    int futureDim() const { return mFutureDim; }

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
    int mFutureDim = 0;
private:
    std::vector<stdsptr<eCharacter>> mCharacters;
    eBuilding* mUnderBuilding = nullptr;
    stdsptr<eBuilding> mBuilding;
    eSpawner* mSpawner = nullptr;
};

#endif // ETILE_H
