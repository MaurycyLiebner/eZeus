#ifndef ESPAWNER_H
#define ESPAWNER_H

#include "engine/egameboard.h"

class eSpawner {
public:
    eSpawner(eTile* const tile,
             const int maxCount,
             const int spawnFreq,
             eGameBoard& board);
    virtual ~eSpawner();

    virtual void spawn(eTile* const tile) = 0;

    void incTime(const int by);
    void decCount();

    void spawnMax();

    int count() const { return mCount; }

    eGameBoard& board() { return mBoard; }
private:
    eTile* const mTile;
    eGameBoard& mBoard;
    const int mMaxCount;
    const int mSpawnFreq;

    int mCount = 0;

    int mTime = 0;
};

#endif // ESPAWNER_H
