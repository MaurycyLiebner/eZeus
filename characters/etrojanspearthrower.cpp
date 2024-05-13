#include "etrojanspearthrower.h"

#include "textures/egametextures.h"

eTrojanSpearthrower::eTrojanSpearthrower(eGameBoard& board) :
    eSpearthrowerBase(board, &eCharacterTextures::fTrojanSpearthrower,
                      eCharacterType::trojanSpearthrower) {
    eGameTextures::loadTrojanSpearthrower();
}
