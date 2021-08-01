#include "epathfinder.h"

ePathFinder::ePathFinder(eTile* const startTile,
                         const eTileWalkable& walkable,
                         const eTileFinish& finish) :
    mWalkable(walkable),
    mFinish(finish),
    mStart(startTile) {

}

bool ePathFinder::findPath(const int maxDist,
                           std::vector<eOrientation>& path,
                           const bool randomize,
                           const bool onlyDiagonal) const {
    if(!mStart) return false;
    const int startX = mStart->x();
    const int startY = mStart->y();

    std::vector<std::vector<int>> board;
    const int boardDim = 2*maxDist + 1;
    board.reserve(boardDim);
    for(int x = 0; x < boardDim; x++) {
        board.emplace_back(boardDim, __INT_MAX__);
    }
    using eTilePair = std::pair<eTile*, int*>;
    using eTileGetter = std::function<eTilePair(int, int)>;
    const eTileGetter tileGetter = [&](const int tx, const int ty) {
        const auto tile = mStart->tileAbs(tx, ty);
        const int bx = maxDist + tx + 1 - startX;
        const int by = maxDist + ty + 1 - startY;
        if(!tile ||
           bx < 0 || bx >= boardDim ||
           by < 0 || by >= boardDim) {
            return eTilePair{nullptr, nullptr};
        }
        return eTilePair{tile, &board[bx][by]};
    };
    int bestFinishX = -1;
    int bestFinishY = -1;
    int bestDistance = __INT_MAX__;
    using ePFinder = std::function<void(const eTilePair&, const int)>;
    ePFinder pathFinder;
    pathFinder = [&](const eTilePair& from, const int dist) {
        if(randomize) {
            if(dist > bestDistance) return;
        } else {
            if(dist >= bestDistance) return;
        }
        const auto tile = from.first;
        if(!tile) return;
        const int tx = tile->x();
        const int ty = tile->y();
        if(randomize) {
            if(dist > *from.second) return;
        } else {
            if(dist >= *from.second) return;
        }
        *from.second = dist;
        if(randomize && bestDistance == dist) {
            const bool r = rand() % 2;
            if(r && mFinish(tile)) {
                bestFinishX = tx;
                bestFinishY = ty;
                bestDistance = dist;
            }
        } else {
            if(bestDistance > dist && mFinish(tile)) {
                bestFinishX = tx;
                bestFinishY = ty;
                bestDistance = dist;
            }
        }

        for(const auto x : {0, 1, -1}) {
            for(const auto y : {0, 1, -1}) {
                if(onlyDiagonal && x != 0 && y != 0) continue;
                const auto tt = tileGetter(tx + x, ty + y);
                if(tt.first && mWalkable(tt.first)) pathFinder(tt, dist + 1);
            }
        }
    };

    pathFinder(tileGetter(startX, startY), 0);
    *tileGetter(startX, startY).second = 0;

    if(bestDistance == __INT_MAX__) return false;

    path.clear();
    path.reserve(bestDistance);
    using eBFinder = std::function<bool(const eTilePair&)>;
    eBFinder bestFinder;
    bestFinder = [&](const eTilePair& from) {
        const auto tile = from.first;
        if(!tile) return false;
        const int dist = *from.second;
        const int tx = tile->x();
        const int ty = tile->y();
        if(tx == startX && ty == startY) return true;

        const auto tr = tileGetter(tx, ty - 1);
        const auto br = tileGetter(tx + 1, ty);
        const auto bl = tileGetter(tx, ty + 1);
        const auto tl = tileGetter(tx - 1, ty);

        using eNeigh = std::pair<eOrientation, eTilePair>;
        std::vector<eNeigh> neighs{
                {eOrientation::bottomLeft, tr},
                {eOrientation::left, onlyDiagonal ? eTilePair{nullptr, nullptr}
                                                  : tileGetter(tx + 1, ty - 1)},
                {eOrientation::topLeft, br},
                {eOrientation::top, onlyDiagonal ? eTilePair{nullptr, nullptr}
                                                 : tileGetter(tx + 1, ty + 1)},
                {eOrientation::topRight, bl},
                {eOrientation::right, onlyDiagonal ? eTilePair{nullptr, nullptr}
                                                   : tileGetter(tx - 1, ty + 1)},
                {eOrientation::bottomRight, tl},
                {eOrientation::bottom, onlyDiagonal ? eTilePair{nullptr, nullptr}
                                                    : tileGetter(tx - 1, ty - 1)}};
        if(randomize) {
            std::random_shuffle(neighs.begin(), neighs.end());
        }

        for(const auto& n : neighs) {
            const auto& tp = n.second;
            if(!tp.first) continue;
            if(mWalkable(tp.first)) {
                if(*tp.second == dist - 1) {
                    path.emplace_back(n.first);
                    return bestFinder(tp);
                }
            }
        }

        return false;
    };

    const bool r = bestFinder(tileGetter(bestFinishX, bestFinishY));
    if(!r) return false;
    //std::reverse(path.begin(), path.end());
    return true;
}
