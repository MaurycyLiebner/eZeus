#include "ephoenicianhorseman.h"

#include "textures/egametextures.h"

ePhoenicianHorseman::ePhoenicianHorseman(eGameBoard& board) :
    eHorsemanBase(board, &eCharacterTextures::fPhoenicianHorseman,
                  eCharacterType::phoenicianHorseman) {
    eGameTextures::loadPhoenicianHorseman();
}
