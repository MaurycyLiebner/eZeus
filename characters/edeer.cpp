#include "edeer.h"

#include "textures/egametextures.h"

eDeer::eDeer(eGameBoard& board) :
    eWildAnimal(board, &eCharacterTextures::fDeer,
                eCharacterType::deer) {
    eGameTextures::loadDeer();
    setPlayerId(0);
    setAttack(0);
    setHP(100);
}
