#ifndef EHORSEMANBASE_H
#define EHORSEMANBASE_H

#include "esoldier.h"

class eHorsemanBase : public eSoldier {
public:
    using eCharTexs = eFightingCharacterTextures eCharacterTextures::*;
    eHorsemanBase(eGameBoard& board, const eCharTexs charTexs,
                  const eCharacterType type);
};

#endif // EHORSEMANBASE_H
