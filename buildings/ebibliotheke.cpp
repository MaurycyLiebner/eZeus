#include "ebibliotheke.h"

#include "characters/escholar.h"
#include "textures/egametextures.h"

eBibliotheke::eBibliotheke(eGameBoard& board) :
    ePatrolBuilding(board,
                    &eBuildingTextures::fBibliotheke,
                    -1.12, -3.17,
                    &eBuildingTextures::fBibliothekeOverlay,
                    [this]() { return e::make_shared<eScholar>(getBoard()); },
                    eBuildingType::bibliotheke, 2, 2, 5) {
    eGameTextures::loadBibliotheke();
}
