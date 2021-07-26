#ifndef EGAMEBOARDITERATOR_H
#define EGAMEBOARDITERATOR_H

#include <vector>

class eTile;
class eGameBoard;

class eGameBoardIterator {
public:
    eGameBoardIterator(const int x, const int y,
                       const eGameBoard* const board);

    eTile* operator*();
    eGameBoardIterator& operator++();

    bool operator==(const eGameBoardIterator& it) const;
    bool operator!=(const eGameBoardIterator& it) const;
protected:
    void updateTile();

    int mX;
    int mY;
    const eGameBoard* mBoard;
    eTile* mTile = nullptr;
};

class eGameBoardDiagonalIterator {
public:
    eGameBoardDiagonalIterator(const int row, const int column,
                               const eGameBoard* const board);

    eTile* operator*();
    eGameBoardDiagonalIterator& operator++();

    bool operator==(const eGameBoardDiagonalIterator& it) const;
    bool operator!=(const eGameBoardDiagonalIterator& it) const;

    int row() const { return mRow; }
    int column() const { return mColumn; }
    int nColumns() const;

    eTile* tile() const;

    bool isNull() const;

    void nextRow();
protected:
    void nullify();
    void updateTile();

    int mRow;
    int mColumn;
    const eGameBoard* mBoard;
    const std::vector<eTile*>* mRowPtr = nullptr;
    using eTilePtr = eTile*;
    const eTilePtr* mTilePtr = nullptr;
};

#endif // EGAMEBOARDITERATOR_H
