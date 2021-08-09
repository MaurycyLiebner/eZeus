#include "etaxoffice.h"

#include "characters/etaxcollector.h"
#include "textures/egametextures.h"

eTaxOffice::eTaxOffice(eGameBoard& board) :
    ePatrolBuilding(board,
                    &eBuildingTextures::fTaxOffice,
                    -0.35, -2.28,
                    &eBuildingTextures::fTaxOfficeOverlay,
                    [this]() { return new eTaxCollector(getBoard()); },
                    eBuildingType::taxOffice, 2, 2) {
}
