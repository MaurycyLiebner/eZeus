#ifndef ETILEHELPER_H
#define ETILEHELPER_H

class eGameBoard;
class eTile;

namespace eTileHelper {
    void dtileIdToTileId(const int dtx, const int dty,
                         int& tx, int& ty);
    void tileIdToDTileId(const int tx, const int ty,
                         int& dtx, int& dty);

    eTile* closestRoad(const int rdx, const int rdy,
                       eGameBoard& board);
};

#endif // ETILEHELPER_H
