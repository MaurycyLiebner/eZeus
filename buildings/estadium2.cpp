#include "estadium2.h"

#include "characters/egymnast.h"
#include "characters/actions/epatrolaction.h"
#include "textures/egametextures.h"
#include "estadium1.h"

eStadium2Base::eStadium2Base(eGameBoard& board,
                             const eBaseTex baseTex,
                             eStadium1Base* const s1) :
    ePatrolTarget(board, eBuildingType::gymnasium,
                  baseTex, 0, 0, eOverlays(),
                  [this]() { return e::make_shared<eGymnast>(getBoard()); },
                  eBuildingType::stadium2, 5, 5, 0) {
    setOverlayEnabledFunc([this, s1]() {
        const auto t = enabled() && spawnPatrolers();
        if(t) return true;
        const auto s = s1->enabled() && s1->spawnPatrolers();
        return s;
    });
}

void eStadium2Base::timeChanged(const int by) {
    mOverlayTime += by;
    if(mOverlayTime > 1000) {
        mOverlayTime = 0;
        mOverlayId = (mOverlayId + 1) % 4;
    }
    ePatrolTarget::timeChanged(by);
}

eStadium2W::eStadium2W(eGameBoard& board, eStadium1W* const s1) :
    eStadium2Base(board, &eBuildingTextures::fStadium2W, s1) {
}

std::vector<eOverlay> eStadium2W::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings()[sizeId];
    const int t = textureTime();

    std::vector<eOverlay> os;

    {
        const auto& coll = texs.fStadiumAudiance1W;
        eOverlay a0;
        a0.fX = -2.1;
        a0.fY = -7.2;
        const int tt = t % coll.size();
        a0.fTex = coll.getTexture(tt);
        os.push_back(a0);
    }
    {
        const auto& coll = texs.fStadiumAudiance2W;
        eOverlay a0;
        a0.fX = -2.1;
        a0.fY = -3.5;
        const int tt = t % coll.size();
        a0.fTex = coll.getTexture(tt);
        os.push_back(a0);
    }


    double ox = 0;
    double oy = -5;
    const eTextureCollection* coll = nullptr;
    const int oi = overlayId();
    if(oi == 0) {
        coll = &texs.fStadiumOverlay1;
        ox -= 2;
    } else if(oi == 1) {
        coll = &texs.fStadiumOverlay2;
    } else if(oi == 2) {
        coll = &texs.fStadiumOverlay3;
        ox -= 1;
    } else {
        coll = &texs.fStadiumOverlay4W;
    }
    const int tt = t % coll->size();
    os.push_back(eOverlay{ox, oy, coll->getTexture(tt)});
    return os;
}

eStadium2H::eStadium2H(eGameBoard& board, eStadium1H* const s1) :
    eStadium2Base(board, &eBuildingTextures::fStadium2H, s1) {
}

std::vector<eOverlay> eStadium2H::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings()[sizeId];
    const int t = textureTime();

    std::vector<eOverlay> os;

    {
        const auto& coll = texs.fStadiumAudiance1H;
        eOverlay a0;
        a0.fX = -2.0;
        a0.fY = -7.5;
        const int tt = t % coll.size();
        a0.fTex = coll.getTexture(tt);
        os.push_back(a0);
    }
    {
        const auto& coll = texs.fStadiumAudiance2H;
        eOverlay a0;
        a0.fX = 1.5;
        a0.fY = -7.5;
        const int tt = t % coll.size();
        a0.fTex = coll.getTexture(tt);
        os.push_back(a0);
    }


    double ox = 0;
    double oy = -6;
    const eTextureCollection* coll = nullptr;
    const int oi = overlayId();
    if(oi == 0) {
        coll = &texs.fStadiumOverlay1;
        oy -= 2;
    } else if(oi == 1) {
        coll = &texs.fStadiumOverlay2;
    } else if(oi == 2) {
        coll = &texs.fStadiumOverlay3;
        oy -= 1;
    } else {
        coll = &texs.fStadiumOverlay4H;
        oy += 1;
    }
    const int tt = t % coll->size();
    os.push_back(eOverlay{ox, oy, coll->getTexture(tt)});
    return os;
}
