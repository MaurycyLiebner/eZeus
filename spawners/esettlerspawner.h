#ifndef ESETTLERSPAWNER_H
#define ESETTLERSPAWNER_H

#include "espawner.h"

class eSettlerSpawner : public eSpawner {
public:
    eSettlerSpawner(const int id,
                    eTile* const tile,
                    eGameBoard& board);

    void spawn(eTile* const tile);
};

class eSS_spawnFinish : public eCharActFunc {
public:
    eSS_spawnFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::SS_spawnFinish) {}

    void call() override {
        auto& popData = board().populationData();
        popData.incSettlers(-8);
    }

    void read(eReadStream&) override {}

    void write(eWriteStream&) const override {}
};

#endif // ESETTLERSPAWNER_H
