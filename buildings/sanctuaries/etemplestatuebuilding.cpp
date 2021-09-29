#include "etemplestatuebuilding.h"

#include "textures/egametextures.h"

eTempleStatueBuilding::eTempleStatueBuilding(
        const eGodType god,
        const int id, eGameBoard& board) :
    eBuilding(board, eBuildingType::templeStatue, 1, 1),
    mGod(god), mId(id) {

}

std::shared_ptr<eTexture>
eTempleStatueBuilding::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    const eTextureCollection* coll = nullptr;
    switch(mGod) {
    case eGodType::hephaestus:
        coll = &blds.fHephaestusStatues;
        break;
    }

    if(!coll) return nullptr;
    return coll->getTexture(mId);
}
