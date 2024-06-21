#include "eporter.h"

#include "textures/egametextures.h"

ePorter::ePorter(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fPorter,
                   eCharacterType::porter) {
    eGameTextures::loadPorter();
}
