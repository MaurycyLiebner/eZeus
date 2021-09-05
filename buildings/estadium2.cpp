#include "estadium2.h"

#include "characters/egymnast.h"
#include "characters/actions/epatrolaction.h"
#include "textures/egametextures.h"

eStadium2Base::eStadium2Base(eGameBoard& board,
                             const eBaseTex baseTex) :
    ePatrolTarget(board, eBuildingType::gymnasium,
                  baseTex, 0, 0, eOverlays(),
                  [this]() { return e::make_shared<eGymnast>(getBoard()); },
                  eBuildingType::stadium2, 5, 5, 0) {

}

void eStadium2Base::timeChanged(const int by) {
    mOverlayTime += by;
    if(mOverlayTime > 1000) {
        mOverlayTime = 0;
        mOverlayId = (mOverlayId + 1) % 4;
    }
    ePatrolTarget::timeChanged(by);
}

eStadium2W::eStadium2W(eGameBoard& board) :
    eStadium2Base(board, &eBuildingTextures::fStadium2W) {
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

eStadium2H::eStadium2H(eGameBoard& board) :
    eStadium2Base(board, &eBuildingTextures::fStadium2H) {
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
