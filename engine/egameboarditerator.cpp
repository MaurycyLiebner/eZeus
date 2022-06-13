#include "egameboarditerator.h"

#include "egameboard.h"

#include <algorithm>

eGameBoardIterator::eGameBoardIterator(const int x, const int y, const eGameBoard* const board) :
    mX(x), mY(y), mBoard(board) {
    updateTile();
}

eTile* eGameBoardIterator::operator*() {
    return mTile;
}

eGameBoardIterator& eGameBoardIterator::operator++() {
    if(!mTile) return *this;
    if(mX + 1 >= mBoard->width()) {
        mX = 0;
        mY++;
    } else {
        mX++;
    }
    updateTile();
    return* this;
}

bool eGameBoardIterator::operator==(const eGameBoardIterator& it) const {
    return it.mTile == mTile;
}

bool eGameBoardIterator::operator!=(const eGameBoardIterator& it) const {
    return it.mTile != mTile;
}

void eGameBoardIterator::updateTile() {
    if(mX < 0 || mY < 0 ||
       mX >= mBoard->width() ||
       mY >= mBoard->height()) {
        mTile = nullptr;
    } else {
        mTile = mBoard->tile(mX, mY);
    }
}
