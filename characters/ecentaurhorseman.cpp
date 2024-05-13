#include "ecentaurhorseman.h"

#include "textures/egametextures.h"

eCentaurHorseman::eCentaurHorseman(eGameBoard& board) :
    eHorsemanBase(board, &eCharacterTextures::fCentaurHorseman,
                  eCharacterType::centaurHorseman) {
    eGameTextures::loadCentaurHorseman();
}
