#ifndef EPATHFINDER_H
#define EPATHFINDER_H


#include "egameboard.h"

#include <functional>

template <typename T>
class ePathFinder {
public:
    using eTileWalkable = std::function<bool(T* const)>;
    using eTileFinish = std::function<bool(T* const)>;
    ePathFinder(T* const startTile,
                const eTileWalkable& walkable,
                const eTileFinish& finish);

    bool findPath(const int maxDist,
                  std::vector<eOrientation>& path,
                  const bool randomize,
                  const bool onlyDiagonal) const;
private:
    const eTileWalkable mWalkable;
    const eTileFinish mFinish;
    eTile* const mStart;
};

#include "epathfinder.cpp"

#endif // EPATHFINDER_H
