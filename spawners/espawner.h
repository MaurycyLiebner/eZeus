#ifndef ESPAWNER_H
#define ESPAWNER_H

#include "ebanner.h"

class eSpawner : public eBanner {
public:
    eSpawner(const eBannerTypeS type,
             const int id,
             eTile* const tile,
             const int maxCount,
             const int spawnFreq,
             eGameBoard& board);
    virtual ~eSpawner();

    virtual void spawn(eTile* const tile) = 0;

    void read(eReadStream& src);
    void write(eWriteStream& dst) const;

    void incTime(const int by);
    void decCount();

    void spawnMax();

    int count() const { return mCount; }
private:
    int mMaxCount;
    int mSpawnFreq;

    int mCount = 0;

    int mTime = 0;
};

#endif // ESPAWNER_H
