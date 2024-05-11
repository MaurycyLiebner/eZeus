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

        gGameLoaders.emplace_back([i](std::string& text) {
            sDestructionTextures[i].load();
            if(i == 0) {
                text = "Loading tiny destruction textures...";
            } else if(i == 1) {
                text = "Loading small destruction textures...";
            } else if(i == 2) {
                text = "Loading medium destruction textures...";
            } else if(i == 3) {
                text = "Loading large destruction textures...";
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
