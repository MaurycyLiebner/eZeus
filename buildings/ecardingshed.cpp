#include "ecardingshed.h"

#include "characters/eshepherd.h"
#include "textures/egametextures.h"
#include "characters/actions/eshepherdaction.h"

stdsptr<eResourceCollector> cardingShedCharGenerator(eGameBoard& board) {
    return e::make_shared<eShepherd>(board);
}

eCardingShed::eCardingShed(eGameBoard& board) :
    eShepherBuildingBase(board, &eBuildingTextures::fCardingShed,
                         -1.35, -2.95,
                         &eBuildingTextures::fCardingShedOverlay,
                         cardingShedCharGenerator,
                         eBuildingType::cardingShed,
                         eResourceType::fleece,
                         eCharacterType::sheep,
                         2, 2, 8),
    mTextures(eGameTextures::buildings())  {

}
