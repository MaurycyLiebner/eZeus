#include "etrojanhoplite.h"

#include "textures/egametextures.h"

eTrojanHoplite::eTrojanHoplite(eGameBoard& board) :
    eHopliteBase(board, &eCharacterTextures::fTrojanHoplite,
                 eCharacterType::trojanHoplite) {
    eGameTextures::loadTrojanHoplite();
}
