#ifndef ESHEPHERBUILDINGBASE_H
#define ESHEPHERBUILDINGBASE_H

#include "eresourcebuildingbase.h"

#include "textures/ebuildingtextures.h"
#include "enumbers.h"

class eResourceCollectorBase;

enum class eCharacterType;

class eShepherBuildingBase : public eResourceBuildingBase {
public:
    using eBaseTex = std::shared_ptr<eTexture> eBuildingTextures::*;
    using eOverlays = eTextureCollection eBuildingTextures::*;
    using eRC = eResourceCollectorBase;
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
    ~eShepherBuildingBase();

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const override;
    std::vector<eOverlay> getOverlays(const eTileSize size) const override;

    void timeChanged(const int by) override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    bool spawn();
private:
    const eCharGenerator mCharGenerator;
    const std::vector<eBuildingTextures>& mTextures;

    const eBaseTex mBaseTex;
    const eOverlays mOverlays;

    const double mOverlayX;
    const double mOverlayY;

    const eCharacterType mAnimalType;

    stdptr<eResourceCollectorBase> mShepherd;

    int mSpawnTime = 1000000;
};

#endif // ESHEPHERBUILDINGBASE_H
