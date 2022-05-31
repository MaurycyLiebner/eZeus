#ifndef EROCKTHROWERBASE_H
#define EROCKTHROWERBASE_H

#include "erangesoldier.h"

class eRockThrowerBase : public eRangeSoldier {
public:
    using eCharTexs = eRockThrowerTextures eCharacterTextures::*;
    eRockThrowerBase(eGameBoard& board,
                     const eCharTexs charTexs);
};

#endif // EROCKTHROWERBASE_H
