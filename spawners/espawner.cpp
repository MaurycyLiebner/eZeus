#include "espawner.h"

#include "engine/egameboard.h"

eSpawner::eSpawner(eTile* const tile,
                   const int maxCount,
                   const int spawnFreq,
                   eGameBoard& board) :
    eBanner(tile, board),
    mMaxCount(maxCount), mSpawnFreq(spawnFreq) {
    board.registerSpawner(this);
}

eSpawner::~eSpawner() {
    board().unregisterSpawner(this);
}

void eSpawner::incTime(const int by) {
    mTime += by;
    if(mTime >= mSpawnFreq && mCount < mMaxCount) {
        spawn(tile());
        mCount++;
        mTime = 0;
    }
}

void eSpawner::decCount() {
    mCount--;
}

void eSpawner::spawnMax() {
    const int iMax = mMaxCount - mCount;
    for(int i = 0; i < iMax; i++) {
        spawn(tile());
        mCount++;
    }
}
