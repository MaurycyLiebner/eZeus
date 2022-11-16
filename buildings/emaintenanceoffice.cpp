#include "emaintenanceoffice.h"

#include "characters/efirefighter.h"
#include "characters/actions/efirefighteraction.h"


stdsptr<eCharacterAction> gFireFighterActGenerator(
           eCharacter* const c,
           ePatrolBuildingBase* const b,
           const std::vector<ePatrolGuide>& guides,
           const stdsptr<eDirectionTimes>& dirTimes) {
    return e::make_shared<eFireFighterAction>(c, b, guides, dirTimes);
}

eMaintenanceOffice::eMaintenanceOffice(eGameBoard& board) :
    ePatrolBuilding(board, &eBuildingTextures::fMaintenanceOffice,
                    -3.85, -4.35,
                    &eBuildingTextures::fMaintenanceOfficeOverlay,
                    [this]() { return e::make_shared<eFireFighter>(getBoard()); },
                    gFireFighterActGenerator,
                    eBuildingType::maintenanceOffice, 2, 2, 5)  {

}
