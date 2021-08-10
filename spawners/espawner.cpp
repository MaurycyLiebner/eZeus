#include "espawner.h"

#include "engine/egameboard.h"

eSpawner::eSpawner(eTile* const tile,
                   const int maxCount,
                   const int spawnFreq,
                   eGameBoard& board) :
    mTile(tile), mBoard(board),
    mMaxCount(maxCount), mSpawnFreq(spawnFreq) {
    mTile->setSpawner(this);
    mBoard.registerSpawner(this);
}

eSpawner::~eSpawner() {
    mTile->setSpawner(nullptr);
    mBoard.unregisterSpawner(this);
}

void eSpawner::incTime(const int by) {
    mTime += by;
    if(mTime % mSpawnFreq == 0 && mCount < mMaxCount) {
        spawn(mTile);
        mCount++;
    }
}

void eSpawner::decCount() {
    mCount--;
}

void eSpawner::spawnMax() {
    const int iMax = mMaxCount - mCount;
    for(int i = 0; i < iMax; i++) {
        spawn(mTile);
        mCount++;
    }
}
