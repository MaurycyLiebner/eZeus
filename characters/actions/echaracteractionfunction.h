#ifndef ECHARACTERACTIONFUNCTION_H
#define ECHARACTERACTIONFUNCTION_H

#include "fileIO/estreams.h"

enum class eCharacterActionFunctionType {
    AWC_goBackFail,
    AWC_goBackFinish,

    AA_patrolFail,
    AA_patrolFinish,

    ArtA_buildFinish,
    ArtA_buildDelete,

    CTA_findTargetFinish,
    CTA_waitOutsideFinish,
    CTA_spreadFinish,

    CRA_collectFinish,
    CRA_collectFail,
    CRA_callCollectedActionFinish,

    FFA_lookForFireFail,
    FFA_putOutFireFinish,
    GA_lookForSoldierAttackFinish,
    GA_lookForRangeActionFinish,
    GA_teleportFinish,
    GA_hermesRunFinish,
    GA_spawnGodMissilePlaySound,

    GAA_loserDisappearFinish,
    GAA_fightFinish,
    GAA_destroyBuildingFinish,

    GMA_patrolFail,
    GMA_patrolFailFail,
    GMA_patrolFailFinish,
    GMA_spawnMultipleMissilesFinish,
    GMA_spawnMissileFinish,
    GMA_goToTargetFail,

    GRA_workOnDecisionFinish,
    GRA_workOnDecisionDeleteFail,

    killCharacterFinishFail,
    HA_patrolFail,
    HA_huntMonsterFinish,
    HA_fightMonsterDie,

    MA_destroyBuildingFinish,
    MA_lookForRangeActionFinishAttack,

    PA_patrolFail,
    PA_patrolFinish,

    SA_findHouseFail,
    SA_findHouseFinish,

    SA_collectDecisionFinish,
    SA_collectDecisionDeleteFail,
    SA_groomDecisionFinish,
    SA_groomDecisionDeleteFail,

    SA_goToFinish,
    SA_goHomeFinish,
    SA_waitAndGoHomeFinish,

    TA_tradeFail,
    TA_tradeFinish,
    TA_goToTradePostFinish,

    PT_spawnGetActorFinish,

    Char_fightFinish,
    Char_killWithCorpseFinish,

    SS_spawnFinish,

    ZHA_killFinish,

    RC_finishAction,
    RC_finishWalkingAction,

    HA_waitAndGoToHallFinish,

    GWA_huntMonsterFinish,

    FA_remainderSetterFinish
};

using eCharActFuncType = eCharacterActionFunctionType;

class eCharacterActionFunction {
public:
    eCharacterActionFunction(eGameBoard& board,
                             const eCharActFuncType t);

    eCharActFuncType type() const { return mType; }
    eGameBoard& board() { return mBoard; }

    virtual void read(eReadStream& src) = 0;
    virtual void write(eWriteStream& dst) const = 0;

    virtual void call() = 0;

    static stdsptr<eCharacterActionFunction> sCreate(
            eGameBoard& board,
            const eCharActFuncType type);
private:
    eGameBoard& mBoard;
    const eCharActFuncType mType;
};

using eCharActFunc = eCharacterActionFunction;

#endif // ECHARACTERACTIONFUNCTION_H
