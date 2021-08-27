#ifndef ESHEPHERBUILDINGBASE_H
#define ESHEPHERBUILDINGBASE_H

#include "eresourcebuildingbase.h"

#include "textures/ebuildingtextures.h"

class eResourceCollector;

enum class eCharacterType;

class eShepherBuildingBase : public eResourceBuildingBase {
public:
    using eBaseTex = eTexture eBuildingTextures::*;
    using eOverlays = eTextureCollection eBuildingTextures::*;
    using eRC = eResourceCollector;
    using eCharGenerator =  std::function<stdsptr<eRC>(eGameBoard&)>;
    eShepherBuildingBase(eGameBoard& board,
                         const eBaseTex baseTex,
                         const double overlayX,
                         const double overlayY,
                         const eOverlays overlays,
                         const eCharGenerator& charGen,
                         const eBuildingType type,
                         const eResourceType resType,
                         const eCharacterType animalType,
                         const int sw, const int sh,
                         const int maxEmployees);

    eTexture getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;

    void timeChanged();

    bool spawn();
private:
    const eCharGenerator mCharGenerator;
    const std::vector<eBuildingTextures>& mTextures;

    const eBaseTex mBaseTex;
    const eOverlays mOverlays;

    const double mOverlayX;
    const double mOverlayY;

    const eCharacterType mAnimalType;

    stdsptr<eResourceCollector> mShepherd;
    int mWaitTime = 5000;
    int mSpawnTime = mWaitTime;
};

#endif // ESHEPHERBUILDINGBASE_H
