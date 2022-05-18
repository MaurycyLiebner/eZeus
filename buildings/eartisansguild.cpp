#include "eartisansguild.h"

#include "textures/egametextures.h"

eArtisansGuild::eArtisansGuild(eGameBoard& board) :
    eEmployingBuilding(board, eBuildingType::artisansGuild, 2, 2, 25) {

}

eArtisansGuild::~eArtisansGuild() {

}

std::shared_ptr<eTexture> eArtisansGuild::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings()[sizeId];
    return texs.fArtisansGuild;
}

std::vector<eOverlay> eArtisansGuild::
    getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto texs = eGameTextures::buildings()[sizeId];

    const auto& coll = texs.fArtisansGuildOverlay;
    const int texId = textureTime() % coll.size();
    eOverlay o;
    o.fTex = coll.getTexture(texId);
    o.fX = -1.45;
    o.fY = -3.0;

    return {o};
}
