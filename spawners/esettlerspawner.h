#ifndef ESETTLERSPAWNER_H
#define ESETTLERSPAWNER_H

#include "espawner.h"

#include "characters/actions/echaracteractionfunction.h"

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

    void call() override;

    void read(eReadStream&) override {}
    void write(eWriteStream&) const override {}
};

#endif // ESETTLERSPAWNER_H
