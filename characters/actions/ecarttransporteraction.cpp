#include "ecarttransporteraction.h"

#include "../echaracter.h"
#include "buildings/ebuildingwithresource.h"
#include "engine/egameboard.h"
#include "emovetoaction.h"

eCartTransporterAction::eCartTransporterAction(
        eBuilding* const b,
        eTransporterBase* const c,
        const eCartActionType aType,
        const eResourceType resType,
        const eAction& foundAction,
        const eAction& failAction,
        const eAction& finishAction) :
    eActionWithComeback(c, failAction, finishAction),
    mBuilding(b),
    mBuildingType(b->type()),
    mBuildingRect(b->tileRect()),
    mActionType(aType),
    mResource(resType),
    mFoundAction(foundAction) {

}

eCartTransporterAction::eCartTransporterAction(
        eBuilding* const b,
        eTransporterBase* const c,
        const eCartActionType aType,
        const eResourceType resType,
        const eAction& failAction,
        const eAction& finishAction) :
    eCartTransporterAction(b, c, aType, resType,
                           []() {}, failAction, finishAction) {

}

void eCartTransporterAction::increment(const int by) {
    if(!currentAction()) findTarget();
    eActionWithComeback::increment(by);
}

void eCartTransporterAction::findTarget() {
    const auto c = character();

    using eFinalTile = std::function<bool(eThreadTile*)>;
    eFinalTile finalTile;
    const auto resType = mResource;
    const auto buildingRect = mBuildingRect;

    const auto bx = std::make_shared<int>(0);
    const auto by = std::make_shared<int>(0);

    if(mActionType == eCartActionType::give) {
        finalTile = [resType, buildingRect, bx, by](eThreadTile* const t) {
            if(!t->isUnderBuilding()) return false;
            const SDL_Point p{t->x(), t->y()};
            const bool r = SDL_PointInRect(&p, &buildingRect);
            if(r) return false;
            const auto& ub = t->underBuilding();
            const int rsl = ub.resourceSpaceLeft(resType);
            const bool res = rsl > 0;
            if(res) {
                *bx = t->x();
                *by = t->y();
            }
            return res;
        };
    } else { // take
        const auto srcType = mBuildingType;
        finalTile = [resType, buildingRect, srcType, bx, by]
                    (eThreadTile* const t) {
            if(!t->isUnderBuilding()) return false;
            const SDL_Point p{t->x(), t->y()};
            const bool r = SDL_PointInRect(&p, &buildingRect);
            if(r) return false;
            const auto& ub = t->underBuilding();
            const auto ubt = ub.type();
            if((ubt == eBuildingType::granary ||
                ubt == eBuildingType::warehouse) &&
               (srcType == eBuildingType::granary ||
                srcType == eBuildingType::warehouse)) {
                const auto gets = ub.gets();
                if(static_cast<bool>(gets & resType)) return false;
            }

            const int rsl = ub.resourceCount(resType);
            const bool res = rsl > 0;
            if(res) {
                *bx = t->x();
                *by = t->y();
            }
            return res;
        };
    }
    const stdptr<eCartTransporterAction> tptr(this);

    const auto walkable = [buildingRect](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        const bool r = SDL_PointInRect(&p, &buildingRect);
        if(r) return true;
        return t->hasRoad();
    };

    const auto finishAction = [tptr, this, bx, by]() {
        if(!tptr) return;
        const bool r = resourceAction(*bx, *by);
        if(r) {
            goBack2();
        } else {
            findTarget();
        }
    };

    const auto failFunc = [tptr]() {
        if(tptr) tptr->setState(eCharacterActionState::failed);
    };

    const auto a = e::make_shared<eMoveToAction>(c, failFunc, finishAction);

    a->setFoundAction([tptr, c]() {
        if(!tptr) return;
        tptr->mFoundAction();
        c->setActionType(eCharacterActionType::walk);
    });
    a->setRemoveLastTurn(true);
    a->setMaxDistance(200);
    a->start(finalTile, walkable);

    setCurrentAction(a);
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

bool eCartTransporterAction::resourceAction(const int bx, const int by) {
    const auto c = static_cast<eCartTransporter*>(character());
    const auto t = c->tile();
    auto& brd = c->getBoard();
    if(!t) {
        setState(eCharacterActionState::failed);
        return false;
    }
    const auto nn = brd.tile(bx, by);
    if(!nn) return false;
    const auto b = nn->underBuilding();
    if(!b) return false;
    if(const auto rb = dynamic_cast<eBuildingWithResource*>(b)) {
        const auto rt = c->resType();
        const int rc = c->resCount();

        if(mActionType == eCartActionType::give) {
            if(rt == eResourceType::none) return false;
            const int a = rb->add(rt, rc);
            c->setResource(rt, rc - a);
            return c->resCount() == 0;
        } else {
            if(rt != eResourceType::none &&
               rt != mResource) return false;
            const int t = rb->take(mResource, 8 - rc);
            c->setResource(mResource, t + rc);
            return c->resCount() > 0;
        }
    }
    return false;
}
