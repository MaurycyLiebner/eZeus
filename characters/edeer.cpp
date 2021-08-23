#include "edeer.h"

eDeer::eDeer(eSpawner* const s, eGameBoard& board) :
    eAnimal(s, board, &eCharacterTextures::fDeer,
            eCharacterType::deer) {
    setPlayerId(0);
}
