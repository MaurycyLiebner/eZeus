#ifndef EPATHFINDER_H
#define EPATHFINDER_H

#include <functional>

#include "eorientation.h"

class eThreadTile;

class ePathFinder {
public:
    using eTileWalkable = std::function<bool(eThreadTile* const)>;
    using eTileFinish = std::function<bool(eThreadTile* const)>;
    ePathFinder(eThreadTile* const startTile,
                const eTileWalkable& walkable,
                const eTileFinish& finish);

    bool findPath(const int maxDist,
                  std::vector<eOrientation>& path,
                  const bool onlyDiagonal) const;
private:
    const eTileWalkable mWalkable;
    const eTileFinish mFinish;
    eThreadTile* const mStart;
};

#endif // EPATHFINDER_H
