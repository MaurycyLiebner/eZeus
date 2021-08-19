#ifndef ESETTLERSPAWNER_H
#define ESETTLERSPAWNER_H

#include "espawner.h"

class eSettlerSpawner : public eSpawner {
public:
    eSettlerSpawner(eTile* const tile,
                    eGameBoard& board);

    void spawn(eTile* const tile);
};

#endif // ESETTLERSPAWNER_H
