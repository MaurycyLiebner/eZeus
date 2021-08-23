#ifndef EOTHERTHREADPATHFINDER_H
#define EOTHERTHREADPATHFINDER_H

#include "epathfinder.h"

class eThreadTile;

class eOtherThreadPathFinder {
public:
    using eTileWalkable = std::function<bool(eThreadTile*)>;
    using eTileFinish = std::function<bool(eThreadTile*)>;
    eOtherThreadPathFinder(const eTileWalkable& walkable,
                           const eTileFinish& finish);

    bool findPath(eThreadTile* const startTile,
                  const int maxDist,
                  std::vector<eOrientation>& path,
                  const bool onlyDiagonal) const;
private:
    ePathFinder mPathFinder;
};

#endif // EOTHERTHREADPATHFINDER_H
