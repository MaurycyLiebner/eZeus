#include "esickdisgruntledaction.h"

#include "../echaracter.h"
#include "buildings/esmallhouse.h"
#include "epatrolmoveaction.h"
#include "emovearoundaction.h"

eSickDisgruntledAction::eSickDisgruntledAction(eCharacter* const c,
                                               eSmallHouse* const ch) :
    eActionWithComeback(c, ch ? ch->centerTile() : nullptr,
                        eCharActionType::sickDisgruntledAction),
    mBuilding(ch) {
    setFinishOnComeback(true);
}

bool eSickDisgruntledAction::decide() {
    const bool r = eActionWithComeback::decide();
    if(r) return r;
    if(mGoBackNext) {
        goBackDecision();
    } else {
        patrol();
        mGoBackNext = true;
    }
    return true;
}

void eSickDisgruntledAction::read(eReadStream& src) {
    eActionWithComeback::read(src);

    src.readBuilding(&board(), [this](eBuilding* const b) {
        mBuilding = static_cast<eSmallHouse*>(b);
    });
    src >> mGoBackNext;
}

void eSickDisgruntledAction::write(eWriteStream& dst) const {
    eActionWithComeback::write(dst);

    dst.writeBuilding(mBuilding);
    dst << mGoBackNext;
}

void eSickDisgruntledAction::patrol() {
    const auto c = character();
    if(!c) return;
    const auto t = c->tile();
    if(!t) return;
    c->setActionType(eCharacterActionType::walk);
    if(t->hasRoad()) {
        const auto a = e::make_shared<ePatrolMoveAction>(
                           c, true,
                           eWalkableObject::sCreateRoad());
        a->setMaxWalkDistance(50);
        setCurrentAction(a);
    } else {
        auto walkable = eWalkableObject::sCreateDefault();
        if(const auto ub = t->underBuilding()) {
            walkable = eWalkableObject::sCreateRect(ub, walkable);
        }

        const auto a = e::make_shared<eMoveAroundAction>(
                           c, t->x(), t->y(),
                           eWalkableObject::sCreateDefault());
        a->setTime(5000);
        a->setMaxDistance(8);
        setCurrentAction(a);
    }
}

void eSickDisgruntledAction::goBackDecision(const stdsptr<eWalkableObject>& w) {
    goBack(mBuilding, w);
}
