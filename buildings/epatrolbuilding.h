#ifndef EPATROLBUILDING_H
#define EPATROLBUILDING_H

#include "epatrolbuildingbase.h"

#include "characters/actions/epatrolaction.h"
#include "textures/ebuildingtextures.h"

class ePatrolBuilding : public ePatrolBuildingBase {
public:
    using eBaseTex = std::shared_ptr<eTexture> eBuildingTextures::*;
    using eOverlays = eTextureCollection eBuildingTextures::*;
    ePatrolBuilding(eGameBoard& board,
                    const eBaseTex baseTex,
                    const double overlayX,
                    const double overlayY,
                    const eOverlays overlays,
                    const eCharGenerator& charGen,
                    const eActGenerator& actGen,
                    const eBuildingType type,
                    const int sw, const int sh,
                    const int maxEmployees);
    ePatrolBuilding(eGameBoard& board,
                    const eBaseTex baseTex,
                    const double overlayX,
                    const double overlayY,
                    const eOverlays overlays,
                    const eCharGenerator& charGen,
                    const eBuildingType type,
                    const int sw, const int sh,
                    const int maxEmployees);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;
protected:
    void setOverlaySpeed(const double s);
private:
    const eBaseTex mBaseTex;
    const eOverlays mOverlays;

    const double mOverlayX;
    const double mOverlayY;

    double mOverlaySpeed = 1.;
};

#endif // EPATROLBUILDING_H
