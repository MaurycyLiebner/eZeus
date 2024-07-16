#ifndef EANIMALSPAWNER_H
#define EANIMALSPAWNER_H

#include "espawner.h"

#include "pointers/estdselfref.h"

class eWildAnimal;

class eAnimalSpawner : public eSpawner {
public:
    using eSpawner::eSpawner;

    virtual stdsptr<eWildAnimal> create(eGameBoard& board) = 0;

    void spawn(eTile* const tile) override;
};

#endif // EANIMALSPAWNER_H
