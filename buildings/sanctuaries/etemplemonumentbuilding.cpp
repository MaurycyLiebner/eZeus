#include "etemplemonumentbuilding.h"

#include "textures/egametextures.h"

eTempleMonumentBuilding::eTempleMonumentBuilding(
        const eGodType god,
        const int id, eGameBoard& board) :
    eSanctBuilding({0, 5, 0}, 2, board,
                   eBuildingType::templeMonument, 2, 2),
    mGod(god), mId(id) {

}

const eTextureCollection* eTempleMonumentBuilding::sGodMonumentTextureCollection(
        const eTileSize size, const eGodType god) {
    const int sizeId = static_cast<int>(size);
    const auto& blds = eGameTextures::buildings()[sizeId];
    switch(god) {
    case eGodType::aphrodite:
        return &blds.fAphroditeMonuments;
    case eGodType::apollo:
        return &blds.fApolloMonuments;
    case eGodType::ares:
        return &blds.fAresMonuments;
    case eGodType::artemis:
        return &blds.fArtemisMonuments;
    case eGodType::athena:
        return &blds.fAthenaMonuments;
    case eGodType::atlas:
        return &blds.fAtlasMonuments;
    case eGodType::demeter:
        return &blds.fDemeterMonuments;
    case eGodType::dionysus:
        return &blds.fDionysusMonuments;
    case eGodType::hades:
        return &blds.fHadesMonuments;
    case eGodType::hephaestus:
        return &blds.fHephaestusMonuments;
    case eGodType::hera:
        return &blds.fHeraMonuments;
    case eGodType::hermes:
        return &blds.fHermesMonuments;
    case eGodType::poseidon:
        return &blds.fPoseidonMonuments;
    case eGodType::zeus:
        return &blds.fZeusMonuments;
    }
    return nullptr;
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
    const auto coll = sGodMonumentTextureCollection(size, mGod);

    if(!coll) return nullptr;
    return coll->getTexture(mId);
}
