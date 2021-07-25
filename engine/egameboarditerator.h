#ifndef EGAMEBOARDITERATOR_H
#define EGAMEBOARDITERATOR_H

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
protected:
    void updateTile();

    int mRow;
    int mColumn;
    const eGameBoard* mBoard;
    eTile* mTile = nullptr;
};

#endif // EGAMEBOARDITERATOR_H
