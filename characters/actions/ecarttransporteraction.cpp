#include "ecarttransporteraction.h"

#include "../echaracter.h"
#include "buildings/ebuildingwithresource.h"
#include "engine/egameboard.h"
#include "emovetoaction.h"

eCartTransporterAction::eCartTransporterAction(
        eBuildingWithResource* const b,
        eCartTransporter* const c,
        const eAction& failAction,
        const eAction& finishAction) :
    eActionWithComeback(c, failAction, finishAction),
    mBuilding(b) {}

bool eCartTransporterAction::decide() {
    const auto c = static_cast<eCartTransporter*>(character());
    const bool r = eWalkableHelpers::sTileUnderBuilding(
                       c->tile(), mBuilding);
    if(r) {
        if(mTask.fMaxCount > 0) {
            finishResourceAction(mTask);
            clearTask();
        }
        if(mNoTarget) {
            mNoTarget = false;
            wait(1000);
        } else {
            int cc = c->resCount();
            if(cc > 0) {
                const auto rt = c->resType();
                const int r = mBuilding->add(rt, cc);
                c->setResource(rt, cc - r);
                int cc = c->resCount();
                if(cc > 0) {
                    eCartTask task;
                    task.fMaxCount = cc;
                    task.fResource = c->resType();
                    task.fType = eCartActionType::give;
                    findTarget(task);
                }
            } else {
                findTarget();
            }
        }
    } else {
        goBack();
    }
    return true;
}

void eCartTransporterAction::findTarget() {
    const auto tasks = mBuilding->cartTasks();
    findTarget(tasks);
}

void eCartTransporterAction::findTarget(const eCartTask& task) {
    findTarget(std::vector<eCartTask>{task});
}

void eCartTransporterAction::findTarget(const std::vector<eCartTask>& tasks) {
    if(tasks.empty()) return;
    const auto c = character();

    const auto buildingRect = mBuilding->tileRect();

    const auto bx = std::make_shared<int>(0);
    const auto by = std::make_shared<int>(0);

    const auto ttask = std::make_shared<eCartTask>();

    const auto bType = mBuilding->type();
    const auto finalTile = [buildingRect, bType, ttask, tasks, bx, by]
                           (eThreadTile* const t) {
        if(!t->isUnderBuilding()) return false;
        const bool r = eWalkableHelpers::sTileUnderBuilding(t, buildingRect);
        if(r) return false;
        bool found = false;
        const auto& ub = t->underBuilding();
        for(const auto& task : tasks) {
            const auto res = task.fResource;
            if(task.fType == eCartActionType::take) {
                if(bType == eBuildingType::warehouse ||
                   bType == eBuildingType::granary) {
                    const auto gts = ub.gets();
                    const bool gtsRes = static_cast<bool>(gts & res);
                    if(gtsRes) continue;
                }
                const bool has = ub.resourceHas(res);
                if(has) found = true;
            } else { // give
                const auto ets = ub.empties();
                const bool etsRes = static_cast<bool>(ets & res);
                if(etsRes) continue;
                const bool has = ub.resourceHasSpace(res);
                if(has) found = true;
            }
            if(found) {
                int mc;
                if(task.fType == eCartActionType::take) {
                    const int c = ub.resourceCount(res);
                    mc = std::min(c, task.fMaxCount);
                } else { // give
                    const int c = ub.resourceSpaceLeft(res);
                    mc = std::min(c, task.fMaxCount);
                }
                if(mc <= 0) continue;
                *ttask = task;
                ttask->fMaxCount = mc;
                *bx = t->x();
                *by = t->y();
                break;
            }
        }
        return found;
    };
    const stdptr<eCartTransporterAction> tptr(this);

    const auto finishAction = [tptr, this, bx, by]() {
        if(!tptr) return;
        targetResourceAction(*bx, *by);
    };

    const auto a = e::make_shared<eMoveToAction>(c, [](){}, finishAction);

    a->setFoundAction([tptr, this, c, ttask]() {
        if(!tptr) return;
        mTask = *ttask;
        startResourceAction(mTask);
        c->setActionType(eCharacterActionType::walk);
    });
    a->setFindFailAction([tptr, this]() {
        if(!tptr) return;
        mNoTarget = true;
    });
    a->setRemoveLastTurn(true);
    a->setMaxDistance(200);
    const auto w = eWalkableHelpers::sBuildingWalkable(
                       buildingRect, eWalkableHelpers::sRoadWalkable);
    a->start(finalTile, w);

    setCurrentAction(a);
}

void eCartTransporterAction::goBack() {
    eActionWithComeback::goBack(mBuilding, eWalkableHelpers::sRoadWalkable);
}

void eCartTransporterAction::targetResourceAction(const int bx, const int by) {
    const auto c = static_cast<eCartTransporter*>(character());
    auto& brd = c->getBoard();
    const auto t = brd.tile(bx, by);
    const auto b = t->underBuilding();
    if(!b) return;
    const auto rb = dynamic_cast<eBuildingWithResource*>(b);
    targetResourceAction(rb);
}

void eCartTransporterAction::targetResourceAction(eBuildingWithResource* const rb) {
    if(!rb) return;
    targetProcessTask(rb, mTask);
    auto tasks = mBuilding->cartTasks();
    for(const auto task : tasks) {
        const bool r = targetProcessTask(rb, task);
        if(r) return;
    }
}

bool eCartTransporterAction::targetProcessTask(eBuildingWithResource* const rb,
                                               const eCartTask& task) {
    if(task.fMaxCount <= 0) return false;
    const auto c = static_cast<eCartTransporter*>(character());
    const auto res = c->resType();
    const int count = c->resCount();
    const auto tres = task.fResource;
    const int max = tres == eResourceType::sculpture ? 1 : 4;
    if(task.fType == eCartActionType::take) {
        if(count > 0 && res != tres) return false;
        const int space = max - count;
        if(space <= 0) return false;
        const int toTake = std::min(space, task.fMaxCount);
        const int taken = rb->take(tres, toTake);
        c->setResource(tres, taken + count);
        if(taken > 0) return true;
    } else { // give
        if(count == 0) return false;
        if(res != tres) return false;
        const int toAdd = std::min(count, task.fMaxCount);
        const int added = rb->add(tres, toAdd);
        c->setResource(tres, count - added);
        if(added > 0) return true;
    }
    return false;
}

void eCartTransporterAction::startResourceAction(const eCartTask& task) {
    const auto c = static_cast<eCartTransporter*>(character());
    if(c->resCount() > 0) return;
    if(task.fMaxCount <= 0) return;
    if(task.fType == eCartActionType::take) {
        if(c->resCount() == 0) c->setResource(task.fResource, 0);
        return;
    } else { //give
        const int t = mBuilding->take(task.fResource, task.fMaxCount);
        if(t <= 0) {
            clearTask();
        } else {
            c->setResource(task.fResource, t);
        }
    }
}

void eCartTransporterAction::finishResourceAction(const eCartTask& task) {
    const auto c = static_cast<eCartTransporter*>(character());
    if(c->resCount() <= 0) return;
    if(task.fMaxCount <= 0) return;
    if(task.fResource != c->resType()) return;
    if(task.fType == eCartActionType::take) {
        const int crc = c->resCount();
        const int a = mBuilding->add(task.fResource, crc);
        c->setResource(task.fResource, crc - a);
    } else { //give
        return;
    }
}

void eCartTransporterAction::clearTask() {
    mTask.fMaxCount = 0;
    setCurrentAction(nullptr);
}
