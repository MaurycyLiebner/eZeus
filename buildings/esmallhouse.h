#ifndef ESMALLHOUSE_H
#define ESMALLHOUSE_H

#include "ebuilding.h"

class eSmallHouse : public eBuilding {
public:
    eSmallHouse(eGameBoard& board);
    ~eSmallHouse();

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const;

    int provide(const eProvide p, const int n);

    void timeChanged(const int by);

    void nextMonth();

    void levelUp();
    void levelDown();

    int vacancies() const;

    int level() const { return mLevel; }
    int people() const { return mPeople; }

    int moveIn(int c);

    int water() const { return mWater; }
    int food() const { return mFood; }
    int fleece() const { return mFleece; }
    int oil() const { return mOil; }

    int philosophers() const { return mPhilosophers; }
    int actors() const { return mActors; }
    int athletes() const { return mAthletes; }

    bool lowFood() const;
    bool lowFleece() const { return mFleece < 2; }
    bool lowOil() const { return mOil < 2; }
private:
    void updateLevel();
    void setLevel(const int l);
    int evict();
    void setPeople(const int p);

    bool mPaidTaxes = false;

    int mLevel{0};
    int mPeople{0};

    int mWater = 0;
    int mFood = 0;
    int mFleece = 0;
    int mOil = 0;

    int mPhilosophers = 0;
    int mActors = 0;
    int mAthletes = 0;
};

#endif // ESMALLHOUSE_H
