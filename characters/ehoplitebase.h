#ifndef EHOPLITEBASE_H
#define EHOPLITEBASE_H

#include "esoldier.h"

class
        eHopliteBase : public eSoldier {
public:
    using eCharTexs = eFightingCharacterTextures eCharacterTextures::*;
    eHopliteBase(eGameBoard& board, const eCharTexs charTexs);
};

#endif // EHOPLITEBASE_H
