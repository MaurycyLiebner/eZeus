#include "egroweraction.h"

#include "characters/actions/emovetoaction.h"
#include "characters/actions/ewaitaction.h"
#include "buildings/eresourcebuilding.h"

eGrowerAction::eGrowerAction(const eGrowerType type,
                             eGrowersLodge* const lodge,
                             eGrower* const c,
                             const eAction& failAction,
                             const eAction& finishAction) :
    eActionWithComeback(c, failAction, finishAction),
    mType(type), mGrower(c),
    mLodge(lodge) {}

bool hasResource(eThreadTile* const tile, const eGrowerType gt) {
    if(rand() % 2) return false;
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
    const auto& b = tile->underBuilding();
    return !b.workedOn() && !tile->busy();
}

enum class eCollectType {
    groom,
    collect
};

eResourceBuilding* tryToCollect(eTile* const tile,
                                const eGrowerType type,
                                eCollectType& collType) {
    if(tile->busy()) return nullptr;
    const auto b = tile->underBuilding();
    if(b) {
        const auto s = static_cast<eResourceBuilding*>(b);
        if(s->workedOn()) return nullptr;
        const auto t = b->type();
        switch(type) {
        case eGrowerType::grapesAndOlives:
            if(t != eBuildingType::vine &&
               t != eBuildingType::oliveTree) {
                return nullptr;
            }
           break;
        case eGrowerType::oranges:
            if(t != eBuildingType::orangeTree) {
                return nullptr;
            }
           break;
        }

        if(s->resource() > 0) {
            collType = eCollectType::collect;
        } else {
            collType = eCollectType::groom;
        }
        return s;
    }
    return nullptr;
}

bool eGrowerAction::decide() {
    const bool r = eActionWithComeback::decide();
    if(r) return r;

    const auto t = mGrower->tile();

    const int grapes = mGrower->grapes();
    const int olives = mGrower->olives();
    const int oranges = mGrower->oranges();

    const SDL_Point p{t->x(), t->y()};
    const auto rect = mLodge->tileRect();
    const bool inLodge = SDL_PointInRect(&p, &rect);

    if(grapes > 0 || olives > 0 || oranges > 0) {
        if(inLodge) {
            mLodge->add(eResourceType::grapes, grapes);
            mLodge->add(eResourceType::olives, olives);
            mLodge->add(eResourceType::oranges, oranges);

            mGrower->incGrapes(-grapes);
            mGrower->incGrapes(-olives);
            mGrower->incGrapes(-oranges);

            waitDecision();
        } else {
            goBackDecision();
        }
    } else {
        eCollectType collType;
        if(const auto a = tryToCollect(t, mType, collType)) {
            workOnDecision(t);
        } else if(inLodge) {
            int space = 0;
            switch(mType) {
            case eGrowerType::grapesAndOlives:
                space = mLodge->spaceLeft(eResourceType::grapes);
                break;
            case eGrowerType::oranges:
                space = mLodge->spaceLeft(eResourceType::oranges);
                break;
            }

            if(space <= 0 || !mLodge->enabled()) {
                waitDecision();
            } else {
                if(mNoResource) {
                    mNoResource = false;
                    waitDecision();
                } else {
                    findResourceDecision();
                }
            }
        } else if(mNoResource) {
            mNoResource = false;
            goBackDecision();
        } else {
            if(mGroomed > 5) {
                mGroomed = 0;
                goBackDecision();
            } else {
                findResourceDecision();
            }
        }
    }
    return true;
}

bool eGrowerAction::findResourceDecision() {
    const stdptr<eGrowerAction> tptr(this);

    const auto gt = mType;
    const auto hha = [gt](eThreadTile* const tile) {
        return hasResource(tile, gt);
    };

    const auto a = e::make_shared<eMoveToAction>(
                       mGrower, [](){}, [](){});
    a->setFoundAction([tptr, this]() {
        if(!tptr) return;
        if(!mGrower) return;
        mGrower->setActionType(eCharacterActionType::walk);
    });
    const auto findFailFunc = [tptr, this]() {
        if(tptr) mNoResource = true;
    };
    a->setFindFailAction(findFailFunc);
    a->start(hha);
    setCurrentAction(a);
    return true;
}

void eGrowerAction::workOnDecision(eTile* const tile) {
    const auto type = tile->underBuildingType();
    switch(mType) {
    case eGrowerType::grapesAndOlives:
        if(type != eBuildingType::vine &&
           type != eBuildingType::oliveTree) return;
        break;
    case eGrowerType::oranges:
        if(type != eBuildingType::orangeTree) return;
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

    const stdptr<eCharacterAction> tptr(this);
    const auto finish = [tptr, this, tile, type]() {
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
        mGroomed++;
    };

    const auto w = e::make_shared<eWaitAction>(mGrower, finish, finish);
    w->setTime(2000);
    setCurrentAction(w);
}

void eGrowerAction::goBackDecision() {
    mGrower->setActionType(eCharacterActionType::carry);
    const auto rect = mLodge->tileRect();
    eActionWithComeback::goBack([rect](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        const bool r = SDL_PointInRect(&p, &rect);
        if(r) return true;
        return t->walkable();
    });
}

void eGrowerAction::waitDecision() {
    const auto w = e::make_shared<eWaitAction>(
                       mGrower, [](){}, [](){});
    w->setTime(5000);
    setCurrentAction(w);
}
