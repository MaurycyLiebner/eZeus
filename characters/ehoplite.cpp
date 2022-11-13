#include "ehoplite.h"

#include "textures/egametextures.h"

eHoplite::eHoplite(eGameBoard& board) :
    eHopliteBase(board, &eCharacterTextures::fHoplite,
                 eCharacterType::hoplite) {}
