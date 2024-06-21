#include "eoceanidhoplite.h"

#include "textures/egametextures.h"

eOceanidHoplite::eOceanidHoplite(eGameBoard& board) :
    eHopliteBase(board, &eCharacterTextures::fOceanidHoplite,
                 eCharacterType::oceanidHoplite) {
    eGameTextures::loadOceanidHoplite();
}
