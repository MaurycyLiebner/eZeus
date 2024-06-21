#include "ewolf.h"

#include "textures/egametextures.h"

eWolf::eWolf(eGameBoard& board) :
    eWildAnimal(board, &eCharacterTextures::fWolf,
                eCharacterType::wolf) {
    eGameTextures::loadWolf();
    setPlayerId(2);
    setAttack(0.25);
    setHP(300);
}
