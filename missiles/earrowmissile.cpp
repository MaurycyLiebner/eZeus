#include "earrowmissile.h"

#include "textures/egametextures.h"

eArrowMissile::eArrowMissile(eGameBoard& board,
                             const std::vector<ePathPoint>& path) :
    eArrowSpearBase(board, &eDestructionTextures::fArrow,
                    eMissileType::arrow, path) {
    eGameTextures::loadArrow();
}
