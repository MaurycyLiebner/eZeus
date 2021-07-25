#include "egameboard.h"

eGameBoard::eGameBoard() {

}

eGameBoard::eGameBoard(const eGameBoard& board) {
    const int w = board.mWidth;
    const int h = board.mHeight;
    mTiles.reserve(w);
    for(int x = 0; x < w; x++) {
        std::vector<eTile*> yArr;
        yArr.reserve(h);
        for(int y = 0; y < h; y++) {
            const auto tile = new eTile(*board.tile(x, y));
            yArr.push_back(tile);
        }
        mTiles.push_back(yArr);
    }
    mWidth = w;
    mHeight = h;

    updateDiagonalArray();
}

eGameBoard::~eGameBoard() {
    clear();
}

void eGameBoard::initialize(const int w, const int h) {
    clear();
    mTiles.reserve(w);
    for(int x = 0; x < w; x++) {
        std::vector<eTile*> yArr;
        yArr.reserve(h);
        for(int y = 0; y < h; y++) {
            const auto tile = new eTile(x, y);
            yArr.push_back(tile);
        }
        mTiles.push_back(yArr);
    }
    mWidth = w;
    mHeight = h;

    updateDiagonalArray();
}

void eGameBoard::clear() {
    for(const auto& x : mTiles) {
        for(const auto y : x) {
            delete y;
        }
    }
    mTiles.clear();
    mDiagTiles.clear();
    mWidth = 0;
    mHeight = 0;
}

void eGameBoard::updateDiagonalArray() {
    for(int k = 0 ; k <= mWidth + mHeight - 2; k++) {
        std::vector<eTile*> diag;
        for(int j = 0 ; j <= k ; j++) {
            const int i = k - j;
            if(i < mWidth && j < mHeight) {
                diag.push_back(mTiles[i][j]);
            }
        }
        mDiagTiles.push_back(diag);
    }
}
