#ifndef ESOLDIERBANNER_H
#define ESOLDIERBANNER_H

#include <vector>
#include <map>

#include "pointers/eobject.h"
#include "fileIO/estreams.h"

class eSoldier;
class eGameBoard;
class eTile;

enum class eBannerType {
    hoplite,
    horseman,
    rockThrower,
    amazon,
    aresWarrior
};

class eSoldierBanner : public eObject {
public:
    eSoldierBanner(const eBannerType type,
                   eGameBoard& board);

    eBannerType type() const { return mType; }

    int id() const { return mId; }

    void moveTo(const int x, const int y);
    void moveToDefault();
    void goHome();
    void goAbroad();
    void backFromHome();
    void callSoldiers();

    bool isHome() const { return mHome; }
    bool isAbroad() const { return mAbroad; }

    void addSoldier(eSoldier* const s);
    void removeSoldier(eSoldier* const s);

    eTile* tile() const { return mTile; }
    eTile* place(eSoldier* const s) const;

    void killAll();
    void killAllWithCorpse();

    void setSelected(const bool s) { mSelected = s; }
    bool selected() const { return mSelected; }

    void setPlayerId(const int pid) { mPlayerId = pid; }
    int playerId() const { return mPlayerId; }

    int count() const { return mCount; }
    void incCount();
    void decCount();

    bool stationary() const;

    const std::string& name() const { return mName; }
    void setName(const std::string& n) { mName = n; }

    void read(eReadStream& src);
    void write(eWriteStream& dst) const;

    void setRegistered(const bool r) { mRegistered = r; }
    bool registered() const { return mRegistered; }

    static void sPlace(std::vector<eSoldierBanner*> bs,
                       const int ctx, const int cty,
                       eGameBoard& board, const int dist);
private:
    void updatePlaces();
    void updateCount();
    std::vector<eSoldier*> notDead() const;

    const eBannerType mType;
    const int mId;
    std::string mName;

    bool mRegistered = false;

    bool mHome = true;
    bool mAbroad = false;

    bool mSelected = false;

    eGameBoard& mBoard;

    int mX = -1;
    int mY = -1;

    eTile* mTile = nullptr;

    int mCount = 0;

    int mPlayerId = 1;

    std::map<eSoldier*, eTile*> mPlaces;
    std::vector<eSoldier*> mSoldiers;
};

#endif // ESOLDIERBANNER_H
