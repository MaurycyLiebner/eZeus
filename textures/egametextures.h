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
    static void loadInterfaceTexture(const std::function<void(int)>& func);

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
    static void loadPoseidonTowerArcher();
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
    static void loadCompetitor();
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

    static void loadFire();

    static void loadBlessed();
    static void loadCursed();

    static void loadRock();
    static void loadArrow();

    static void loadBless();
    static void loadCurse();

    static void loadPlague();

    static void loadGodOrangeMissile();
    static void loadGodBlueArrow();
    static void loadGodOrangeArrow();
    static void loadMonsterMissile();
    static void loadGodBlueMissile();
    static void loadGodRedMissile();
    static void loadGodGreenMissile();
    static void loadGodPinkMissile();
    static void loadGodPurpleMissile();

    static void loadCommonHouse();
    static void loadPoseidonCommonHouse();
    static void loadEliteHouse();
    static void loadPoseidonEliteHouse();
    static void loadCollege();
    static void loadGymnasium();
    static void loadDramaSchool();
    static void loadPodium();
    static void loadTheater();
    static void loadStadium();
    static void loadFountain();
    static void loadHospital();
    static void loadOliveTree();
    static void loadVine();
    static void loadPlantation();
    static void loadHuntingLodge();
    static void loadFishery();
    static void loadUrchinQuay();
    static void loadCardingShed();
    static void loadDairy();
    static void loadGrowersLodge();
    static void loadTimberMill();
    static void loadMasonryShop();
    static void loadMint();
    static void loadFoundry();
    static void loadArtisansGuild();
    static void loadOlivePress();
    static void loadWinery();
    static void loadSculptureStudio();
    static void loadTriremeWharf();
    static void loadHorseRanch();
    static void loadArmory();
    static void loadGatehouseAndTower();
    static void loadWall();
    static void loadMaintenanceOffice();
    static void loadTaxOffice();
    static void loadWatchpost();
    static void loadRoadblock();
    static void loadBridge();
    static void loadPalace();
    static void loadPalaceTiles();
    static void loadSanctuary();
    static void loadOrangeTendersLodge();
    static void loadWaterPark();
    static void loadShortObelisk();
    static void loadBirdBath();
    static void loadBaths();
    static void loadShellGarden();
    static void loadOrrery();
    static void loadDolphinSculpture();
    static void loadStoneCircle();
    static void loadSpring();
    static void loadTopiary();
    static void loadSundial();
    static void loadTallObelisk();
    static void loadAvenue();
    static void loadColumns();
    static void loadCommemorative();
    static void loadFishPond();
    static void loadHedgeMaze();
    static void loadGazebo();
    static void loadFlowerGarden();
    static void loadBench();
    static void loadPark();

    static void loadZeusMonuments();
    static void loadPoseidonMonuments();
    static void loadHadesMonuments();
    static void loadDemeterMonuments();
    static void loadAthenaMonuments();
    static void loadArtemisMonuments();
    static void loadApolloMonuments();
    static void loadAresMonuments();
    static void loadHephaestusMonuments();
    static void loadAphroditeMonuments();
    static void loadHermesMonuments();
    static void loadDionysusMonuments();

    static void loadHeraMonuments();
    static void loadAtlasMonuments();

    static void loadHerosHall();

    static void loadWaitingOverlay();

    static void loadAgora();
    static void loadPier();
    static void loadTradingPost();
    static void loadGranary();

    static void loadMapOfGreece1();
    static void loadMapOfGreece2();
    static void loadMapOfGreece3();
    static void loadMapOfGreece4();
    static void loadMapOfGreece5();
    static void loadMapOfGreece6();
    static void loadMapOfGreece7();
    static void loadMapOfGreece8();

    static void loadPoseidonMap1();
    static void loadPoseidonMap2();
    static void loadPoseidonMap3();
    static void loadPoseidonMap4();

    static void loadPoseidonCampaign1();
    static void loadPoseidonCampaign2();
    static void loadPoseidonCampaign3();
    static void loadPoseidonCampaign4();
    static void loadPoseidonCampaign5();
    static void loadPoseidonCampaign6();

    static void loadScholar();
    static void loadAstronomer();
    static void loadInventor();
    static void loadCurator();

    static void loadBibliotheke();
    static void loadObservatory();
    static void loadUniversity();
    static void loadLaboratory();
    static void loadInventorsWorkshop();
    static void loadMuseum();
    static void loadChariotFactory();
    static void loadChariotVendor();
    static void loadChariotVendorCharacter();
    static void loadChariot();
    static void loadWineVendorBuilding();
    static void loadElephant();

    static void loadZeusSanctuary();
    static void loadPoseidonSanctuary();
    static void loadPoseidonHerosHall();

    static void loadHoplitePoseidon();
    static void loadArcherPoseidon();
    static void loadChariotPoseidon();

    static void loadCorral();

    static void loadButcher();
    static void loadCattle();
    static void loadBull();

    static void loadPoseidonTrees();

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
