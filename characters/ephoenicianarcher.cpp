#include "ephoenicianarcher.h"

#include "textures/egametextures.h"

ePhoenicianArcher::ePhoenicianArcher(eGameBoard& board) :
    eArcherBase(board, &eCharacterTextures::fPhoenicianArcher,
                eCharacterType::phoenicianArcher) {
    eGameTextures::loadPhoenicianArcher();
}
