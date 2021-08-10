#include "ehuntinglodge.h"

#include "characters/ehunter.h"
#include "textures/egametextures.h"

eHuntingLodge::eHuntingLodge(eGameBoard& board) :
    eBuilding(board, eBuildingType::huntingLodge, 2, 2),
    mTextures(eGameTextures::buildings())  {

}

eTexture eHuntingLodge::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].fHuntingLodge;
}

std::vector<eOverlay> eHuntingLodge::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& coll = mTextures[sizeId].fHuntingLodgeOverlay;
    const int texId = textureTime() % coll.size();
    eOverlay o;
    o.fTex = coll.getTexture(texId);
    o.fX = -1.95;
    o.fY = -2.4;
    return std::vector<eOverlay>({o});
}
