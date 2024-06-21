#include "eatlanteanhoplite.h"

#include "textures/egametextures.h"

eAtlanteanHoplite::eAtlanteanHoplite(eGameBoard& board) :
    eHopliteBase(board, &eCharacterTextures::fAtlanteanHoplite,
                 eCharacterType::atlanteanHoplite) {
    eGameTextures::loadAtlanteanHoplite();
}
