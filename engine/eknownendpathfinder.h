#ifndef EKNOWNENDPATHFINDER_H
#define EKNOWNENDPATHFINDER_H

#include "epathfinderbase.h"

class eKnownEndPathFinder {
public:
    using eTileWalkable = std::function<bool(eTileBase* const)>;
    using eTileFinish = std::function<bool(eTileBase* const)>;
    eKnownEndPathFinder(const eTileWalkable& walkable,
                        eTileBase* const endTile);

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
    eTileBase* const mEndTile;

    ePathFinderMode mMode = ePathFinderMode::findSingle;

    ePathFindData mData;
};

#endif // EKNOWNENDPATHFINDER_H
