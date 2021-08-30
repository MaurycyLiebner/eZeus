#ifndef ETHEATER_H
#define ETHEATER_H

#include "eemployingbuilding.h"
#include "textures/ebuildingtextures.h"
#include "characters/actions/epatrolaction.h"

class eTheater : public eEmployingBuilding {
public:
    eTheater(eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
private:
    const std::vector<eBuildingTextures>& mTextures;
};

#endif // ETHEATER_H
