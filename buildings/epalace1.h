#ifndef EPALACE1_H
#define EPALACE1_H

#include "ebuilding.h"
#include "textures/ebuildingtextures.h"
#include "characters/actions/epatrolaction.h"

class ePalace1W : public eBuilding {
public:
    ePalace1W(eGameBoard& board);

    eTexture getTexture(const eTileSize size) const;
private:
    const std::vector<eBuildingTextures>& mTextures;
};

class ePalace1H : public eBuilding {
public:
    ePalace1H(eGameBoard& board);

    eTexture getTexture(const eTileSize size) const;
private:
    const std::vector<eBuildingTextures>& mTextures;
};

#endif // EPALACE1_H
