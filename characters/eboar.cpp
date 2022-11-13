#include "eboar.h"

eBoar::eBoar(eGameBoard& board) :
    eWildAnimal(board, &eCharacterTextures::fBoar,
                eCharacterType::boar) {
    setPlayerId(0);
    setHP(100);
    setAttack(0);
}
