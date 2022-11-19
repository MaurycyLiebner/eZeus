#include "ehunter.h"

eHunter::eHunter(eGameBoard& board) :
    eResourceCollector(board, &eCharacterTextures::fHunter,
                       eCharacterType::hunter) {
    setAttack(0.3);
}

void eHunter::setDeerHunter(const bool h) {
    mDeerHunter = h;
    if(h) {
        setCharTexs(&eCharacterTextures::fDeerHunter);
    } else {
        setCharTexs(&eCharacterTextures::fHunter);
    }
}

void eHunter::read(eReadStream& src) {
    eResourceCollector::read(src);
    bool deerHunter;
    src >> deerHunter;
    setDeerHunter(deerHunter);
}

void eHunter::write(eWriteStream& dst) const {
    eResourceCollector::write(dst);
    dst << mDeerHunter;
}

