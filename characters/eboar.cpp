#include "eboar.h"

eBoar::eBoar(eSpawner* const s, eGameBoard& board) :
    eAnimal(s, board, &eCharacterTextures::fBoar,
            eCharacterType::boar) {
    setPlayerId(0);
}
