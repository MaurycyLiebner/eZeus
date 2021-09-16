#ifndef EELITEHOUSING_H
#define EELITEHOUSING_H

#include "ebuilding.h"

class eEliteHousing : public eBuilding {
public:
    eEliteHousing(eGameBoard& board);
    ~eEliteHousing();

    std::shared_ptr<eTexture>
    getTexture(const eTileSize) const { return nullptr; }

    std::shared_ptr<eTexture>
        getLeftTexture(const eTileSize size) const;
    std::shared_ptr<eTexture>
        getBottomTexture(const eTileSize size) const;
    std::shared_ptr<eTexture>
        getTopTexture(const eTileSize size) const;
    std::shared_ptr<eTexture>
        getRightTexture(const eTileSize size) const;
    std::vector<eOverlay>
        getHorseOverlays(const eTileSize size) const;

    int provide(const eProvide p, const int n);

    void timeChanged(const int by);

    void nextMonth();

    void levelUp();
    void levelDown();

    int vacancies() const;

    int level() const { return mLevel; }
    int people() const { return mPeople; }

    int moveIn(int c);

    int food() const { return mFood; }
    int fleece() const { return mFleece; }
    int oil() const { return mOil; }

    int wine() const { return mWine; }
    int arms() const { return mArms; }

    int horses() const { return mHorses; }

    int philosophers() const { return mPhilosophers; }
    int actors() const { return mActors; }
    int athletes() const { return mAthletes; }
private:
    const eTextureCollection& getTextureCollection(
            const eTileSize size) const;

    void updateLevel();
    void setLevel(const int l);
    int evict();
    void setPeople(const int p);

    bool mPaidTaxes = false;

    int mLevel{0};
    int mPeople{0};

    int mFood = 0;
    int mFleece = 0;
    int mOil = 0;
    int mWine = 0;
    int mArms = 0;
    int mHorses = 0;

    int mPhilosophers = 0;
    int mActors = 0;
    int mAthletes = 0;
};

#endif // EELITEHOUSING_H
