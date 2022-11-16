#include "ehorseranchenclosure.h"

#include "textures/egametextures.h"

#include "characters/ehorse.h"
#include "characters/actions/eanimalaction.h"

#include "ehorseranch.h"

eHorseRanchEnclosure::eHorseRanchEnclosure(eGameBoard& board) :
    eBuilding(board, eBuildingType::horseRanchEnclosure, 4, 4) {
    setEnabled(true);
}

void eHorseRanchEnclosure::erase() {
    mRanch->eBuilding::erase();
    eBuilding::erase();
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
    const auto walkable = eWalkableObject::sCreateRanch();
    const int tx = tile->x();
    const int ty = tile->y();
    const auto a = e::make_shared<eAnimalAction>(
                       h.get(), tx, ty, walkable);
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

void eHorseRanchEnclosure::setRanch(eHorseRanch* const ranch) {
    mRanch = ranch;
}

void eHorseRanchEnclosure::read(eReadStream& src) {
    eBuilding::read(src);

    int nh;
    src >> nh;
    for(int i = 0; i < nh; i++) {
        spawnHorse();
    }
}

void eHorseRanchEnclosure::write(eWriteStream& dst) const {
    eBuilding::write(dst);

    dst << mHorses.size();
}
