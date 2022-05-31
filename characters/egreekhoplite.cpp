#include "egreekhoplite.h"
#include "textures/egametextures.h"

eGreekHoplite::eGreekHoplite(eGameBoard& board) :
    eHopliteBase(board, &eCharacterTextures::fGreekHoplite) {}
