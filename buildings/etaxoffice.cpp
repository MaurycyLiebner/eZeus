#include "etaxoffice.h"

#include "characters/etaxcollector.h"
#include "textures/egametextures.h"

eTaxOffice::eTaxOffice(eGameBoard& board) :
    ePatrolBuilding(board,
                    &eBuildingTextures::fTaxOffice,
                    -0.65, -2.55,
                    &eBuildingTextures::fTaxOfficeOverlay,
                    [this]() { return e::make_shared<eTaxCollector>(getBoard()); },
                    eBuildingType::taxOffice, 2, 2, 8) {
    eGameTextures::loadTaxOffice();
}
