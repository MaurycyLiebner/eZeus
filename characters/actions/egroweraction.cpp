#include "egroweraction.h"

#include "characters/actions/emovetoaction.h"
#include "characters/actions/ewaitaction.h"
#include "buildings/eresourcebuilding.h"
#include "engine/egameboard.h"

eGrowerAction::eGrowerAction(const eGrowerType type,
                             eGrowersLodge* const lodge,
                             eCharacter* const c) :
    eActionWithComeback(c, eCharActionType::growerAction),
    mType(type), mGrower(static_cast<eGrower*>(c)),
    mLodge(lodge) {}

eGrowerAction::eGrowerAction(eCharacter* const c) :
    eGrowerAction(eGrowerType::grapesAndOlives, nullptr, c) {}

bool hasResource(eThreadTile* const tile, const eGrowerType gt,
                 const bool grapesDisabled, const bool olivesDisabled) {
    if(eRand::rand() % 2) return false;
    const auto ub = tile->underBuildingType();
    bool r;
    switch(gt) {
    case eGrowerType::grapesAndOlives:
        r = (ub == eBuildingType::vine && !grapesDisabled) ||
            (ub == eBuildingType::oliveTree && !olivesDisabled);
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

    const bool inLodge = eWalkableHelpers::sTileUnderBuilding(t, mLodge);

    if(grapes > 0 || olives > 0 || oranges > 0) {
        if(inLodge) {
            mLodge->add(eResourceType::grapes, grapes);
            mLodge->add(eResourceType::olives, olives);
            mLodge->add(eResourceType::oranges, oranges);

            mGrower->incGrapes(-grapes);
            mGrower->incOlives(-olives);
            mGrower->incOranges(-oranges);

            if(mFinishOnce) {
                setState(eCharacterActionState::finished);
                return true;
            } else {
                waitDecision();
            }
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

void eGrowerAction::read(eReadStream& src) {
    eActionWithComeback::read(src);
    src >> mType;
    src.readCharacter(&board(), [this](eCharacter* const c) {
        mGrower = static_cast<eGrower*>(c);
    });
    src.readBuilding(&board(), [this](eBuilding* const b) {
        mLodge = static_cast<eGrowersLodge*>(b);
    });
    src >> mFinishOnce;
    src >> mGroomed;
    src >> mNoResource;
}

void eGrowerAction::write(eWriteStream& dst) const {
    eActionWithComeback::write(dst);
    dst << mType;
    dst.writeCharacter(mGrower);
    dst.writeBuilding(mLodge);
    dst << mFinishOnce;
    dst << mGroomed;
    dst << mNoResource;
}

bool eGrowerAction::findResourceDecision() {
    const stdptr<eGrowerAction> tptr(this);

    const auto gt = mType;
    auto& board = this->board();
    const bool gd = board.isShutDown(eResourceType::grapes);
    const bool od = board.isShutDown(eResourceType::olives);
    const auto hha = [gt, gd, od](eThreadTile* const tile) {
        return hasResource(tile, gt, gd, od);
    };

    const auto a = e::make_shared<eMoveToAction>(mGrower);
    a->setFoundAction([tptr, this]() {
        if(!tptr) return;
        if(mLodge) mLodge->setNoTarget(false);
        if(!mGrower) return;
        mGrower->setActionType(eCharacterActionType::walk);
    });
    const auto findFailFunc = [tptr, this]() {
        if(tptr) {
            mNoResource = true;
            if(mLodge) mLodge->setNoTarget(true);
        }
    };
    a->setFindFailAction(findFailFunc);
    a->setMaxFindDistance(40);
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
    const auto finish = std::make_shared<eGRA_workOnDecisionFinish>(
                            board(), this, tile, type);

    const auto w = e::make_shared<eWaitAction>(mGrower);
    w->setFailAction(finish);
    w->setFinishAction(finish);
    const auto deleteFail = std::make_shared<eGRA_workOnDecisionDeleteFail>(
                            board(), tile);
    w->setDeleteFailAction(deleteFail);
    w->setTime(2000);
    setCurrentAction(w);
}

void eGrowerAction::goBackDecision() {
    mGrower->setActionType(eCharacterActionType::carry);
    goBack(mLodge, eWalkableObject::sCreateDefault());
}

void eGrowerAction::waitDecision() {
    wait(5000);
}
