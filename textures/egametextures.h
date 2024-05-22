#ifndef EGAMETEXTURES_H
#define EGAMETEXTURES_H

#include "eterraintextures.h"
#include "egodtextures.h"
#include "ebuildingtextures.h"
#include "echaractertextures.h"
#include "einterfacetextures.h"
#include "edestructiontextures.h"

#include "esettings.h"

class eGameTextures {
public:
    static const std::vector<eTerrainTextures>& terrain() {
        return sTerrainTextures;
    }
    static const std::vector<eGodTextures>& gods() {
        return sGodTextures;
    }
    static const std::vector<eBuildingTextures>& buildings() {
        return sBuildingTextures;
    }
    static const std::vector<eCharacterTextures>& characters() {
        return sCharacterTextures;
    }
    static const std::vector<eInterfaceTextures>& interface() {
        return sInterfaceTextures;
    }
    static const std::vector<eDestructionTextures>& destrution() {
        return sDestructionTextures;
    }

    static void loadTexture(const std::function<void(int)>& func);

    static void loadPeddler();
    static void loadActor();
    static void loadOx();
    static void loadPorter();
    static void loadOxHandler();
    static void loadTrailer();
    static void loadSettlers();
    static void loadHomeless();
    static void loadFireFighter();
    static void loadWatchman();
    static void loadGoatherd();
    static void loadBronzeMiner();
    static void loadArtisan();
    static void loadFoodVendor();
    static void loadFleeceVendor();
    static void loadOilVendor();
    static void loadWineVendor();
    static void loadArmsVendor();
    static void loadHorseVendor();
    static void loadSheep();
    static void loadHorse();
    static void loadShepherd();
    static void loadMarbleMiner();
    static void loadSilverMiner();
    static void loadArcher();
    static void loadLumberjack();
    static void loadTaxCollector();
    static void loadTransporter();
    static void loadGrower();
    static void loadTrader();
    static void loadWaterDistributor();
    static void loadRockThrower();
    static void loadHoplite();
    static void loadHorseman();
    static void loadHealer();
    static void loadCart();
    static void loadBoar();
    static void loadGymnast();
    static void loadGoat();
    static void loadWolf();
    static void loadHunter();
    static void loadPhilosopher();
    static void loadUrchinGatherer();
    static void loadFishingBoat();
    static void loadTradeBoat();
    static void loadDeer();
    static void loadGreekHoplite();
    static void loadGreekHorseman();
    static void loadGreekRockThrower();
    static void loadTrojanHoplite();
    static void loadTrojanHorseman();
    static void loadTrojanSpearthrower();
    static void loadCentaurHorseman();
    static void loadCentaurArcher();
    static void loadEgyptianHoplite();
    static void loadEgyptianChariot();
    static void loadEgyptianArcher();
    static void loadMayanHoplite();
    static void loadMayanArcher();
    static void loadOceanidHoplite();
    static void loadOceanidSpearthrower();
    static void loadPhoenicianHorseman();
    static void loadPhoenicianArcher();
    static void loadAtlanteanHoplite();
    static void loadAtlanteanChariot();
    static void loadAtlanteanArcher();
    static void loadPersianHoplite();
    static void loadPersianHorseman();
    static void loadPersianArcher();
    static void loadAmazonSpear();
    static void loadAmazonArcher();
    static void loadAresWarrior();
    static void loadDonkey();
    static void loadDisgruntled();
    static void loadSick();

    static void loadBanners();

    static void loadCalydonianBoar();
    static void loadCerberus();
    static void loadChimera();
    static void loadCyclops();
    static void loadDragon();
    static void loadEchidna();
    static void loadHarpie();
    static void loadHector();
    static void loadHydra();
    static void loadKraken();
    static void loadMaenads();
    static void loadMedusa();
    static void loadMinotaur();
    static void loadScylla();
    static void loadSphinx();
    static void loadTalos();

    static void loadAchilles();
    static void loadAtalanta();
    static void loadBellerophon();
    static void loadHeracles();
    static void loadJason();
    static void loadOdysseus();
    static void loadPerseus();
    static void loadTheseus();

    static void loadAphrodite();
    static void loadApollo();
    static void loadAres();
    static void loadArtemis();
    static void loadAthena();
    static void loadAtlas();
    static void loadDemeter();
    static void loadDionysus();
    static void loadHades();
    static void loadHephaestus();
    static void loadHera();
    static void loadHermes();
    static void loadPoseidon();
    static void loadZeus();

    static bool initialize(SDL_Renderer* const r);
    static bool loadNextMenu(const eSettings& settings,
                             std::string& text);
    static bool loadNextGame(const eSettings& settings,
                             std::string& text);
    static int gameSize(const eSettings& settings);
    static int menuSize();

    static void setSettings(const eSettings& s);
private:
    static eSettings sSettings;
    static bool sInitialized;
    static std::vector<eTerrainTextures> sTerrainTextures;
    static std::vector<eGodTextures> sGodTextures;
    static std::vector<eBuildingTextures> sBuildingTextures;
    static std::vector<eCharacterTextures> sCharacterTextures;
    static std::vector<eInterfaceTextures> sInterfaceTextures;
    static std::vector<eDestructionTextures> sDestructionTextures;
};

#endif // EGAMETEXTURES_H
