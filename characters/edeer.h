#ifndef EDEER_H
#define EDEER_H

#include "ewildanimal.h"

class eDeer : public eWildAnimal {
public:
    eDeer(eSpawner* const s, eGameBoard& board);
};

#endif // EDEER_H
