#include "emonsteraction.h"

#include "engine/egameboard.h"

#include "engine/boardData/eheatmaptask.h"
#include "engine/boardData/eheatmapdivisor.h"
#include "buildings/eheatgetters.h"

#include "emovetoaction.h"
#include "ewaitaction.h"
#include "emovearoundaction.h"

eMonsterAction::eMonsterAction(eCharacter* const c,
                               const eAction& failAction,
                               const eAction& finishAction) :
    eGodMonsterAction(c, failAction, finishAction),
    mType(eMonster::sCharacterToMonsterType(c->type())) {}

bool eMonsterAction::decide() {
    const auto c = character();
    switch(mStage) {
    case eMonsterAttackStage::none:
        mStage = eMonsterAttackStage::attack;
        randomPlaceOnBoard();
        if(!c->tile()) c->kill();
        break;
    case eMonsterAttackStage::wait:
        mStage = eMonsterAttackStage::attack;
        goToTarget();
        break;
    case eMonsterAttackStage::attack:
        mStage = eMonsterAttackStage::wait;
        moveAround();
        break;
    }
    return true;
}

void eMonsterAction::randomPlaceOnBoard() {
    const auto c = character();
    const stdptr<eMonsterAction> tptr(this);
    const stdptr<eCharacter> cptr(c);
    const auto hmFinish = [tptr, this, cptr, c](eHeatMap& map) {
        if(!tptr || !cptr) return;
        eHeatMapDivisor divisor(map);
        divisor.divide(10);
        int tx;
        int ty;
        const bool r = divisor.maxHeatTile(tx, ty);
        if(r) {
            const auto& board = c->getBoard();
            c->changeTile(board.tile(tx, ty));
        } else {
            setCurrentAction(nullptr);
        }
    };
    const auto hg = eHeatGetters::empty;
    const auto task = new eHeatMapTask(hg, hmFinish);
    auto& board = c->getBoard();
    auto& tp = board.threadPool();
    tp.queueTask(task);
    wait();
}

void eMonsterAction::goToTarget() {
    const stdptr<eMonsterAction> tptr(this);
    const auto tryAgain = [tptr, this](eTile* const tile) {
        (void)tile;
        if(!tptr) return;
        setCurrentAction(nullptr);
    };
    eGodMonsterAction::goToTarget(eHeatGetters::any, tryAgain);
}
