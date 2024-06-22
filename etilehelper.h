#ifndef ETILEHELPER_H
#define ETILEHELPER_H

class eGameBoard;
class eTile;
enum class eWorldDirection;
struct SDL_Rect;

namespace eTileHelper {
    void rotatedDTileIdToDTileId(const int rdtx, const int rdty,
                                 int& dtx, int& dty,
                                 const eWorldDirection dir,
                                 const int width, const int height);
    void dTileIdToRotatedDTileId(const int dtx, const int dty,
                                 int& rdtx, int& rdty,
                                 const eWorldDirection dir,
                                 const int width, const int height);
    void dtileIdToTileId(const int dtx, const int dty,
                         int& tx, int& ty);
    void tileIdToDTileId(const int tx, const int ty,
                         int& dtx, int& dty);
    void tileIdToRotatedTileId(const int tx, const int ty,
                               int& rtx, int& rty,
                               const eWorldDirection dir,
                               const int width, const int height);
    void rotatedTileIdToTileId(const int rtx, const int rty,
                               int& tx, int& ty,
                               const eWorldDirection dir,
                               const int width, const int height);

    eTile* closestRoad(const int rdx, const int rdy,
                       eGameBoard& board);

    SDL_Rect toRotatedRect(const SDL_Rect& r,
                           const eWorldDirection dir,
                           const int width, const int height);
};

#endif // ETILEHELPER_H
