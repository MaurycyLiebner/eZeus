#include "ethreadboard.h"

#include "etilehelper.h"

void eThreadBoard::initialize(const int w, const int h) {
    clear();
    mTiles.reserve(w);
    for(int x = 0; x < w; x++) {
        auto& yArr = mTiles.emplace_back();
        yArr.reserve(h);
        for(int y = 0; y < h; y++) {
            yArr.emplace_back();
        }
    }
    mWidth = w;
    mHeight = h;

    updateNeighbours();
}

void eThreadBoard::clear() {
    mTiles.clear();
    mWidth = 0;
    mHeight = 0;
}

eThreadTile* eThreadBoard::tile(const int x, const int y) {
    int dtx;
    int dty;
    eTileHelper::tileIdToDTileId(x, y, dtx, dty);
    return dtile(dtx, dty);
}

eThreadTile* eThreadBoard::dtile(const int x, const int y) {
    if(x < 0 || x >= mWidth) return nullptr;
    if(y < 0 || y >= mHeight) return nullptr;
    return &mTiles[x][y];
}

void eThreadBoard::updateNeighbours() {
    for(int x = 0; x < mWidth; x++) {
        for(int y = 0; y < mHeight; y++) {
            auto& t = mTiles[x][y];
            {
                const int dx = y % 2 == 0 ? -1 : 0;
                t.setTopLeft(dtile(x + dx, y - 1));
                t.setBottomLeft(dtile(x + dx, y + 1));
            }
            {
                const int dx = y % 2 == 0 ? 0 : 1;
                t.setTopRight(dtile(x + dx, y - 1));
                t.setBottomRight(dtile(x + dx, y + 1));
            }
        }
    }
}
