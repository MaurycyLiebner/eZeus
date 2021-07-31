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
                           std::vector<eOrientation>& path,
                           const bool randomize) {
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
    *tileGetter(mStartX, mStartY).second = 0;

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
        if(tx == mStartX && ty == mStartY) return true;

        const auto tr = tileGetter(tx, ty - 1);
        const auto r = tileGetter(tx + 1, ty - 1);
        const auto br = tileGetter(tx + 1, ty);
        const auto b = tileGetter(tx + 1, ty + 1);
        const auto bl = tileGetter(tx, ty + 1);
        const auto l = tileGetter(tx - 1, ty + 1);
        const auto tl = tileGetter(tx - 1, ty);
        const auto t = tileGetter(tx - 1, ty - 1);

        using eNeigh = std::pair<eOrientation, eTilePair>;
        std::vector<eNeigh> neighs{
                {eOrientation::bottomLeft, tr},
                {eOrientation::left, r},
                {eOrientation::topLeft, br},
                {eOrientation::top, b},
                {eOrientation::topRight, bl},
                {eOrientation::right, l},
                {eOrientation::bottomRight, tl},
                {eOrientation::bottom, t}};
        if(randomize) {
            std::random_shuffle(neighs.begin(), neighs.end());
        }

        for(const auto& n : neighs) {
            const auto& tp = n.second;
            if(tp.first && *tp.second == dist - 1) {
                path.emplace_back(n.first);
                return bestFinder(tp);
            }
        }

        return false;
    };

    const bool r = bestFinder(tileGetter(bestFinishX, bestFinishY));
    if(!r) return false;
    std::reverse(path.begin(), path.end());
    return true;
}
