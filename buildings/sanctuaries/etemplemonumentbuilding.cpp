#include "etemplemonumentbuilding.h"

#include "textures/egametextures.h"

eTempleMonumentBuilding::eTempleMonumentBuilding(
        const eGodType god,
        const int id, eGameBoard& board) :
    eSanctBuilding(board, eBuildingType::templeMonument, 2, 2),
    mGod(god), mId(id) {

}

std::shared_ptr<eTexture>
eTempleMonumentBuilding::getTexture(const eTileSize size) const {
    const int p = progress();
    if(p <= 0) return nullptr;
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    if(p == 1) {
        return blds.fBlankMonument;
    }
    const eTextureCollection* coll = nullptr;
    switch(mGod) {
    case eGodType::hephaestus:
        coll = &blds.fHephaestusMonuments;
        break;
    case eGodType::artemis:
        coll = &blds.fArtemisMonuments;
        break;
    }

    if(!coll) return nullptr;
    return coll->getTexture(mId);
}
