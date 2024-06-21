#include "epersianhoplite.h"

#include "textures/egametextures.h"

ePersianHoplite::ePersianHoplite(eGameBoard& board) :
    eHopliteBase(board, &eCharacterTextures::fPersianHoplite,
                 eCharacterType::persianHoplite) {
    eGameTextures::loadPersianHoplite();
}
