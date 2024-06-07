#include "egametextures.h"

#include <functional>

bool eGameTextures::sInitialized = false;
std::vector<eTerrainTextures> eGameTextures::sTerrainTextures;
std::vector<eGodTextures> eGameTextures::sGodTextures;
std::vector<eBuildingTextures> eGameTextures::sBuildingTextures;
std::vector<eCharacterTextures> eGameTextures::sCharacterTextures;
std::vector<eInterfaceTextures> eGameTextures::sInterfaceTextures;
std::vector<eDestructionTextures> eGameTextures::sDestructionTextures;
eSettings eGameTextures::sSettings;

struct eLoader {
    using eFunc = std::function<void(std::string&)>;
    eLoader(const eFunc& f, const int s) :
        fFunc(f), fSize(s) {}

    eFunc fFunc;
    int fSize;
    bool fFinished = false;
};

std::vector<eLoader> gMenuLoaders;
std::vector<eLoader> gGameLoaders;

void eGameTextures::loadTexture(const std::function<void(int)>& func) {
    for(int i = 0; i < 4; i++) {
        if(i == 0 && !sSettings.fTinyTextures) continue;
        if(i == 1 && !sSettings.fSmallTextures) continue;
        if(i == 2 && !sSettings.fMediumTextures) continue;
        if(i == 3 && !sSettings.fLargeTextures) continue;
        func(i);
    }
}

void eGameTextures::loadInterfaceTexture(const std::function<void(int)>& func) {
    const auto& res = sSettings.fRes;
    const auto scale =  res.uiScale();
    for(int i = 0; i < 4; i++) {
        if(i == 0 && scale != eUIScale::tiny) continue;
        if(i == 1 && scale != eUIScale::small) continue;
        if(i == 2 && scale != eUIScale::medium) continue;
        if(i == 3 && scale != eUIScale::large) continue;
        func(i);
    }
}

void eGameTextures::loadPeddler() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadPeddler();
    });
}

void eGameTextures::loadActor() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadActor();
    });
}

void eGameTextures::loadOx() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadOx();
    });
}

void eGameTextures::loadPorter() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadPorter();
    });
}

void eGameTextures::loadOxHandler() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadOxHandler();
    });
}

void eGameTextures::loadTrailer() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadTrailer();
    });
}

void eGameTextures::loadSettlers() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadSettlers();
    });
}

void eGameTextures::loadHomeless() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadHomeless();
    });
}

void eGameTextures::loadFireFighter() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadFireFighter();
    });
}

void eGameTextures::loadWatchman() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadWatchman();
    });
}

void eGameTextures::loadGoatherd() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadGoatherd();
    });
}

void eGameTextures::loadBronzeMiner() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadBronzeMiner();
    });
}

void eGameTextures::loadArtisan() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadArtisan();
    });
}

void eGameTextures::loadFoodVendor() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadFoodVendor();
    });
}

void eGameTextures::loadFleeceVendor() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadFleeceVendor();
    });
}

void eGameTextures::loadOilVendor() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadOilVendor();
    });
}

void eGameTextures::loadWineVendor() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadWineVendor();
    });
}

void eGameTextures::loadArmsVendor() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadArmsVendor();
    });
}

void eGameTextures::loadHorseVendor() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadHorseVendor();
    });
}

void eGameTextures::loadSheep() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadSheep();
    });
}

void eGameTextures::loadHorse() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadHorse();
    });
}

void eGameTextures::loadShepherd() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadShepherd();
    });
}

void eGameTextures::loadMarbleMiner() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadMarbleMiner();
    });
}

void eGameTextures::loadSilverMiner() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadSilverMiner();
    });
}

void eGameTextures::loadArcher() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadArcher();
    });
}

void eGameTextures::loadLumberjack() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadLumberjack();
    });
}

void eGameTextures::loadTaxCollector() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadTaxCollector();
    });
}

void eGameTextures::loadTransporter() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadTransporter();
    });
}

void eGameTextures::loadGrower() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadGrower();
    });
}

void eGameTextures::loadTrader() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadTrader();
    });
}

void eGameTextures::loadWaterDistributor() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadWaterDistributor();
    });
}

void eGameTextures::loadRockThrower() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadRockThrower();
    });
}

void eGameTextures::loadHoplite() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadHoplite();
    });
}

void eGameTextures::loadHorseman() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadHorseman();
    });
}

void eGameTextures::loadHealer() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadHealer();
    });
}

void eGameTextures::loadCart() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadCart();
    });
}

void eGameTextures::loadBoar() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadBoar();
    });
}

void eGameTextures::loadGymnast() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadGymnast();
    });
}

void eGameTextures::loadCompetitor() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadCompetitor();
    });
}

void eGameTextures::loadGoat() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadGoat();
    });
}

void eGameTextures::loadWolf() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadWolf();
    });
}

void eGameTextures::loadHunter() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadHunter();
    });
}

void eGameTextures::loadPhilosopher() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadPhilosopher();
    });
}

void eGameTextures::loadUrchinGatherer() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadUrchinGatherer();
    });
}

void eGameTextures::loadFishingBoat() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadFishingBoat();
    });
}

void eGameTextures::loadTradeBoat() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadTradeBoat();
    });
}

void eGameTextures::loadDeer() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadDeer();
    });
}

void eGameTextures::loadGreekHoplite() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadGreekHoplite();
    });
}

void eGameTextures::loadGreekHorseman() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadGreekHorseman();
    });
}

void eGameTextures::loadGreekRockThrower() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadGreekRockThrower();
    });
}

void eGameTextures::loadTrojanHoplite() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadTrojanHoplite();
    });
}

void eGameTextures::loadTrojanHorseman() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadTrojanHorseman();
    });
}

void eGameTextures::loadTrojanSpearthrower() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadTrojanSpearthrower();
    });
}

void eGameTextures::loadCentaurHorseman() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadCentaurHorseman();
    });
}

void eGameTextures::loadCentaurArcher() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadCentaurArcher();
    });
}

void eGameTextures::loadEgyptianHoplite() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadEgyptianHoplite();
    });
}

void eGameTextures::loadEgyptianChariot() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadEgyptianChariot();
    });
}

void eGameTextures::loadEgyptianArcher() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadEgyptianArcher();
    });
}

void eGameTextures::loadMayanHoplite() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadMayanHoplite();
    });
}

void eGameTextures::loadMayanArcher() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadMayanArcher();
    });
}

void eGameTextures::loadPhoenicianHorseman() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadPhoenicianHorseman();
    });
}

void eGameTextures::loadPhoenicianArcher() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadPhoenicianArcher();
    });
}

void eGameTextures::loadOceanidHoplite() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadOceanidHoplite();
    });
}

void eGameTextures::loadOceanidSpearthrower() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadOceanidSpearthrower();
    });
}

void eGameTextures::loadAtlanteanHoplite() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadAtlanteanHoplite();
    });
}

void eGameTextures::loadAtlanteanChariot() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadAtlanteanChariot();
    });
}

void eGameTextures::loadAtlanteanArcher() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadAtlanteanArcher();
    });
}

void eGameTextures::loadPersianHoplite() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadPersianHoplite();
    });
}

void eGameTextures::loadPersianHorseman() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadPersianHorseman();
    });
}

void eGameTextures::loadPersianArcher() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadPersianArcher();
    });
}

void eGameTextures::loadAmazonSpear() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadAmazonSpear();
    });
}

void eGameTextures::loadAmazonArcher() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadAmazonArcher();
    });
}

void eGameTextures::loadAresWarrior() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadAresWarrior();
    });
}

void eGameTextures::loadDonkey() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadDonkey();
    });
}

void eGameTextures::loadDisgruntled() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadDisgruntled();
    });
}

void eGameTextures::loadSick() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadSick();
    });
}

void eGameTextures::loadBanners() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadBanners();
    });
}


void eGameTextures::loadCalydonianBoar() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadCalydonianBoar();
    });
}

void eGameTextures::loadCerberus() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadCerberus();
    });
}

void eGameTextures::loadChimera() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadChimera();
    });
}

void eGameTextures::loadCyclops() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadCyclops();
    });
}

void eGameTextures::loadDragon() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadDragon();
    });
}

void eGameTextures::loadEchidna() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadEchidna();
    });
}

void eGameTextures::loadHarpie() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadHarpie();
    });
}

void eGameTextures::loadHector() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadHector();
    });
}

void eGameTextures::loadHydra() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadHydra();
    });
}

void eGameTextures::loadKraken() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadKraken();
    });
}

void eGameTextures::loadMaenads() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadMaenads();
    });
}

void eGameTextures::loadMedusa() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadMedusa();
    });
}

void eGameTextures::loadMinotaur() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadMinotaur();
    });
}

void eGameTextures::loadScylla() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadScylla();
    });
}

void eGameTextures::loadSphinx() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadSphinx();
    });
}

void eGameTextures::loadTalos() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadTalos();
    });
}

void eGameTextures::loadAchilles() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadAchilles();
    });
}

void eGameTextures::loadAtalanta() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadAtalanta();
    });
}

void eGameTextures::loadBellerophon() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadBellerophon();
    });
}

void eGameTextures::loadHeracles() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadHeracles();
    });
}

void eGameTextures::loadJason() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadJason();
    });
}

void eGameTextures::loadOdysseus() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadOdysseus();
    });
}

void eGameTextures::loadPerseus() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadPerseus();
    });
}

void eGameTextures::loadTheseus() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadTheseus();
    });
}

void eGameTextures::loadAphrodite() {
    loadTexture([](const int i) {
        auto& c = sGodTextures[i];
        c.loadAphrodite();
    });
}

void eGameTextures::loadApollo() {
    loadTexture([](const int i) {
        auto& c = sGodTextures[i];
        c.loadApollo();
    });
}

void eGameTextures::loadAres() {
    loadTexture([](const int i) {
        auto& c = sGodTextures[i];
        c.loadAres();
    });
}

void eGameTextures::loadArtemis() {
    loadTexture([](const int i) {
        auto& c = sGodTextures[i];
        c.loadArtemis();
    });
}

void eGameTextures::loadAthena() {
    loadTexture([](const int i) {
        auto& c = sGodTextures[i];
        c.loadAthena();
    });
}

void eGameTextures::loadAtlas() {
    loadTexture([](const int i) {
        auto& c = sGodTextures[i];
        c.loadAtlas();
    });
}

void eGameTextures::loadDemeter() {
    loadTexture([](const int i) {
        auto& c = sGodTextures[i];
        c.loadDemeter();
    });
}

void eGameTextures::loadDionysus() {
    loadTexture([](const int i) {
        auto& c = sGodTextures[i];
        c.loadDionysus();
    });
}

void eGameTextures::loadHades() {
    loadTexture([](const int i) {
        auto& c = sGodTextures[i];
        c.loadHades();
    });
}

void eGameTextures::loadHephaestus() {
    loadTexture([](const int i) {
        auto& c = sGodTextures[i];
        c.loadHephaestus();
    });
}

void eGameTextures::loadHera() {
    loadTexture([](const int i) {
        auto& c = sGodTextures[i];
        c.loadHera();
    });
}

void eGameTextures::loadHermes() {
    loadTexture([](const int i) {
        auto& c = sGodTextures[i];
        c.loadHermes();
    });
}

void eGameTextures::loadPoseidon() {
    loadTexture([](const int i) {
        auto& c = sGodTextures[i];
        c.loadPoseidon();
    });
}

void eGameTextures::loadZeus() {
    loadTexture([](const int i) {
        auto& c = sGodTextures[i];
        c.loadZeus();
    });
}

void eGameTextures::loadFire() {
    loadTexture([](const int i) {
        auto& c = sDestructionTextures[i];
        c.loadFire();
    });
}

void eGameTextures::loadBlessed() {
    loadTexture([](const int i) {
        auto& c = sDestructionTextures[i];
        c.loadBlessed();
    });
}

void eGameTextures::loadCursed() {
    loadTexture([](const int i) {
        auto& c = sDestructionTextures[i];
        c.loadCursed();
    });
}

void eGameTextures::loadRock() {
    loadTexture([](const int i) {
        auto& c = sDestructionTextures[i];
        c.loadRock();
    });
}

void eGameTextures::loadArrow() {
    loadTexture([](const int i) {
        auto& c = sDestructionTextures[i];
        c.loadArrow();
    });
}

void eGameTextures::loadBless() {
    loadTexture([](const int i) {
        auto& c = sDestructionTextures[i];
        c.loadBless();
    });
}

void eGameTextures::loadCurse() {
    loadTexture([](const int i) {
        auto& c = sDestructionTextures[i];
        c.loadCurse();
    });
}

void eGameTextures::loadPlague() {
    loadTexture([](const int i) {
        auto& c = sDestructionTextures[i];
        c.loadPlague();
    });
}

void eGameTextures::loadGodOrangeMissile() {
    loadTexture([](const int i) {
        auto& c = sDestructionTextures[i];
        c.loadGodOrangeMissile();
    });
}

void eGameTextures::loadGodBlueArrow() {
    loadTexture([](const int i) {
        auto& c = sDestructionTextures[i];
        c.loadGodBlueArrow();
    });
}

void eGameTextures::loadGodOrangeArrow() {
    loadTexture([](const int i) {
        auto& c = sDestructionTextures[i];
        c.loadGodOrangeArrow();
    });
}

void eGameTextures::loadMonsterMissile() {
    loadTexture([](const int i) {
        auto& c = sDestructionTextures[i];
        c.loadMonsterMissile();
    });
}

void eGameTextures::loadGodBlueMissile() {
    loadTexture([](const int i) {
        auto& c = sDestructionTextures[i];
        c.loadGodBlueMissile();
    });
}

void eGameTextures::loadGodRedMissile() {
    loadTexture([](const int i) {
        auto& c = sDestructionTextures[i];
        c.loadGodRedMissile();
    });
}

void eGameTextures::loadGodGreenMissile() {
    loadTexture([](const int i) {
        auto& c = sDestructionTextures[i];
        c.loadGodGreenMissile();
    });
}

void eGameTextures::loadGodPinkMissile() {
    loadTexture([](const int i) {
        auto& c = sDestructionTextures[i];
        c.loadGodPinkMissile();
    });
}

void eGameTextures::loadGodPurpleMissile() {
    loadTexture([](const int i) {
        auto& c = sDestructionTextures[i];
        c.loadGodPurpleMissile();
    });
}

void eGameTextures::loadCommonHouse() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadCommonHouse();
    });
}

void eGameTextures::loadEliteHouse() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadEliteHouse();
    });
}

void eGameTextures::loadCollege() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadCollege();
    });
}

void eGameTextures::loadGymnasium() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadGymnasium();
    });
}

void eGameTextures::loadDramaSchool() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadDramaSchool();
    });
}

void eGameTextures::loadPodium() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadPodium();
    });
}

void eGameTextures::loadTheater() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadTheater();
    });
}

void eGameTextures::loadStadium() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadStadium();
    });
}

void eGameTextures::loadFountain() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadFountain();
    });
}

void eGameTextures::loadHospital() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadHospital();
    });
}

void eGameTextures::loadOliveTree() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadOliveTree();
    });
}

void eGameTextures::loadVine() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadVine();
    });
}

void eGameTextures::loadPlantation() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadPlantation();
    });
}

void eGameTextures::loadHuntingLodge() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadHuntingLodge();
    });
}

void eGameTextures::loadFishery() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadFishery();
    });
}

void eGameTextures::loadUrchinQuay() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadUrchinQuay();
    });
}

void eGameTextures::loadCardingShed() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadCardingShed();
    });
}

void eGameTextures::loadDairy() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadDairy();
    });
}

void eGameTextures::loadGrowersLodge() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadGrowersLodge();
    });
}

void eGameTextures::loadTimberMill() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadTimberMill();
    });
}

void eGameTextures::loadMasonryShop() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadMasonryShop();
    });
}

void eGameTextures::loadMint() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadMint();
    });
}

void eGameTextures::loadFoundry() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadFoundry();
    });
}

void eGameTextures::loadArtisansGuild() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadArtisansGuild();
    });
}

void eGameTextures::loadOlivePress() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadOlivePress();
    });
}

void eGameTextures::loadWinery() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadWinery();
    });
}

void eGameTextures::loadSculptureStudio() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadSculptureStudio();
    });
}

void eGameTextures::loadTriremeWharf() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadTriremeWharf();
    });
}

void eGameTextures::loadHorseRanch() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadHorseRanch();
    });
}

void eGameTextures::loadArmory() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadArmory();
    });
}

void eGameTextures::loadGatehouseAndTower() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadGatehouseAndTower();
    });
}

void eGameTextures::loadWall() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadWall();
    });
}

void eGameTextures::loadMaintenanceOffice() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadMaintenanceOffice();
    });
}

void eGameTextures::loadTaxOffice() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadTaxOffice();
    });
}

void eGameTextures::loadWatchpost() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadWatchpost();
    });
}

void eGameTextures::loadRoadblock() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadRoadblock();
    });
}

void eGameTextures::loadBridge() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadBridge();
    });
}

void eGameTextures::loadPalace() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadPalace();
    });
}

void eGameTextures::loadPalaceTiles() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadPalaceTiles();
    });
}

void eGameTextures::loadSanctuary() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadSanctuary();
    });
}

void eGameTextures::loadOrangeTendersLodge() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadOrangeTendersLodge();
    });
}

void eGameTextures::loadWaterPark() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadWaterPark();
    });
}

void eGameTextures::loadShortObelisk() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadShortObelisk();
    });
}

void eGameTextures::loadBirdBath() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadBirdBath();
    });
}

void eGameTextures::loadBaths() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadBaths();
    });
}

void eGameTextures::loadShellGarden() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadShellGarden();
    });
}

void eGameTextures::loadOrrery() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadOrrery();
    });
}

void eGameTextures::loadDolphinSculpture() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadDolphinSculpture();
    });
}

void eGameTextures::loadStoneCircle() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadStoneCircle();
    });
}

void eGameTextures::loadSpring() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadSpring();
    });
}

void eGameTextures::loadTopiary() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadTopiary();
    });
}

void eGameTextures::loadSundial() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadSundial();
    });
}

void eGameTextures::loadTallObelisk() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadTallObelisk();
    });
}

void eGameTextures::loadAvenue() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadAvenue();
    });
}

void eGameTextures::loadColumns() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadColumns();
    });
}

void eGameTextures::loadCommemorative() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadCommemorative();
    });
}

void eGameTextures::loadFishPond() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadFishPond();
    });
}

void eGameTextures::loadHedgeMaze() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadHedgeMaze();
    });
}

void eGameTextures::loadGazebo() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadGazebo();
    });
}

void eGameTextures::loadFlowerGarden() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadFlowerGarden();
    });
}

void eGameTextures::loadBench() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadBench();
    });
}

void eGameTextures::loadPark() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadPark();
    });
}

void eGameTextures::loadZeusMonuments() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadZeusMonuments();
    });
}

void eGameTextures::loadPoseidonMonuments() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadPoseidonMonuments();
    });
}

void eGameTextures::loadHadesMonuments() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadHadesMonuments();
    });
}

void eGameTextures::loadDemeterMonuments() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadDemeterMonuments();
    });
}

void eGameTextures::loadAthenaMonuments() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadAthenaMonuments();
    });
}

void eGameTextures::loadArtemisMonuments() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadArtemisMonuments();
    });
}

void eGameTextures::loadApolloMonuments() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadApolloMonuments();
    });
}

void eGameTextures::loadAresMonuments() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadAresMonuments();
    });
}

void eGameTextures::loadHephaestusMonuments() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadHephaestusMonuments();
    });
}

void eGameTextures::loadAphroditeMonuments() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadAphroditeMonuments();
    });
}

void eGameTextures::loadHermesMonuments() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadHermesMonuments();
    });
}

void eGameTextures::loadDionysusMonuments() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadDionysusMonuments();
    });
}

void eGameTextures::loadHeraMonuments() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadHeraMonuments();
    });
}

void eGameTextures::loadAtlasMonuments() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadAtlasMonuments();
    });
}

void eGameTextures::loadHerosHall() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadHerosHall();
    });
}

void eGameTextures::loadWaitingOverlay() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadWaitingOverlay();
    });
}

void eGameTextures::loadAgora() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadAgora();
    });
}

void eGameTextures::loadPier() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadPier();
    });
}

void eGameTextures::loadTradingPost() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadTradingPost();
    });
}

void eGameTextures::loadGranary() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadGranary();
    });
}

void eGameTextures::loadMapOfGreece1() {
    loadInterfaceTexture([](const int i) {
        auto& c = sInterfaceTextures[i];
        c.loadMapOfGreece1();
    });
}

void eGameTextures::loadMapOfGreece2() {
    loadInterfaceTexture([](const int i) {
        auto& c = sInterfaceTextures[i];
        c.loadMapOfGreece2();
    });
}

void eGameTextures::loadMapOfGreece3() {
    loadInterfaceTexture([](const int i) {
        auto& c = sInterfaceTextures[i];
        c.loadMapOfGreece3();
    });
}

void eGameTextures::loadMapOfGreece4() {
    loadInterfaceTexture([](const int i) {
        auto& c = sInterfaceTextures[i];
        c.loadMapOfGreece4();
    });
}

void eGameTextures::loadMapOfGreece5() {
    loadInterfaceTexture([](const int i) {
        auto& c = sInterfaceTextures[i];
        c.loadMapOfGreece5();
    });
}

void eGameTextures::loadMapOfGreece6() {
    loadInterfaceTexture([](const int i) {
        auto& c = sInterfaceTextures[i];
        c.loadMapOfGreece6();
    });
}

void eGameTextures::loadMapOfGreece7() {
    loadInterfaceTexture([](const int i) {
        auto& c = sInterfaceTextures[i];
        c.loadMapOfGreece7();
    });
}

void eGameTextures::loadMapOfGreece8() {
    loadInterfaceTexture([](const int i) {
        auto& c = sInterfaceTextures[i];
        c.loadMapOfGreece8();
    });
}

void eGameTextures::loadPoseidonMap1() {
    loadInterfaceTexture([](const int i) {
        auto& c = sInterfaceTextures[i];
        c.loadPoseidonMap1();
    });
}

void eGameTextures::loadPoseidonMap2() {
    loadInterfaceTexture([](const int i) {
        auto& c = sInterfaceTextures[i];
        c.loadPoseidonMap2();
    });
}

void eGameTextures::loadPoseidonMap3() {
    loadInterfaceTexture([](const int i) {
        auto& c = sInterfaceTextures[i];
        c.loadPoseidonMap3();
    });
}

void eGameTextures::loadPoseidonMap4() {
    loadInterfaceTexture([](const int i) {
        auto& c = sInterfaceTextures[i];
        c.loadPoseidonMap4();
    });
}

void eGameTextures::loadScholar() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadScholar();
    });
}

void eGameTextures::loadAstronomer() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadAstronomer();
    });
}

void eGameTextures::loadInventor() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadInventor();
    });
}

void eGameTextures::loadCurator() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadCurator();
    });
}

void eGameTextures::loadBibliotheke() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadBibliotheke();
    });
}

void eGameTextures::loadObservatory() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadObservatory();
    });
}

void eGameTextures::loadUniversity() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadUniversity();
    });
}

void eGameTextures::loadLaboratory() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadLaboratory();
    });
}

void eGameTextures::loadInventorsWorkshop() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadInventorsWorkshop();
    });
}

void eGameTextures::loadMuseum() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadMuseum();
    });
}

void eGameTextures::loadChariotFactory() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadChariotFactory();
    });
}

void eGameTextures::loadChariotVendor() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadChariotVendor();
    });
}

void eGameTextures::loadChariotVendorCharacter() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadChariotVendor();
    });
}

void eGameTextures::loadChariot() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadChariot();
    });
}

void eGameTextures::loadWineVendorBuilding() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadWineVendor();
    });
}

void eGameTextures::loadHoplitePoseidon() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadHoplitePoseidon();
    });
}

void eGameTextures::loadArcherPoseidon() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadArcherPoseidon();
    });
}

void eGameTextures::loadChariotPoseidon() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadChariotPoseidon();
    });
}

void eGameTextures::loadCorral() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadCorral();
    });
}

void eGameTextures::loadButcher() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadButcher();
    });
}

void eGameTextures::loadCattle() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadCattle();
    });
}

void eGameTextures::loadBull() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadBull();
    });
}

bool eGameTextures::initialize(SDL_Renderer* const r) {
    if(sInitialized) return true;
    int i = 0;
    for(const auto& s : {std::pair<int, int>{30, 15},
                         std::pair<int, int>{60, 30},
                         std::pair<int, int>{90, 45},
                         std::pair<int, int>{120, 60}}) {
        sTerrainTextures.emplace_back(s.first, s.second, r);
        sGodTextures.emplace_back(s.first, s.second, r);
        sBuildingTextures.emplace_back(s.first, s.second, r);
        sCharacterTextures.emplace_back(s.first, s.second, r);
        sInterfaceTextures.emplace_back(s.first, s.second, r);
        sDestructionTextures.emplace_back(s.first, s.second, r);

        gGameLoaders.emplace_back([i](std::string& text) {
            sTerrainTextures[i].load();
            if(i == 0) {
                text = "Loading tiny terrain textures...";
            } else if(i == 1) {
                text = "Loading small terrain textures...";
            } else if(i == 2) {
                text = "Loading medium terrain textures...";
            } else if(i == 3) {
                text = "Loading large terrain textures...";
            }
        }, i);

        gGameLoaders.emplace_back([i](std::string& text) {
            sBuildingTextures[i].load();
            if(i == 0) {
                text = "Loading tiny building textures...";
            } else if(i == 1) {
                text = "Loading small building textures...";
            } else if(i == 2) {
                text = "Loading medium building textures...";
            } else if(i == 3) {
                text = "Loading large building textures...";
            }
        }, i);

        gMenuLoaders.emplace_back([i](std::string& text) {
            sInterfaceTextures[i].load();
            if(i == 0) {
                text = "Loading tiny interface textures...";
            } else if(i == 1) {
                text = "Loading small interface textures...";
            } else if(i == 2) {
                text = "Loading medium interface textures...";
            } else if(i == 3) {
                text = "Loading large interface textures...";
            }
        }, i);

        i++;
    }

    sInitialized = true;

    return true;
}

bool eGameTextures::loadNextMenu(const eSettings& settings,
                                 std::string& text) {
    const int iMax = gMenuLoaders.size();
    const auto res = settings.fRes;
    const auto uiScale = res.uiScale();
    for(int i = 0; i < iMax; i++) {
        auto& g = gMenuLoaders[i];
        if(g.fFinished) continue;
        if(uiScale != eUIScale::tiny &&
           g.fSize == 0) continue;
        if(uiScale != eUIScale::small &&
           g.fSize == 1) continue;
        if(uiScale != eUIScale::medium &&
           g.fSize == 2) continue;
        if(uiScale != eUIScale::large &&
           g.fSize == 3) continue;
        g.fFunc(text);
        g.fFinished = true;
        return false;
    }
    text = "Finished";
    return true;
}

bool eGameTextures::loadNextGame(const eSettings& settings,
                                 std::string& text) {
    const int iMax = gGameLoaders.size();
    for(int i = 0; i < iMax; i++) {
        auto& g = gGameLoaders[i];
        if(g.fFinished) continue;
        if(!settings.fTinyTextures &&
           g.fSize == 0) continue;
        if(!settings.fSmallTextures &&
           g.fSize == 1) continue;
        if(!settings.fMediumTextures &&
           g.fSize == 2) continue;
        if(!settings.fLargeTextures &&
           g.fSize == 3) continue;
        g.fFunc(text);
        g.fFinished = true;
        return false;
    }
    text = "Finished";
    return true;
}

int eGameTextures::gameSize(const eSettings& settings) {
    int result = 0;
    const int iMax = gGameLoaders.size();
    for(int i = 0; i < iMax; i++) {
        auto& g = gGameLoaders[i];
        if(g.fFinished) continue;
        if(!settings.fTinyTextures &&
           g.fSize == 0) continue;
        if(!settings.fSmallTextures &&
           g.fSize == 1) continue;
        if(!settings.fMediumTextures &&
           g.fSize == 2) continue;
        if(!settings.fLargeTextures &&
           g.fSize == 3) continue;
        result++;
    }
    return result;
}

int eGameTextures::menuSize() {
    return sInterfaceTextures.size();
}

void eGameTextures::setSettings(const eSettings& s) {
    sSettings = s;
}
