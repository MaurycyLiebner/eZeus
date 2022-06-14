#include "etilehelper.h"

void eTileHelper::dtileIdToTileId(const int dtx, const int dty, int& tx, int& ty) {
    tx = dtx + (dty + 1)/2;
    ty = dty/2 - dtx;
}

void eTileHelper::tileIdToDTileId(const int tx, const int ty, int& dtx, int& dty) {
    dty = tx + ty;
    dtx = (tx + ty)/2 - ty;
}
