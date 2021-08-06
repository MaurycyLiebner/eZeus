#ifndef ESTADIUM2_H
#define ESTADIUM2_H

#include "ebuilding.h"
#include "textures/ebuildingtextures.h"
#include "characters/actions/epatrolaction.h"

class eStadium2W : public eBuilding {
public:
    eStadium2W();

    eTexture getTexture(const eTileSize size) const;
private:
    const std::vector<eBuildingTextures>& mTextures;
};

class eStadium2H : public eBuilding {
public:
    eStadium2H();

    eTexture getTexture(const eTileSize size) const;
private:
    const std::vector<eBuildingTextures>& mTextures;
};

#endif // ESTADIUM2_H
