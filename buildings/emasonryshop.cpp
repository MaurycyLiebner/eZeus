#include "emasonryshop.h"

#include "characters/emarbleminer.h"
#include "textures/egametextures.h"

#include "textures/emarbletile.h"

#include "characters/ecarttransporter.h"

#include "characters/actions/efollowaction.h"
#include "characters/actions/emovetoaction.h"

void transformMarble(eTile* const t) {
    if(eMarbleTile::isEdge(t)) {
        t->setMarbleLevel(1);
    } else {
        const int l = t->marbleLevel();
        if(l == 0) {
            t->setMarbleLevel(1);
            t->setResource(100);
        } else {
            t->setMarbleLevel(2);
        }
    }
}

bool hasMarble(eTileBase* const t) {
    const int r = t->resource();
    if(r <= 0) return false;
    return t->terrain() == eTerrain::marble;
}

eMasonryShop::eMasonryShop(eGameBoard& board) :
    eResourceCollectBuilding(board,
                             &eBuildingTextures::fMasonryShop,
                             0, 0, nullptr,
                             [this]() { return e::make_shared<eMarbleMiner>(getBoard()); },
                             eBuildingType::masonryShop,
                             hasMarble, transformMarble, 2, 2, 15,
                             eResourceType::marble) {
    setAddResource(false);
}

std::vector<eOverlay>
eMasonryShop::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& btexs = eGameTextures::buildings()[sizeId];
    std::vector<eOverlay> os;
    const int t = textureTime();
    if(mRawCount) {
        const auto& stones = btexs.fMasonryShopStones;
        const int sid = std::clamp(8 - mRawCount, 0, stones.size());
        eOverlay o;
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
        os.push_back(o);

        if(sid < 4) {
            eOverlay o;
            const auto& ov = btexs.fMasonryShopOverlay1[0];
            const int id = t % ov.size();
            o.fTex = ov.getTexture(id);
            o.fX = 0.50;
            o.fY = -0.90;
            os.push_back(o);
        } else {
            eOverlay o;
            const auto& ov = btexs.fMasonryShopOverlay2[0];
            const int id = t % ov.size();
            o.fTex = ov.getTexture(id);
            o.fX = 0.50;
            o.fY = -1.00;
            os.push_back(o);
        }
    } else {
        eOverlay o;
        const auto& ov = btexs.fMasonryShopOverlay0[3];
        const int id = t % ov.size();
        o.fTex = ov.getTexture(id);
        o.fX = 0.50;
        o.fY = -1.50;
        os.push_back(o);
    }

    return os;
}

void eMasonryShop::timeChanged(const int by) {
    if(!mCollectActionSet) {
        mCollectActionSet = true;
        setCollectAction();
    }
    const int proccessTime = 3000;
    if(enabled()) {
        mProcessTime += by;
        if(mProcessTime > proccessTime) {
            mProcessTime -= proccessTime;
            if(mRawCount > 0) {
                const int c = eResourceCollectBuilding::add(
                                  eResourceType::marble, 1);
                mRawCount -= c;
                if(mRawCount <= 0) enableSpawn();
            }
        }
    }
    eResourceCollectBuilding::timeChanged(by);
}

void eMasonryShop::addRaw() {
    mRawCount = 8;
    disableSpawn();
}

void eMasonryShop::setCollectAction() {
    const stdptr<eMasonryShop> tptr(this);
    setCollectedAction([tptr, this](eTile* const tile) {
        if(!tptr) return;
        auto& board = getBoard();

        const auto r = e::make_shared<eCartTransporter>(board);
        r->changeTile(tile);
        r->setBigTrailer(true);
        r->setResource(eResourceType::marble, 1);

        const auto finish = [tptr, this]() {
            if(!tptr) return;
            addRaw();
        };
        const auto a = e::make_shared<eMoveToAction>(
                           r.get(), [](){}, finish);
        a->start(this);
        r->setAction(a);
        r->setActionType(eCharacterActionType::walk);
    });
}
