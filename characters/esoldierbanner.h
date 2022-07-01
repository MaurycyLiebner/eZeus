#ifndef ESOLDIERBANNER_H
#define ESOLDIERBANNER_H

#include <vector>
#include <map>

#include "pointers/eobject.h"

class eSoldier;
class eGameBoard;
class eTile;

enum class eBannerType {
    hoplite,
    horseman,
    rockThrower
};

class eSoldierBanner : public eObject {
public:
    eSoldierBanner(const eBannerType type,
                   eGameBoard& board);

    eBannerType type() const { return mType; }

    int id() const { return mId; }

    void moveTo(const int x, const int y);
    void goHome();
    void backFromHome();
    void callSoldiers();

    void addSoldier(eSoldier* const s);
    void removeSoldier(eSoldier* const s);
    eSoldier* takeSoldier();

    eTile* place(eSoldier* const s);

    void setSelected(const bool s) { mSelected = s; }
    bool selected() const { return mSelected; }

    int count() const { return mCount; }
    void incCount();
    void decCount();
private:
    void updatePlaces();
    void updateCount();
    std::vector<eSoldier*> notDead() const;

    const eBannerType mType;
    const int mId;

    bool mHome = true;

    bool mSelected = false;

    eGameBoard& mBoard;

    int mX = -1;
    int mY = -1;

    eTile* mTile = nullptr;

    int mCount = 0;

    std::map<eSoldier*, eTile*> mPlaces;
    std::vector<eSoldier*> mSoldiers;
};

#endif // ESOLDIERBANNER_H
