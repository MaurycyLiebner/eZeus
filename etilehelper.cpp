#include "etilehelper.h"

#include "eiteratesquare.h"
#include "engine/egameboard.h"

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

void eTileHelper::rotatedDTileIdToDTileId(const int rdtx, const int rdty,
                                          int& dtx, int& dty,
                                          const eWorldDirection dir,
                                          const int width, const int height) {
    if(dir == eWorldDirection::N) {
        dtx = rdtx;
        dty = rdty;
    } else if(dir == eWorldDirection::E) {
        dtx = width - 1 - (rdty + 1)/2;
        dty = 2*rdtx + (rdty % 2);
    } else if(dir == eWorldDirection::S) {
        dtx = width - rdtx - 1;
        dty = height - rdty - 1;
    } else { // if(dir == eWorldDirection::W) {
        dtx = rdty/2;
        dty = (height - 2) - 2*rdtx - (rdty % 2);
    }
}

void eTileHelper::dTileIdToRotatedDTileId(const int dtx, const int dty,
                                          int& rdtx, int& rdty,
                                          const eWorldDirection dir,
                                          const int width, const int height) {
    if(dir == eWorldDirection::N) {
        rdtx = dtx;
        rdty = dty;
    } else if(dir == eWorldDirection::E) {
        rdtx = dty/2;
        rdty = 2*width - 2 - 2*dtx - (dty % 2);
    } else if(dir == eWorldDirection::S) {
        rdtx = width - dtx - 1;
        rdty = height - dty - 1;
    } else { // if(dir == eWorldDirection::W) {
        rdtx = (height - 1)/2 - dty/2 - (dty % 2);
        rdty = 2*dtx + (dty % 2);
    }
}

void eTileHelper::tileIdToRotatedTileId(const int tx, const int ty,
                                        int& rtx, int& rty,
                                        const eWorldDirection dir,
                                        const int width, const int height) {
    int dtx;
    int dty;
    tileIdToDTileId(tx, ty, dtx, dty);
    int rdtx;
    int rdty;
    dTileIdToRotatedDTileId(dtx, dty, rdtx, rdty, dir, width, height);
    dtileIdToTileId(rdtx, rdty, rtx, rty);
}

SDL_Rect eTileHelper::toRotatedRect(const SDL_Rect& r, const eWorldDirection dir,
                                    const int width, const int height) {
    if(dir == eWorldDirection::N) {
        return r;
    } else if(dir == eWorldDirection::E) {
        const int tx = r.x + r.w - 1;
        const int ty = r.y;
        int rtx;
        int rty;
        tileIdToRotatedTileId(tx, ty, rtx, rty, dir, width, height);
        return SDL_Rect{rtx, rty, r.h, r.w};
    } else if(dir == eWorldDirection::S) {
        const int tx = r.x + r.w - 1;
        const int ty = r.y + r.h - 1;
        int rtx;
        int rty;
        tileIdToRotatedTileId(tx, ty, rtx, rty, dir, width, height);
        return SDL_Rect{rtx, rty, r.w, r.h};
    } else if(dir == eWorldDirection::W) {
        const int tx = r.x;
        const int ty = r.y + r.h - 1;
        int rtx;
        int rty;
        tileIdToRotatedTileId(tx, ty, rtx, rty, dir, width, height);
        return SDL_Rect{rtx, rty, r.h, r.w};
    }
    return r;
}
