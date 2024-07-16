#ifndef EDEERSPAWNER_H
#define EDEERSPAWNER_H

#include "eanimalspawner.h"

class eDeerSpawner : public eAnimalSpawner {
public:
    eDeerSpawner(const int id, eTile* const tile,
                 eGameBoard& board);

    stdsptr<eWildAnimal> create(eGameBoard& board) override;
};

#endif // EDEERSPAWNER_H
