#ifndef EPALACE2_H
#define EPALACE2_H

#include "ebuilding.h"
#include "textures/ebuildingtextures.h"
#include "characters/actions/epatrolaction.h"

class ePalace2W : public eBuilding {
public:
    ePalace2W();

    eTexture getTexture(const eTileSize size) const;
private:
    const std::vector<eBuildingTextures>& mTextures;
};

class ePalace2H : public eBuilding {
public:
    ePalace2H();

    eTexture getTexture(const eTileSize size) const;
private:
    const std::vector<eBuildingTextures>& mTextures;
};

#endif // EPALACE2_H
