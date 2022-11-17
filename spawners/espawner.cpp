#include "espawner.h"

#include "engine/egameboard.h"

eSpawner::eSpawner(const eBannerTypeS type,
                   const int id, eTile* const tile,
                   const int maxCount,
                   const int spawnFreq,
                   eGameBoard& board) :
    eBanner(type, id, tile, board),
    mMaxCount(maxCount), mSpawnFreq(spawnFreq) {
    board.registerSpawner(this);
}

eSpawner::~eSpawner() {
    board().unregisterSpawner(this);
}

void eSpawner::read(eReadStream& src) {
    eBanner::read(src);
    src >> mMaxCount;
    src >> mSpawnFreq;
    src >> mCount;
    src >> mTime;
}

void eSpawner::write(eWriteStream& dst) const {
    eBanner::write(dst);
    dst << mMaxCount;
    dst << mSpawnFreq;
    dst << mCount;
    dst << mTime;
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
