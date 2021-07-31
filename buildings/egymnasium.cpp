#include "egymnasium.h"

eGymnasium::eGymnasium(std::vector<eBuildingTextures>& texs) :
    eBuilding(eBuildingType::gymnasium, 3, 3), mTextures(texs) {

}

eTexture eGymnasium::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    return mTextures[sizeId].fGymnasium;
}

std::vector<eOverlay> eGymnasium::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& coll = mTextures[sizeId].fGymnasiumOverlay;
    const int texId = (time()/4) % coll.size();
    eOverlay o;
    o.fTex = coll.getTexture(texId);
    o.fX = 0.30;
    o.fY = -1.7;
    return std::vector<eOverlay>({o});
}

void eGymnasium::setMovePath(const eMovePath& path) {
    mMovePath = path;
}
