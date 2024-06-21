#ifndef EPATHFINDER_H
#define EPATHFINDER_H

#include "epathfinderbase.h"

class ePathFinder {
public:
    using eTileWalkable = std::function<bool(eTileBase* const)>;
    using eTileFinish = std::function<bool(eTileBase* const)>;
    ePathFinder(const eTileWalkable& walkable,
                const eTileFinish& finish);

    using eTileDistance = std::function<int(eTileBase* const)>;
    bool findPath(eTileBase* const startTile,
                  const int maxDist,
                  const bool onlyDiagonal,
                  const int srcW, const int srcH,
                  const eTileDistance& distance = nullptr);
    bool extractPath(std::vector<eOrientation>& path);
    bool extractPath(std::vector<std::pair<int, int>>& path);
    bool extractPath(std::vector<eTile*>& path,
                     eGameBoard& board);
    using ePathFunc = std::function<void(const eNeigh&)>;
    bool extractPath(const ePathFunc& pathFunc);
    bool extractData(ePathFindData& data);

    void setMode(const ePathFinderMode m)
    { mMode = m; }
private:
    const eTileWalkable mWalkable;
    const eTileFinish mFinish;

    ePathFinderMode mMode = ePathFinderMode::findSingle;

    ePathFindData mData;
};

#endif // EPATHFINDER_H
