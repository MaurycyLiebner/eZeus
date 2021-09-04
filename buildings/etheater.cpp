#include "etheater.h"

#include "characters/eactor.h"
#include "characters/actions/epatrolaction.h"
#include "textures/egametextures.h"
#include "characters/actions/emovepathaction.h"
#include "engine/epathfinder.h"
#include "epathfindtask.h"
#include "engine/ethreadpool.h"
#include "characters/actions/ewaitaction.h"

eTheater::eTheater(eGameBoard& board) :
    ePatrolBuilding(board, &eBuildingTextures::fTheater,
                    -1.25, -6.5,
                    &eBuildingTextures::fTheaterOverlay,
                    [this]() { return e::make_shared<eActor>(getBoard()); },
                    eBuildingType::theater, 5, 5, 18)  {
    setSpawnPatrolers(false);
}

void eTheater::timeChanged(const int by) {
    (void)by;
    const int t = time();
    mActor -= by;
    if(mActor < 0) setSpawnPatrolers(false);
    if(!mChar && t >= mSpawnTime) {
        spawnGetActor();
        mSpawnTime = t + mWaitTime;
    }
    ePatrolBuilding::timeChanged(by);
}

void eTheater::spawnGetActor() {
    const auto t = tile();
    const auto tp = getBoard().threadPool();

    const int tx = t->x();
    const int ty = t->y();

    const auto startTile = [tx, ty](eThreadBoard& board) {
        return board.absTile(tx, ty);
    };
    const auto buildingRect = tileRect();
    const auto school = std::make_shared<std::pair<int, int>>(0, 0);
    const auto finalTile = [school](eThreadTile* const t) {
        school->first = t->x();
        school->second = t->y();
        return t->underBuildingType() == eBuildingType::dramaSchool;
    };
    const auto failFunc = []() {};
    const auto walkable = [buildingRect](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        const bool r = SDL_PointInRect(&p, &buildingRect);
        if(r) return true;
        return t->hasRoad();
    };
    const stdptr<eTheater> tptr(this);
    const auto finishFunc = [tptr, this, school, walkable](
                            std::vector<eOrientation> path) {
        if(!tptr) return;
        const auto finishAction = [tptr, this]() {
            if(!tptr) return;
            mActor = 2*mWaitTime;
            setSpawnPatrolers(true);
        };

        if(path.empty()) {
            finishAction();
        } else {
            std::reverse(path.begin(), path.end());
            path.erase(path.begin());
            for(auto& o : path) o = !o;

            const auto failFunc = []() {};
            auto& brd = getBoard();
            const auto c = e::make_shared<eActor>(brd);
            const auto t = brd.tile(school->first, school->second);
            c->changeTile(t);

            c->setActionType(eCharacterActionType::walk);
            const auto a = e::make_shared<eMovePathAction>(
                               c.get(), path, walkable,
                               failFunc, finishAction);
            c->setAction(a);
        }
    };

    const auto pft = new ePathFindTask(startTile, walkable,
                                       finalTile, finishFunc,
                                       failFunc, true, 200);
    tp->queueTask(pft);
}
