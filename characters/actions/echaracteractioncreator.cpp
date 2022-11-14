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
#include "egodaction.h"

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
    case eCharActionType::godAction:
        return e::make_shared<eGodAction>(c);
    }
}
