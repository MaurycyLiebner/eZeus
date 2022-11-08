#ifndef ESPAWNER_H
#define ESPAWNER_H

#include "ebanner.h"

class eSpawner : public eBanner {
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
private:
    const int mMaxCount;
    const int mSpawnFreq;

    int mCount = 0;

    int mTime = 0;
};

#endif // ESPAWNER_H
