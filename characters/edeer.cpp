#include "edeer.h"

eDeer::eDeer(eSpawner* const s, eGameBoard& board) :
    eWildAnimal(s, board, &eCharacterTextures::fDeer,
                eCharacterType::deer) {
    setPlayerId(0);
    setAttack(0);
    setHP(100);
}
