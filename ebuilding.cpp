#include "ebuilding.h"

eBuilding::eBuilding(eTexture& tex,
                     const std::vector<std::pair<int, int>>& overlayPos,
                     std::vector<eTextureCollection>& overlays) :
    mTex(tex), mOverlayPos(overlayPos), mOverlays(overlays) {

}

void eBuilding::draw(ePainter& p,
                     const int x, const int y,
                     const eAlignment align) {
    p.drawTexture(x, y, mTex, align);
    const int texTime = mTime/4;
    const int iMax = mOverlays.size();
    for(int i = 0; i < iMax; i++) {
        const auto& o = mOverlays[i];
        const auto& pos = mOverlayPos[i];
        const int texId = texTime % o.size();
        p.drawTexture(x + pos.first,
                      y + pos.second,
                      o.getTexture(texId), align);
    }
}
