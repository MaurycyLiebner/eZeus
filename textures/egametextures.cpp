#include "egametextures.h"

#include <functional>
#include <filesystem>

#include "egamedir.h"

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

void eGameTextures::loadOrichalcMiner() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadOrichalcMiner();
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

void eGameTextures::loadPoseidonTowerArcher() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadPoseidonTowerArcher();
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

void eGameTextures::loadTrireme() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadTrireme();
        c.loadTriremeOverlay();
    });
}

void eGameTextures::loadEnemyBoat() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadEnemyBoat();
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

void eGameTextures::loadSatyr() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadSatyr();
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

void eGameTextures::loadBlackSpear() {
    loadTexture([](const int i) {
        auto& c = sDestructionTextures[i];
        c.loadBlackSpear();
    });
}

void eGameTextures::loadSpear() {
    loadTexture([](const int i) {
        auto& c = sDestructionTextures[i];
        c.loadSpear();
    });
}

void eGameTextures::loadBlackArrow() {
    loadTexture([](const int i) {
        auto& c = sDestructionTextures[i];
        c.loadBlackArrow();
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

void eGameTextures::loadPoseidonCommonHouse() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadPoseidonCommonHouse();
    });
}

void eGameTextures::loadEliteHouse() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadEliteHouse();
    });
}

void eGameTextures::loadPoseidonEliteHouse() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadPoseidonEliteHouse();
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

void eGameTextures::loadAltarBullOverlay() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadAltarBullOverlay();
    });
}

void eGameTextures::loadAltarSheepOverlay() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadAltarSheepOverlay();
    });
}

void eGameTextures::loadAltarGoodsOverlay() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadAltarGoodsOverlay();
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

void eGameTextures::loadPoseidonCampaign1() {
    loadInterfaceTexture([](const int i) {
        auto& c = sInterfaceTextures[i];
        c.loadPoseidonCampaign1();
    });
}

void eGameTextures::loadPoseidonCampaign2() {
    loadInterfaceTexture([](const int i) {
        auto& c = sInterfaceTextures[i];
        c.loadPoseidonCampaign2();
    });
}

void eGameTextures::loadPoseidonCampaign3() {
    loadInterfaceTexture([](const int i) {
        auto& c = sInterfaceTextures[i];
        c.loadPoseidonCampaign3();
    });
}

void eGameTextures::loadPoseidonCampaign4() {
    loadInterfaceTexture([](const int i) {
        auto& c = sInterfaceTextures[i];
        c.loadPoseidonCampaign4();
    });
}

void eGameTextures::loadPoseidonCampaign5() {
    loadInterfaceTexture([](const int i) {
        auto& c = sInterfaceTextures[i];
        c.loadPoseidonCampaign5();
    });
}

void eGameTextures::loadPoseidonCampaign6() {
    loadInterfaceTexture([](const int i) {
        auto& c = sInterfaceTextures[i];
        c.loadPoseidonCampaign6();
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

void eGameTextures::loadElephant() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadElephant();
    });
}

void eGameTextures::loadZeusSanctuary() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadZeusSanctuary();
    });
}

void eGameTextures::loadPoseidonSanctuary() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadPoseidonSanctuary();
    });
}

void eGameTextures::loadPoseidonHerosHall() {
    loadTexture([](const int i) {
        auto& c = sBuildingTextures[i];
        c.loadPoseidonHerosHall();
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

void eGameTextures::loadPoseidonTrees() {
    loadTexture([](const int i) {
        auto& c = sTerrainTextures[i];
        c.loadPoseidonTrees();
    });
}

void eGameTextures::loadEliteCitizen() {
    loadTexture([](const int i) {
        auto& c = sCharacterTextures[i];
        c.loadEliteCitizen();
    });
}

struct eFile {
    std::string fFilename;
    int fSize;
};

bool checkTextureFiles() {
    const std::vector<eFile> files = {
        {"zeus_hydra.555", 6793032},
        {"Poseidon_AtlasStat.555", 136293},
        {"Zeus_God02.sg3", 695080},
        {"Zeus_Sanctuary3.555", 367257},
        {"Zeus_MapOfGreece09.JPG", 255670},
        {"Zeus_persian.sg3", 991080},
        {"Zeus_Defeat.555", 1572864},
//            {"Zeus_DEMO1.555", 614400},
        {"zeus_statcon1.sg3", 695080},
        {"Poseidon_Chimera.555", 10049365},
//            {"Zeus_DEMO3.555", 614400},
        {"PoseidonImps2.sg3", 991080},
        {"zeus_talos.555", 3693451},
        {"zeus_statcon3.sg3", 695080},
        {"zeus_cerberus.555", 4694886},
        {"zeus_dragon.555", 6630383},
//            {"scoreb.jpg", 163708},
        {"Poseidon_Atlantean.555", 1229999},
        {"zeus_statcon6.555", 65680},
        {"Zeus_God05.sg3", 695080},
        {"zeus_satyr.555", 2092414},
        {"Poseidon_Egyptian.555", 1119386},
        {"Zeus_trojan.555", 881763},
        {"Zeus_AresWarriors.sg3", 991080},
        {"Zeus_MapOfGreece01.JPG", 271431},
        {"Poseidon_Atalanta.sg3", 991080},
        {"zeus_achilles.555", 1824423},
        {"Poseidon_Loaded.555", 9390226},
        {"Zeus_AresWarriors.555", 488655},
        {"zeus_perseus.sg3", 991080},
        {"Zeus_God02.555", 141890},
        {"PoseidonImps.sg3", 991080},
        {"Zeus_Load4.jpg", 160304},
        {"Zeus_MapOfGreece08.JPG", 255670},
        {"Zeus_God01.sg3", 695080},
        {"Poseidon_Sanctuary3.sg3", 695080},
        {"zeus_scylla.sg3", 991080},
        {"Poseidon_Unloaded.sg3", 695080},
        {"Poseidon_Egyptian.sg3", 991080},
        {"Zeus_God10.sg3", 695080},
        {"Poseidon_GrandStatue3.sg3", 695080},
        {"Zeus_Interface.sg3", 695080},
        {"Zeus_trojan.sg3", 991080},
        {"Zeus_Hades.sg3", 991080},
        {"Poseidon_Atlas.sg3", 991080},
        {"Zeus_Hermes.555", 4170959},
        {"zeus_maenads.sg3", 991080},
        {"Poseidon_Phoenician.555", 565558},
        {"zeus_heracles.555", 1478018},
        {"Poseidon_Oceanid.555", 352558},
//            {"Zeus_FE_ChooseGame.jpg", 273777},
        {"Zeus_Zeus.sg3", 991080},
        {"Poseidon_map02.jpg", 519337},
        {"zeus_hector.sg3", 991080},
        {"Zeus_Greek.555", 1864773},
        {"Zeus_MapOfGreece04.JPG", 276583},
        {"Zeus_Sanctuary2.sg3", 695080},
        {"Zeus_MapOfGreece07.JPG", 272842},
        {"zeus_maenads.555", 3473119},
        {"Zeus_Athena.sg3", 991080},
        {"Zeus_Load3.jpg", 136115},
        {"Poseidon_Harpie.sg3", 991080},
        {"Zeus_WorldThumbnails.555", 1013600},
        {"Poseidon_GrandStatue3.555", 517508},
        {"Zeus_Zeus.555", 9436703},
        {"zeus_hydra.sg3", 991080},
        {"Zeus_centaur.555", 861854},
        {"Poseidon_Bellerophon.sg3", 991080},
        {"zeus_odysseus.sg3", 991080},
        {"Zeus_MapOfGreece01.sg3", 695080},
        {"Poseidon_Sphinx.sg3", 991080},
        {"Zeus_Victory.jpg", 254798},
        {"Zeus_General.555", 6195784},
        {"Poseidon_GrandStatue1.555", 458157},
//            {"Zeus_Title.jpg", 134497},
        {"Zeus_God03.sg3", 695080},
        {"Zeus_Sanctuary3.sg3", 695080},
        {"zeus_statcon4.sg3", 695080},
        {"Zeus_General.sg3", 695080},
        {"destruction.sg3", 991080},
        {"PoseidonImps2.555", 5845803},
        {"zeus_odysseus.555", 3632645},
//            {"Zeus_FE_MainMenu.jpg", 273122},
        {"Poseidon_Sanctuary3.555", 367257},
        {"Poseidon_Loaded.sg3", 695080},
        {"zeus_jason.sg3", 991080},
        {"Zeus_Ares.sg3", 991080},
        {"zeus_kraken.555", 11185029},
        {"Zeus_God07.sg3", 695080},
        {"Poseidon_Oceanid.sg3", 991080},
        {"Zeus_Sanctuary1.555", 189914},
        {"PoseidonImps.555", 25251109},
        {"Zeus_MapOfGreece06.JPG", 277229},
        {"zeus_hector.555", 2743516},
//            {"Poseidon_FE_MainMenu.JPG", 176221},
        {"Poseidon_Echidna.555", 7579780},
        {"Zeus_Artemis.sg3", 991080},
        {"zeus_kraken.sg3", 991080},
        {"Poseidon_Load1.jpg", 149618},
        {"Poseidon_Load3.jpg", 109507},
        {"Poseidon_GrandStatue2.555", 520078},
        {"Poseidon_Load7.jpg", 230960},
        {"Poseidon_Phoenician.sg3", 991080},
        {"Poseidon_Bellerophon.555", 4518763},
        {"Zeus_MapOfGreece10.JPG", 255670},
        {"zeus_statcon6.sg3", 695080},
        {"Poseidon_Atlas.555", 8089871},
        {"Zeus_Poseidon.555", 5330976},
        {"Zeus_Hermes.sg3", 991080},
        {"Zeus_Sanctuary1.sg3", 695080},
        {"Poseidon_Portraits.555", 391050},
        {"Zeus_Demeter.555", 4801528},
        {"Zeus_Aphrodite.sg3", 991080},
        {"Zeus_Load2.jpg", 168342},
        {"Zeus_Dionysus.sg3", 991080},
//            {"Poseidon_FE_Registry.jpg", 217089},
        {"Poseidon_map01.jpg", 482447},
//            {"Tutorial2.555", 380110},
        {"Poseidon_Load8.jpg", 210231},
        {"Zeus_God12.sg3", 695080},
        {"Zeus_God01.555", 139549},
        {"Poseidon_Load6.jpg", 223208},
        {"zeus_statcon1.555", 84839},
        {"Zeus_God07.555", 137345},
        {"Poseidon_GrandStatue1.sg3", 695080},
        {"zeus_theseus.sg3", 991080},
        {"Zeus_God10.555", 137678},
        {"zeus_calydonianboar.555", 2050608},
        {"Zeus_Poseidon.sg3", 991080},
        {"Zeus_God11.sg3", 695080},
        {"Poseidon_Load2.jpg", 205428},
        {"Zeus_God09.sg3", 695080},
        {"zeus_cerberus.sg3", 991080},
        {"Zeus_MapOfGreece03.JPG", 268073},
        {"Poseidon_Atalanta.555", 2200056},
        {"Zeus_Hephaestus.555", 2375563},
        {"Poseidon_Hera.555", 5931730},
        {"Poseidon_WorldThumbnails.555", 152040},
        {"zeus_perseus.555", 1556654},
        {"Poseidon_Load5.jpg", 199072},
        {"zeus_statcon5.555", 65680},
        {"Zeus_Load1.jpg", 195191},
        {"Poseidon_map04.jpg", 588190},
        {"zeus_achilles.sg3", 991080},
        {"SprMain.sg3", 991080},
        {"zeus_Unloaded.555", 39218},
        {"God_Portraits.555", 278080},
        {"Poseidon_map03.jpg", 466302},
        {"destruction.555", 5725044},
        {"Zeus_Apollo.555", 5604649},
        {"zeus_cyclops.sg3", 991080},
        {"SprMain.555", 15270017},
        {"Zeus_Apollo.sg3", 991080},
        {"zeus_statcon3.555", 65680},
//            {"Picture9.555", 964040},
        {"zeus_calydonianboar.sg3", 991080},
        {"Zeus_amazon.555", 618167},
        {"Poseidon_Chimera.sg3", 991080},
//        {"Zeus_Fonts.sg3", 695080},
        {"zeus_minotaur.555", 4964285},
        {"Zeus_God06.sg3", 695080},
        {"Poseidon_HeraStat.sg3", 695080},
        {"zeus_statcon2.sg3", 695080},
        {"zeus_medusa.sg3", 991080},
//            {"Zeus_DEMO2.555", 614400},
//            {"map_panels.555", 248832},
        {"zeus_dragon.sg3", 991080},
        {"Poseidon_Harpie.555", 8167597},
        {"zeus_cyclops.555", 4779943},
        {"zeus_statcon5.sg3", 695080},
//            {"Tutorial1.555", 593220},
        {"Zeus_Demeter.sg3", 991080},
        {"Poseidon_Sphinx.555", 8250702},
        {"zeus_scylla.555", 9469592},
        {"Zeus_Terrain.555", 4210543},
        {"Zeus_God09.555", 131916},
        {"Zeus_Interface.555", 4461887},
        {"Poseidon_Hera.sg3", 991080},
//        {"zeus_Fonts.555", 489709},
        {"SprAmbient.sg3", 991080},
        {"Poseidon_Echidna.sg3", 991080},
        {"Zeus_centaur.sg3", 991080},
        {"CampaignIllustrations.555", 2160000},
        {"Poseidon_GrandStatue2.sg3", 695080},
        {"Zeus_God08.sg3", 695080},
        {"Poseidon_Mayan.sg3", 991080},
        {"Zeus_God03.555", 131516},
        {"zeus_talos.sg3", 991080},
        {"Zeus_FE_Registry.jpg", 154974},
        {"Zeus_Defeat.jpg", 196124},
//            {"Zeus_FE_tutorials.JPG", 265818},
        {"Zeus_amazon.sg3", 991080},
        {"Zeus_Greek.sg3", 991080},
        {"Zeus_Aphrodite.555", 3627738},
        {"Portraits.555", 1051490},
        {"Zeus_Dionysus.555", 6361139},
        {"Zeus_God11.555", 122320},
        {"zeus_statcon2.555", 65680},
        {"Zeus_Ares.555", 5374332},
        {"Zeus_MapOfGreece02.JPG", 274035},
        {"Zeus_persian.555", 1103880},
        {"Poseidon_HeraStat.555", 134186},
        {"Zeus_FE_MissionIntroduction.jpg", 152920},
        {"Poseidon_Mayan.555", 489119},
        {"Zeus_Hades.555", 4021368},
        {"zeus_satyr.sg3", 991080},
        {"zeus_statcon4.555", 65680},
        {"Zeus_God05.555", 142461},
        {"Poseidon_AtlasStat.sg3", 695080},
        {"Zeus_Athena.555", 3467534},
        {"zeus_minotaur.sg3", 991080},
        {"Zeus_Terrain.sg3", 695080},
        {"Zeus_God08.555", 138697},
        {"zeus_theseus.555", 2034580},
        {"Zeus_God06.555", 127529},
        {"zeus_jason.555", 2541355},
//            {"Zeus_FE_CampaignSelection.JPG", 190012},
        {"Zeus_God12.555", 159323},
        {"Poseidon_Atlantean.sg3", 991080},
        {"Poseidon_Unloaded.555", 89898},
        {"zeus_medusa.555", 3576724},
        {"zeus_heracles.sg3", 991080},
        {"Poseidon_Load4.jpg", 340306},
        {"Zeus_God04.555", 131644},
        {"Zeus_MapOfGreece05.JPG", 275769},
        {"Zeus_God04.sg3", 695080},
        {"Zeus_Hephaestus.sg3", 991080},
        {"Zeus_Unloaded.sg3", 695080},
        {"Zeus_Sanctuary2.555", 307672},
        {"Zeus_Artemis.555", 3198753},
        {"SprAmbient.555", 5654853},
    };

    bool missing = false;
    for(const auto& f : files) {
        const auto path = eGameDir::path("DATA/" + f.fFilename);
        const bool e = std::filesystem::exists(path);
        if(!e) {
            missing = true;
            printf("File missing '%s'\n", path.c_str());
        }
    }

    return !missing;
}

bool eGameTextures::initialize(SDL_Renderer* const r) {
    if(sInitialized) return true;
    const bool e = checkTextureFiles();
    if(!e) return false;
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
