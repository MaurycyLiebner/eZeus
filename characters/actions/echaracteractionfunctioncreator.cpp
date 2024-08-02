#include "echaracteractionfunction.h"

#include "eactionwithcomeback.h"
#include "earcheraction.h"
#include "eartisanaction.h"
#include "ecarttransporteraction.h"
#include "ecollectresourceaction.h"
#include "efirefighteraction.h"
#include "egodaction.h"
#include "egodattackaction.h"
#include "egodmonsteraction.h"
#include "egroweraction.h"
#include "eheroaction.h"
#include "emonsteraction.h"
#include "esettleraction.h"
#include "eshepherdaction.h"
#include "esoldieraction.h"
#include "etraderaction.h"
#include "ekillcharacterfinishfail.h"
#include "ereplacecattleaction.h"
#include "egodworshippedaction.h"
#include "efollowaction.h"

#include "godHelp/ezeushelpaction.h"

#include "buildings/epatroltarget.h"

#include "characters/echaracter.h"

#include "spawners/eentrypoint.h"

stdsptr<eCharActFunc> eCharActFunc::sCreate(
        eGameBoard& board,
        const eCharActFuncType type) {
    switch(type) {
    case eCharActFuncType::AWC_goBackFail:
        return std::make_shared<eAWC_goBackFail>(board);
    case eCharActFuncType::AWC_goBackFinish:
        return std::make_shared<eAWC_goBackFinish>(board);

    case eCharActFuncType::AA_patrolFail:
        return std::make_shared<eAA_patrolFail>(board);
    case eCharActFuncType::AA_patrolFinish:
        return std::make_shared<eAA_patrolFinish>(board);

    case eCharActFuncType::ArtA_buildFinish:
        return std::make_shared<eArtA_buildFinish>(board);
    case eCharActFuncType::ArtA_buildDelete:
        return std::make_shared<eArtA_buildDelete>(board);

    case eCharActFuncType::CTA_findTargetFinish:
        return std::make_shared<eCTA_findTargetFinish>(board);
    case eCharActFuncType::CTA_waitOutsideFinish:
        return std::make_shared<eCTA_waitOutsideFinish>(board);
    case eCharActFuncType::CTA_spreadFinish:
        return std::make_shared<eCTA_spreadFinish>(board);

    case eCharActFuncType::CRA_collectFinish:
        return std::make_shared<eCRA_collectFinish>(board);
    case eCharActFuncType::CRA_collectFail:
        return std::make_shared<eCRA_collectFail>(board);
    case eCharActFuncType::CRA_callCollectedActionFinish:
        return std::make_shared<eCRA_callCollectedActionFinish>(board);

    case eCharActFuncType::FFA_lookForFireFail:
        return std::make_shared<eFFA_lookForFireFail>(board);
    case eCharActFuncType::FFA_putOutFireFinish:
        return std::make_shared<eFFA_putOutFireFinish>(board);

    case eCharActFuncType::GA_lookForRangeActionFinish:
        return std::make_shared<eGA_lookForRangeActionFinish>(board);
    case eCharActFuncType::GA_lookForSoldierAttackFinish:
        return std::make_shared<eGA_lookForSoldierAttackFinish>(board);
    case eCharActFuncType::GA_teleportFinish:
        return std::make_shared<eGA_teleportFinish>(board);
    case eCharActFuncType::GA_hermesRunFinish:
        return std::make_shared<eGA_hermesRunFinish>(board);
    case eCharActFuncType::GA_spawnGodMissilePlaySound:
        return std::make_shared<eGA_spawnGodMissilePlaySound>(board);

    case eCharActFuncType::GAA_loserDisappearFinish:
        return std::make_shared<eGAA_loserDisappearFinish>(board);
    case eCharActFuncType::GAA_fightFinish:
        return std::make_shared<eGAA_fightFinish>(board);
    case eCharActFuncType::GAA_destroyBuildingFinish:
        return std::make_shared<eGAA_destroyBuildingFinish>(board);

    case eCharActFuncType::GMA_patrolFail:
        return std::make_shared<eGMA_patrolFail>(board);
    case eCharActFuncType::GMA_patrolFailFail:
        return std::make_shared<eGMA_patrolFailFail>(board);
    case eCharActFuncType::GMA_patrolFailFinish:
        return std::make_shared<eGMA_patrolFailFinish>(board);
    case eCharActFuncType::GMA_spawnMultipleMissilesFinish:
        return std::make_shared<eGMA_spawnMultipleMissilesFinish>(board);
    case eCharActFuncType::GMA_spawnMissileFinish:
        return std::make_shared<eGMA_spawnMissileFinish>(board);
    case eCharActFuncType::GMA_goToTargetFail:
        return std::make_shared<eGMA_goToTargetFail>(board);

    case eCharActFuncType::GRA_workOnDecisionFinish:
        return std::make_shared<eGRA_workOnDecisionFinish>(board);
    case eCharActFuncType::GRA_workOnDecisionDeleteFail:
        return std::make_shared<eGRA_workOnDecisionDeleteFail>(board);

    case eCharActFuncType::killCharacterFinishFail:
        return std::make_shared<eKillCharacterFinishFail>(board);
    case eCharActFuncType::HA_patrolFail:
        return std::make_shared<eHA_patrolFail>(board);
    case eCharActFuncType::HA_huntMonsterFinish:
        return std::make_shared<eHA_huntMonsterFinish>(board);
    case eCharActFuncType::HA_fightMonsterDie:
        return std::make_shared<eHA_fightMonsterDie>(board);

    case eCharActFuncType::MA_destroyBuildingFinish:
        return std::make_shared<eMA_destroyBuildingFinish>(board);
    case eCharActFuncType::MA_lookForRangeActionFinishAttack:
        return std::make_shared<eMA_lookForRangeActionFinishAttack>(board);

    case eCharActFuncType::PA_patrolFail:
        return std::make_shared<ePA_patrolFail>(board);
    case eCharActFuncType::PA_patrolFinish:
        return std::make_shared<ePA_patrolFinish>(board);

    case eCharActFuncType::SA_findHouseFail:
        return std::make_shared<eSA_findHouseFail>(board);
    case eCharActFuncType::SA_findHouseFinish:
        return std::make_shared<eSA_findHouseFinish>(board);

    case eCharActFuncType::SA_collectDecisionFinish:
        return std::make_shared<eSA_collectDecisionFinish>(board);
    case eCharActFuncType::SA_collectDecisionDeleteFail:
        return std::make_shared<eSA_collectDecisionDeleteFail>(board);
    case eCharActFuncType::SA_groomDecisionFinish:
        return std::make_shared<eSA_groomDecisionFinish>(board);
    case eCharActFuncType::SA_groomDecisionDeleteFail:
        return std::make_shared<eSA_groomDecisionDeleteFail>(board);

    case eCharActFuncType::SA_goToFinish:
        return std::make_shared<eSA_goToFinish>(board);
    case eCharActFuncType::SA_goHomeFinish:
        return std::make_shared<eSA_goHomeFinish>(board);
    case eCharActFuncType::SA_waitAndGoHomeFinish:
        return std::make_shared<eSA_waitAndGoHomeFinish>(board);

    case eCharActFuncType::TA_tradeFail:
        return std::make_shared<eTA_tradeFail>(board);
    case eCharActFuncType::TA_tradeFinish:
        return std::make_shared<eTA_tradeFinish>(board);
    case eCharActFuncType::TA_goToTradePostFinish:
        return std::make_shared<eTA_goToTradePostFinish>(board);

    case eCharActFuncType::PT_spawnGetActorFinish:
        return std::make_shared<ePT_spawnGetActorFinish>(board);

    case eCharActFuncType::Char_fightFinish:
        return std::make_shared<eChar_fightFinish>(board);
    case eCharActFuncType::Char_killWithCorpseFinish:
        return std::make_shared<eChar_killWithCorpseFinish>(board);

    case eCharActFuncType::SS_spawnFinish:
        return std::make_shared<eSS_spawnFinish>(board);

    case eCharActFuncType::ZHA_killFinish:
        return std::make_shared<eZHA_killFinish>(board);

    case eCharActFuncType::RC_finishAction:
        return std::make_shared<eRC_finishAction>(board);
    case eCharActFuncType::RC_finishWalkingAction:
        return std::make_shared<eRC_finishWalkingAction>(board);

    case eCharActFuncType::HA_waitAndGoToHallFinish:
        return std::make_shared<eHA_waitAndGoToHallFinish>(board);

    case eCharActFuncType::GWA_huntMonsterFinish:
        return std::make_shared<eGWA_huntMonsterFinish>(board);

    case eCharActFuncType::FA_remainderSetterFinish:
        return std::make_shared<eFA_remainderSetterFinish>(board);
    }
    return nullptr;
}
