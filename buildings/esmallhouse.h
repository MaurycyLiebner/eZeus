#ifndef ESMALLHOUSE_H
#define ESMALLHOUSE_H

#include "ebuilding.h"
#include "textures/ebuildingtextures.h"

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
private:
    void updateLevel();
    void setLevel(const int l);
    int evict();
    void setPeople(const int p);

    bool mPaidTaxes = false;

    int mLevel{0};
    int mPeople{0};
    const std::vector<eBuildingTextures>& mTextures;

    int mWater = 0;
    int mFood = 0;
    int mFleece = 0;
    int mOil = 0;

    int mPodium = 0;
    int mTheatre = 0;
    int mGymnasium = 0;
};

#endif // ESMALLHOUSE_H
