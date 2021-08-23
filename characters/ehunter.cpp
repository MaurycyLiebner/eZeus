#include "ehunter.h"

eHunter::eHunter(eGameBoard& board) :
    eResourceCollector(board, &eCharacterTextures::fHunter,
                       eCharacterType::hunter) {
    setAttack(3);
}

void eHunter::setDeerHunter(const bool h) {
    mDeerHunter = h;
    if(h) {
        setCharTexs(&eCharacterTextures::fDeerHunter);
    } else {
        setCharTexs(&eCharacterTextures::fHunter);
    }
}

