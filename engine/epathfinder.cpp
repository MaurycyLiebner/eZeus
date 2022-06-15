#include "epathfinder.h"

#include <deque>

#include "engine/etilebase.h"

ePathBoard::ePathBoard(const int x, const int y,
                       const int w, const int h) :
    fX(x), fY(y), fW(w), fH(h) {
    fData.reserve(w);
    for(int x = 0; x < w; x++) {
        fData.emplace_back(h, __INT_MAX__);
    }
}

bool ePathBoard::getAbsValue(const int x, const int y, int** value) {
    if(x < fX) return false;
    if(y < fY) return false;
    if(x >= fX + fW) return false;
    if(y >= fY + fH) return false;
    *value = &fData[x - fX][y - fY];
    return true;
}

bool ePathBoard::getAbsValue(const int x, const int y, int& value) const {
    if(x < fX) return false;
    if(y < fY) return false;
    if(x >= fX + fW) return false;
    if(y >= fY + fH) return false;
    value = fData[x - fX][y - fY];
    return true;
}

ePathFinder::ePathFinder(const eTileWalkable& walkable,
                         const eTileFinish& finish) :
    mWalkable(walkable),
    mFinish(finish) {

}

using eTilePair = std::pair<eTileBase*, int*>;
using ePFinder = std::function<void(const eTilePair&)>;
using eTileGetter = std::function<eTilePair(eTileBase*, int, int)>;

eTilePair tileGetter(ePathBoard& brd,
                     eTileBase* const from,
                     const int dx, const int dy) {
    const auto tile = from->tileRel<eTileBase>(dx, dy);
    if(!tile) return eTilePair{nullptr, nullptr};
    const int tx = tile->x();
    const int ty = tile->y();
    int* value = nullptr;
    const bool r = brd.getAbsValue(tx, ty, &value);
    if(!r) return eTilePair{nullptr, nullptr};
    return eTilePair{tile, value};
};

bool ePathFinder::findPath(eTileBase* const start,
                           const int maxDist,
                           const bool onlyDiagonal,
                           const int srcW, const int srcH) {
    if(!start) return false;
    if(mFinish(start)) return true;
    const int startX = start->x();
    const int startY = start->y();

    const int minX = startX - maxDist;
    const int minY = startY - maxDist;

    const int maxX = startX + maxDist;
    const int maxY = startY + maxDist;

    const bool finishOnFound = mMode == ePathFinderMode::findSingle;

    mData = ePathFindData();
    mData.fOnlyDiagonal = onlyDiagonal;
    mData.fStart = start;
    auto& brd = mData.fBoard;
    brd = ePathBoard(minX, minY, maxX - minX, maxY - minY);

    std::deque<eTilePair> toProcess;
    ePFinder pathFinder;
    pathFinder = [&](const eTilePair& from) {
        const int dist = *from.second;
        const auto tile = from.first;

        for(const int x : {0, 1, -1}) {
            for(const int y : {0, 1, -1}) {
                if(x == 0 && y == 0) continue;
                const bool notDiagonal = x != 0 && y != 0;
                if(onlyDiagonal && notDiagonal) continue;
                const auto tt = tileGetter(brd, tile, x, y);
                if(!tt.first || !tt.second) continue;
                const int newDist = dist + 1;
                if(mFinish(tt.first)) {
                    *tt.second = newDist;
                    const int ttx = tt.first->x();
                    const int tty = tt.first->y();
                    mData.fFound = true;
                    mData.fDistance = newDist;
                    mData.fFinalX = ttx;
                    mData.fFinalY = tty;
                    if(finishOnFound) return;
                }
                if(!mWalkable(tt.first)) continue;
                if(notDiagonal) {
                    {
                        const auto ttt = tileGetter(brd, tile, 0, -y);
                        if(ttt.first && ttt.second) {
                            if(!mWalkable(ttt.first)) continue;
                        }
                    }
                    {
                        const auto ttt = tileGetter(brd, tile, -x, 0);
                        if(ttt.first && ttt.second) {
                            if(!mWalkable(ttt.first)) continue;
                        }
                    }
                }
                if(*tt.second > newDist) {
                    *tt.second = newDist;
                    toProcess.push_back(tt);
                }
            }
        }
    };

    const auto t = tileGetter(brd, start, 0, 0);
    if(!t.first || !t.second) return false;
    *t.second = 0;
    toProcess.push_back(t);
    while((!mData.fFound || !finishOnFound) && !toProcess.empty()) {
        const auto t = toProcess.front();
        toProcess.pop_front();
        pathFinder(t);
    }

    return mData.fFound;
}

bool ePathFinder::extractPath(std::vector<eOrientation>& path) {
    if(!mData.fFound) return false;

    auto& brd = mData.fBoard;
    path.clear();
    path.reserve(mData.fDistance);
    using eBFinder = std::function<bool(const eTilePair&)>;
    eBFinder bestFinder;
    bestFinder = [&](const eTilePair& from) {
        if(!from.first || !from.second) return false;
        const auto tile = from.first;
        const int dist = *from.second;
        const int tx = tile->x();
        const int ty = tile->y();
        const int dtx = mData.fStart->x();
        const int dty = mData.fStart->y();
        if(tx == dtx && ty == dty) return true;

        const auto tr = tileGetter(brd, tile, 0, -1);
        const auto br = tileGetter(brd, tile, 1, 0);
        const auto bl = tileGetter(brd, tile, 0, 1);
        const auto tl = tileGetter(brd, tile, -1, 0);

        using eNeigh = std::pair<eOrientation, eTilePair>;
        const bool od = mData.fOnlyDiagonal;
        std::vector<eNeigh> neighs{
                {eOrientation::bottomLeft, tr},
                {eOrientation::topLeft, br},
                {eOrientation::topRight, bl},
                {eOrientation::bottomRight, tl},
                {eOrientation::left, od ? eTilePair{nullptr, nullptr}
                                        : tileGetter(brd, tile, 1, -1)},
                {eOrientation::top, od ? eTilePair{nullptr, nullptr}
                                       : tileGetter(brd, tile, 1, 1)},
                {eOrientation::right, od ? eTilePair{nullptr, nullptr}
                                         : tileGetter(brd, tile, -1, 1)},
                {eOrientation::bottom, od ? eTilePair{nullptr, nullptr}
                                          : tileGetter(brd, tile, -1, -1)}};

        for(const auto& n : neighs) {
            const auto& tp = n.second;
            if(!tp.first || !tp.second) continue;
            if(mWalkable(tp.first)) {
                if(*tp.second == dist - 1) {
                    path.emplace_back(n.first);
                    return bestFinder(tp);
                }
            }
        }

        return false;
    };

    const auto start = mData.fStart;
    const int startX = start->x();
    const int startY = start->y();
    const auto t = tileGetter(brd, mData.fStart,
                              mData.fFinalX - startX,
                              mData.fFinalY - startY);
    const bool r = bestFinder(t);
    return r;
}

bool ePathFinder::extractData(ePathFindData& data) {
    if(!mData.fFound) return false;
    data = mData;
    return true;
}
