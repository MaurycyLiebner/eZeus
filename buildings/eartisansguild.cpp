#include "eartisansguild.h"

#include "textures/egametextures.h"
#include "characters/actions/eartisanaction.h"

eArtisansGuild::eArtisansGuild(eGameBoard& board) :
    eEmployingBuilding(board, eBuildingType::artisansGuild, 2, 2, 25) {

}

eArtisansGuild::~eArtisansGuild() {
    if(mArtisan) mArtisan->kill();
}

std::shared_ptr<eTexture> eArtisansGuild::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings()[sizeId];
    return texs.fArtisansGuild;
}

std::vector<eOverlay> eArtisansGuild::
    getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings()[sizeId];

    const auto& coll = texs.fArtisansGuildOverlay;
    const int texId = textureTime() % coll.size();
    eOverlay o;
    o.fTex = coll.getTexture(texId);
    o.fX = -1.45;
    o.fY = -3.0;

    return {o};
}

void eArtisansGuild::timeChanged(const int by) {
    if(enabled()) {
        if(!mArtisan) spawnArtisan(&eArtisansGuild::mArtisan);
    }
    eEmployingBuilding::timeChanged(by);
}

bool eArtisansGuild::spawnArtisan(const eArtisanPtr artisan) {
    const auto t = centerTile();
    auto& g = this->*artisan;
    this->*artisan = e::make_shared<eArtisan>(getBoard());
    g->changeTile(t);
    const eStdPointer<eArtisansGuild> tptr(this);
    const auto finishAct = [tptr, this, artisan]() {
        if(!tptr) return;
        auto& g = this->*artisan;
        if(g) g->kill();
        g = nullptr;
    };
    const auto a = e::make_shared<eArtisanAction>(
                       this, g.get(),
                       finishAct, finishAct);
    g->setAction(a);
    return true;
}
