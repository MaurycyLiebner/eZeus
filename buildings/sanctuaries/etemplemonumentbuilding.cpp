#include "etemplemonumentbuilding.h"

#include "textures/egametextures.h"

eTempleMonumentBuilding::eTempleMonumentBuilding(
        const eGodType god,
        const int id, eGameBoard& board) :
    eBuilding(board, eBuildingType::templeMonument, 2, 2),
    mGod(god), mId(id) {

}

std::shared_ptr<eTexture>
eTempleMonumentBuilding::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    const eTextureCollection* coll = nullptr;
    switch(mGod) {
    case eGodType::hephaestus:
        coll = &blds.fHephaestusMonuments;
        break;
    }

    if(!coll) return nullptr;
    return coll->getTexture(mId);
}
