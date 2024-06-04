#include "ephilosopher.h"

#include "textures/egametextures.h"

ePhilosopher::ePhilosopher(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fPhilosopher,
                   eCharacterType::philosopher) {
    eGameTextures::loadPhilosopher();
    setProvide(eProvide::philosopherInventor, 10000);
}
