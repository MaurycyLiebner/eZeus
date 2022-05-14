#include "edairy.h"

#include "characters/egoatherd.h"
#include "textures/egametextures.h"
#include "characters/actions/eshepherdaction.h"

stdsptr<eResourceCollectorBase> dairyCharGenerator(eGameBoard& board) {
    return e::make_shared<eGoatherd>(board);
}

eDairy::eDairy(eGameBoard& board) :
    eShepherBuildingBase(board, &eBuildingTextures::fDairy,
                         -1.35, -2.95,
                         &eBuildingTextures::fDairyOverlay,
                         dairyCharGenerator,
                         eBuildingType::dairy,
                         eResourceType::cheese,
                         eCharacterType::goat,
                         2, 2, 8),
    mTextures(eGameTextures::buildings())  {

}

std::vector<eOverlay> eDairy::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = mTextures[sizeId];
    auto os = eShepherBuildingBase::getOverlays(size);
    if(resource() > 0) {
        eOverlay cheeese;
        const int res = std::clamp(resource() - 1, 0, 4);
        cheeese.fTex = texs.fWaitingCheese.getTexture(res);
        cheeese.fX = 0;
        cheeese.fY = -1.5;

        os.push_back(cheeese);
    }
    return os;
}
