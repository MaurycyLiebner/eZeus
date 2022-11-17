#ifndef EDEERSPAWNER_H
#define EDEERSPAWNER_H

#include "espawner.h"

class eDeerSpawner : public eSpawner {
public:
    eDeerSpawner(const int id, eTile* const tile,
                 eGameBoard& board);

    void spawn(eTile* const tile);
};

#endif // EDEERSPAWNER_H
