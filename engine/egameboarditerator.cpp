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

eGameBoardDiagonalIterator::eGameBoardDiagonalIterator(
        const int row, const int column,
        const eGameBoard* const board) :
    mRow(row), mColumn(column), mBoard(board) {
    updateTile();
}

eTile* eGameBoardDiagonalIterator::operator*() {
    return mTile;
}

eGameBoardDiagonalIterator& eGameBoardDiagonalIterator::operator++() {
    if(!mTile) return *this;
    const int w = mBoard->width();
    const int h = mBoard->height();
    const int nCols = std::min({mRow + 1, w + h - mRow - 1, w, h});
    mColumn++;
    if(mColumn >= nCols) {
        mColumn = 0;
        mRow++;
    }
    updateTile();
    return* this;
}

bool eGameBoardDiagonalIterator::operator==(
        const eGameBoardDiagonalIterator& it) const {
    return it.mTile == mTile;
}

bool eGameBoardDiagonalIterator::operator!=(
        const eGameBoardDiagonalIterator& it) const {
    return it.mTile != mTile;
}

void eGameBoardDiagonalIterator::updateTile() {
    mTile = nullptr;
    const int w = mBoard->width();
    const int h = mBoard->height();
    const int nRows = w + h - 1;

    if(mRow >= 0 && mRow < nRows) {
        const int nCols = std::min({mRow + 1, w + h - mRow - 1, w, h});
        if(mColumn >= 0 && mColumn < nCols) {
            mTile = mBoard->mDiagTiles[mRow][mColumn];
        }
    }
}
