#include "ecardingshed.h"

#include "characters/eshepherd.h"
#include "textures/egametextures.h"
#include "characters/actions/eshepherdaction.h"

stdsptr<eResourceCollectorBase> cardingShedCharGenerator(eGameBoard& board) {
    return e::make_shared<eShepherd>(board);
}

eCardingShed::eCardingShed(eGameBoard& board) :
    eShepherBuildingBase(board, &eBuildingTextures::fCardingShed,
                         -0.98, -2.15,
                         &eBuildingTextures::fCardingShedOverlay,
                         cardingShedCharGenerator,
                         eBuildingType::cardingShed,
                         eResourceType::fleece,
                         eCharacterType::sheep,
                         2, 2, 8),
    mTextures(eGameTextures::buildings())  {
    eGameTextures::loadCardingShed();
}

std::vector<eOverlay> eCardingShed::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::interface()[sizeId];
    auto os = eShepherBuildingBase::getOverlays(size);
    if(resource() > 0) {
        const int res = std::clamp((resource() + 1)/2, 0, 4);

        for(int i = 0; i < res; i++) {
            eOverlay fleece;
            fleece.fTex = texs.fFleeceUnit;
            fleece.fX = 0.3 - i*0.2 + (i > 1 ? 0.5 : 0);
            fleece.fY = -1.6 - i*0.2;
            os.push_back(fleece);
        }
    }
    return os;
}

