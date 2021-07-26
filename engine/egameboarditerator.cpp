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
    return *mTilePtr;
}

eGameBoardDiagonalIterator& eGameBoardDiagonalIterator::operator++() {
    if(isNull()) return *this;
    mColumn++;
    if(mColumn >= nColumns()) {
        nextRow();
    } else {
        mTilePtr++;
    }
    return* this;
}

bool eGameBoardDiagonalIterator::operator==(
        const eGameBoardDiagonalIterator& it) const {
    return it.mTilePtr == mTilePtr;
}

bool eGameBoardDiagonalIterator::operator!=(
        const eGameBoardDiagonalIterator& it) const {
    return it.mTilePtr != mTilePtr;
}

int eGameBoardDiagonalIterator::nColumns() const {
    const int w = mBoard->width();
    const int h = mBoard->height();
    return std::min({mRow + 1, w + h - mRow - 1, w, h});
}

eTile* eGameBoardDiagonalIterator::tile() const {
    if(isNull()) return nullptr;
    return *mTilePtr;
}

bool eGameBoardDiagonalIterator::isNull() const {
    return !mTilePtr;
}

void eGameBoardDiagonalIterator::nextRow() {
    if(isNull()) return;
    const int w = mBoard->width();
    const int h = mBoard->height();
    const int nRows = w + h - 1;
    mRow++;
    if(mRow >= nRows) return nullify();
    mColumn = 0;
    mRowPtr++;
    mTilePtr = &(*mRowPtr)[0];
}

void eGameBoardDiagonalIterator::nullify() {
    mRow = -1;
    mColumn = -1;
    mRowPtr = nullptr;
    mTilePtr = nullptr;
}

void eGameBoardDiagonalIterator::updateTile() {
    mTilePtr = nullptr;
    const int w = mBoard->width();
    const int h = mBoard->height();
    const int nRows = w + h - 1;

    if(mRow >= 0 && mRow < nRows) {
        if(mColumn >= 0 && mColumn < nColumns()) {
            mRowPtr = &mBoard->mDiagTiles[mRow];
            mTilePtr = &(*mRowPtr)[mColumn];
        }
    }
}
