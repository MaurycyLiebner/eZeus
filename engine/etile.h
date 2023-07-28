#ifndef ETILE_H
#define ETILE_H

#include <vector>
#include <functional>

#include "etilebase.h"
#include "eterrain.h"
#include "eorientation.h"

#include "pointers/estdselfref.h"
#include "pointers/estdpointer.h"

#include "characters/esoldierbanner.h"

enum class eTileSize : int {
    s15, s30, s45, s60
};

class eMissile;
class eCharacter;
class eBuilding;
class eBuildingRenderer;
class eBanner;
class eSoldierBanner;
class eTexture;
class eTextureCollection;

struct eTileTerrainPainter {
    stdsptr<eTexture> fTex = nullptr;
    const eTextureCollection* fColl = nullptr;
    int fFutureDim = 1;
    int fDrawDim = 1;
};

class eTile : public eTileBase {
public:
    eTile(const int x, const int y,
          const int dx, const int dy);

    int scrubId(const int nLevels) const;

    void addCharacter(const stdsptr<eCharacter>& c,
                      const bool prepend = false);
    bool removeCharacter(const stdsptr<eCharacter>& c);
    bool hasCharacter(const eHasChar& func) const override;

    const std::vector<stdsptr<eCharacter>>& characters() const
    { return mCharacters; }

    void addMissile(const stdsptr<eMissile>& m);
    bool removeMissile(const stdsptr<eMissile>& m);

    const std::vector<stdsptr<eMissile>>& missiles() const
    { return mMissiles; }

    void setBuilding(const stdsptr<eBuildingRenderer>& b);
    eBuildingRenderer* building() const { return mBuilding.get(); }
    bool hasRoad() const override;
    void setUnderBuilding(const stdsptr<eBuilding>& b);
    eBuilding* underBuilding() const { return mUnderBuilding.get(); }
    eBuildingType underBuildingType() const override;

    void setBanner(eBanner* const s);
    eBanner* banner() const { return mBanner; }

    void setSoldierBanner(eSoldierBanner* const b);
    eSoldierBanner* soldierBanner() const { return mSoldierBanner; }

    // used for stones rendering
    void setFutureDimension(const int futureDim);
    int futureDim() const { return mTerrainPainter.fFutureDim; }

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

    void addTerrainTile(eTile* const tile) { mTerrainTiles.push_back(tile); }
    std::vector<eTile*>& terrainTiles() { return mTerrainTiles; }

    eTileTerrainPainter& terrainPainter() { return mTerrainPainter; }
    bool updateTerrain() const { return mUpdateTerrain; }
    void scheduleTerrainUpdate() { mUpdateTerrain = true; }
    void terrainUpdated() { mUpdateTerrain = false; }

    bool onFire() const override;
    void setOnFire(const bool f) override;

    void setTerrain(const eTerrain terr) override;
    void setMarbleLevel(const int l) override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    eTileTerrainPainter mTerrainPainter;
    bool mUpdateTerrain = false;
    std::vector<eTile*> mTerrainTiles;

    std::vector<stdsptr<eMissile>> mMissiles;
    std::vector<stdsptr<eCharacter>> mCharacters;
    stdsptr<eBuilding> mUnderBuilding;
    stdsptr<eBuildingRenderer> mBuilding;
    eBanner* mBanner = nullptr;
    stdptr<eSoldierBanner> mSoldierBanner;
};

#endif // ETILE_H
