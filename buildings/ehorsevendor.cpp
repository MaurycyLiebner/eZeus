#include "ehorsevendor.h"

eHorseVendor::eHorseVendor(const stdsptr<eAgoraBase>& agora,
                           eGameBoard& board) :
    eVendor(board, agora,
            eResourceType::horse, eProvide::horses,
            &eBuildingTextures::fHorseTrainer,
            -1.15, -3.40, &eBuildingTextures::fHorseTrainerOverlay,
            -0.55, -2.5, &eBuildingTextures::fHorseTrainerOverlay2,
            eBuildingType::horseTrainer, 2, 2, 4) {
    setResMult(1);
    setMaxRes(4);
}
