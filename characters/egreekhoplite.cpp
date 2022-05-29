#include "egreekhoplite.h"
#include "textures/egametextures.h"

eGreekHoplite::eGreekHoplite(eGameBoard& board) :
    eSoldier(board, &eCharacterTextures::fGreekHoplite,
             eCharacterType::hoplite) {}
