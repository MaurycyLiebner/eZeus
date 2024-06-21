#include "epatrolsourcebuilding.h"

#include "textures/egametextures.h"

#include "characters/actions/emovetoaction.h"
#include "engine/epathfinder.h"
#include "epathfindtask.h"
#include "engine/ethreadpool.h"
#include "engine/egameboard.h"
#include "characters/actions/walkable/ewalkableobject.h"
#include "evectorhelpers.h"
#include "epatroltarget.h"
#include "estadium.h"
#include "emuseum.h"

ePatrolSourceBuilding::ePatrolSourceBuilding(eGameBoard& board,
                                             const eBaseTex baseTex,
                                             const double overlayX,
                                             const double overlayY,
                                             const eOverlays overlays,
                                             const eTargets& targets,
                                             const eBuildingType type,
                                             const int sw, const int sh,
                                             const int maxEmployees,
                                             const eCharGenerator& charGen) :
    ePatrolBuilding(board, baseTex,  overlayX, overlayY,
                    overlays, charGen, type, sw, sh, maxEmployees),
    mTargets(targets) {
    for(const auto& t : mTargets) {
        (void)t;
        mTargetData.push_back({rand() % mSpawnWaitTime, -1});
    }
}

void ePatrolSourceBuilding::timeChanged(const int by) {
    ePatrolBuilding::timeChanged(by);
    if(enabled()) {
        const int iMax = mTargetData.size();
        for(int i = 0; i < iMax; i++) {
            int& spawnTime = mTargetData[i].fSpawnTime;
            spawnTime += by;
            if(spawnTime > mSpawnWaitTime) {
                spawnTime -= mSpawnWaitTime;
                spawn(i);
            }
        }
    }
}

void ePatrolSourceBuilding::read(eReadStream& src) {
    ePatrolBuilding::read(src);
    for(auto& t : mTargetData) {
        src >> t.fSpawnTime;
        src >> t.fLastId;
    }
}

void ePatrolSourceBuilding::write(eWriteStream& dst) const {
    ePatrolBuilding::write(dst);
    for(const auto& t : mTargetData) {
        dst << t.fSpawnTime;
        dst << t.fLastId;
    }
}

bool operator==(const SDL_Rect& r1, const SDL_Rect& r2) {
    return r1.x == r2.x && r1.y == r2.y &&
           r1.w == r2.w && r1.h == r2.h;
}

void ePatrolSourceBuilding::spawn(const int id) {
    auto& board = getBoard();
    const auto& target = mTargets[id];
    const auto targetType = target.second;
    if(targetType == eBuildingType::stadium) {
        const auto s = board.stadium();
        if(!s) return;
        return spawn(id, s);
    } else if(targetType == eBuildingType::museum) {
        const auto m = board.museum();
        if(!m) return;
        return spawn(id, m);
    }


    const auto t = centerTile();
    auto& tp = board.threadPool();

    const int tx = t->x();
    const int ty = t->y();

    const auto startTile = [tx, ty](eThreadBoard& board) {
        return board.tile(tx, ty);
    };
    using eTargetRects = std::vector<SDL_Rect>;
    const auto targetRects = std::make_shared<eTargetRects>();
    const auto tRect = tileRect();
    const auto finalTile = [targetType, targetRects](eThreadTile* const t) {
        const auto& ub = t->underBuilding();
        const auto ubt = ub.type();
        const bool found = ubt == targetType;
        if(found) {
            const auto ubr = ub.tileRect();
            const bool c = eVectorHelpers::contains(*targetRects, ubr);
            if(!c) targetRects->push_back(ubr);
        }
        return found;
    };
    const auto failFunc = []() {};
    const auto rw = eWalkableObject::sCreateRoad();
    const auto walkable = eWalkableObject::sCreateRect(tRect, rw);
    using ePath = std::vector<eOrientation>;
    const auto finishFunc = [this, walkable, targetRects, id](const ePath&) {
        if(targetRects->empty()) return;
        auto& targetData = mTargetData[id];
        const int lastId = targetData.fLastId;
        const int nTargets = targetRects->size();
        int newId = lastId + 1;
        if(newId >= nTargets) newId = 0;
        else if(newId < 0) newId = 0;
        const auto& targetRect = (*targetRects)[newId];
        targetData.fLastId = newId;

        auto& board = getBoard();
        const auto targetTile = board.tile(targetRect.x, targetRect.y);
        if(!targetTile) return spawn(id);
        const auto targetBuilding = targetTile->underBuilding();
        if(!targetBuilding) return spawn(id);
        spawn(id, targetBuilding);
    };

    const auto pft = new ePathFindTask(startTile, walkable,
                                       finalTile, finishFunc,
                                       failFunc, true, 200,
                                       nullptr, nullptr, true);
    tp.queueTask(pft);
}

void ePatrolSourceBuilding::spawn(const int id, eBuilding* const targetBuilding) {
    const auto patrolTarget = dynamic_cast<ePatrolTarget*>(targetBuilding);
    if(!patrolTarget) return spawn(id);

    const auto& target = mTargets[id];
    auto& board = getBoard();
    const auto c = eCharacter::sCreate(target.first, board);
    c->changeTile(centerTile());

    const auto finishAction = std::make_shared<ePT_spawnGetActorFinish>(
                                  board, patrolTarget);

    const auto a = e::make_shared<eMoveToAction>(c.get());
    a->setFinishAction(finishAction);
    c->setAction(a);
    c->setActionType(eCharacterActionType::walk);
    a->start(targetBuilding, eWalkableObject::sCreateRoad());
}
