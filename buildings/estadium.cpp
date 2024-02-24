#include "estadium.h"

#include "characters/egymnast.h"

#include "engine/egameboard.h"

#include "textures/egametextures.h"

eStadium::eStadium(eGameBoard& board, const bool r) :
    ePatrolTarget(board, eBuildingType::gymnasium,
                  nullptr, 0, 0, eOverlays(),
                  [this]() { return e::make_shared<eGymnast>(getBoard()); },
                  eBuildingType::stadium, r ? 5 : 10, r ? 10 : 5, 45),
    mRotated(r) {
    board.registerStadium(this);
}

eStadium::~eStadium() {
    auto& b = getBoard();
    b.unregisterStadium();
}

void eStadium::timeChanged(const int by) {
    mOverlayTime++;
    if(mOverlayTime > 500) {
        mOverlayTime = 0;
        mOverlayId = (mOverlayId + 1) % 5;
    }
    ePatrolTarget::timeChanged(by);
}

eTextureSpace eStadium::getTextureSpace(const int tx, const int ty,
                                        const eTileSize size) const {
    const SDL_Point p{tx, ty};
    const auto r = tileRect();
    if(!SDL_PointInRect(&p, &r)) return {nullptr};
    const auto& blds = eGameTextures::buildings();
    const int sizeId = static_cast<int>(size);
    const auto& plcs = blds[sizeId];
    if(mRotated) {
        if(ty - r.y > 4) return {plcs.fStadium2H, SDL_Rect{r.x, r.y + 5, 5, 5}};
        else return {plcs.fStadium1H, SDL_Rect{r.x, r.y, 5, 5}};
    } else {
        if(tx - r.x > 4) return {plcs.fStadium2W, SDL_Rect{r.x + 5, r.y, 5, 5}};
        else return {plcs.fStadium1W, SDL_Rect{r.x, r.y, 5, 5}};
    }
}

std::shared_ptr<eTexture> eStadium::getTexture1(const eTileSize size) const {
    const auto& blds = eGameTextures::buildings();
    const int sizeId = static_cast<int>(size);
    if(mRotated) {
        return blds[sizeId].fStadium1H;
    } else {
        return blds[sizeId].fStadium1W;
    }
}

std::shared_ptr<eTexture> eStadium::getTexture2(const eTileSize size) const {
    const auto& blds = eGameTextures::buildings();
    const int sizeId = static_cast<int>(size);
    if(mRotated) {
        return blds[sizeId].fStadium2H;
    } else {
        return blds[sizeId].fStadium2W;
    }
}

std::vector<eOverlay> eStadium::getOverlays2(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings()[sizeId];

    std::vector<eOverlay> os;

    const int tt = textureTime();
    if(mRotated) {
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
    } else {
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
    }
    return os;
}
