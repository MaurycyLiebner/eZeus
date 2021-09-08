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

class eSpawner;
class eCharacter;
class eBuilding;
class eThreadPool;

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

    bool hasStadium() const { return mStadiumCount > 0; }

    void registerPalace();
    void unregisterPalace();

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
private:
    void updateDiagonalArray();
    void updateNeighbours();

    int mDrachmas = 2500;
    eDifficulty mDifficulty = eDifficulty::beginner;

    int mTime = 0;
    eDate mDate = eDate(1, eMonth::january, -1500);

    eThreadPool* mThreadPool = nullptr;

    int mWidth = 0;
    int mHeight = 0;
    std::vector<std::vector<eTile*>> mTiles;
    std::vector<std::vector<eTile*>> mDiagTiles;

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
