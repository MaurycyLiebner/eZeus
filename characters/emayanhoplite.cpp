#include "emayanhoplite.h"

#include "textures/egametextures.h"

eMayanHoplite::eMayanHoplite(eGameBoard& board) :
    eHopliteBase(board, &eCharacterTextures::fMayanHoplite,
                 eCharacterType::mayanHoplite) {
    eGameTextures::loadMayanHoplite();
}
