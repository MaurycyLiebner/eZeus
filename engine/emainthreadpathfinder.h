#ifndef EMAINTHREADPATHFINDER_H
#define EMAINTHREADPATHFINDER_H

#include "epathfinder.h"

class eTile;

class eMainThreadPathFinder {
public:
    using eTileWalkable = std::function<bool(eTile*)>;
    using eTileFinish = std::function<bool(eTile*)>;
    eMainThreadPathFinder(const eTileWalkable& walkable,
                          const eTileFinish& finish);

    bool findPath(eTile* const startTile,
                  const int maxDist,
                  std::vector<eOrientation>& path,
                  const bool onlyDiagonal) const;
private:
    ePathFinder mPathFinder;
};

#endif // EMAINTHREADPATHFINDER_H
