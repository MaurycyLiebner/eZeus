#include "ehoplite.h"

#include "textures/egametextures.h"

eHoplite::eHoplite(eGameBoard& board) :
    eHopliteBase(board, &eCharacterTextures::fHoplite) {
    setAttack(0.5);
}
