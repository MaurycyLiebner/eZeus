#ifndef ESMALLHOUSE_H
#define ESMALLHOUSE_H

#include "ehousebase.h"

class eSmallHouse : public eHouseBase {
public:
    eSmallHouse(eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;

    int provide(const eProvide p, const int n);

    void timeChanged(const int by);

    void nextMonth();

    int water() const { return mWater; }

    bool lowFood() const;
    bool lowFleece() const { return mFleece < 2; }
    bool lowOil() const { return mOil < 2; }

    eHouseMissing missing() const;
private:
    void updateLevel();

    int mWater = 0;
};

#endif // ESMALLHOUSE_H
