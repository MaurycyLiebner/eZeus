#include "etemplemonumentbuilding.h"

#include "textures/egametextures.h"
#include "engine/egameboard.h"

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
    auto& board = getBoard();
    const auto dir = board.direction();
    int dirId;
    if(dir == eWorldDirection::N) {
        dirId = mId;
    } else if(dir == eWorldDirection::E) {
        if(mId == 0) {
            dirId = 3;
        } else if(mId == 1) {
            dirId = 0;
        } else if(mId == 2) {
            dirId = 1;
        } else { // if(mId == 3) {
            dirId = 2;
        }
    } else if(dir == eWorldDirection::S) {
        if(mId == 0) {
            dirId = 1;
        } else if(mId == 1) {
            dirId = 3;
        } else if(mId == 2) {
            dirId = 0;
        } else { // if(mId == 3) {
            dirId = 2;
        }
    } else { // if(dir == eWorldDirection::W) {
        if(mId == 0) {
            dirId = 1;
        } else if(mId == 1) {
            dirId = 2;
        } else if(mId == 2) {
            dirId = 3;
        } else { // if(mId == 3) {
            dirId = 0;
        }
    }
    return coll->getTexture(dirId);
}
