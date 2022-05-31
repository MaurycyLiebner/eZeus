#include "eboar.h"

eBoar::eBoar(eSpawner* const s, eGameBoard& board) :
    eWildAnimal(s, board, &eCharacterTextures::fBoar,
                eCharacterType::boar) {
    setPlayerId(0);
    setHP(100);
    setAttack(0);
}
