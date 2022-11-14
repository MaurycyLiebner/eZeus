#include "echaracteractionfunction.h"

#include "eactionwithcomeback.h"
#include "earcheraction.h"
#include "eartisanaction.h"
#include "ecarttransporteraction.h"
#include "ecollectresourceaction.h"
#include "efirefighteraction.h"
#include "egodaction.h"
#include "egodattackaction.h"

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

    case eCharActFuncType::GA_patrolFail:
        return std::make_shared<eGA_patrolFail>(board);
    case eCharActFuncType::GA_patrolFailFail:
        return std::make_shared<eGA_patrolFailFail>(board);
    case eCharActFuncType::GA_patrolFailFinish:
        return std::make_shared<eGA_patrolFailFinish>(board);
    case eCharActFuncType::GA_lookForSoldierAttackFinish:
        return std::make_shared<eGA_lookForSoldierAttackFinish>(board);
    case eCharActFuncType::GA_teleportFinish:
        return std::make_shared<eGA_teleportFinish>(board);
    case eCharActFuncType::GA_hermesRunFinish:
        return std::make_shared<eGA_hermesRunFinish>(board);

    case eCharActFuncType::GAA_loserDisappearFinish:
        return std::make_shared<eGAA_loserDisappearFinish>(board);
    case eCharActFuncType::GAA_fightFinish:
        return std::make_shared<eGAA_fightFinish>(board);
    }
}
