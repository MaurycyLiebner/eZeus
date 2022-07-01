#include "ehorseman.h"

#include "textures/egametextures.h"

eHorseman::eHorseman(eGameBoard& board) :
    eHorsemanBase(board, &eCharacterTextures::fHorseman) {}
