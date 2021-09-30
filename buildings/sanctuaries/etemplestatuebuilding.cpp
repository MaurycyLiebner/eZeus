#include "etemplestatuebuilding.h"

#include "textures/egametextures.h"

eTempleStatueBuilding::eTempleStatueBuilding(
        const eGodType god,
        const int id, eGameBoard& board) :
    eSanctBuilding({0, 0, 1}, 1, board, eBuildingType::templeStatue, 1, 1),
    mGod(god), mId(id) {

}

std::shared_ptr<eTexture>
eTempleStatueBuilding::getTexture(const eTileSize size) const {
    const int p = progress();
    if(p <= 0) return nullptr;
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    const eTextureCollection* coll = nullptr;
    switch(mGod) {
    case eGodType::hephaestus:
        coll = &blds.fHephaestusStatues;
        break;
    case eGodType::artemis:
        coll = &blds.fArtemisStatues;
        break;
    }

    if(!coll) return nullptr;
    return coll->getTexture(mId);
}
