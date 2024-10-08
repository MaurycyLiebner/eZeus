#include "etemplestatuebuilding.h"

#include "textures/egametextures.h"
#include "engine/egameboard.h"

eTempleStatueBuilding::eTempleStatueBuilding(
        const eGodType god,
        const int id, eGameBoard& board) :
    eSanctBuilding({0, 0, 1}, 1, board,
                   eBuildingType::templeStatue, 1, 1),
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
    case eGodType::aphrodite:
        coll = &blds.fAphroditeStatues;
        break;
    case eGodType::apollo:
        coll = &blds.fApolloStatues;
        break;
    case eGodType::ares:
        coll = &blds.fAresStatues;
        break;
    case eGodType::artemis:
        coll = &blds.fArtemisStatues;
        break;
    case eGodType::athena:
        coll = &blds.fAthenaStatues;
        break;
    case eGodType::atlas:
        coll = &blds.fAtlasStatues;
        break;
    case eGodType::demeter:
        coll = &blds.fDemeterStatues;
        break;
    case eGodType::dionysus:
        coll = &blds.fDionysusStatues;
        break;
    case eGodType::hades:
        coll = &blds.fHadesStatues;
        break;
    case eGodType::hephaestus:
        coll = &blds.fHephaestusStatues;
        break;
    case eGodType::hera:
        coll = &blds.fHeraStatues;
        break;
    case eGodType::hermes:
        coll = &blds.fHermesStatues;
        break;
    case eGodType::poseidon:
        coll = &blds.fPoseidonStatues;
        break;
    case eGodType::zeus:
        coll = &blds.fZeusStatues;
        break;
    }
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
    if(!coll) return nullptr;
    return coll->getTexture(dirId);
}
