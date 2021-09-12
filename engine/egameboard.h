#ifndef EGAMEBOARD_H
#define EGAMEBOARD_H

#include <vector>

#include "etile.h"
#include "egameboarditerator.h"

#include "boardData/epopulationdata.h"
#include "boardData/eemploymentdata.h"
#include "boardData/eappealmap.h"

#include "edifficulty.h"
#include "edate.h"

#include "eresourcetype.h"

#include "pointers/eobject.h"

class eSpawner;
class eCharacter;
class eBuilding;
class eStorageBuilding;

class eThreadPool;

enum class eEvent {
    fire,
    collapse
};

class eGameBoard {
    friend class eGameBoardIterator;
    friend class eGameBoardDiagonalIterator;
public:
    using eIter = eGameBoardIterator;
    using eDiagIter = eGameBoardDiagonalIterator;

    eGameBoard(eThreadPool* const tpool);

    ~eGameBoard();

    void initialize(const int w, const int h);
    void clear();

    eTile* tile(const int x, const int y) const;

    int width() const { return mWidth; }
    int height() const { return mHeight; }

    eIter begin() const {
        return eIter(0, 0, this);
    }

    eIter end() const {
        return eIter(-1, -1, this);
    }

    eDiagIter dBegin() const {
        return eDiagIter(0, 0, this);
    }

    eDiagIter dEnd() const {
        return eDiagIter(-1, -1, this);
    }

    void registerCharacter(eCharacter* const c);
    bool unregisterCharacter(eCharacter* const c);

    void registerBuilding(eBuilding* const b);
    bool unregisterBuilding(eBuilding* const b);

    void registerSpawner(eSpawner* const s);
    bool unregisterSpawner(eSpawner* const s);

    void registerStadium();
    void unregisterStadium();

    void registerStorBuilding(eStorageBuilding* const b);
    bool unregisterStorBuilding(eStorageBuilding* const b);

    bool hasStadium() const { return mStadiumCount > 0; }

    void registerPalace();
    void unregisterPalace();

    void updateResources();
    using eResources = std::vector<std::pair<eResourceType, int>>;
    const eResources& resources() const { return mResources; }

    bool hasPalace() const { return mPalaceCount > 0; }

    void incTime(const int by);

    eThreadPool* threadPool() const { return mThreadPool; }

    ePopulationData& populationData() { return mPopData; }
    eEmploymentData& employmentData() { return mEmplData; }
    eAppealMap& appealMap() { return mAppealMap; }

    void incDrachmas(const int d);
    int drachmas() const { return mDrachmas; }
    eDifficulty difficulty() const { return mDifficulty; }
    const eDate& date() const { return mDate; }

    double appeal(const int tx, const int ty) const;

    double taxRate() const { return mTaxRate; }

    void addRubbish(const stdsptr<eObject>& o);
    void emptyRubbish();

    using eEventHandler = std::function<void(eEvent, eTile*)>;
    void setEventHandler(const eEventHandler& eh);
    void event(const eEvent e, eTile* const tile);
private:
    void updateDiagonalArray();
    void updateNeighbours();

    eEventHandler mEventHandler;

    int mDrachmas = 2500;
    eDifficulty mDifficulty = eDifficulty::beginner;

    double mTaxRate = 0.09;

    int mTime = 0;
    eDate mDate = eDate(1, eMonth::january, -1500);

    eThreadPool* mThreadPool = nullptr;

    int mWidth = 0;
    int mHeight = 0;
    std::vector<std::vector<eTile*>> mTiles;
    std::vector<std::vector<eTile*>> mDiagTiles;

    eResources mResources = {{eResourceType::urchin, 0},
                             {eResourceType::fish, 0},
                             {eResourceType::meat, 0},
                             {eResourceType::cheese, 0},
                             {eResourceType::carrots, 0},
                             {eResourceType::onions, 0},
                             {eResourceType::wheat, 0},
                             {eResourceType::oranges, 0},

                             {eResourceType::grapes, 0},
                             {eResourceType::olives, 0},
                             {eResourceType::wine, 0},
                             {eResourceType::oliveOil, 0},
                             {eResourceType::fleece, 0},

                             {eResourceType::wood, 0},
                             {eResourceType::bronze, 0},
                             {eResourceType::marble, 0},

                             {eResourceType::armor, 0},
                             {eResourceType::sculpture, 0}};

    std::vector<stdsptr<eObject>> mRubbish;

    std::vector<eStorageBuilding*> mStorBuildings;
    std::vector<eCharacter*> mCharacters;
    std::vector<eBuilding*> mBuildings;
    std::vector<eSpawner*> mSpawners;

    int mStadiumCount = 0;
    int mPalaceCount = 0;

    ePopulationData mPopData;

    eEmploymentData mEmplData;

    eAppealMap mAppealMap;
};

#endif // EGAMEBOARD_H
