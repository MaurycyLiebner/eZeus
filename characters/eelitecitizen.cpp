#include "eelitecitizen.h"

#include "textures/egametextures.h"

eEliteCitizen::eEliteCitizen(eGameBoard& board) :
    eFightingPatroler(board, &eCharacterTextures::fEliteCitizen,
                      eCharacterType::eliteCitizen) {
    eGameTextures::loadEliteCitizen();
    setAttack(0.5);
    setHP(200);
}
