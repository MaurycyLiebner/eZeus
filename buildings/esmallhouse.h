#ifndef ESMALLHOUSE_H
#define ESMALLHOUSE_H

#include "ehousebase.h"

class eSmallHouse : public eHouseBase {
public:
    eSmallHouse(eGameBoard& board);

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const override;

    int provide(const eProvide p, const int n) override;

    void timeChanged(const int by) override;

    void nextMonth() override;

    int water() const { return mWater; }

    bool lowFood() const;
    bool lowFleece() const { return mFleece < 2; }
    bool lowOil() const { return mOil < 2; }

    eHouseMissing missing() const override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    void updateLevel();

    int mWater = 0;
};

#endif // ESMALLHOUSE_H
