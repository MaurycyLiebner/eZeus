#ifndef EHORSEMANBASE_H
#define EHORSEMANBASE_H

#include "esoldier.h"

class eHorsemanBase : public eSoldier {
public:
    using eCharTexs = eFightingCharacterTextures eCharacterTextures::*;
    eHorsemanBase(eGameBoard& board, const eCharTexs charTexs);
};

#endif // EHORSEMANBASE_H
