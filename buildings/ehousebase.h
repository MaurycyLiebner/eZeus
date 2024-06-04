#ifndef EHOUSEBASE_H
#define EHOUSEBASE_H

#include "ebuilding.h"

enum class eHouseMissing {
    water,
    food,
    fleece,
    oil,
    venues,
    appeal,
    wine,
    arms,
    horse,
    nothing
};

class eHouseBase : public eBuilding {
public:
    eHouseBase(eGameBoard& board,
               const eBuildingType type,
               const int sw, const int sh,
               const std::vector<int>& maxPeople);
    ~eHouseBase();

    virtual eHouseMissing missing() const = 0;

    void timeChanged(const int by) override;

    int paidTaxes() const { return mPaidTaxes; }
    int paidTaxesLastMonth() const { return mPaidTaxesLastMonth; }

    int food() const { return mFood; }
    int fleece() const { return mFleece; }
    int oil() const { return mOil; }

    int philosophersInventors() const { return mPhilosophers; }
    int actorsAstronomers() const { return mActors; }
    int athletesScholars() const { return mAthletes; }

    void levelUp();
    void levelDown();

    int level() const { return mLevel; }
    int people() const { return mPeople; }

    int kill(int k);
    int moveIn(int c);

    int vacancies() const;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
protected:
    void setLevel(const int l);
    int evict();
    void setPeople(const int p);

    int mPaidTaxes = 0;
    int mPaidTaxesLastMonth = 0;

    int mLevel{0};
    int mPeople{0};

    int mFood = 0;
    int mFleece = 0;
    int mOil = 0;

    int mUpdateCulture = 0;

    int mPhilosophers = 0;
    int mActors = 0;
    int mAthletes = 0;
private:
    const std::vector<int> mMaxPeople;
};

#endif // EHOUSEBASE_H
