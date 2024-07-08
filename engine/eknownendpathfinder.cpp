#include "eknownendpathfinder.h"

#include <deque>
#include <map>

#include "engine/etilebase.h"
#include "engine/egameboard.h"

eKnownEndPathFinder::eKnownEndPathFinder(
        const eTileWalkable& walkable,
        eTileBase* const endTile) :
    mWalkable(walkable),
    mEndTile(endTile) {}

int manhattanDistance(const int x0, const int y0,
                      const int x1, const int y1) {
    return std::abs(x0 - x1) + std::abs(y0 - y1);
}

int manhattanDistance(const eTileBase* const t0,
                      const eTileBase* const t1) {
    return manhattanDistance(t0->x(), t0->y(),
                             t1->x(), t1->y());
}

bool eKnownEndPathFinder::findPath(
        eTileBase* const start,
        const int maxDist,
        const bool onlyDiagonal,
        const int srcW, const int srcH,
        const eTileDistance& distance) {
    if(!start) return false;

    const bool finishOnFound = mMode == ePathFinderMode::findSingle;

    mData = ePathFindData();
    mData.fOnlyDiagonal = onlyDiagonal;
    mData.fStart = start;

    if(finishOnFound && mEndTile == start) {
        mData.fFound = true;
        mData.fDistance = 0;
        mData.fFinalX = start->x();
        mData.fFinalY = start->y();
        return true;
    }

    auto& brd = mData.fBoard;
    {
//        const int startX = start->dx();
//        const int startY = start->dy();

//        const int minX = std::max(0, startX - maxDist);
//        int minY = std::max(0, startY - maxDist);
//        if(minY % 2) {
//            minY--;
//        }

//        const int maxX = std::min(srcW, startX + maxDist);
//        const int maxY = std::min(srcH, startY + maxDist);

//        brd = ePathBoard(minX, minY, maxX - minX, maxY - minY);
        brd = ePathBoard(0, 0, srcW, srcH);
    }

    std::map<int, std::vector<eTilePair>> toProcess;
    const auto processTile = [&](eTilePair* const tile,
                                 const int x, const int y,
                                 const int dist) {
        if(x == 0 && y == 0) return;
        const bool notDiagonal = x != 0 && y != 0;
        if(onlyDiagonal && notDiagonal) return;
        auto tt = tileGetter(brd, tile->first, x, y);
        if(!tt.first || !tt.second) return;
        const int dinc = distance ? distance(tt.first) : 1;
        const int newDist = dist + dinc;
        if(mEndTile == tt.first) {
            *tt.second = newDist;
            const int ttx = tt.first->x();
            const int tty = tt.first->y();
            mData.fFound = true;
            mData.fDistance = newDist;
            mData.fFinalX = ttx;
            mData.fFinalY = tty;
            if(finishOnFound) return;
        }
        if(!mWalkable(tt.first)) return;
        if(notDiagonal) {
            if(x == -1 && y == -1) { // top
                {
                    const auto ttt = tileGetter(brd, tile->first, 0, -1);
                    if(ttt.first && ttt.second) {
                        if(!mWalkable(ttt.first)) return;
                    }
                }
                {
                    const auto ttt = tileGetter(brd, tile->first, -1, 0);
                    if(ttt.first && ttt.second) {
                        if(!mWalkable(ttt.first)) return;
                    }
                }
            } else if(x == -1 && y == 1) { // left
                {
                    const auto ttt = tileGetter(brd, tile->first, -1, 0);
                    if(ttt.first && ttt.second) {
                        if(!mWalkable(ttt.first)) return;
                    }
                }
                {
                    const auto ttt = tileGetter(brd, tile->first, 0, 1);
                    if(ttt.first && ttt.second) {
                        if(!mWalkable(ttt.first)) return;
                    }
                }
            } else if(x == 1 && y == 1) { // bottom
                {
                    const auto ttt = tileGetter(brd, tile->first, 1, 0);
                    if(ttt.first && ttt.second) {
                        if(!mWalkable(ttt.first)) return;
                    }
                }
                {
                    const auto ttt = tileGetter(brd, tile->first, 0, 1);
                    if(ttt.first && ttt.second) {
                        if(!mWalkable(ttt.first)) return;
                    }
                }
            } else if(x == 1 && y == -1) { // right
                {
                    const auto ttt = tileGetter(brd, tile->first, 1, 0);
                    if(ttt.first && ttt.second) {
                        if(!mWalkable(ttt.first)) return;
                    }
                }
                {
                    const auto ttt = tileGetter(brd, tile->first, 0, -1);
                    if(ttt.first && ttt.second) {
                        if(!mWalkable(ttt.first)) return;
                    }
                }
            }
        }
        if(*tt.second > newDist) {
            *tt.second = newDist;
            toProcess[manhattanDistance(mEndTile, tt.first)].push_back(tt);
        }
    };
    const auto pathFinder = [&](eTilePair& from) {
        if(!from.first || !from.second) return;
        const int dist = *from.second;
        if(dist > maxDist) return;

        for(const int x : {0, 1, -1}) {
            for(const int y : {0, 1, -1}) {
                processTile(&from, x, y, dist);
            }
        }
    };

    const auto t = tileGetter(brd, start, 0, 0);
    if(!t.first || !t.second) return false;
    *t.second = 0;
    toProcess[manhattanDistance(mEndTile, t.first)].push_back(t);
    while((!mData.fFound || !finishOnFound) && !toProcess.empty()) {
        const auto it = toProcess.begin();
        auto& vec = it->second;
        auto t = vec.back();
        vec.pop_back();
        if(vec.empty()) toProcess.erase(it);
        pathFinder(t);
    }
    return mData.fFound;
}

bool eKnownEndPathFinder::extractPath(
        std::vector<eOrientation>& path) {
    if(!mData.fFound) return false;
    path.clear();
    path.reserve(mData.fDistance);
    return extractPath([&](const eNeigh& n) {
        path.emplace_back(n.first);
    });
}

bool eKnownEndPathFinder::extractPath(
        std::vector<std::pair<int, int>>& path) {
    if(!mData.fFound) return false;
    path.clear();
    path.reserve(mData.fDistance);
    return extractPath([&](const eNeigh& n) {
        const auto t = n.second.first;
        path.emplace_back(std::pair<int, int>{t->x(), t->y()});
    });
}

bool eKnownEndPathFinder::extractPath(
        std::vector<eTile*>& path, eGameBoard& board) {
    if(!mData.fFound) return false;
    path.clear();
    path.reserve(mData.fDistance);
    return extractPath([&](const eNeigh& n) {
        const auto t = n.second.first;
        path.emplace_back(board.tile(t->x(), t->y()));
    });
}

bool eKnownEndPathFinder::extractPath(
        const ePathFunc& pathFunc) {
    auto& brd = mData.fBoard;
    using eBFinder = std::function<bool(const eTilePair&)>;
    eBFinder bestFinder;
    bestFinder = [&](const eTilePair& from) {
        if(!from.first || !from.second) return false;
        const auto tile = from.first;
        const int tx = tile->x();
        const int ty = tile->y();
        const int dtx = mData.fStart->x();
        const int dty = mData.fStart->y();
        if(tx == dtx && ty == dty) return true;

        const auto tr = tileGetter(brd, tile, 0, -1);
        const auto br = tileGetter(brd, tile, 1, 0);
        const auto bl = tileGetter(brd, tile, 0, 1);
        const auto tl = tileGetter(brd, tile, -1, 0);

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

        int distP = __INT_MAX__;
        eNeigh best{eOrientation::topRight, {nullptr, &distP}};
        for(const auto& n : neighs) {
            const auto& tp = n.second;
            if(!tp.first || !tp.second) continue;

            if(mWalkable(tp.first)) {
                const int ddist = *tp.second;
                if(ddist < *best.second.second) {
                    best = n;
                }
            }
        }
        if(best.second.first) {
            pathFunc(best);
            return bestFinder(best.second);
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

bool eKnownEndPathFinder::extractData(ePathFindData& data) {
    if(!mData.fFound) return false;
    std::swap(mData, data);
    return true;
}
