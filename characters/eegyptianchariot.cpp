#include "eegyptianchariot.h"

#include "textures/echaractertextures.h"
#include "textures/egametextures.h"

eEgyptianChariot::eEgyptianChariot(eGameBoard& board) :
    eChariotBase(board, &eCharacterTextures::fEgyptianChariot,
                 eCharacterType::egyptianChariot) {
    eGameTextures::loadEgyptianChariot();
}
