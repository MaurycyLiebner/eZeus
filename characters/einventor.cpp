#include "einventor.h"

#include "textures/egametextures.h"

eInventor::eInventor(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fInventor,
                   eCharacterType::inventor) {
    eGameTextures::loadInventor();
    setProvide(eProvide::philosopherInventor, 10000);
}
