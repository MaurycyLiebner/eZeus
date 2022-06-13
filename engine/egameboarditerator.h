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

    int y() const { return mY; }
    int x() const { return mX; }
protected:
    void updateTile();

    int mX;
    int mY;
    const eGameBoard* mBoard;
    eTile* mTile = nullptr;
};

#endif // EGAMEBOARDITERATOR_H
