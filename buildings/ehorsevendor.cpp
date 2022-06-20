#include "ehorsevendor.h"

#include "characters/ehorsevendorchar.h"

eHorseVendor::eHorseVendor(const stdsptr<eCommonAgora>& agora,
                           eGameBoard& board) :
    eVendor(board, agora,
            eResourceType::horse, eProvide::horses,
            &eBuildingTextures::fHorseTrainer,
            -1.05, -3.40, &eBuildingTextures::fHorseTrainerOverlay,
            [this]() { return e::make_shared<eHorseVendorChar>(getBoard()); },
            eBuildingType::horseTrainer, 2, 2, 4) {}
