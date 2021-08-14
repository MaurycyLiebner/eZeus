#include "ethreadboard.h"

void eThreadBoard::initialize(const int x, const int y,
                              const int w, const int h) {
    clear();
    mTiles.reserve(w);
    for(int x = 0; x < w; x++) {
        auto& yArr = mTiles.emplace_back();
        yArr.reserve(h);
        for(int y = 0; y < h; y++) {
            yArr.emplace_back();
        }
    }
    mX = x;
    mY = y;
    mWidth = w;
    mHeight = h;

    updateNeighbours();
}

void eThreadBoard::clear() {
    mTiles.clear();
    mWidth = 0;
    mHeight = 0;
}

eThreadTile* eThreadBoard::relTile(const int x, const int y) {
    if(x < 0 || x >= mWidth) return nullptr;
    if(y < 0 || y >= mHeight) return nullptr;
    return &mTiles[x][y];
}

eThreadTile* eThreadBoard::absTile(const int x, const int y) {
    return relTile(x - mX, y - mY);
}

void eThreadBoard::updateNeighbours() {
    for(int x = 0; x < mWidth; x++) {
        for(int y = 0; y < mHeight; y++) {
            auto& t = mTiles[x][y];
            t.setTopLeft(relTile(x - 1, y));
            t.setTopRight(relTile(x, y - 1));
            t.setBottomRight(relTile(x + 1, y));
            t.setBottomLeft(relTile(x, y + 1));
        }
    }
}

void eThreadBoard::assign(const eThreadBoard& src) {
    for(int x = 0; x < mWidth; x++) {
        for(int y = 0; y < mHeight; y++) {
            auto& t = mTiles[x][y];
            auto& srcT = src.mTiles[x][y];
            t.load(srcT);
        }
    }
}
