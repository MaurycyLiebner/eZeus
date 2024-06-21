#include "eboar.h"

#include "textures/egametextures.h"

eBoar::eBoar(eGameBoard& board) :
    eWildAnimal(board, &eCharacterTextures::fBoar,
                eCharacterType::boar) {
    eGameTextures::loadBoar();
    setPlayerId(0);
    setHP(100);
    setAttack(0);
}
