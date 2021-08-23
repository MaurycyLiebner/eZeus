#include "eotherthreadpathfinder.h"

#include "engine/thread/ethreadtile.h"

eOtherThreadPathFinder::eOtherThreadPathFinder(
        const eTileWalkable& walkable,
        const eTileFinish& finish) :
    mPathFinder(
    [walkable](eTileBase* const t) {
        return walkable(static_cast<eThreadTile*>(t));
    },
    [finish](eTileBase* const t) {
        return finish(static_cast<eThreadTile*>(t));
    }) {}

bool eOtherThreadPathFinder::findPath(
        eThreadTile* const startTile,
        const int maxDist,
        std::vector<eOrientation>& path,
        const bool onlyDiagonal) const {
    return mPathFinder.findPath(startTile, maxDist, path, onlyDiagonal);
}
