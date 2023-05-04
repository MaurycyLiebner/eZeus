#include "eavailablebuildings.h"

#include "fileIO/ereadstream.h"
#include "fileIO/ewritestream.h"

#include "buildings/ebuilding.h"

void eAvailableBuildings::read(eReadStream& src) {
    src >> fWheatFarm;
    src >> fCarrotsFarm;
    src >> fOnionFarm;

    src >> fVine;
    src >> fOliveTree;
    src >> fOrangeTree;

    src >> fDairy;
    src >> fCardingShed;

    src >> fFishery;
    src >> fUrchinQuay;
    src >> fHuntingLodge;

    src >> fMint;
    src >> fFoundry;
    src >> fTimberMill;
    src >> fMasonryShop;

    src >> fWinery;
    src >> fOlivePress;
    src >> fSculptureStudio;

    src >> fAphroditeSanctuary;
    src >> fApolloSanctuary;
    src >> fAresSanctuary;
    src >> fArtemisSanctuary;
    src >> fAthenaSanctuary;
    src >> fAtlasSanctuary;
    src >> fDemeterSanctuary;
    src >> fDionysusSanctuary;
    src >> fHadesSanctuary;
    src >> fHephaestusSanctuary;
    src >> fHeraSanctuary;
    src >> fHermesSanctuary;
    src >> fPoseidonSanctuary;
    src >> fZeusSanctuary;

    src >> fAchillesHall;
    src >> fAtalantaHall;
    src >> fBellerophonHall;
    src >> fHerculesHall;
    src >> fJasonHall;
    src >> fOdysseusHall;
    src >> fPerseusHall;
    src >> fTheseusHall;

    src >> fArmory;

    src >> fPopulationMonument;
    src >> fVictoryMonument;
    src >> fColonyMonument;
    src >> fAthleteMonument;
    src >> fConquestMonument;
    src >> fHappinessMonument;
    src >> f7Monument;
    src >> f8Monument;
    src >> fScholarMonument;
}

void eAvailableBuildings::write(eWriteStream& dst) const {
    dst << fWheatFarm;
    dst << fCarrotsFarm;
    dst << fOnionFarm;

    dst << fVine;
    dst << fOliveTree;
    dst << fOrangeTree;

    dst << fDairy;
    dst << fCardingShed;

    dst << fFishery;
    dst << fUrchinQuay;
    dst << fHuntingLodge;

    dst << fMint;
    dst << fFoundry;
    dst << fTimberMill;
    dst << fMasonryShop;

    dst << fWinery;
    dst << fOlivePress;
    dst << fSculptureStudio;

    dst << fAphroditeSanctuary;
    dst << fApolloSanctuary;
    dst << fAresSanctuary;
    dst << fArtemisSanctuary;
    dst << fAthenaSanctuary;
    dst << fAtlasSanctuary;
    dst << fDemeterSanctuary;
    dst << fDionysusSanctuary;
    dst << fHadesSanctuary;
    dst << fHephaestusSanctuary;
    dst << fHeraSanctuary;
    dst << fHermesSanctuary;
    dst << fPoseidonSanctuary;
    dst << fZeusSanctuary;

    dst << fAchillesHall;
    dst << fAtalantaHall;
    dst << fBellerophonHall;
    dst << fHerculesHall;
    dst << fJasonHall;
    dst << fOdysseusHall;
    dst << fPerseusHall;
    dst << fTheseusHall;

    dst << fArmory;

    dst << fPopulationMonument;
    dst << fVictoryMonument;
    dst << fColonyMonument;
    dst << fAthleteMonument;
    dst << fConquestMonument;
    dst << fHappinessMonument;
    dst << f7Monument;
    dst << f8Monument;
    dst << fScholarMonument;
}

bool eAvailableBuildings::available(
        const eBuildingType type,
        const int id) const {
    switch(type) {
    case eBuildingType::wheatFarm:
        return fWheatFarm;
    case eBuildingType::carrotsFarm:
        return fCarrotsFarm;
    case eBuildingType::onionsFarm:
        return fOnionFarm;

    case eBuildingType::growersLodge:
        return fVine || fOliveTree;
    case eBuildingType::vine:
        return fVine;
    case eBuildingType::oliveTree:
        return fOliveTree;
    case eBuildingType::orangeTendersLodge:
    case eBuildingType::orangeTree:
        return fOrangeTree;

    case eBuildingType::dairy:
    case eBuildingType::goat:
        return fDairy;
    case eBuildingType::cardingShed:
    case eBuildingType::sheep:
        return fCardingShed;

    case eBuildingType::fishery:
        return fFishery;
    case eBuildingType::urchinQuay:
        return fUrchinQuay;
    case eBuildingType::huntingLodge:
        return fHuntingLodge;

    case eBuildingType::mint:
        return fMint;
    case eBuildingType::foundry:
        return fFoundry;
    case eBuildingType::timberMill:
        return fTimberMill;
    case eBuildingType::masonryShop:
        return fMasonryShop;

    case eBuildingType::winery:
        return fWinery;
    case eBuildingType::olivePress:
        return fOlivePress;
    case eBuildingType::sculptureStudio:
        return fSculptureStudio;

    case eBuildingType::templeAphrodite:
        return fAphroditeSanctuary == eAvailable::available;
    case eBuildingType::templeApollo:
        return fApolloSanctuary == eAvailable::available;
    case eBuildingType::templeAres:
        return fAresSanctuary == eAvailable::available;
    case eBuildingType::templeArtemis:
        return fArtemisSanctuary == eAvailable::available;
    case eBuildingType::templeAthena:
        return fAthenaSanctuary == eAvailable::available;
    case eBuildingType::templeAtlas:
        return fAtlasSanctuary == eAvailable::available;
    case eBuildingType::templeDemeter:
        return fDemeterSanctuary == eAvailable::available;
    case eBuildingType::templeDionysus:
        return fDionysusSanctuary == eAvailable::available;
    case eBuildingType::templeHades:
        return fHadesSanctuary == eAvailable::available;
    case eBuildingType::templeHephaestus:
        return fHephaestusSanctuary == eAvailable::available;
    case eBuildingType::templeHera:
        return fHeraSanctuary == eAvailable::available;
    case eBuildingType::templeHermes:
        return fHermesSanctuary == eAvailable::available;
    case eBuildingType::templePoseidon:
        return fPoseidonSanctuary == eAvailable::available;
    case eBuildingType::templeZeus:
        return fZeusSanctuary == eAvailable::available;

    case eBuildingType::achillesHall:
        return fAchillesHall == eAvailable::available;
    case eBuildingType::atalantaHall:
        return fAtalantaHall == eAvailable::available;
    case eBuildingType::bellerophonHall:
        return fBellerophonHall == eAvailable::available;
    case eBuildingType::herculesHall:
        return fHerculesHall == eAvailable::available;
    case eBuildingType::jasonHall:
        return fJasonHall == eAvailable::available;
    case eBuildingType::odysseusHall:
        return fOdysseusHall == eAvailable::available;
    case eBuildingType::perseusHall:
        return fPerseusHall == eAvailable::available;
    case eBuildingType::theseusHall:
        return fTheseusHall == eAvailable::available;

    case eBuildingType::armory:
        return fArmory;

    case eBuildingType::commemorative:
        if(id == 0) return fPopulationMonument;
        if(id == 1) return fVictoryMonument;
        if(id == 2) return fColonyMonument;
        if(id == 3) return fAthleteMonument;
        if(id == 4) return fConquestMonument;
        if(id == 5) return fHappinessMonument;
        if(id == 6) return f7Monument;
        if(id == 7) return f8Monument;
        if(id == 8) return fScholarMonument;
    default:
        return true;
    }
    return true;
}

void eAvailableBuildings::built(
        const eBuildingType type, const int id) {
    switch(type) {
    case eBuildingType::commemorative: {
        int* c = nullptr;
        if(id == 0) c = &fPopulationMonument;
        else if(id == 1) c = &fVictoryMonument;
        else if(id == 2) c = &fColonyMonument;
        else if(id == 3) c = &fAthleteMonument;
        else if(id == 4) c = &fConquestMonument;
        else if(id == 5) c = &fHappinessMonument;
        else if(id == 6) c = &f7Monument;
        else if(id == 7) c = &f8Monument;
        else if(id == 8) c = &fScholarMonument;
        if(!c) return;
        *c = std::max(0, *c - 1);
    } break;

    case eBuildingType::templeAphrodite:
        fAphroditeSanctuary = eAvailable::built; break;
    case eBuildingType::templeApollo:
        fApolloSanctuary = eAvailable::built; break;
    case eBuildingType::templeAres:
        fAresSanctuary = eAvailable::built; break;
    case eBuildingType::templeArtemis:
        fArtemisSanctuary = eAvailable::built; break;
    case eBuildingType::templeAthena:
        fAthenaSanctuary = eAvailable::built; break;
    case eBuildingType::templeAtlas:
        fAtlasSanctuary = eAvailable::built; break;
    case eBuildingType::templeDemeter:
        fDemeterSanctuary = eAvailable::built; break;
    case eBuildingType::templeDionysus:
        fDionysusSanctuary = eAvailable::built; break;
    case eBuildingType::templeHades:
        fHadesSanctuary = eAvailable::built; break;
    case eBuildingType::templeHephaestus:
        fHephaestusSanctuary = eAvailable::built; break;
    case eBuildingType::templeHera:
        fHeraSanctuary = eAvailable::built; break;
    case eBuildingType::templeHermes:
        fHermesSanctuary = eAvailable::built; break;
    case eBuildingType::templePoseidon:
        fPoseidonSanctuary = eAvailable::built; break;
    case eBuildingType::templeZeus:
        fZeusSanctuary = eAvailable::built; break;

    case eBuildingType::achillesHall:
        fAchillesHall = eAvailable::built; break;
    case eBuildingType::atalantaHall:
        fAtalantaHall = eAvailable::built; break;
    case eBuildingType::bellerophonHall:
        fBellerophonHall = eAvailable::built; break;
    case eBuildingType::herculesHall:
        fHerculesHall = eAvailable::built; break;
    case eBuildingType::jasonHall:
        fJasonHall = eAvailable::built; break;
    case eBuildingType::odysseusHall:
        fOdysseusHall = eAvailable::built; break;
    case eBuildingType::perseusHall:
        fPerseusHall = eAvailable::built; break;
    case eBuildingType::theseusHall:
        fTheseusHall = eAvailable::built; break;

    default:
        break;
    }
}

void eAvailableBuildings::destroyed(
        const eBuildingType type, const int id) {
    (void)id;
    const auto a = availablePtr(type);
    if(!a) return;
    if(*a == eAvailable::built) *a = eAvailable::available;
}

void eAvailableBuildings::allow(
        const eBuildingType type, const int id) {
    switch(type) {
    case eBuildingType::commemorative: {
        int* c = nullptr;
        if(id == 0) c = &fPopulationMonument;
        else if(id == 1) c = &fVictoryMonument;
        else if(id == 2) c = &fColonyMonument;
        else if(id == 3) c = &fAthleteMonument;
        else if(id == 4) c = &fConquestMonument;
        else if(id == 5) c = &fHappinessMonument;
        else if(id == 6) c = &f7Monument;
        else if(id == 7) c = &f8Monument;
        else if(id == 8) c = &fScholarMonument;
        if(!c) return;
        (*c)++;
    } break;


    case eBuildingType::templeAphrodite:
    case eBuildingType::templeApollo:
    case eBuildingType::templeAres:
    case eBuildingType::templeArtemis:
    case eBuildingType::templeAthena:
    case eBuildingType::templeAtlas:
    case eBuildingType::templeDemeter:
    case eBuildingType::templeDionysus:
    case eBuildingType::templeHades:
    case eBuildingType::templeHephaestus:
    case eBuildingType::templeHera:
    case eBuildingType::templeHermes:
    case eBuildingType::templePoseidon:
    case eBuildingType::templeZeus:

    case eBuildingType::achillesHall:
    case eBuildingType::atalantaHall:
    case eBuildingType::bellerophonHall:
    case eBuildingType::herculesHall:
    case eBuildingType::jasonHall:
    case eBuildingType::odysseusHall:
    case eBuildingType::perseusHall:
    case eBuildingType::theseusHall: {
        const auto a = availablePtr(type);
        if(!a) return;
        if(*a == eAvailable::built) return;
        *a = eAvailable::available;
    } break;

    default:
        break;
    }
}

void eAvailableBuildings::disallow(
        const eBuildingType type, const int id) {
    (void)id;
    switch(type) {
    case eBuildingType::templeAphrodite:
    case eBuildingType::templeApollo:
    case eBuildingType::templeAres:
    case eBuildingType::templeArtemis:
    case eBuildingType::templeAthena:
    case eBuildingType::templeAtlas:
    case eBuildingType::templeDemeter:
    case eBuildingType::templeDionysus:
    case eBuildingType::templeHades:
    case eBuildingType::templeHephaestus:
    case eBuildingType::templeHera:
    case eBuildingType::templeHermes:
    case eBuildingType::templePoseidon:
    case eBuildingType::templeZeus:

    case eBuildingType::achillesHall:
    case eBuildingType::atalantaHall:
    case eBuildingType::bellerophonHall:
    case eBuildingType::herculesHall:
    case eBuildingType::jasonHall:
    case eBuildingType::odysseusHall:
    case eBuildingType::perseusHall:
    case eBuildingType::theseusHall: {
        const auto a = availablePtr(type);
        if(!a) return;
        *a = eAvailable::notAvailable;
    } break;

    default:
        break;
    }
}

eAvailable* eAvailableBuildings::availablePtr(const eBuildingType type) {
    eAvailable* a = nullptr;

    switch(type) {
    case eBuildingType::templeAphrodite:
        a = &fAphroditeSanctuary; break;
    case eBuildingType::templeApollo:
        a = &fApolloSanctuary; break;
    case eBuildingType::templeAres:
        a = &fAresSanctuary; break;
    case eBuildingType::templeArtemis:
        a = &fArtemisSanctuary; break;
    case eBuildingType::templeAthena:
        a = &fAthenaSanctuary; break;
    case eBuildingType::templeAtlas:
        a = &fAtlasSanctuary; break;
    case eBuildingType::templeDemeter:
        a = &fDemeterSanctuary; break;
    case eBuildingType::templeDionysus:
        a = &fDionysusSanctuary; break;
    case eBuildingType::templeHades:
        a = &fHadesSanctuary; break;
    case eBuildingType::templeHephaestus:
        a = &fHephaestusSanctuary; break;
    case eBuildingType::templeHera:
        a = &fHeraSanctuary; break;
    case eBuildingType::templeHermes:
        a = &fHermesSanctuary; break;
    case eBuildingType::templePoseidon:
        a = &fPoseidonSanctuary; break;
    case eBuildingType::templeZeus:
        a = &fZeusSanctuary; break;

    case eBuildingType::achillesHall:
        a = &fAchillesHall; break;
    case eBuildingType::atalantaHall:
        a = &fAtalantaHall; break;
    case eBuildingType::bellerophonHall:
        a = &fBellerophonHall; break;
    case eBuildingType::herculesHall:
        a = &fHerculesHall; break;
    case eBuildingType::jasonHall:
        a = &fJasonHall; break;
    case eBuildingType::odysseusHall:
        a = &fOdysseusHall; break;
    case eBuildingType::perseusHall:
        a = &fPerseusHall; break;
    case eBuildingType::theseusHall:
        a = &fTheseusHall; break;

    default:
        break;
    }
    return a;
}
