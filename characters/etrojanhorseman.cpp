#include "etrojanhorseman.h"

#include "textures/egametextures.h"

eTrojanHorseman::eTrojanHorseman(eGameBoard& board) :
    eHorsemanBase(board, &eCharacterTextures::fTrojanHorseman,
                  eCharacterType::trojanHorseman) {
    eGameTextures::loadTrojanHorseman();
}
