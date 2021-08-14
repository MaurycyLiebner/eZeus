#ifndef EGAMEBOARD_H
#define EGAMEBOARD_H

#include <vector>

#include "etile.h"
#include "egameboarditerator.h"

class eSpawner;
class eCharacter;
class eBuilding;

class eGameBoard {
    friend class eGameBoardIterator;
    friend class eGameBoardDiagonalIterator;
public:
    using eIter = eGameBoardIterator;
    using eDiagIter = eGameBoardDiagonalIterator;

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

    void incTime(const int by);
private:
    void updateDiagonalArray();
    void updateNeighbours();

    int mWidth = 0;
    int mHeight = 0;
    std::vector<std::vector<eTile*>> mTiles;
    std::vector<std::vector<eTile*>> mDiagTiles;

    std::vector<eCharacter*> mCharacters;
    std::vector<eBuilding*> mBuildings;
    std::vector<eSpawner*> mSpawners;
};

#endif // EGAMEBOARD_H
