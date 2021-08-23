#ifndef EPATHFINDER_H
#define EPATHFINDER_H

#include <functional>

#include "eorientation.h"

class eTileBase;

class ePathFinder {
public:
    using eTileWalkable = std::function<bool(eTileBase* const)>;
    using eTileFinish = std::function<bool(eTileBase* const)>;
    ePathFinder(const eTileWalkable& walkable,
                const eTileFinish& finish);

    bool findPath(eTileBase* const startTile,
                  const int maxDist,
                  std::vector<eOrientation>& path,
                  const bool onlyDiagonal,
                  int* finalX = nullptr,
                  int* finalY = nullptr) const;
private:
    const eTileWalkable mWalkable;
    const eTileFinish mFinish;
};

#endif // EPATHFINDER_H
