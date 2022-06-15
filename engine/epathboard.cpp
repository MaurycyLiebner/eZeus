#include "epathboard.h"

#include "etilehelper.h"

ePathBoard::ePathBoard(const int x, const int y,
                       const int w, const int h) :
    mX(x), mY(y), mW(w), mH(h) {
    mData.reserve(w);
    for(int x = 0; x < w; x++) {
        mData.emplace_back(h, __INT_MAX__);
    }
}

bool ePathBoard::getAbsValue(const int x, const int y, int** value) {
    int dtx;
    int dty;
    eTileHelper::tileIdToDTileId(x, y, dtx, dty);
    return getDAbsValue(dtx, dty, value);
}

bool ePathBoard::getAbsValue(const int x, const int y, int& value) const {
    int dtx;
    int dty;
    eTileHelper::tileIdToDTileId(x, y, dtx, dty);
    return getDAbsValue(dtx, dty, value);
}

bool ePathBoard::getDAbsValue(const int x, const int y, int** value) {
    if(x < mX) return false;
    if(y < mY) return false;
    if(x >= mX + mW) return false;
    if(y >= mY + mH) return false;
    *value = &mData[x - mX][y - mY];
    return true;
}

bool ePathBoard::getDAbsValue(const int x, const int y, int& value) const {
    if(x < mX) return false;
    if(y < mY) return false;
    if(x >= mX + mW) return false;
    if(y >= mY + mH) return false;
    value = mData[x - mX][y - mY];
    return true;
}
