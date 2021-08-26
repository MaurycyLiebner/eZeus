#include "ehospital.h"

#include "characters/ehealer.h"

eHospital::eHospital(eGameBoard& board) :
    ePatrolBuilding(board, &eBuildingTextures::fHospital,
                    -1.78, -4.5,
                    &eBuildingTextures::fHospitalOverlay,
                    [this]() { return e::make_shared<eHealer>(getBoard()); },
                    eBuildingType::hospital, 4, 4, 11)  {

}
