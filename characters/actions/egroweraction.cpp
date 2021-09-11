#include "egroweraction.h"

#include "epathfindtask.h"
#include "engine/ethreadpool.h"
#include "characters/actions/ewaitaction.h"
#include "buildings/eresourcebuilding.h"

eGrowerAction::eGrowerAction(const eGrowerType type,
                             const SDL_Rect& buildingRect,
                             eGrower* const c,
                             const eAction& failAction,
                             const eAction& finishAction) :
    eActionWithComeback(c, failAction, finishAction),
    mType(type), mGrower(c),
    mBuildingRect(buildingRect) {}

void eGrowerAction::increment(const int by) {
    if(!currentAction()) findResource();
    else eActionWithComeback::increment(by);
}

bool eGrowerAction::findResource() {
    const auto t = mGrower->tile();
    const auto& brd = mGrower->getBoard();
    const auto tp = brd.threadPool();

    const int tx = t->x();
    const int ty = t->y();

    const auto startTile = [tx, ty](eThreadBoard& board) {
        return board.absTile(tx, ty);
    };
    const auto rect = mBuildingRect;
    const auto tileWalkable = [rect](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        const bool r = SDL_PointInRect(&p, &rect);
        if(r) return true;
        return t->walkable();
    };

    const stdptr<eCharacterAction> tptr(this);
    const auto failFunc = [tptr]() {
        if(tptr) tptr->setState(eCharacterActionState::failed);
    };

    auto aType = std::make_shared<eBuildingType>();

    const auto finishFunc = [tptr, this, tileWalkable,
                            failFunc, aType](
                            const std::vector<eOrientation>& path) {
        if(!tptr) return;
        const auto finishAction = [tptr, this, aType]() {
            workOn(mGrower->tile());
        };

        mGrower->setActionType(eCharacterActionType::walk);
        const auto a  = e::make_shared<eMovePathAction>(
                            mGrower, path, tileWalkable,
                            failFunc, finishAction);
        setCurrentAction(a);
    };

    const auto gt = mType;
    const auto hha = [aType, gt](eThreadTile* const tile) {
        const auto ub = tile->underBuildingType();
        bool r;
        switch(gt) {
        case eGrowerType::grapesAndOlives:
            r = ub == eBuildingType::vine ||
                ub == eBuildingType::oliveTree;
            break;
        case eGrowerType::oranges:
            r = ub == eBuildingType::orangeTree;
            break;
        }

        if(!r) return false;
        *aType = ub;
        const auto& b = tile->underBuilding();
        return !b.workedOn() && !tile->busy();
    };

    const auto pft = new ePathFindTask(startTile, tileWalkable,
                                       hha, finishFunc,
                                       failFunc, false, 50);
    tp->queueTask(pft);

    setCurrentAction(e::make_shared<eWaitAction>(mGrower, []() {}, []() {}));

    return true;
}

bool eGrowerAction::workOn(eTile* const tile) {
    const auto type = tile->underBuildingType();
    switch(mType) {
    case eGrowerType::grapesAndOlives:
        if(type != eBuildingType::vine &&
           type != eBuildingType::oliveTree) return false;
        break;
    case eGrowerType::oranges:
        if(type != eBuildingType::orangeTree) return false;
        break;
    }
    tile->setBusy(true);
    const auto b = tile->underBuilding();
    const auto bb = dynamic_cast<eResourceBuilding*>(b);
    if(bb->resource() > 0) {
        if(type == eBuildingType::vine) {
            mGrower->setActionType(eCharacterActionType::collectGrapes);
        } else if(type == eBuildingType::oliveTree) {
            mGrower->setActionType(eCharacterActionType::collectOlives);
        } else if(type == eBuildingType::orangeTree) {
            mGrower->setActionType(eCharacterActionType::collectOranges);
        }
    } else {
        if(type == eBuildingType::vine) {
            mGrower->setActionType(eCharacterActionType::workOnGrapes);
        } else if(type == eBuildingType::oliveTree) {
            mGrower->setActionType(eCharacterActionType::workOnOlives);
        } else if(type == eBuildingType::orangeTree) {
            mGrower->setActionType(eCharacterActionType::workOnOranges);
        }
    }

    const auto failAction = [this, tile]() {
        tile->setBusy(false);
        setState(eCharacterActionState::failed);
    };

    const stdptr<eCharacterAction> tptr(this);
    const auto finishAction = [tptr, this, tile, type]() {
        tile->setBusy(false);
        if(!tptr) return;
        if(const auto b = tile->underBuilding()) {
            if(const auto bb = dynamic_cast<eResourceBuilding*>(b)) {
                bb->workOn();
                const int took = bb->takeResource(1);
                if(took > 0) {
                    if(type == eBuildingType::vine) {
                        mGrower->incGrapes();
                    } else if(type == eBuildingType::oliveTree) {
                        mGrower->incOlives();
                    } else if(type == eBuildingType::orangeTree) {
                        mGrower->incOranges();
                    }
                }
            }
        }
        if(mCount++ > 5) goBack2();
        else findResource();
    };

    const auto w = e::make_shared<eWaitAction>(mGrower, failAction, finishAction);
    w->setTime(2000);
    setCurrentAction(w);
    return false;
}

void eGrowerAction::goBack2() {
    mGrower->setActionType(eCharacterActionType::carry);
    const auto rect = mBuildingRect;
    eActionWithComeback::goBack([rect](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        const bool r = SDL_PointInRect(&p, &rect);
        if(r) return true;
        return t->walkable();
    });
}
