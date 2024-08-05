#include "egodvisitaction.h"

#include "characters/echaracter.h"
#include "enumbers.h"

eGodVisitAction::eGodVisitAction(eCharacter* const c) :
    eGodAction(c, eCharActionType::godVisitAction) {}

void eGodVisitAction::increment(const int by) {
    const int attackPeriod = eNumbers::sGodVisitSoldierAttackPeriod;
    const int attackRange = eNumbers::sGodVisitSoldierAttackRange;
    const int blessPeriod = eNumbers::sGodVisitBlessPeriod;
    const int blessRange = eNumbers::sGodVisitBlessRange;

    bool r = lookForBlessCurse(by, mLookForBless, blessPeriod, blessRange, 1);
    if(!r) lookForSoldierAttack(by, mLookForSoldierAttack, attackPeriod, attackRange);

    eGodAction::increment(by);
}

bool eGodVisitAction::decide() {
    const auto c = character();
    switch(mStage) {
    case eGodVisitStage::none:
        mStage = eGodVisitStage::appear;
        randomPlaceOnBoard();
        if(!c->tile()) {
            c->kill();
        } else {
            appear();
        }
        break;
    case eGodVisitStage::appear: {
        mStage = eGodVisitStage::patrol;
        const auto tile = c->tile();
        if(tile->hasRoad()) patrol(nullptr, eNumbers::sGodVisitPatrolDistance);
        else moveAround(nullptr, eNumbers::sGodVisitMoveAroundTime);
    }   break;
    case eGodVisitStage::patrol:
        mStage = eGodVisitStage::disappear;
        disappear();
        break;
    case eGodVisitStage::disappear:
        c->kill();
        break;
    }
    return true;
}

void eGodVisitAction::read(eReadStream& src) {
    eGodAction::read(src);
    src >> mStage;
    src >> mLookForBless;
    src >> mLookForSoldierAttack;
}

void eGodVisitAction::write(eWriteStream& dst) const {
    eGodAction::write(dst);
    dst << mStage;
    dst << mLookForBless;
    dst << mLookForSoldierAttack;
}
