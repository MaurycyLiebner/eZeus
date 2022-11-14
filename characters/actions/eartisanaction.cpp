#include "eartisanaction.h"

#include "characters/actions/emovetoaction.h"
#include "characters/actions/ewaitaction.h"
#include "characters/actions/ebuildaction.h"
#include "engine/egameboard.h"

eArtisanAction::eArtisanAction(eCharacter* const c,
                               eArtisansGuild* const guild) :
    eActionWithComeback(c, eCharActionType::artisanAction),
    mGuild(guild) {}

eArtisanAction::eArtisanAction(eCharacter* const c) :
    eArtisanAction(c, nullptr) {}

bool hasTarget(eThreadTile* const tile) {
    const auto& b = tile->underBuilding();
    return b.resourcesAvailable() && !b.workedOn() && !tile->busy();
}

bool eArtisanAction::decide() {
    const bool r = eActionWithComeback::decide();
    if(r) return r;

    const auto c = character();
    const auto t = c->tile();

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
        const auto& brd = board();
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

void eArtisanAction::read(eReadStream& src) {
    eActionWithComeback::read(src);
    src.readBuilding(&board(), [this](eBuilding* const b) {
        mGuild = static_cast<eArtisansGuild*>(b);
    });
    src >> mNoTarget;
}

void eArtisanAction::write(eWriteStream& dst) const {
    eActionWithComeback::write(dst);
    dst.writeBuilding(mGuild);
    dst << mNoTarget;
}

bool eArtisanAction::findTargetDecision() {
    const stdptr<eArtisanAction> tptr(this);

    const auto hha = [](eThreadTile* const tile) {
        return hasTarget(tile);
    };

    const auto c = character();
    const auto a = e::make_shared<eMoveToAction>(
                       c, [](){}, [](){});
    const stdptr<eCharacter> cptr(c);
    a->setFoundAction([cptr]() {
        if(!cptr) return;
        cptr->setActionType(eCharacterActionType::walk);
    });
    const auto findFailFunc = [tptr, this]() {
        if(tptr) mNoTarget = true;
    };

    a->setFindFailAction(findFailFunc);
    a->setRemoveLastTurn(true);
    a->start(hha, eWalkableObject::sCreateDefault());
    setCurrentAction(a);
    return true;
}

void eArtisanAction::workOnDecision(eTile* const tile) {
    const auto b = tile->underBuilding();
    const auto bb = dynamic_cast<eSanctBuilding*>(b);
    if(!bb || bb->workedOn() || bb->finished() ||
       !bb->resourcesAvailable()) return;
    bb->setWorkedOn(true);
    const auto c = character();
    c->setActionType(eCharacterActionType::build);
    const auto t = c->tile();
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
    c->setOrientation(o);
    const auto w = e::make_shared<eBuildAction>(c);
    const auto finish = std::make_shared<eArtA_buildFinish>(board(), bb);
    w->setFailAction(finish);
    w->setFinishAction(finish);
    const auto deleteFail = std::make_shared<eArtA_buildDelete>(board(), bb);
    w->setDeleteFailAction(deleteFail);
    setCurrentAction(w);
}

void eArtisanAction::goBackDecision() {
    const auto c = character();
    c->setActionType(eCharacterActionType::walk);
    goBack(mGuild, eWalkableObject::sCreateDefault());
}
