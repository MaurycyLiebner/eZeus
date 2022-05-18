#include "etemplemonumentbuilding.h"

#include "textures/egametextures.h"

eTempleMonumentBuilding::eTempleMonumentBuilding(
        const eGodType god,
        const int id, eGameBoard& board) :
    eSanctBuilding({0, 5, 0}, 2, board, eBuildingType::templeMonument, 2, 2),
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
    case eGodType::aphrodite:
        coll = &blds.fAphroditeMonuments;
        break;
    case eGodType::apollo:
        coll = &blds.fApolloMonuments;
        break;
    case eGodType::ares:
        coll = &blds.fAresMonuments;
        break;
    case eGodType::artemis:
        coll = &blds.fArtemisMonuments;
        break;
    case eGodType::athena:
        coll = &blds.fAthenaMonuments;
        break;
    case eGodType::atlas:
        coll = &blds.fAtlasMonuments;
        break;
    case eGodType::demeter:
        coll = &blds.fDemeterMonuments;
        break;
    case eGodType::dionysus:
        coll = &blds.fDionysusMonuments;
        break;
    case eGodType::hades:
        coll = &blds.fHadesMonuments;
        break;
    case eGodType::hephaestus:
        coll = &blds.fHephaestusMonuments;
        break;
    case eGodType::hera:
        coll = &blds.fHeraMonuments;
        break;
    case eGodType::hermes:
        coll = &blds.fHermesMonuments;
        break;
    case eGodType::poseidon:
        coll = &blds.fPoseidonMonuments;
        break;
    case eGodType::zeus:
        coll = &blds.fZeusMonuments;
        break;
    }

    if(!coll) return nullptr;
    return coll->getTexture(mId);
}
