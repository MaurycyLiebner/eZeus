#include "eheroshall.h"

#include "textures/egametextures.h"

eBuildingType eHerosHall::sHeroTypeToHallType(const eHeroType type) {
    switch(type) {
    case eHeroType::achilles: return eBuildingType::achillesHall;
    case eHeroType::atalanta: return eBuildingType::atalantaHall;
    case eHeroType::bellerophon: return eBuildingType::bellerophonHall;
    case eHeroType::hercules: return eBuildingType::herculesHall;
    case eHeroType::jason: return eBuildingType::jasonHall;
    case eHeroType::odysseus: return eBuildingType::odysseusHall;
    case eHeroType::perseus: return eBuildingType::perseusHall;
    case eHeroType::theseus: return eBuildingType::theseusHall;
    }
}

eHeroType eHerosHall::sHallTypeToHeroType(const eBuildingType type,
                                          bool* const valid) {
    if(valid) *valid = true;
    switch(type) {
    case eBuildingType::achillesHall: return eHeroType::achilles;
    case eBuildingType::atalantaHall: return eHeroType::atalanta;
    case eBuildingType::bellerophonHall: return eHeroType::bellerophon;
    case eBuildingType::herculesHall: return eHeroType::hercules;
    case eBuildingType::jasonHall: return eHeroType::jason;
    case eBuildingType::odysseusHall: return eHeroType::odysseus;
    case eBuildingType::perseusHall: return eHeroType::perseus;
    case eBuildingType::theseusHall: return eHeroType::theseus;
    default: break;
    }
    if(valid) *valid = false;
    return eHeroType::achilles;
}

eHerosHall::eHerosHall(const eHeroType type, eGameBoard& board) :
    eBuilding(board, sHeroTypeToHallType(type), 4, 4),
    mType(type) {
    setOverlayEnabledFunc([]() { return true; });
}

std::shared_ptr<eTexture> eHerosHall::getTexture(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings()[sizeId];
    return texs.fHeroHall;
}

std::vector<eOverlay> eHerosHall::getOverlays(const eTileSize size) const {
    const int sizeId = static_cast<int>(size);
    const auto& texs = eGameTextures::buildings()[sizeId];
    const auto& statues = texs.fHeroStatues;
    int id;
    switch(mType) {
    case eHeroType::achilles:
        id = 0;
        break;
    case eHeroType::hercules:
        id = 1;
        break;
    case eHeroType::jason:
        id = 2;
        break;
    case eHeroType::odysseus:
        id = 3;
        break;
    case eHeroType::perseus:
        id = 4;
        break;
    case eHeroType::theseus:
        id = 5;
        break;
    case eHeroType::bellerophon:
        id = 6;
        break;
    case eHeroType::atalanta:
        id = 7;
        break;
    }
    eOverlay o;
    o.fTex = statues.getTexture(id);
    o.fX = 0;
    o.fY = -1.5;
    o.fAlignTop = true;
    return {o};
}
