#include "eoceanidspearthrower.h"

#include "textures/egametextures.h"

eOceanidSpearthrower::eOceanidSpearthrower(eGameBoard& board) :
    eSpearthrowerBase(board, &eCharacterTextures::fOceanidSpearthrower,
                      eCharacterType::oceanidSpearthrower) {
    eGameTextures::loadOceanidSpearthrower();
}
