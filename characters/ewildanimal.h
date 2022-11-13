#ifndef EWILDANIMAL_H
#define EWILDANIMAL_H

#include "eanimal.h"

#include "textures/echaractertextures.h"

class eSpawner;

class eWildAnimal : public eAnimal {
public:
    eWildAnimal(eGameBoard& board,
                const eCharTexs charTexs,
                const eCharacterType type);
    ~eWildAnimal();

    void setSpawner(eSpawner* const s)
    { mSpawner = s; }
private:
    eSpawner* mSpawner = nullptr;
};

#endif // EWILDANIMAL_H
