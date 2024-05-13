#ifndef EARCHERBASE_H
#define EARCHERBASE_H

#include "esoldier.h"

class eArcherBase : public eSoldier {
public:
    eArcherBase(eGameBoard& board,
                const eCharTexs charTexs,
                const eCharacterType type);
};

#endif // EARCHERBASE_H
