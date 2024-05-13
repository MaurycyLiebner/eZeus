#ifndef ESPEARTHROWERBASE_H
#define ESPEARTHROWERBASE_H

#include "esoldier.h"

class eSpearthrowerBase : public eSoldier {
public:
    eSpearthrowerBase(eGameBoard& board,
                      const eCharTexs charTexs,
                      const eCharacterType type);
};

#endif // ESPEARTHROWERBASE_H
