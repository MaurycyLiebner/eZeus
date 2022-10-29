#ifndef EPATHFINDER_H
#define EPATHFINDER_H

#include <functional>
#include <SDL2/SDL_rect.h>

#include "eorientation.h"
#include "epathboard.h"

class eTileBase;
class eTile;
class eGameBoard;

struct ePathFindData {
    ePathBoard fBoard;

    eTileBase* fStart = nullptr;
    bool fOnlyDiagonal = false;

    bool fFound = false;
    int fDistance = -1;
    int fFinalX = -1;
    int fFinalY = -1;
};

enum class ePathFinderMode {
    findSingle,
    findAll
};

using eTilePair = std::pair<eTileBase*, int*>;
using eNeigh = std::pair<eOrientation, eTilePair>;

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
