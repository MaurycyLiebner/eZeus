#include "eegyptianhoplite.h"

#include "textures/egametextures.h"

eEgyptianHoplite::eEgyptianHoplite(eGameBoard& board) :
    eHopliteBase(board, &eCharacterTextures::fEgyptianHoplite,
                 eCharacterType::egyptianHoplite) {
    eGameTextures::loadEgyptianHoplite();
}
