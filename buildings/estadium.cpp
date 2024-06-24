#include "estadium.h"

#include "characters/ecompetitor.h"

#include "engine/egameboard.h"

#include "textures/egametextures.h"

eStadium::eStadium(eGameBoard& board, const bool r) :
    ePatrolTarget(board,
                  nullptr, 0, 0, eOverlays(),
                  [this]() { return e::make_shared<eCompetitor>(getBoard()); },
                  eBuildingType::stadium, r ? 5 : 10, r ? 10 : 5, 45),
    mRotated(r) {
    eGameTextures::loadStadium();
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
    auto& board = getBoard();
    const auto dir = board.direction();
    const bool dirRot = dir == eWorldDirection::E ||
                        dir == eWorldDirection::W;
    const bool dirReorder = dir == eWorldDirection::E ||
                            dir == eWorldDirection::S;
    if(mRotated) {
        const bool h2 = ty - r.y > 4;
        SDL_Rect rect;
        if(h2) {
            rect = SDL_Rect{r.x, r.y + 5, 5, 5};
        } else {
            rect = SDL_Rect{r.x, r.y, 5, 5};
        }
        if(dirRot) {
            if(h2 != dirReorder) {
                return {plcs.fStadium1W, false, rect};
            } else {
                return {plcs.fStadium2W, true, rect};
            }
        } else {
            if(h2 != dirReorder) {
                return {plcs.fStadium2H, true, rect};
            } else {
                return {plcs.fStadium1H, false, rect};
            }
        }
    } else {
        const bool h2 = tx - r.x > 4;
        SDL_Rect rect;
        if(h2) {
            rect = SDL_Rect{r.x + 5, r.y, 5, 5};
        } else {
            rect = SDL_Rect{r.x, r.y, 5, 5};
        }
        if(dirRot) {
            if(h2 != dirReorder) {
                return {plcs.fStadium2H, true, rect};
            } else {
                return {plcs.fStadium1H, false, rect};
            }
        } else {
            if(h2 != dirReorder) {
                return {plcs.fStadium2W, true, rect};
            } else {
                return {plcs.fStadium1W, false, rect};
            }
        }
    }
}

std::vector<eOverlay> eStadium::getOverlays(const eTileSize size) const {
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
