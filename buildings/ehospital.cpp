#include "ehospital.h"

#include "characters/ehealer.h"
#include "textures/egametextures.h"

eHospital::eHospital(eGameBoard& board) :
    ePatrolBuilding(board, &eBuildingTextures::fHospital,
                    -1.84, -4.5,
                    &eBuildingTextures::fHospitalOverlay,
                    [this]() { return e::make_shared<eHealer>(getBoard()); },
                    eBuildingType::hospital, 4, 4, 11)  {
    eGameTextures::loadHospital();
}
