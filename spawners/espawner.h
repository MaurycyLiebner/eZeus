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

    virtual void incTime(const int by);

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    void decCount();

    void spawnMax();

    int count() const { return mCount; }

    void setSpawnPeriod(const int p);
private:
    const int mMaxCount;
    int mSpawnPeriod = 100;

    int mCount = 0;
    int mTime = 0;
};

#endif // ESPAWNER_H
