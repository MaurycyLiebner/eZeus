#ifndef EWILDANIMAL_H
#define EWILDANIMAL_H

#include "eanimal.h"

#include "textures/echaractertextures.h"

class eWildAnimal : public eAnimal {
public:
    eWildAnimal(eSpawner* const s,
                eGameBoard& board,
                const eCharTexs charTexs,
                const eCharacterType type);
    ~eWildAnimal();
private:
    eSpawner* const mSpawner;
};

#endif // EWILDANIMAL_H
