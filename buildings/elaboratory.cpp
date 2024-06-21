#include "elaboratory.h"

#include "characters/einventor.h"
#include "textures/egametextures.h"

eLaboratory::eLaboratory(eGameBoard& board) :
    ePatrolTarget(board,
                  &eBuildingTextures::fLaboratory,
                  -5.55, -7.48,
                  &eBuildingTextures::fLaboratoryOverlay,
                  [this]() { return e::make_shared<eInventor>(getBoard()); },
                  eBuildingType::laboratory, 4, 4, 9) {
    eGameTextures::loadLaboratory();
}
