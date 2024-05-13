#include "etrojanhoplite.h"

#include "textures/egametextures.h"

eTrojanHoplite::eTrojanHoplite(eGameBoard& board) :
    eHopliteBase(board, &eCharacterTextures::fGreekHoplite,
                 eCharacterType::trojanHoplite) {
    eGameTextures::loadTrojanHoplite();
}
