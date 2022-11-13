#include "edeer.h"

eDeer::eDeer(eGameBoard& board) :
    eWildAnimal(board, &eCharacterTextures::fDeer,
                eCharacterType::deer) {
    setPlayerId(0);
    setAttack(0);
    setHP(100);
}
