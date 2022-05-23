#include "epatroltarget.h"

#include "characters/actions/epatrolaction.h"
#include "textures/egametextures.h"
#include "characters/actions/emovepathaction.h"
#include "engine/epathfinder.h"
#include "epathfindtask.h"
#include "engine/ethreadpool.h"
#include "characters/actions/ewaitaction.h"
#include "characters/echaracter.h"
#include "engine/egameboard.h"

ePatrolTarget::ePatrolTarget(eGameBoard& board,
                             const eBuildingType fromBuilding,
                             const eBaseTex baseTex,
                             const double overlayX,
                             const double overlayY,
                             const eOverlays overlays,
                             const eCharGenerator& charGen,
                             const eBuildingType type,
                             const int sw, const int sh,
                             const int maxEmployees) :
    ePatrolBuilding(board, baseTex,
                    overlayX, overlayY,
                    overlays, charGen,
                    type, sw, sh,
                    maxEmployees),
    mFromBuilding(fromBuilding),
    mCharGen(charGen) {

}

void ePatrolTarget::timeChanged(const int by) {
    const int t = time();
    mActor -= by;
    if(mActor < 0) setSpawnPatrolers(false);
    if(enabled()) {
        if(!mChar && t >= mSpawnTime) {
            spawnGetActor();
            mSpawnTime = t + mWaitTime;
        }
    }
    ePatrolBuilding::timeChanged(by);
}

void ePatrolTarget::spawnGetActor() {
    const auto t = centerTile();
    auto& tp = getBoard().threadPool();

    const int tx = t->x();
    const int ty = t->y();

    const auto startTile = [tx, ty](eThreadBoard& board) {
        return board.absTile(tx, ty);
    };
    const auto buildingRect = tileRect();
    const auto school = std::make_shared<std::pair<int, int>>(0, 0);
    const auto fromBuilding = mFromBuilding;
    const auto finalTile = [school, fromBuilding](eThreadTile* const t) {
        school->first = t->x();
        school->second = t->y();
        return t->underBuildingType() == fromBuilding;
    };
    const auto failFunc = []() {};
    const auto walkable = [buildingRect](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        const bool r = SDL_PointInRect(&p, &buildingRect);
        if(r) return true;
        return t->hasRoad();
    };
    const stdptr<ePatrolTarget> tptr(this);
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
            const auto c = mCharGen();
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
    tp.queueTask(pft);
}
