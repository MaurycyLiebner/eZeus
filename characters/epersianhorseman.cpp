#include "epersianhorseman.h"

#include "textures/egametextures.h"

ePersianHorseman::ePersianHorseman(eGameBoard& board) :
    eHorsemanBase(board, &eCharacterTextures::fPersianHorseman,
                  eCharacterType::persianHorseman) {
    eGameTextures::loadPersianHorseman();
}
