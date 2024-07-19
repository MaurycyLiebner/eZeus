#include "eenemyboat.h"

#include "textures/egametextures.h"

eEnemyBoat::eEnemyBoat(eGameBoard& board) :
    eBoatBase(board, &eCharacterTextures::fEnemyBoat,
              eCharacterType::enemyBoat) {
    eGameTextures::loadEnemyBoat();
}
