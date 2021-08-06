#ifndef ESTADIUM1_H
#define ESTADIUM1_H

#include "ebuilding.h"
#include "textures/ebuildingtextures.h"
#include "characters/actions/epatrolaction.h"

class eStadium1W : public eBuilding {
public:
    eStadium1W();

    eTexture getTexture(const eTileSize size) const;
private:
    const std::vector<eBuildingTextures>& mTextures;
};

class eStadium1H : public eBuilding {
public:
    eStadium1H();

    eTexture getTexture(const eTileSize size) const;
private:
    const std::vector<eBuildingTextures>& mTextures;
};

#endif // ESTADIUM1_H
