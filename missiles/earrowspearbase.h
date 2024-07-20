#ifndef EARROWSPEARBASE_H
#define EARROWSPEARBASE_H

#include "emissile.h"

#include "textures/edestructiontextures.h"

class eArrowSpearBase : public eMissile {
public:
    using eMissileTexs = eTextureCollection eDestructionTextures::*;
    eArrowSpearBase(eGameBoard& board,
                    const eMissileTexs missileTexs,
                    const eMissileType type,
                    const std::vector<ePathPoint>& path = {});

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;
private:
    const eMissileTexs mTexs;
};

#endif // EARROWSPEARBASE_H
