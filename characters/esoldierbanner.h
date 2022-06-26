#ifndef ESOLDIERBANNER_H
#define ESOLDIERBANNER_H

#include <vector>
#include <map>

class eSoldier;
class eGameBoard;
class eTile;

enum class eBannerType {
    hoplite,
    horseman,
    rockThrower
};

class eSoldierBanner {
public:
    eSoldierBanner(const eBannerType type,
                   const int id, eGameBoard& board);

    eBannerType type() const { return mType; }

    int id() const { return mId; }

    void moveTo(const int x, const int y);

    void callSoldiers();

    void addSoldier(eSoldier* const s);
    void removeSoldier(eSoldier* const s);

    eTile* place(eSoldier* const s);

    void setSelected(const bool s) { mSelected = s; }
    bool selected() const { return mSelected; }
private:
    void updatePlaces();

    const eBannerType mType;
    const int mId;

    bool mSelected = false;

    eGameBoard& mBoard;

    int mX = -1;
    int mY = -1;

    eTile* mTile = nullptr;

    std::map<eSoldier*, eTile*> mPlaces;

    std::vector<eSoldier*> mSoldiers;
};

#endif // ESOLDIERBANNER_H
