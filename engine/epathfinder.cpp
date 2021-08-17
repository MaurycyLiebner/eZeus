#include "epathfinder.h"

#include <deque>

ePathFinder::ePathFinder(eTileBase* const startTile,
                         const eTileWalkable& walkable,
                         const eTileFinish& finish) :
    mWalkable(walkable),
    mFinish(finish),
    mStart(startTile) {

}

bool ePathFinder::findPath(const int maxDist,
                           std::vector<eOrientation>& path,
                           const bool onlyDiagonal) const {
    if(!mStart) return false;
    printf("enter\n");
    const int startX = mStart->x();
    const int startY = mStart->y();

    std::vector<std::vector<int>> board;
    const int boardDim = 2*maxDist + 1;
    board.reserve(boardDim);
    for(int x = 0; x < boardDim; x++) {
        board.emplace_back(boardDim, __INT_MAX__);
    }
    using eTilePair = std::pair<eTileBase*, int*>;
    using eTileGetter = std::function<eTilePair(eTileBase*, int, int)>;
    const eTileGetter tileGetter = [&](eTileBase* const from,
                                       const int dx, const int dy) {
        const auto tile = from->tileRel(dx, dy);
        if(!tile) return eTilePair{nullptr, nullptr};
        const int tx = tile->x();
        const int ty = tile->y();
        const int bx = maxDist + tx + 1 - startX;
        const int by = maxDist + ty + 1 - startY;
        if(bx < 0 || bx >= boardDim ||
           by < 0 || by >= boardDim) {
            return eTilePair{nullptr, nullptr};
        }
        return eTilePair{tile, &board[bx][by]};
    };
    int bestFinishX = -1;
    int bestFinishY = -1;
    int foundDistance;
    using ePFinder = std::function<void(const eTilePair&)>;
    std::deque<eTilePair> toProcess;
    ePFinder pathFinder;
    bool found = false;
    pathFinder = [&](const eTilePair& from) {
        const int dist = *from.second;
        const auto tile = from.first;
        const int tx = tile->x();
        const int ty = tile->y();

        if(mFinish(tile)) {
            bestFinishX = tx;
            bestFinishY = ty;
            foundDistance = dist;
            found = true;
            return;
        }

        for(const int x : {0, 1, -1}) {
            for(const int y : {0, 1, -1}) {
                if(x == 0 && y == 0) continue;
                if(onlyDiagonal && x != 0 && y != 0) continue;
                const auto tt = tileGetter(tile, x, y);
                if(!tt.first || !tt.second) continue;
                if(!mWalkable(tt.first)) continue;
                const int newDist = dist + 1;
                if(*tt.second > newDist) {
                    *tt.second = newDist;
                    toProcess.push_back(tt);
                }
            }
        }
    };

    const auto t = tileGetter(mStart, 0, 0);
    if(!t.first || !t.second) return false;
    *t.second = 0;
    toProcess.push_back(t);
    while(!found && !toProcess.empty()) {
        const auto t = toProcess.front();
        toProcess.pop_front();
        pathFinder(t);
    }

    if(!found) return false;

    path.clear();
    path.reserve(foundDistance);
    using eBFinder = std::function<bool(const eTilePair&)>;
    eBFinder bestFinder;
    bestFinder = [&](const eTilePair& from) {
        if(!from.first || !from.second) return false;
        const auto tile = from.first;
        const int dist = *from.second;
        const int tx = tile->x();
        const int ty = tile->y();
        if(tx == startX && ty == startY) return true;

        const auto tr = tileGetter(tile, 0, -1);
        const auto br = tileGetter(tile, 1, 0);
        const auto bl = tileGetter(tile, 0, 1);
        const auto tl = tileGetter(tile, -1, 0);

        using eNeigh = std::pair<eOrientation, eTilePair>;
        std::vector<eNeigh> neighs{
                {eOrientation::bottomLeft, tr},
                {eOrientation::left, onlyDiagonal ? eTilePair{nullptr, nullptr}
                                                  : tileGetter(tile, 1, -1)},
                {eOrientation::topLeft, br},
                {eOrientation::top, onlyDiagonal ? eTilePair{nullptr, nullptr}
                                                 : tileGetter(tile, 1, 1)},
                {eOrientation::topRight, bl},
                {eOrientation::right, onlyDiagonal ? eTilePair{nullptr, nullptr}
                                                   : tileGetter(tile, -1, 1)},
                {eOrientation::bottomRight, tl},
                {eOrientation::bottom, onlyDiagonal ? eTilePair{nullptr, nullptr}
                                                    : tileGetter(tile, -1, -1)}};

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

    const bool r = bestFinder(tileGetter(mStart,
                                         bestFinishX - startX,
                                         bestFinishY - startY));
    return r;
}
