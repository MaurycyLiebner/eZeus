#ifndef ESMALLHOUSE_H
#define ESMALLHOUSE_H

#include "ebuilding.h"
#include "textures/ebuildingtextures.h"

class eSmallHouse : public eBuilding {
public:
    eSmallHouse(eGameBoard& board);
    ~eSmallHouse();

    eTexture getTexture(const eTileSize size) const;

    int provide(const eProvide p, const int n);

    void levelUp();
    void levelDown();

    int vacancies() const;

    int level() const { return mLevel; }
    int people() const { return mPeople; }

    int moveIn(int c);
private:
    void updateLevel();
    void setLevel(const int l);
    int evict();
    void setPeople(const int p);

    int mLevel{0};
    int mPeople{0};
    const std::vector<eBuildingTextures>& mTextures;

    int mWater = 0;
    int mFood = 0;
};

#endif // ESMALLHOUSE_H
