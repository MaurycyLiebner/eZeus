#include "ehoplite.h"

#include "textures/egametextures.h"

eHoplite::eHoplite(eGameBoard& board) :
    eSoldier(board, &eCharacterTextures::fHoplite,
             eCharacterType::hoplite) {}
