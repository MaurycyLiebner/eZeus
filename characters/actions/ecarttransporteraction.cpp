#include "ecarttransporteraction.h"

#include "../echaracter.h"
#include "engine/ethreadpool.h"
#include "epathfindtask.h"
#include "ewaitaction.h"
#include "buildings/ebuildingwithresource.h"

eCartTransporterAction::eCartTransporterAction(
        const SDL_Rect& buildingRect,
        eCartTransporter* const c,
        const eCartActionType aType,
        const eResourceType resType,
        const eAction& foundAction,
        const eAction& failAction,
        const eAction& finishAction) :
    eActionWithComeback(c, failAction, finishAction),
    mActionType(aType),
    mResource(resType),
    mBuildingRect(buildingRect),
    mFoundAction(foundAction) {

}

eCartTransporterAction::eCartTransporterAction(
        const SDL_Rect& buildingRect,
        eCartTransporter* const c,
        const eCartActionType aType,
        const eResourceType resType,
        const eAction& failAction,
        const eAction& finishAction) :
    eCartTransporterAction(buildingRect, c, aType, resType,
                           []() {}, failAction, finishAction) {

}

void eCartTransporterAction::increment(const int by) {
    if(!currentAction()) findTarget();
    eActionWithComeback::increment(by);
}

void eCartTransporterAction::findTarget() {
    const auto c = character();
    const auto t = c->tile();
    const auto& brd = c->board();
    const auto tp = brd.threadPool();

    const int tx = t->x();
    const int ty = t->y();

    const auto startTile = [tx, ty](eThreadBoard& board) {
        return board.absTile(tx, ty);
    };
    using eFinalTile = std::function<bool(eThreadTile*)>;
    eFinalTile finalTile;
    const auto resType = mResource;
    if(mActionType == eCartActionType::give) {
        finalTile = [resType](eThreadTile* const t) {
            if(!t->isUnderBuilding()) return false;
            const auto& ub = t->underBuilding();
            const int rsl = ub.resourceSpaceLeft(resType);
            return rsl > 0;
        };
    } else {
        finalTile = [resType](eThreadTile* const t) {
            if(!t->isUnderBuilding()) return false;
            const auto& ub = t->underBuilding();
            const int rsl = ub.resourceCount(resType);
            return rsl > 0;
        };
    }
    const stdptr<eCharacterAction> tptr(this);
    const auto failFunc = [tptr]() {
        if(tptr) tptr->setState(eCharacterActionState::failed);
    };
    const auto rect = mBuildingRect;
    const auto walkable = [rect](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        const bool r = SDL_PointInRect(&p, &rect);
        if(r) return true;
        return t->hasRoad();
    };
    const auto finishFunc = [tptr, this, c, walkable](
                            std::vector<eOrientation> path) {
        if(!tptr) return;
        mFoundAction();
        if(path.empty()) {
            tptr->setState(eCharacterActionState::failed);
            return;
        }
        mBuildingO = path.front();
        path.erase(path.begin());
        const auto finishAction = [tptr, this]() {
            if(!tptr) return;
            const bool r = resourceAction();
            if(r) {
                goBack2();
            } else {
                findTarget();
            }
        };

        if(path.empty()) {
            finishAction();
        } else {
            const auto failFunc = [tptr, this]() {
                if(tptr) findTarget();
            };

            c->setActionType(eCharacterActionType::walk);
            const auto a = e::make_shared<eMovePathAction>(
                               c, path, walkable,
                               failFunc, finishAction);
            setCurrentAction(a);
        }
    };

    const auto pft = new ePathFindTask(startTile, walkable,
                                       finalTile, finishFunc,
                                       failFunc, true, 200);
    tp->queueTask(pft);

    setCurrentAction(e::make_shared<eWaitAction>(c, []() {}, []() {}));
}

void eCartTransporterAction::goBack2() {
    const auto rect = mBuildingRect;
    const auto walkable = [rect](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        const bool r = SDL_PointInRect(&p, &rect);
        if(r) return true;
        return t->hasRoad();
    };
    eActionWithComeback::goBack(walkable);
}

bool eCartTransporterAction::resourceAction() {
    const auto c = static_cast<eCartTransporter*>(character());
    const auto t = c->tile();
    if(!t) {
        setState(eCharacterActionState::failed);
        return false;
    }
    const auto nn = t->neighbour<eTile>(mBuildingO);
    if(!nn) return false;
    const auto b = nn->underBuilding();
    if(!b) return false;
    if(const auto rb = dynamic_cast<eBuildingWithResource*>(b)) {
        const auto rt = c->resourceType();
        const int rc = c->resourceCount();

        if(mActionType == eCartActionType::give) {
            if(rt == eResourceType::none) return false;
            const int a = rb->add(rt, rc);
            c->setResource(rt, rc - a);
            return c->resourceCount() == 0;
        } else {
            if(rt != eResourceType::none &&
               rt != mResource) return false;
            const int t = rb->take(mResource, 8 - rc);
            c->setResource(mResource, t + rc);
            return c->resourceCount() > 0;
        }
    }
    return false;
}