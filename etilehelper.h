#ifndef ETILEHELPER_H
#define ETILEHELPER_H

namespace eTileHelper {
    void dtileIdToTileId(const int dtx, const int dty,
                         int& tx, int& ty);
    void tileIdToDTileId(const int tx, const int ty,
                         int& dtx, int& dty);
};

#endif // ETILEHELPER_H
