#include "egreekhorseman.h"

#include "textures/egametextures.h"

eGreekHorseman::eGreekHorseman(eGameBoard& board) :
    eHorsemanBase(board, &eCharacterTextures::fGreekHorseman,
                  eCharacterType::greekHorseman) {}
