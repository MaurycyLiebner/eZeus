#include "egreekrockthrower.h"

#include "textures/egametextures.h"

eGreekRockThrower::eGreekRockThrower(eGameBoard& board) :
    eRangeSoldier(board, &eCharacterTextures::fRockThrower,
                  eCharacterType::rockThrower, 4) {}
