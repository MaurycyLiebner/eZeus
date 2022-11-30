#include "erockthrower.h"

#include "textures/egametextures.h"

eRockThrower::eRockThrower(eGameBoard& board) :
    eRockThrowerBase(board, &eCharacterTextures::fRockThrower,
                     eCharacterType::rockThrower) {
    eGameTextures::loadRockThrower();
}
