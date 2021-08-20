#ifndef EPATROLBUILDING_H
#define EPATROLBUILDING_H

#include "ebuilding.h"

#include "characters/actions/epatrolaction.h"
#include "textures/ebuildingtextures.h"

class ePatrolBuilding : public eBuilding {
public:
    using eBaseTex = eTexture eBuildingTextures::*;
    using eOverlays = eTextureCollection eBuildingTextures::*;
    using eCharGenerator =  std::function<eCharacter*()>;
    using eActGenerator =  std::function<eCharacterAction*(
                                eCharacter* const c,
                                const std::vector<ePatrolGuide>& guides,
                                const eAction& failAction,
                                const eAction& finishAction)>;
    ePatrolBuilding(eGameBoard& board,
                    const eBaseTex baseTex,
                    const double overlayX,
                    const double overlayY,
                    const eOverlays overlays,
                    const eCharGenerator& charGen,
                    const eActGenerator& actGen,
                    const eBuildingType type,
                    const int sw, const int sh);
    ePatrolBuilding(eGameBoard& board,
                    const eBaseTex baseTex,
                    const double overlayX,
                    const double overlayY,
                    const eOverlays overlays,
                    const eCharGenerator& charGen,
                    const eBuildingType type,
                    const int sw, const int sh);

    eTexture getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;

    void timeChanged();

    using ePatrolGuides = std::vector<ePatrolGuide>;
    ePatrolGuides* patrolGuides() { return &mPatrolGuides; };
    void setPatrolGuides(const ePatrolGuides& g);

    eMoveDirection spawnDirection() const { return mSpawnDirection; }
    void setSpawnDirection(const eMoveDirection d);

    bool spawn();
private:
    const eCharGenerator mCharGenerator;
    const eActGenerator mActGenerator;
    const std::vector<eBuildingTextures>& mTextures;

    const eBaseTex mBaseTex;
    const eOverlays mOverlays;

    const double mOverlayX;
    const double mOverlayY;

    int mWaitTime = 5000;
    int mSpawnTime = 0;
    bool mSpawned{false};

    eMoveDirection mSpawnDirection{eMoveDirection::allDirections};
    ePatrolGuides mPatrolGuides;
};

#endif // EPATROLBUILDING_H
