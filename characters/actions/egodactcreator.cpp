#include "egodaction.h"
#include "godHelp/eartemishelpaction.h"

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
    }
    return nullptr;
}