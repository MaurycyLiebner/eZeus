#include "echaracteraction.h"

#include "eanimalaction.h"
#include "earcheraction.h"
#include "eartisanaction.h"
#include "ebuildaction.h"
#include "ecarttransporteraction.h"
#include "ecollectaction.h"
#include "ecollectresourceaction.h"
#include "edieaction.h"
#include "efightaction.h"
#include "efirefighteraction.h"
#include "efollowaction.h"
#include "edionysusfollowaction.h"
#include "egodattackaction.h"
#include "egodvisitaction.h"
#include "egodworshippedaction.h"
#include "egroweraction.h"
#include "eheroaction.h"
#include "ehuntaction.h"
#include "emonsteraction.h"
#include "emovearoundaction.h"
#include "emovepathaction.h"
#include "emovetoaction.h"
#include "epatrolaction.h"
#include "epatrolguidedmoveaction.h"
#include "esettleraction.h"
#include "eshepherdaction.h"
#include "esoldieraction.h"
#include "etraderaction.h"
#include "ewaitaction.h"
#include "esickdisgruntledaction.h"
#include "etakecattleaction.h"
#include "ereplacecattleaction.h"

#include "godHelp/eaphroditehelpaction.h"
#include "godHelp/eartemishelpaction.h"
#include "godHelp/eathenahelpaction.h"
#include "godHelp/eatlashelpaction.h"
#include "godHelp/edemeterhelpaction.h"
#include "godHelp/edionysushelpaction.h"
#include "godHelp/ehadeshelpaction.h"
#include "godHelp/eherahelpaction.h"
#include "godHelp/eposeidonhelpaction.h"
#include "godHelp/ezeushelpaction.h"
#include "godHelp/eapollohelpaction.h"
#include "godHelp/eareshelpaction.h"
#include "godHelp/ehermeshelpaction.h"
#include "godHelp/ehephaestushelpaction.h"

#include "edefendcityaction.h"

stdsptr<eCharacterAction> eCharacterAction::sCreate(
        eCharacter* const c, const eCharActionType type) {
    switch(type) {
    case eCharActionType::animalAction:
        return e::make_shared<eAnimalAction>(c);
    case eCharActionType::archerAction:
        return e::make_shared<eArcherAction>(c);
    case eCharActionType::artisanAction:
        return e::make_shared<eArtisanAction>(c);
    case eCharActionType::buildAction:
        return e::make_shared<eBuildAction>(c);
    case eCharActionType::cartTransporterAction:
        return e::make_shared<eCartTransporterAction>(c);
    case eCharActionType::collectAction:
        return e::make_shared<eCollectAction>(c);
    case eCharActionType::collectResourceAction:
        return e::make_shared<eCollectResourceAction>(c);
    case eCharActionType::dieAction:
        return e::make_shared<eDieAction>(c);
    case eCharActionType::fightAction:
        return e::make_shared<eFightAction>(c);
    case eCharActionType::fireFighterAction:
        return e::make_shared<eFireFighterAction>(c);
    case eCharActionType::followAction:
        return e::make_shared<eFollowAction>(c);
    case eCharActionType::dionysusFollowAction:
        return e::make_shared<eDionysusFollowAction>(c);
    case eCharActionType::godAttackAction:
        return e::make_shared<eGodAttackAction>(c);
    case eCharActionType::godVisitAction:
        return e::make_shared<eGodVisitAction>(c);
    case eCharActionType::godWorshippedAction:
        return e::make_shared<eGodWorshippedAction>(c);
    case eCharActionType::growerAction:
        return e::make_shared<eGrowerAction>(c);
    case eCharActionType::heroAction:
        return e::make_shared<eHeroAction>(c);
    case eCharActionType::takeCattleAction:
        return e::make_shared<eTakeCattleAction>(c);
    case eCharActionType::replaceCattleAction:
        return e::make_shared<eReplaceCattleAction>(c);
    case eCharActionType::huntAction:
        return e::make_shared<eHuntAction>(c);
    case eCharActionType::monsterAction:
        return e::make_shared<eMonsterAction>(c);
    case eCharActionType::moveAroundAction:
        return e::make_shared<eMoveAroundAction>(c);
    case eCharActionType::movePathAction:
        return e::make_shared<eMovePathAction>(c);
    case eCharActionType::moveToAction:
        return e::make_shared<eMoveToAction>(c);
    case eCharActionType::patrolAction:
        return e::make_shared<ePatrolAction>(c);
    case eCharActionType::patrolGuidedMoveAction:
        return e::make_shared<ePatrolGuidedMoveAction>(c);
    case eCharActionType::patrolMoveAction:
        return e::make_shared<ePatrolMoveAction>(c);
    case eCharActionType::settlerAction:
        return e::make_shared<eSettlerAction>(c);
    case eCharActionType::shepherdAction:
        return e::make_shared<eShepherdAction>(c);
    case eCharActionType::soldierAction:
        return e::make_shared<eSoldierAction>(c);
    case eCharActionType::traderAction:
        return e::make_shared<eTraderAction>(c);
    case eCharActionType::waitAction:
        return e::make_shared<eWaitAction>(c);

    case eCharActionType::aphroditeHelpAction:
        return e::make_shared<eAphroditeHelpAction>(c);
    case eCharActionType::apolloHelpAction:
        return e::make_shared<eApolloHelpAction>(c);
    case eCharActionType::aresHelpAction:
        return e::make_shared<eAresHelpAction>(c);
    case eCharActionType::artemisHelpAction:
        return e::make_shared<eArtemisHelpAction>(c);
    case eCharActionType::athenaHelpAction:
        return e::make_shared<eAthenaHelpAction>(c);
    case eCharActionType::atlasHelpAction:
        return e::make_shared<eAtlasHelpAction>(c);
    case eCharActionType::demeterHelpAction:
        return e::make_shared<eDemeterHelpAction>(c);
    case eCharActionType::dionysusHelpAction:
        return e::make_shared<eDionysusHelpAction>(c);
    case eCharActionType::hadesHelpAction:
        return e::make_shared<eHadesHelpAction>(c);
    case eCharActionType::heraHelpAction:
        return e::make_shared<eHeraHelpAction>(c);
    case eCharActionType::hephaestusHelpAction:
        return e::make_shared<eHephaestusHelpAction>(c);
    case eCharActionType::hermesHelpAction:
        return e::make_shared<eHermesHelpAction>(c);
    case eCharActionType::poseidonHelpAction:
        return e::make_shared<ePoseidonHelpAction>(c);
    case eCharActionType::zeusHelpAction:
        return e::make_shared<eZeusHelpAction>(c);

    case eCharActionType::godMonsterActionInd:
        return e::make_shared<eGodMonsterActionInd>(c);
    case eCharActionType::sickDisgruntledAction:
        return e::make_shared<eSickDisgruntledAction>(c, nullptr);

    case eCharActionType::defendCityAction:
        return e::make_shared<eDefendCityAction>(c);
    }
    return nullptr;
}
