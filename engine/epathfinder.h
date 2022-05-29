#ifndef EPATHFINDER_H
#define EPATHFINDER_H

#include <functional>
#include <SDL2/SDL_rect.h>

#include "eorientation.h"

class eTileBase;

struct ePathBoard {
    ePathBoard() {}
    ePathBoard(const int x, const int y,
               const int w, const int h);

    int fX;
    int fY;
    int fW;
    int fH;
    std::vector<std::vector<int>> fData;

    bool getAbsValue(const int x, const int y, int** value);
    bool getAbsValue(const int x, const int y, int& value) const;
};

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

class ePathFinder {
public:
    using eTileWalkable = std::function<bool(eTileBase* const)>;
    using eTileFinish = std::function<bool(eTileBase* const)>;
    ePathFinder(const eTileWalkable& walkable,
                const eTileFinish& finish);

    bool findPath(eTileBase* const startTile,
                  const int maxDist,
                  const bool onlyDiagonal,
                  const int srcW, const int srcH);
    bool extractPath(std::vector<eOrientation>& path);
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
