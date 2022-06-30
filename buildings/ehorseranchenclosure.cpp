#include "ehorseranchenclosure.h"

#include "textures/egametextures.h"

#include "characters/ehorse.h"
#include "characters/actions/eanimalaction.h"

eHorseRanchEnclosure::eHorseRanchEnclosure(
        eGameBoard& board, eHorseRanch* const hr) :
    eBuilding(board, eBuildingType::horseRanchEnclosure, 4, 4),
    mRanch(hr) {
    setEnabled(true);
}

std::shared_ptr<eTexture> eHorseRanchEnclosure::getTexture(
        const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    auto& blds = eGameTextures::buildings();
    return blds[sizeId].fHorseRanchEnclosure;
}

std::vector<eOverlay> eHorseRanchEnclosure::getOverlays(
        const eTileSize size) const {
    const auto ct = centerTile();
    if(!ct) return {};
    const int ctx = ct->x();
    const int cty = ct->y();
    std::vector<eOverlay> os;
    for(const auto& h : mHorses) {
        auto& o = os.emplace_back();
        o.fTex = h->getTexture(size);
        const auto t = h->tile();
        const int tx = t->x();
        const int ty = t->y();
        o.fX = tx + h->x() - ctx - 0.5;
        o.fY = ty + h->y() - cty - 3.5;
    }
    return os;
}

bool eHorseRanchEnclosure::spawnHorse() {
    if(mHorses.size() > 5) return false;
    const auto h = e::make_shared<eHorse>(getBoard());
    const auto tile = centerTile();
    h->changeTile(tile);
    const auto e = []() {};
    const auto walkable = [](eTileBase* const tile) {
        const auto t = tile->underBuildingType();
        if(t != eBuildingType::horseRanchEnclosure) return false;

        const auto bl = tile->bottomLeft();
        if(!bl) return false;
        const auto blt = bl->underBuildingType();
        if(blt != eBuildingType::horseRanchEnclosure) return false;

        const auto br = tile->bottomRight();
        if(!br) return false;
        const auto brt = br->underBuildingType();
        if(brt != eBuildingType::horseRanchEnclosure) return false;

        return true;
    };
    const int tx = tile->x();
    const int ty = tile->y();
    const auto a = e::make_shared<eAnimalAction>(
                       h.get(), e, e, tx, ty, walkable);
    a->setLayTime(500);
    a->setWalkTime(1);
    h->setAction(a);
    mHorses.push_back(h);
    return true;
}

bool eHorseRanchEnclosure::takeHorse() {
    if(mHorses.empty()) return false;
    auto& h = mHorses.back();
    h->kill();
    mHorses.pop_back();
    return true;
}
