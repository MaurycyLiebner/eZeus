#ifndef ESTADIUM1_H
#define ESTADIUM1_H

#include "eemployingbuilding.h"
#include "textures/ebuildingtextures.h"
#include "characters/actions/epatrolaction.h"

class eStadium1W : public eEmployingBuilding {
public:
    eStadium1W(eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
private:
    const std::vector<eBuildingTextures>& mTextures;
};

class eStadium1H : public eEmployingBuilding {
public:
    eStadium1H(eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
private:
    const std::vector<eBuildingTextures>& mTextures;
};

#endif // ESTADIUM1_H
