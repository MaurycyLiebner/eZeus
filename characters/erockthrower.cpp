#include "erockthrower.h"

#include "textures/egametextures.h"

eRockThrower::eRockThrower(eGameBoard& board) :
    eRangeSoldier(board, &eCharacterTextures::fRockThrower,
                  eCharacterType::rockThrower, 4) {}
