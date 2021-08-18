#include "emaintenanceoffice.h"

#include "characters/efirefighter.h"

eMaintenanceOffice::eMaintenanceOffice(eGameBoard& board) :
    ePatrolBuilding(board, &eBuildingTextures::fMaintenanceOffice,
                    -3.85, -4.35,
                    &eBuildingTextures::fMaintenanceOfficeOverlay,
                    [this]() { return new eFireFighter(getBoard()); },
                    eBuildingType::maintenanceOffice, 2, 2)  {

}
