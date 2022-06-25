#include "eartisanaction.h"

#include "characters/actions/emovetoaction.h"
#include "characters/actions/ewaitaction.h"
#include "characters/actions/ebuildaction.h"
#include "engine/egameboard.h"

eArtisanAction::eArtisanAction(eArtisansGuild* const guild,
                               eArtisan* const c,
                               const eAction& failAction,
                               const eAction& finishAction) :
    eActionWithComeback(c, failAction, finishAction),
    mArtisan(c), mGuild(guild) {}

bool hasTarget(eThreadTile* const tile) {
    const auto& b = tile->underBuilding();
    return b.resourcesAvailable() && !b.workedOn() && !tile->busy();
}

bool eArtisanAction::decide() {
    const bool r = eActionWithComeback::decide();
    if(r) return r;

    const auto t = mArtisan->tile();

    const bool inGuild = eWalkableHelpers::sTileUnderBuilding(t, mGuild);

    if(inGuild) {
        if(mNoTarget) {
            mNoTarget = false;
            wait(5000);
        } else {
            findTargetDecision();
        }
    } else if(mNoTarget) {
        mNoTarget = false;
        goBackDecision();
    } else {
        const auto& brd = mArtisan->getBoard();
        eTile* tt = nullptr;
        for(int i = -1; i < 2; i++) {
            for(int j = -1; j < 2; j++) {
                const auto ttt = brd.tile(t->x() + i, t->y() + j);
                if(!ttt) continue;
                const auto b = ttt->underBuilding();
                if(const auto bb = dynamic_cast<eSanctBuilding*>(b)) {
                    if(bb->finished()) continue;
                    if(bb->workedOn()) continue;
                    if(!bb->resourcesAvailable()) continue;
                    tt = ttt;
                    break;
                }
            }
        }
        if(tt) {
            workOnDecision(tt);
        } else {
            findTargetDecision();
        }
    }

    return true;
}

bool eArtisanAction::findTargetDecision() {
    const stdptr<eArtisanAction> tptr(this);

    const auto hha = [](eThreadTile* const tile) {
        return hasTarget(tile);
    };

    const auto a = e::make_shared<eMoveToAction>(
                       mArtisan, [](){}, [](){});
    a->setFoundAction([tptr, this]() {
        if(!tptr) return;
        if(!mArtisan) return;
        mArtisan->setActionType(eCharacterActionType::walk);
    });
    const auto findFailFunc = [tptr, this]() {
        if(tptr) mNoTarget = true;
    };

    a->setFindFailAction(findFailFunc);
    a->setRemoveLastTurn(true);
    a->start(hha, eWalkableHelpers::sDefaultWalkable);
    setCurrentAction(a);
    return true;
}

void eArtisanAction::workOnDecision(eTile* const tile) {
    const auto b = tile->underBuilding();
    const auto bb = dynamic_cast<eSanctBuilding*>(b);
    if(!bb || bb->workedOn() || bb->finished() ||
       !bb->resourcesAvailable()) return;
    bb->setWorkedOn(true);
    const stdptr<eSanctBuilding> bbptr(bb);
    const auto finish = [bbptr]() {
        if(!bbptr) return;
        bbptr->setWorkedOn(false);
        if(bbptr->resourcesAvailable()) {
            bbptr->incProgress();
        }
    };
    mArtisan->setActionType(eCharacterActionType::build);
    const auto t = mArtisan->tile();
    const int dx = t->x() - tile->x();
    const int dy = t->y() - tile->y();
    eOrientation o;
    if(dx > 0 && dy == 0) {
        o = eOrientation::topLeft;
    } else if(dx < 0 && dy == 0) {
        o = eOrientation::bottomRight;
    } else if(dx == 0 && dy > 0) {
        o = eOrientation::topRight;
    } else if(dx == 0 && dy < 0) {
        o = eOrientation::bottomLeft;
    } else if(dx < 0 && dy < 0) {
        o = eOrientation::bottom;
    } else if(dx > 0 && dy > 0) {
        o = eOrientation::top;
    } else if(dx < 0 && dy > 0) {
        o = eOrientation::right;
    } else if(dx > 0 && dy < 0) {
        o = eOrientation::left;
    } else {
        o = eOrientation::topLeft;
    }
    mArtisan->setOrientation(o);
    const auto w = e::make_shared<eBuildAction>(mArtisan, finish, finish);
    w->setDeleteFailAction([bbptr]() {
        if(!bbptr) return;
        bbptr->setWorkedOn(false);
    });
    setCurrentAction(w);
}

void eArtisanAction::goBackDecision() {
    mArtisan->setActionType(eCharacterActionType::walk);
    goBack(mGuild, eWalkableHelpers::sDefaultWalkable);
}
