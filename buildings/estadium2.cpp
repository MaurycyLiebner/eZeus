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
    mOverlayTime++;
    if(mOverlayTime > 2000) {
        mOverlayTime = 0;
        mOverlayId = (mOverlayId + 1) % 5;
    }
    ePatrolTarget::timeChanged(by);
}

eStadium2W::eStadium2W(eGameBoard& board, eStadium1W* const s1) :
    eStadium2Base(board, &eBuildingTextures::fStadium2W, s1) {
}

std::vector<eOverlay> eStadium2W::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings()[sizeId];

    std::vector<eOverlay> os;

    const int tt = textureTime();

    {
        const auto& coll = texs.fStadiumAudiance1W;
        eOverlay a0;
        a0.fX = -2.1;
        a0.fY = -7.2;
        const int ttt = tt % coll.size();
        a0.fTex = coll.getTexture(ttt);
        os.push_back(a0);
    }
    {
        const auto& coll = texs.fStadiumAudiance2W;
        eOverlay a0;
        a0.fX = -2.1;
        a0.fY = -3.5;
        const int ttt = tt % coll.size();
        a0.fTex = coll.getTexture(ttt);
        os.push_back(a0);
    }


    bool wrap = true;
    double ox = 0;
    double oy = -5;
    const eTextureCollection* coll = nullptr;
    const int oi = overlayId();
    if(oi == 0) {
        coll = &texs.fStadiumOverlay1;
        ox -= 2;
    } else if(oi == 1) {
        coll = &texs.fStadiumOverlay5W;
        wrap = false;
        ox -= 1;
    } else if(oi == 2) {
        coll = &texs.fStadiumOverlay3;
        ox -= 1;
    } else if(oi == 3) {
        coll = &texs.fStadiumOverlay4W;
        wrap = false;
    } else {
        coll = &texs.fStadiumOverlay2;
        ox -= 3;
    }
    const int t = overlayTime();

    const int ttt = wrap ? t % coll->size() :
                           std::clamp(t, 0, coll->size() - 1);
    os.push_back(eOverlay{ox, oy, coll->getTexture(ttt)});
    return os;
}

eStadium2H::eStadium2H(eGameBoard& board, eStadium1H* const s1) :
    eStadium2Base(board, &eBuildingTextures::fStadium2H, s1) {
}

std::vector<eOverlay> eStadium2H::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings()[sizeId];
    const int tt = textureTime();

    std::vector<eOverlay> os;

    {
        const auto& coll = texs.fStadiumAudiance1H;
        eOverlay a0;
        a0.fX = -2.0;
        a0.fY = -7.5;
        const int ttt = tt % coll.size();
        a0.fTex = coll.getTexture(ttt);
        os.push_back(a0);
    }
    {
        const auto& coll = texs.fStadiumAudiance2H;
        eOverlay a0;
        a0.fX = 1.5;
        a0.fY = -7.5;
        const int ttt = tt % coll.size();
        a0.fTex = coll.getTexture(ttt);
        os.push_back(a0);
    }

    bool wrap = true;
    double ox = 0;
    double oy = -6;
    const eTextureCollection* coll = nullptr;
    const int oi = overlayId();
    if(oi == 0) {
        coll = &texs.fStadiumOverlay1;
        oy -= 2;
    } else if(oi == 1) {
        coll = &texs.fStadiumOverlay5H;
        wrap = false;
    } else if(oi == 2) {
        coll = &texs.fStadiumOverlay3;
        oy -= 1;
    } else if(oi == 3) {
        coll = &texs.fStadiumOverlay4H;
        wrap = false;
        oy += 0.5;
    } else {
        coll = &texs.fStadiumOverlay2;
        oy -= 3;
    }

    const int t = overlayTime();

    const int ttt = wrap ? t % coll->size() :
                           std::clamp(t, 0, coll->size() - 1);
    os.push_back(eOverlay{ox, oy, coll->getTexture(ttt)});
    return os;
}
