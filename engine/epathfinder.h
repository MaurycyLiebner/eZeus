#ifndef EPATHFINDER_H
#define EPATHFINDER_H


#include "egameboard.h"

#include <functional>

class ePathFinder {
public:
    using eTileWalkable = std::function<bool(eTileBase* const)>;
    using eTileFinish = std::function<bool(eTileBase* const)>;
    ePathFinder(eTileBase* const startTile,
                const eTileWalkable& walkable,
                const eTileFinish& finish);

    bool findPath(const int maxDist,
                  std::vector<eOrientation>& path,
                  const bool onlyDiagonal) const;
private:
    const eTileWalkable mWalkable;
    const eTileFinish mFinish;
    eTileBase* const mStart;
};

#endif // EPATHFINDER_H
