#include "ecarttransporteraction.h"

#include "../echaracter.h"
#include "buildings/ebuildingwithresource.h"
#include "engine/egameboard.h"
#include "emovetoaction.h"

eCartTransporterAction::eCartTransporterAction(
        eCharacter* const c,
        eBuildingWithResource* const b) :
    eActionWithComeback(c, eCharActionType::cartTransporterAction),
    mBuilding(b) {}

eCartTransporterAction::eCartTransporterAction(eCharacter* const c) :
    eCartTransporterAction(c, nullptr){}

void eCartTransporterAction::increment(const int by) {
    updateWaiting();
    eActionWithComeback::increment(by);
}

bool eCartTransporterAction::decide() {
    const auto c = static_cast<eCartTransporter*>(character());
    const bool r = eWalkableHelpers::sTileUnderBuilding(
                       c->tile(), mBuilding);
    const int count = c->resCount();
    const auto res = c->resType();
    bool continuee = false;
    if(mTask.fMaxCount > 0 && mTask.fResource == res) {
        if(mTask.fType == eCartActionType::take) {
            const int max = res == eResourceType::sculpture ? 1 : 4;
            const int space = max - count;
            continuee = space > 0;
        } else { // give
            continuee = count > 0;
        }
    }
    if(r || mWaitOutside) {
        if(mTask.fMaxCount > 0) {
            finishResourceAction(mTask);
            clearTask();
        }
        if(mNoTarget) {
            mNoTarget = false;
            const bool hr = c->hasResource();
            if(!hr || mWaitOutside) wait(1000);
            else if(hr) waitOutside();
        } else {
            int cc = c->resCount();
            if(cc > 0) {
                const auto supp = support();
                if(supp & eCartActionTypeSupport::take) {
                    const auto rt = c->resType();
                    const int r = mBuilding->add(rt, cc);
                    c->take(rt, r);
                    cc = c->resCount();
                    if(cc > 0) {
                        const int s = mBuilding->stash(rt, cc);
                        c->take(rt, s);
                        cc = c->resCount();
                    }
                }
                if(cc > 0 && supp & eCartActionTypeSupport::give) {
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
    } else if(continuee && !mNoTarget) {
        findTarget(mTask);
    } else {
        goBack();
    }
    return true;
}

eCartActionTypeSupport eCartTransporterAction::support() const {
    const auto c = character();
    const auto ct = static_cast<eCartTransporter*>(c);
    return ct->support();
}

eResourceType eCartTransporterAction::supportsResource() const {
    const auto c = character();
    const auto ct = static_cast<eCartTransporter*>(c);
    return ct->supportsResource();
}

void eCartTransporterAction::findTarget() {
    const auto tasks = mBuilding->cartTasks();
    const auto supp = support();
    if(supp == eCartActionTypeSupport::both) {
        findTarget(tasks);
    } else {
        std::vector<eCartTask> handled;
        const bool supportGive = supp & eCartActionTypeSupport::give;
        const bool supportTake = supp & eCartActionTypeSupport::take;
        for(const auto& t : tasks) {
            if(t.fType == eCartActionType::give && !supportGive) continue;
            if(t.fType == eCartActionType::take && !supportTake) continue;
            const auto r = t.fResource;
            const auto sr = supportsResource();
            const bool spprts = static_cast<bool>(r & sr);
            if(spprts) handled.push_back(t);
        }
        findTarget(handled);
    }
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
                   bType == eBuildingType::granary ||
                   bType == eBuildingType::tradePost) {
                    const bool g = ub.gets(res);
                    if(g) continue;
                }
                const bool has = ub.resourceHas(res);
                if(has) found = true;
            } else { // give
                const bool e = ub.empties(res);
                if(e) continue;
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
                *bx = t->x();
                *by = t->y();
                break;
            }
        }
        return found;
    };
    const stdptr<eCartTransporterAction> tptr(this);

    const auto finishAction = std::make_shared<eCTA_findTargetFinish>(
                                  board(), this);

    const auto a = e::make_shared<eMoveToAction>(c);
    a->setFinishAction(finishAction);

    a->setFoundAction([tptr, this, c, ttask, bx, by, finishAction]() {
        finishAction->setXY(*bx, *by);
        if(!tptr) return;
        mWaitOutside = false;
        mTask = *ttask;
        startResourceAction(mTask);
        c->setActionType(eCharacterActionType::walk);
    });
    a->setFindFailAction([tptr, this]() {
        if(!tptr) return;
        mNoTarget = true;
    });
    a->setRemoveLastTurn(true);
    if(const auto cart = dynamic_cast<eCartTransporter*>(c)) {
        a->setMaxFindDistance(cart->maxDistance());
    }
    const auto w = eWalkableObject::sCreateRect(
                       buildingRect, eWalkableObject::sCreateRoadAvenue());
    a->start(finalTile, w);

    setCurrentAction(a);
}

void eCartTransporterAction::goBack() {
    eActionWithComeback::goBack(mBuilding, eWalkableObject::sCreateRoadAvenue());
}

void eCartTransporterAction::targetResourceAction(const int bx, const int by) {
    const auto c = character();
    const auto ct = static_cast<eCartTransporter*>(c);
    auto& brd = ct->getBoard();
    const auto t = brd.tile(bx, by);
    const auto b = t->underBuilding();
    if(!b) return;
    const auto rb = dynamic_cast<eBuildingWithResource*>(b);
    targetResourceAction(rb);
}

void eCartTransporterAction::targetResourceAction(eBuildingWithResource* const rb) {
    if(!rb) return;
    const auto c = character();
    const auto ct = static_cast<eCartTransporter*>(c);
    const int takenGiven = targetProcessTask(rb, mTask);
    mTask.fMaxCount -= takenGiven;

    auto tasks = mBuilding->cartTasks();
    const auto supp = support();
    const bool supportGive = supp & eCartActionTypeSupport::give;
    const bool supportTake = supp & eCartActionTypeSupport::take;
    for(auto& task : tasks) {
        if(task.fType == eCartActionType::give && !supportGive) continue;
        if(task.fType == eCartActionType::take && !supportTake) continue;
        if(task.fType == eCartActionType::take) {
            if(ct->resType() == task.fResource) {
                task.fMaxCount -= ct->resCount();
            }
        }
        targetProcessTask(rb, task);
    }
}

int eCartTransporterAction::targetProcessTask(eBuildingWithResource* const rb,
                                              const eCartTask& task) {
    if(task.fMaxCount <= 0) return 0;
    const auto c = static_cast<eCartTransporter*>(character());
    const auto res = c->resType();
    const int count = c->resCount();
    const auto tres = task.fResource;
    const int max = tres == eResourceType::sculpture ? 1 : 4;
    if(task.fType == eCartActionType::take) {
        if(count > 0 && res != tres) return 0;
        const int space = max - count;
        if(space <= 0) return 0;
        const int toTake = std::min(space, task.fMaxCount);
        const int taken = rb->take(tres, toTake);
        c->setResource(tres, taken + count);
        if(taken > 0) return taken;
    } else { // give
        if(count == 0) return 0;
        if(res != tres) return 0;
        const int toAdd = std::min(count, task.fMaxCount);
        const int added = rb->add(tres, toAdd);
        c->setResource(tres, count - added);
        return added;
    }
    return 0;
}

void eCartTransporterAction::startResourceAction(const eCartTask& task) {
    const auto c = static_cast<eCartTransporter*>(character());
    if(c->resCount() > 0) return;
    if(task.fMaxCount <= 0) return;
    if(task.fType == eCartActionType::take) {
        if(c->resCount() == 0) c->setResource(task.fResource, 0);
        return;
    } else { //give
        const int max = eResourceTypeHelpers::transportSize(task.fResource);
        const int mmax = std::min(max, task.fMaxCount);
        const int t = mBuilding->take(task.fResource, mmax);
        if(t <= 0) {
            clearTask();
        } else {
            c->setResource(task.fResource, t);
        }
    }
}

void eCartTransporterAction::finishResourceAction(const eCartTask& task) {
    const auto c = static_cast<eCartTransporter*>(character());
    if(c->resCount() <= 0) return disappear();
    if(task.fMaxCount <= 0) return;
    if(task.fResource != c->resType()) return;
    if(task.fType == eCartActionType::take) {
        const int crc = c->resCount();
        const int a = mBuilding->add(task.fResource, crc);
        c->setResource(task.fResource, crc - a);
        if(c->resCount() <= 0) return disappear();
    } else { //give
        return;
    }
}

void eCartTransporterAction::read(eReadStream& src) {
    eActionWithComeback::read(src);
    src.readBuilding(&board(), [this](eBuilding* const b) {
        mBuilding = static_cast<eBuildingWithResource*>(b);
    });

    src >> mTask.fMaxCount;
    src >> mTask.fResource;
    src >> mTask.fType;

    src >> mUpdateWaiting;
    src >> mNoTarget;
    src >> mWaitOutside;
}

void eCartTransporterAction::write(eWriteStream& dst) const {
    eActionWithComeback::write(dst);
    dst.writeBuilding(mBuilding);

    dst << mTask.fMaxCount;
    dst << mTask.fResource;
    dst << mTask.fType;

    dst << mUpdateWaiting;
    dst << mNoTarget;
    dst << mWaitOutside;
}

void eCartTransporterAction::updateWaiting() {
    const auto c = static_cast<eCartTransporter*>(character());
    const bool r = eWalkableHelpers::sTileUnderBuilding(
                       c->tile(), mBuilding);
    c->setWaiting(mWaitOutside || r);
}

void eCartTransporterAction::waitOutside() {
    if(mWaitOutside) return;
    const auto neighs = mBuilding->neighbours();
    if(neighs.empty()) return;
    const auto c = character();
    eTile* tt = nullptr;
    for(const auto t : neighs) {
        if(!t->hasRoad()) continue;
        tt = t;
        break;
    }
    if(!tt) return;
    mWaitOutside = true;

    const auto stand = std::make_shared<eCTA_waitOutsideFinish>(
                           board(), this);
    const auto a = e::make_shared<eMoveToAction>(c);
    a->setFinishAction(stand);
    a->setFailAction(stand);

    const auto buildingRect = mBuilding->tileRect();
    const auto w = eWalkableObject::sCreateRect(
                       buildingRect, eWalkableObject::sCreateRoadAvenue());
    a->start(tt, w);

    setCurrentAction(a);
}

void eCartTransporterAction::spread() {
    const auto c = character();
    const auto ct = static_cast<eCartTransporter*>(c);
    if(!ct->isOx()) {
        c->setActionType(eCharacterActionType::stand);
        return;
    }

    const auto stand = std::make_shared<eCTA_spreadFinish>(
                           board(), ct);
    const auto a = e::make_shared<eMoveToAction>(c);
    a->setFailAction(stand);
    a->setFinishAction(stand);

    const auto ctt = ct->tile();
    const int tx = ctt->x();
    const int ty = ctt->y();

    const auto finalFunc = [tx, ty](eTileBase* const t) {
        const int ttx = t->x();
        const int tty = t->y();
        const int dx = tx - ttx;
        const int dy = ty - tty;
        return sqrt(dx*dx + dy*dy) > 4;
    };
    a->setRemoveLastTurn(true);
    a->start(finalFunc, eWalkableObject::sCreateRoadAvenue());

    setCurrentAction(a);
}

void eCartTransporterAction::clearTask() {
    mTask.fMaxCount = 0;
    setCurrentAction(nullptr);
}

void eCartTransporterAction::disappear() {
    const auto c = character();
    const auto ct = static_cast<eCartTransporter*>(c);
    if(ct->resCount() == 0) ct->setResource(eResourceType::wine, 0);
}
