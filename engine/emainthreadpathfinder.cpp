#include "emainthreadpathfinder.h"

#include "engine/etile.h"

eMainThreadPathFinder::eMainThreadPathFinder(
        const eTileWalkable& walkable,
        const eTileFinish& finish) :
    mPathFinder(
    [walkable](eTileBase* const t) {
        return walkable(static_cast<eTile*>(t));
    },
    [finish](eTileBase* const t) {
        return finish(static_cast<eTile*>(t));
    }) {}

bool eMainThreadPathFinder::findPath(
        eTile* const startTile,
        const int maxDist,
        std::vector<eOrientation>& path,
        const bool onlyDiagonal) const {
    return mPathFinder.findPath(startTile, maxDist, path, onlyDiagonal);
}
