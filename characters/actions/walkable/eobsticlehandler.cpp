#include "eobsticlehandler.h"

#include "characters/actions/emonsteraction.h"
#include "characters/actions/egodattackaction.h"
#include "characters/actions/esoldieraction.h"

stdsptr<eObsticleHandler> eObsticleHandler::sCreate(
        eGameBoard& board,
        const eObsticleHandlerType type) {
    switch(type) {
    case eObsticleHandlerType::monster:
        return std::make_shared<eMonsterObsticleHandler>(board);
    case eObsticleHandlerType::god:
        return std::make_shared<eGodObsticleHandler>(board);
    case eObsticleHandlerType::soldier:
        return std::make_shared<eSoldierObsticleHandler>(board);
    }
}
