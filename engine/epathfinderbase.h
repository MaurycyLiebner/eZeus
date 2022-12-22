#ifndef EPATHFINDERBASE_H
#define EPATHFINDERBASE_H

#include <functional>
#include <SDL2/SDL_rect.h>

#include "eorientation.h"
#include "epathboard.h"

#include "engine/etilebase.h"

struct ePathFindData {
    ePathBoard fBoard;

    eTileBase* fStart = nullptr;
    bool fOnlyDiagonal = false;

    bool fFound = false;
    int fDistance = -1;
    int fFinalX = -1;
    int fFinalY = -1;
};

enum class ePathFinderMode {
    findSingle,
    findAll
};

using eTilePair = std::pair<eTileBase*, int*>;
using eNeigh = std::pair<eOrientation, eTilePair>;

inline eTilePair tileGetter(ePathBoard& brd,
                            eTileBase* const from,
                            const int dx, const int dy) {
    const auto tile = from->tileRel<eTileBase>(dx, dy);
    if(!tile) return eTilePair{nullptr, nullptr};
    const int tx = tile->x();
    const int ty = tile->y();
    int* value = nullptr;
    const bool r = brd.getAbsValue(tx, ty, &value);
    if(!r) return eTilePair{nullptr, nullptr};
    return eTilePair{tile, value};
};

#endif // EPATHFINDERBASE_H
