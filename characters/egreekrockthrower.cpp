#include "egreekrockthrower.h"

#include "textures/egametextures.h"

eGreekRockThrower::eGreekRockThrower(eGameBoard& board) :
    eRockThrowerBase(board, &eCharacterTextures::fGreekRockThrower,
                     eCharacterType::greekRockThrower) {
    eGameTextures::loadGreekRockThrower();
}
