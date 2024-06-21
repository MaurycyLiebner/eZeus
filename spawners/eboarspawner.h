#ifndef EBOARSPAWNER_H
#define EBOARSPAWNER_H

#include "espawner.h"

class eBoarSpawner : public eSpawner {
public:
    eBoarSpawner(const int id,
                 eTile* const tile,
                 eGameBoard& board);

    void spawn(eTile* const tile);
};

#endif // EBOARSPAWNER_H
