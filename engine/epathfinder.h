#ifndef EPATHFINDER_H
#define EPATHFINDER_H


#include "egameboard.h"

#include <functional>

class ePathFinder {
public:
    using eTileWalkable = std::function<bool(eTile* const)>;
    using eTileFinish = std::function<bool(eTile* const)>;
    ePathFinder(const int startX, const int startY,
                const eGameBoard& board,
                const eTileWalkable& walkable,
                const eTileFinish& finish);

    bool findPath(const int maxDist,
                  std::vector<eOrientation>& path,
                  const bool randomize);
private:
    const eGameBoard& mBoard;
    const eTileWalkable mWalkable;
    const eTileFinish mFinish;
    const int mStartX;
    const int mStartY;
};

#endif // EPATHFINDER_H
