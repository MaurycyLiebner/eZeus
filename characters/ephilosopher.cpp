#include "ephilosopher.h"

ePhilosopher::ePhilosopher(eGameBoard& board) :
    eBasicPatroler(board, &eCharacterTextures::fPhilosopher,
                   eCharacterType::philosopher) {
    setProvide(eProvide::philosopher, 10000);
}
