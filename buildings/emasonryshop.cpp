#include "emasonryshop.h"

#include "characters/emarbleminer.h"
#include "textures/egametextures.h"

#include "textures/emarbletile.h"

#include "characters/ecarttransporter.h"

#include "characters/actions/efollowaction.h"
#include "characters/actions/emovetoaction.h"

#include "eiteratesquare.h"
#include "engine/egameboard.h"

bool hasMarble(eTileBase* const t) {
    const int r = t->resource();
    if(r <= 0) return false;
    return t->terrain() == eTerrain::marble;
}

eMasonryShop::eMasonryShop(eGameBoard& board) :
    eResourceCollectBuilding(board,
                             &eBuildingTextures::fMasonryShop,
                             0, 0, nullptr,
                             3, 0.5, -1.5,
                             [this]() { return e::make_shared<eMarbleMiner>(getBoard()); },
                             eBuildingType::masonryShop,
                             hasMarble, 2, 2, 15,
                             eResourceType::marble) {
    setAddResource(false);
    setRawInc(8);
    setRawCountCollect(0);
}

std::vector<eOverlay>
eMasonryShop::getOverlays(const eTileSize size) const {
    auto os = eResourceCollectBuilding::getOverlays(size);
    const int sizeId = static_cast<int>(size);
    const auto& btexs = eGameTextures::buildings()[sizeId];
    const int t = textureTime();
    const int rc = rawCount();
    if(rc) {
        const auto& stones = btexs.fMasonryShopStones;
        const int sid = std::clamp(8 - rc, 0, stones.size());

        eOverlay& o = os.emplace_back();
        o.fAlignTop = true;
        o.fTex = stones.getTexture(sid);
        o.fX = 0.25;
        o.fY = -0.75;
        if(sid > 0 && sid < 4) {
            o.fX -= 0.1;
            o.fY -= 0.1;
        } else if(sid == 4) {
            o.fY -= 0.15;
        } else if(sid == 5) {
            o.fX -= 0.10;
            o.fY -= 0.20;
        } else if(sid == 6) {
            o.fY -= 0.30;
        } else if(sid == 7) {
            o.fX -= 0.15;
            o.fY -= 0.5;
        }

        if(sid < 4) {
            eOverlay& o = os.emplace_back();
            const auto& ov = btexs.fMasonryShopOverlay1[0];
            const int id = t % ov.size();
            o.fTex = ov.getTexture(id);
            o.fX = 0.50;
            o.fY = -0.90;
        } else {
            eOverlay& o = os.emplace_back();
            const auto& ov = btexs.fMasonryShopOverlay2[0];
            const int id = t % ov.size();
            o.fTex = ov.getTexture(id);
            o.fX = 0.50;
            o.fY = -1.00;
        }
    }

    return os;
}

void eMasonryShop::timeChanged(const int by) {
    if(!mCollectActionSet) {
        mCollectActionSet = true;
        setCollectAction();
    }
    eResourceCollectBuilding::timeChanged(by);
}

void eMasonryShop::setCollectAction() {
    setCollectedAction(eTileActionType::masonry);
}
