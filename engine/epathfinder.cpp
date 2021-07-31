#include "epathfinder.h"

ePathFinder::ePathFinder(const int startX, const int startY,
                         const eGameBoard& board,
                         const eTileWalkable& walkable,
                         const eTileFinish& finish) :
    mBoard(board),
    mWalkable(walkable),
    mFinish(finish),
    mStartX(startX),
    mStartY(startY) {

}

bool ePathFinder::findPath(const int maxDist,
                           std::vector<eOrientation>& path) {
    std::vector<std::vector<int>> board;
    const int boardDim = 2*maxDist + 1;
    board.reserve(boardDim);
    for(int x = 0; x < boardDim; x++) {
        board.emplace_back(boardDim, __INT_MAX__);
    }
    using eTilePair = std::pair<eTile*, int*>;
    using eTileGetter = std::function<eTilePair(int, int)>;
    const eTileGetter tileGetter = [&](const int tx, const int ty) {
        const auto tile = mBoard.tile(tx, ty);
        const int bx = maxDist + tx + 1 - mStartX;
        const int by = maxDist + ty + 1 - mStartY;
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
        if(dist >= bestDistance || dist > maxDist) return;
        const auto tile = from.first;
        if(!tile) return;
        const int tx = tile->x();
        const int ty = tile->y();
        if(dist >= *from.second) return;
        *from.second = dist;
        if(bestDistance > dist && mFinish(tile)) {
            bestFinishX = tx;
            bestFinishY = ty;
            bestDistance = dist;
        }
        const auto tr = tileGetter(tx, ty - 1);
        const auto r = tileGetter(tx + 1, ty - 1);
        const auto br = tileGetter(tx + 1, ty);
        const auto b = tileGetter(tx + 1, ty + 1);
        const auto bl = tileGetter(tx, ty + 1);
        const auto l = tileGetter(tx - 1, ty + 1);
        const auto tl = tileGetter(tx - 1, ty);
        const auto t = tileGetter(tx - 1, ty - 1);

        pathFinder(tr, dist + 1);
        pathFinder(r, dist + 1);
        pathFinder(br, dist + 1);
        pathFinder(b, dist + 1);
        pathFinder(bl, dist + 1);
        pathFinder(l, dist + 1);
        pathFinder(tl, dist + 1);
        pathFinder(t, dist + 1);
    };

    pathFinder(tileGetter(mStartX, mStartY), 0);

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

        const auto tr = tileGetter(tx, ty - 1);
        const auto r = tileGetter(tx + 1, ty - 1);
        const auto br = tileGetter(tx + 1, ty);
        const auto b = tileGetter(tx + 1, ty + 1);
        const auto bl = tileGetter(tx, ty + 1);
        const auto l = tileGetter(tx - 1, ty + 1);
        const auto tl = tileGetter(tx - 1, ty);
        const auto t = tileGetter(tx - 1, ty - 1);

        if(tr.first && *tr.second == dist + 1) {
            path.emplace_back(eOrientation::topRight);
            return bestFinder(tr);
        }
        if(r.first && *r.second == dist + 1) {
            path.emplace_back(eOrientation::topRight);
            return bestFinder(r);
        }
        if(br.first && *br.second == dist + 1) {
            path.emplace_back(eOrientation::topRight);
            return bestFinder(br);
        }
        if(b.first && *b.second == dist + 1) {
            path.emplace_back(eOrientation::topRight);
            return bestFinder(b);
        }
        if(bl.first && *bl.second == dist + 1) {
            path.emplace_back(eOrientation::topRight);
            return bestFinder(bl);
        }
        if(l.first && *l.second == dist + 1) {
            path.emplace_back(eOrientation::topRight);
            return bestFinder(l);
        }
        if(tl.first && *tl.second == dist + 1) {
            path.emplace_back(eOrientation::topRight);
            return bestFinder(tl);
        }
        if(t.first && *t.second == dist + 1) {
            path.emplace_back(eOrientation::topRight);
            return bestFinder(t);
        }
        return false;
    };

    return bestFinder(tileGetter(bestFinishX, bestFinishY));
}
