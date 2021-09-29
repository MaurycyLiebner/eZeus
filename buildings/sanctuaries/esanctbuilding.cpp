#include "esanctbuilding.h"

#include "textures/egametextures.h"

eSanctBuilding::eSanctBuilding(eGameBoard& board,
                               const eBuildingType type,
                               const int sw, const int sh) :
    eBuilding(board, type, sw, sh) {
    setOverlayEnabledFunc([]() { return true; });
}

std::vector<eOverlay>
eSanctBuilding::getOverlays(const eTileSize size) const {
    if(mProgress) return {};
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    const auto& coll = blds.fSanctuarySpace;
    const int sd = seed();
    std::vector<eOverlay> os;
    const int sw = spanW();
    const int sh = spanH();
    os.reserve(sw*sh);
    double dx = 0;
    double dy = 0;
    if(sw == 2 && sh == 2) {
        dx = -0.5;
        dy = -1.5;
    } else if(sw == 4 && sh == 4) {
        dx = -1.5;
        dy = -4.5;
    }
    for(int x = 0; x < sw; x++) {
        for(int y = 0; y < sh; y++) {
            auto& o = os.emplace_back();
            const int id = (sd + x + y) % coll.size();
            o.fTex = coll.getTexture(id);
            o.fX = x + dx;
            o.fY = y + dy;
            o.fAlignTop = true;
        }
    }
    return os;
}
