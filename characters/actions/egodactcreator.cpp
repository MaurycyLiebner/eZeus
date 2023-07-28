#include "egodaction.h"

#include "godHelp/eprovideresourcehelpaction.h"
#include "godHelp/eatlashelpaction.h"
#include "godHelp/ehadeshelpaction.h"
#include "godHelp/eherahelpaction.h"

stdsptr<eGodAct> eGodAct::sCreate(
        eGameBoard& board, const eGodActType t) {
    switch(t) {
    case eGodActType::lookForSoldierAttack:
        return std::make_shared<eLookForSoldierAttackGodAct>(board);
    case eGodActType::lookForBless:
        return std::make_shared<eLookForBlessGodAct>(board);
    case eGodActType::playMonsterBuildingAttackSound:
        return std::make_shared<ePlayMonsterBuildingAttackSoundGodAct>(board);
    case eGodActType::playFightGodHitSoundGodAct:
        return std::make_shared<ePlayFightGodHitSoundGodAct>(board);
    case eGodActType::lookForAttack:
        return std::make_shared<eLookForAttackGodAct>(board);

    case eGodActType::provideResource:
        return std::make_shared<eGodProvideResourceAct>(board);
    case eGodActType::provideAgora:
        return std::make_shared<eGodProvideAgoraAct>(board);
    case eGodActType::provideDrachmas:
        return std::make_shared<eGodProvideDrachmasAct>(board);
    case eGodActType::atlasHelp:
        return std::make_shared<eAtlasHelpAct>(board);
    }
    return nullptr;
}
