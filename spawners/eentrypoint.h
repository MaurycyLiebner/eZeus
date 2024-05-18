#ifndef eentrypoint_H
#define eentrypoint_H

#include "espawner.h"

#include "characters/actions/echaracteractionfunction.h"

class eEntryPoint : public eSpawner {
public:
    eEntryPoint(const int id,
                eTile* const tile,
                eGameBoard& board);

    void incTime(const int by) override;
    void spawn(eTile* const tile) override;
};

class eSS_spawnFinish : public eCharActFunc {
public:
    eSS_spawnFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::SS_spawnFinish) {}

    void call() override;

    void read(eReadStream&) override {}
    void write(eWriteStream&) const override {}
};

#endif // eentrypoint_H
