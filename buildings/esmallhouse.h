#ifndef ESMALLHOUSE_H
#define ESMALLHOUSE_H

#include "ehousebase.h"

class eSick;
class eDisgruntled;

class eSmallHouse : public eHouseBase {
public:
    eSmallHouse(eGameBoard& board);
    ~eSmallHouse();

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const override;

    int provide(const eProvide p, const int n) override;

    void timeChanged(const int by) override;

    void nextMonth() override;

    int water() const { return mWater; }
    int hygiene() const { return mHygiene; }

    void setPlague(const bool p);
    bool plague() const { return mPlague; }

    void setDisgruntled(const bool d);
    bool disgruntled() const { return mDisgruntled; }

    bool lowFood() const;
    bool lowFleece() const { return mFleece < 2; }
    bool lowOil() const { return mOil < 2; }

    int foodSatisfaction() const { return mFoodSatisfaction; }
    int waterSatisfaction() const { return mWaterSatisfaction; }
    int workSatisfaction() const { return mWorkSatisfaction; }
    int satisfaction() const { return mSatisfaction; }

    eHouseMissing missing() const override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    void updateLevel();
    void updateSatisfaction();

    void spawnCharacter(const stdsptr<eCharacter>& c);
    void spawnSick();
    void spawnDisgruntled();

    int mUpdateSatisfaction = 0;
    int mSatisfaction = 100;
    int mFoodSatisfaction = 100;
    int mWaterSatisfaction = 100;
    int mWorkSatisfaction = 100;

    int mUpdateWater = 0;
    int mUpdateHygiene = 8;
    int mUpdateLevel = 0;

    int mWater = 0;
    int mHygiene = 100; // 0-100
    bool mPlague = false;
    bool mDisgruntled = false;

    int mSpawnSick = 0;
    stdptr<eSick> mSick;
    int mSpawnDisg = 0;
    stdptr<eDisgruntled> mDisg;
};

#endif // ESMALLHOUSE_H
