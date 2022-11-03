#include "etilehelper.h"

#include "eiteratesquare.h"

void eTileHelper::dtileIdToTileId(const int dtx, const int dty, int& tx, int& ty) {
    tx = dtx + (dty + 1)/2;
    ty = dty/2 - dtx;
}

void eTileHelper::tileIdToDTileId(const int tx, const int ty, int& dtx, int& dty) {
    dty = tx + ty;
    dtx = (tx + ty)/2 - ty;
}

eTile* eTileHelper::closestRoad(const int rdx, const int rdy,
                                eGameBoard& board) {
    eTile* roadTile = nullptr;
    eTile* plainTile = nullptr;
    const auto prcsTile = [&](const int i, const int j) {
        const int tx = rdx + i;
        const int ty = rdy + j;
        const auto tt = board.tile(tx, ty);
        if(!tt) return false;
        if(tt->hasRoad()) {
            roadTile = tt;
            return true;
        } else if(!plainTile && tt->walkable()) {
            plainTile = tt;
        }
        return false;
    };

    for(int k = 0; k < 1000; k++) {
        eIterateSquare::iterateSquare(k, prcsTile, 1);
        if(roadTile) break;
    }

    const auto tile = roadTile ? roadTile : plainTile;
    return tile;
}
