#ifndef ETHEATER_H
#define ETHEATER_H

#include "ebuilding.h"
#include "textures/ebuildingtextures.h"
#include "characters/actions/epatrolaction.h"

class eTheater : public eBuilding {
public:
    eTheater();

    eTexture getTexture(const eTileSize size) const;
private:
    const std::vector<eBuildingTextures>& mTextures;
};

#endif // ETHEATER_H
