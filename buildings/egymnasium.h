#ifndef EGYMNASIUM_H
#define EGYMNASIUM_H

#include "ebuilding.h"
#include "textures/ebuildingtextures.h"
#include "characters/actions/epatrolaction.h"

class eGymnasium : public eBuilding {
public:
    eGymnasium();

    eTexture getTexture(const eTileSize size) const;
    std::vector<eOverlay> getOverlays(const eTileSize size) const;

    using ePatrolGuides = std::vector<ePatrolGuide>;
    void setPatrolGuides(const ePatrolGuides& g);

    void spawn() const;
private:
    const std::vector<eBuildingTextures>& mTextures;
    ePatrolGuides mPatrolGuides;
};

#endif // EGYMNASIUM_H
