#include "espearmissile.h"

#include "textures/egametextures.h"

eSpearMissile::eSpearMissile(eGameBoard& board,
                             const std::vector<ePathPoint>& path) :
    eArrowSpearBase(board, &eDestructionTextures::fSpear,
                    eMissileType::spear, path) {
    eGameTextures::loadSpear();
}
