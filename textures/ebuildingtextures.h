#ifndef EBUILDINGTEXTURES_H
#define EBUILDINGTEXTURES_H

#include "etexturecollection.h"

struct eSpriteData;

class eBuildingTextures {
public:
    eBuildingTextures(const int tileW, const int tileH,
                     SDL_Renderer* const renderer);

    void load();
    bool fLoaded = false;

    const int fTileW;
    const int fTileH;
    SDL_Renderer* const fRenderer;

    bool fCommonHouseLoaded = false;
    void loadCommonHouse();
    bool fPoseidonCommonHouseLoaded = false;
    void loadPoseidonCommonHouse();
    bool fEliteHouseLoaded = false;
    void loadEliteHouse();
    bool fPoseidonEliteHouseLoaded = false;
    void loadPoseidonEliteHouse();
    bool fCollegeLoaded = false;
    void loadCollege();
    bool fGymnasiumLoaded = false;
    void loadGymnasium();
    bool fDramaSchoolLoaded = false;
    void loadDramaSchool();
    bool fPodiumLoaded = false;
    void loadPodium();
    bool fTheaterLoaded = false;
    void loadTheater();
    bool fStadiumLoaded = false;
    void loadStadium();
    bool fFountainLoaded = false;
    void loadFountain();
    bool fHospitalLoaded = false;
    void loadHospital();
    bool fOliveTreeLoaded = false;
    void loadOliveTree();
    bool fVineLoaded = false;
    void loadVine();
    bool fPlantationLoaded = false;
    void loadPlantation();
    bool fHuntingLodgeLoaded = false;
    void loadHuntingLodge();
    bool fFisheryLoaded = false;
    void loadFishery();
    bool fUrchinQuayLoaded = false;
    void loadUrchinQuay();
    bool fCardingShedLoaded = false;
    void loadCardingShed();
    bool fDairyLoaded = false;
    void loadDairy();
    bool fGrowersLodgeLoaded = false;
    void loadGrowersLodge();
    bool fTimberMillLoaded = false;
    void loadTimberMill();
    bool fMasonryShopLoaded = false;
    void loadMasonryShop();
    bool fBlackMarbleWorkshopLoaded = false;
    void loadBlackMarbleWorkshop();
    bool fOrichalcTowerOverlayLoaded = false;
    void loadOrichalcTowerOverlay();
    bool fMasonryShopOverlaysLoaded = false;
    void loadMasonryShopOverlays();
    bool fMintLoaded = false;
    void loadMint();
    bool fFoundryLoaded = false;
    void loadFoundry();
    bool fArtisansGuildLoaded = false;
    void loadArtisansGuild();
    bool fOlivePressLoaded = false;
    void loadOlivePress();
    bool fWineryLoaded = false;
    void loadWinery();
    bool fSculptureStudioLoaded = false;
    void loadSculptureStudio();
    bool fTriremeWharfLoaded = false;
    void loadTriremeWharf();
    bool fHorseRanchLoaded = false;
    void loadHorseRanch();
    bool fArmoryLoaded = false;
    void loadArmory();
    bool fGatehouseAndTowerLoaded = false;
    void loadGatehouseAndTower();
    bool fWallLoaded = false;
    void loadWall();
    bool fMaintenanceOfficeLoaded = false;
    void loadMaintenanceOffice();
    bool fTaxOfficeLoaded = false;
    void loadTaxOffice();
    bool fWatchpostLoaded = false;
    void loadWatchpost();
    bool fRoadblockLoaded = false;
    void loadRoadblock();
    bool fBridgeLoaded = false;
    void loadBridge();
    bool fPoseidonBridgeLoaded = false;
    void loadPoseidonBridge();
    bool fPalaceLoaded = false;
    void loadPalace();
    bool fPalaceTilesLoaded = false;
    void loadPalaceTiles();
    bool fSanctuaryLoaded = false;
    void loadSanctuary();
    bool fZeusSanctuaryLoaded = false;
    void loadZeusSanctuary();
    bool fPoseidonSanctuaryLoaded = false;
    void loadPoseidonSanctuary();
    bool fPyramidLoaded = false;
    void loadPyramid();
    bool fPyramid2Loaded = false;
    void loadPyramid2();
    bool fPoseidonHerosHallLoaded = false;
    void loadPoseidonHerosHall();
    bool fHerosHallLoaded = false;
    void loadHerosHall();
    bool fWaitingOverlayLoaded = false;
    void loadWaitingOverlay();
    bool fOrangeTendersLodgeLoaded = false;
    void loadOrangeTendersLodge();
    bool fWaterParkLoaded = false;
    void loadWaterPark();
    bool fShortObeliskLoaded = false;
    void loadShortObelisk();
    bool fBirdBathLoaded = false;
    void loadBirdBath();
    bool fBathsLoaded = false;
    void loadBaths();
    bool fShellGardenLoaded = false;
    void loadShellGarden();
    bool fOrreryLoaded = false;
    void loadOrrery();
    bool fDolphinSculptureLoaded = false;
    void loadDolphinSculpture();
    bool fStoneCircleLoaded = false;
    void loadStoneCircle();
    bool fSpringLoaded = false;
    void loadSpring();
    bool fTopiaryLoaded = false;
    void loadTopiary();
    bool fSundialLoaded = false;
    void loadSundial();
    bool fTallObeliskLoaded = false;
    void loadTallObelisk();
    bool fAvenueLoaded = false;
    void loadAvenue();
    bool fColumnsLoaded = false;
    void loadColumns();
    bool fCommemorativeLoaded = false;
    void loadCommemorative();
    bool fFishPondLoaded = false;
    void loadFishPond();
    bool fHedgeMazeLoaded = false;
    void loadHedgeMaze();
    bool fGazeboLoaded = false;
    void loadGazebo();
    bool fFlowerGardenLoaded = false;
    void loadFlowerGarden();
    bool fBenchLoaded = false;
    void loadBench();
    bool fParkLoaded = false;
    void loadPark();

    bool fZeusMonumentsLoaded = false;
    void loadZeusMonuments();
    bool fPoseidonMonumentsLoaded = false;
    void loadPoseidonMonuments();
    bool fHadesMonumentsLoaded = false;
    void loadHadesMonuments();
    bool fDemeterMonumentsLoaded = false;
    void loadDemeterMonuments();
    bool fAthenaMonumentsLoaded = false;
    void loadAthenaMonuments();
    bool fArtemisMonumentsLoaded = false;
    void loadArtemisMonuments();
    bool fApolloMonumentsLoaded = false;
    void loadApolloMonuments();
    bool fAresMonumentsLoaded = false;
    void loadAresMonuments();
    bool fHephaestusMonumentsLoaded = false;
    void loadHephaestusMonuments();
    bool fAphroditeMonumentsLoaded = false;
    void loadAphroditeMonuments();
    bool fHermesMonumentsLoaded = false;
    void loadHermesMonuments();
    bool fDionysusMonumentsLoaded = false;
    void loadDionysusMonuments();

    bool fHeraMonumentsLoaded = false;
    void loadHeraMonuments();
    bool fAtlasMonumentsLoaded = false;
    void loadAtlasMonuments();

    bool fAgoraLoaded = false;
    void loadAgora();
    bool fGranaryLoaded = false;
    void loadGranary();
    bool fPierLoaded = false;
    void loadPier();
    bool fTradingPostLoaded = false;
    void loadTradingPost();

    bool fBibliothekeLoaded = false;
    void loadBibliotheke();
    bool fObservatoryLoaded = false;
    void loadObservatory();
    bool fUniversityLoaded = false;
    void loadUniversity();
    bool fLaboratoryLoaded = false;
    void loadLaboratory();
    bool fInventorsWorkshopLoaded = false;
    void loadInventorsWorkshop();
    bool fMuseumLoaded = false;
    void loadMuseum();

    bool fCorralLoaded = false;
    void loadCorral();

    bool fChariotFactoryLoaded = false;
    void loadChariotFactory();

    bool fChariotVendorLoaded = false;
    void loadChariotVendor();

    bool fWineVendorLoaded = false;
    void loadWineVendor();

    bool fAltarBullOverlayLoaded = false;
    void loadAltarBullOverlay();
    bool fAltarSheepOverlayLoaded = false;
    void loadAltarSheepOverlay();
    bool fAltarGoodsOverlayLoaded = false;
    void loadAltarGoodsOverlay();

    std::shared_ptr<eTexture> fHouseSpace;
    std::vector<eTextureCollection> fCommonHouse;
    std::vector<eTextureCollection> fPoseidonCommonHouse;

    std::vector<eTextureCollection> fEliteHouse;
    std::vector<eTextureCollection> fPoseidonEliteHouse;
    eTextureCollection fEliteHouseHorses;

    std::shared_ptr<eTexture> fGymnasium;
    eTextureCollection fGymnasiumOverlay;

    std::shared_ptr<eTexture> fCollege;
    eTextureCollection fCollegeOverlay;

    std::shared_ptr<eTexture> fDramaSchool;
    eTextureCollection fDramaSchoolOverlay;

    std::shared_ptr<eTexture> fPodium;
    eTextureCollection fPodiumOverlay;

    std::shared_ptr<eTexture> fTheater;
    eTextureCollection fTheaterOverlay;

    std::shared_ptr<eTexture> fStadium1H;
    std::shared_ptr<eTexture> fStadium2H;

    std::shared_ptr<eTexture> fStadium1W;
    std::shared_ptr<eTexture> fStadium2W;

    eTextureCollection fStadiumOverlay1;
    eTextureCollection fStadiumOverlay2;
    eTextureCollection fStadiumOverlay3;
    eTextureCollection fStadiumOverlay4W;
    eTextureCollection fStadiumOverlay4H;
    eTextureCollection fStadiumOverlay5W;
    eTextureCollection fStadiumOverlay5H;

    eTextureCollection fStadiumAudiance1W;
    eTextureCollection fStadiumAudiance2W;

    eTextureCollection fStadiumAudiance1H;
    eTextureCollection fStadiumAudiance2H;

    std::shared_ptr<eTexture> fBibliotheke;
    eTextureCollection fBibliothekeOverlay;

    std::shared_ptr<eTexture> fObservatory;
    eTextureCollection fObservatoryOverlay;

    std::shared_ptr<eTexture> fUniversity;
    eTextureCollection fUniversityOverlay;

    std::shared_ptr<eTexture> fLaboratory;
    eTextureCollection fLaboratoryOverlay;

    std::shared_ptr<eTexture> fInventorsWorkshop;
    eTextureCollection fInventorsWorkshopOverlay;

    std::shared_ptr<eTexture> fMuseum;
    eTextureCollection fMuseumOverlay;

    std::shared_ptr<eTexture> fPalace1H;
    std::shared_ptr<eTexture> fPalace2H;

    std::shared_ptr<eTexture> fPalace1W;
    std::shared_ptr<eTexture> fPalace2W;

    eTextureCollection fPalaceHOverlay;
    eTextureCollection fPalaceWOverlay;

    eTextureCollection fPalaceTiles;

    std::shared_ptr<eTexture> fFountain;
    eTextureCollection fFountainOverlay;

    std::shared_ptr<eTexture> fHospital;
    eTextureCollection fHospitalOverlay;


    eTextureCollection fOliveTree;
    eTextureCollection fVine;
    eTextureCollection fOrangeTree;

    std::shared_ptr<eTexture> fPlantation;
    eTextureCollection fWheat;
    eTextureCollection fCarrots;
    eTextureCollection fOnions;

    std::shared_ptr<eTexture> fHuntingLodge;
    eTextureCollection fHuntingLodgeOverlay;

    eTextureCollection fFishery;
    eTextureCollection fFisheryBoatBuildingW;
    eTextureCollection fFisheryBoatBuildingH;
    std::vector<eTextureCollection> fFisheryOverlay;
    eTextureCollection fFisheryUnpackingOverlayTL;
    eTextureCollection fFisheryUnpackingOverlayTR;
    eTextureCollection fFisheryUnpackingOverlayBL;
    eTextureCollection fFisheryUnpackingOverlayBR;
    eTextureCollection fUrchinQuay;
    eTextureCollection fUrchinQuayUnpackingOverlayTL;
    eTextureCollection fUrchinQuayUnpackingOverlayTR;
    eTextureCollection fUrchinQuayUnpackingOverlayBL;
    eTextureCollection fUrchinQuayUnpackingOverlayBR;

    std::shared_ptr<eTexture> fCardingShed;
    eTextureCollection fCardingShedOverlay;

    std::shared_ptr<eTexture> fDairy;
    eTextureCollection fDairyOverlay;

    std::shared_ptr<eTexture> fGrowersLodge;
    eTextureCollection fGrowersLodgeOverlay;

//    std::shared_ptr<eTexture> fCorral;
//    eTextureCollection fCorralOverlay;

    std::shared_ptr<eTexture> fOrangeTendersLodge;
    eTextureCollection fOrangeTendersLodgeOverlay;

    std::shared_ptr<eTexture> fTimberMill;
    eTextureCollection fTimberMillOverlay;

    std::shared_ptr<eTexture> fMasonryShop;
    eTextureCollection fMasonryShopStones;
    std::shared_ptr<eTexture> fBlackMarbleWorkshop;
    eTextureCollection fBlackMarbleWorkshopStones;
    std::vector<eTextureCollection> fWaitingOverlay0;
    std::vector<eTextureCollection> fWaitingOverlay1;
    std::vector<eTextureCollection> fMasonryShopOverlay1;
    std::vector<eTextureCollection> fMasonryShopOverlay2;

    std::shared_ptr<eTexture> fOrichalcTowerOverlay;

    std::shared_ptr<eTexture> fMint;
    eTextureCollection fMintOverlay;

    std::shared_ptr<eTexture> fFoundry;
    eTextureCollection fFoundryOverlay;

    std::shared_ptr<eTexture> fArtisansGuild;
    eTextureCollection fArtisansGuildOverlay;

    std::shared_ptr<eTexture> fOlivePress;
    eTextureCollection fOlivePressOverlay;

    std::shared_ptr<eTexture> fWinery;
    eTextureCollection fWineryOverlay;

    std::shared_ptr<eTexture> fSculptureStudio;
    eTextureCollection fSculptureStudioOverlay;

    eTextureCollection fTriremeWharf;
    eTextureCollection fTriremeWharfOverlay1BL;
    eTextureCollection fTriremeWharfOverlay1BR;
    eTextureCollection fTriremeWharfOverlay1TL;
    eTextureCollection fTriremeWharfOverlay1TR;
    eTextureCollection fTriremeWharfOverlay2BL;
    eTextureCollection fTriremeWharfOverlay2BR;
    eTextureCollection fTriremeWharfOverlay2TL;
    eTextureCollection fTriremeWharfOverlay2TR;

    std::shared_ptr<eTexture> fHorseRanch;
    eTextureCollection fHorseRanchOverlay;
    std::shared_ptr<eTexture> fHorseRanchEnclosure;

    std::shared_ptr<eTexture> fCorral;
    eTextureCollection fCorralOverlay;
    std::vector<eTextureCollection> fCorralCattleOverlay;
    eTextureCollection fCorralProcessingOverlay;

    std::shared_ptr<eTexture> fArmory;
    eTextureCollection fArmoryOverlay;

    eTextureCollection fGatehouseW;
    eTextureCollection fGatehouseH;
    std::shared_ptr<eTexture> fTower;
    eTextureCollection fWall;

    std::shared_ptr<eTexture> fMaintenanceOffice;
    eTextureCollection fMaintenanceOfficeOverlay;

    std::shared_ptr<eTexture> fTaxOffice;
    eTextureCollection fTaxOfficeOverlay;

    std::shared_ptr<eTexture> fWatchPost;
    eTextureCollection fWatchPostOverlay;

    eTextureCollection fWaitingMeat;
    eTextureCollection fWaitingCheese;
    eTextureCollection fWaitingWheat;
    eTextureCollection fWaitingOranges;
    eTextureCollection fWaitingWood;
    eTextureCollection fWaitingBronze;
    eTextureCollection fWaitingGrapes;
    eTextureCollection fWaitingOlives;
    eTextureCollection fWaitingArmor;
    eTextureCollection fWaitingOrichalc;

    eTextureCollection fAgoraRoad;
    eTextureCollection fAgora;

    std::shared_ptr<eTexture> fFoodVendor;
    std::shared_ptr<eTexture> fFoodVendorOverlay;
    eTextureCollection fFoodVendorOverlay2;

    std::shared_ptr<eTexture> fFleeceVendor;
    std::shared_ptr<eTexture> fFleeceVendorOverlay;
    eTextureCollection fFleeceVendorOverlay2;

    std::shared_ptr<eTexture> fOilVendor;
    std::shared_ptr<eTexture> fOilVendorOverlay;
    eTextureCollection fOilVendorOverlay2;

    std::shared_ptr<eTexture> fArmsVendor;
    std::shared_ptr<eTexture> fArmsVendorOverlay;
    eTextureCollection fArmsVendorOverlay2;

    std::shared_ptr<eTexture> fWineVendor;
    std::shared_ptr<eTexture> fWineVendorOverlay;
    eTextureCollection fWineVendorOverlay2;

    std::shared_ptr<eTexture> fHorseTrainer;
    std::shared_ptr<eTexture> fHorseTrainerOverlay;
    eTextureCollection fHorseTrainerOverlay2;

    std::shared_ptr<eTexture> fChariotVendor;
    std::shared_ptr<eTexture> fChariotVendorOverlay;
    eTextureCollection fChariotVendorOverlay2;

    std::shared_ptr<eTexture> fChariotFactory;
    eTextureCollection fChariotFactoryOverlay;
    eTextureCollection fChariotFactoryOverlay1;
    std::vector<eTextureCollection> fChariotFactoryHorses;
    eTextureCollection fChariotFactoryChariots;

    std::shared_ptr<eTexture> fWarehouse;
    eTextureCollection fWarehouseOverlay;

    eTextureCollection fPier1;
    std::shared_ptr<eTexture> fPier2;

    std::shared_ptr<eTexture> fTradingPost;
    eTextureCollection fTradingPostOverlay;

    std::shared_ptr<eTexture> fWarehouseEmpty;
    eTextureCollection fWarehouseUrchin;
    eTextureCollection fWarehouseFish;
    eTextureCollection fWarehouseMeat;
    eTextureCollection fWarehouseCheese;
    eTextureCollection fWarehouseCarrots;
    eTextureCollection fWarehouseOnions;
    eTextureCollection fWarehouseWheat;
    eTextureCollection fWarehouseOranges;
    eTextureCollection fWarehouseBlackMarble;
    eTextureCollection fWarehouseOrichalc;

    eTextureCollection fWarehouseWood;
    eTextureCollection fWarehouseBronze;
    eTextureCollection fWarehouseMarble;
    eTextureCollection fWarehouseGrapes;
    eTextureCollection fWarehouseOlives;
    eTextureCollection fWarehouseFleece;
    eTextureCollection fWarehouseArmor;
    std::shared_ptr<eTexture> fWarehouseSculpture;
    eTextureCollection fWarehouseOliveOil;
    eTextureCollection fWarehouseWine;

    std::shared_ptr<eTexture> fGranary;
    eTextureCollection fGranaryOverlay;

    std::shared_ptr<eTexture> fGranaryUrchin;
    std::shared_ptr<eTexture> fGranaryFish;
    std::shared_ptr<eTexture> fGranaryMeat;
    std::shared_ptr<eTexture> fGranaryCheese;
    std::shared_ptr<eTexture> fGranaryCarrots;
    std::shared_ptr<eTexture> fGranaryOnions;
    std::shared_ptr<eTexture> fGranaryWheat;
    std::shared_ptr<eTexture> fGranaryOranges;

    eTextureCollection fPark;
    eTextureCollection fLargePark;
    eTextureCollection fHugePark;

    std::shared_ptr<eTexture> fWaterPark1;
    eTextureCollection fWaterPark1Overlay;

    std::shared_ptr<eTexture> fWaterPark2;
    eTextureCollection fWaterPark2Overlay;

    std::shared_ptr<eTexture> fWaterPark3;
    eTextureCollection fWaterPark3Overlay;

    std::shared_ptr<eTexture> fWaterPark4;
    eTextureCollection fWaterPark4Overlay;

    std::shared_ptr<eTexture> fWaterPark5;
    eTextureCollection fWaterPark5Overlay;

    std::shared_ptr<eTexture> fWaterPark6;
    eTextureCollection fWaterPark6Overlay;

    std::shared_ptr<eTexture> fWaterPark7;
    eTextureCollection fWaterPark7Overlay;

    std::shared_ptr<eTexture> fWaterPark8;
    eTextureCollection fWaterPark8Overlay;

    std::shared_ptr<eTexture> fBench;
    std::shared_ptr<eTexture> fFlowerGarden;
    std::shared_ptr<eTexture> fGazebo;
    std::shared_ptr<eTexture> fHedgeMaze;
    std::shared_ptr<eTexture> fFishPond;
    eTextureCollection fFishPondOverlay;

    std::shared_ptr<eTexture> fDoricColumn;
    std::shared_ptr<eTexture> fIonicColumn;
    std::shared_ptr<eTexture> fCorinthianColumn;

    std::vector<eTextureCollection> fAvenue;
    eTextureCollection fAvenueRoad;

    eTextureCollection fCommemorative;

    std::shared_ptr<eTexture> fColumnConnectionH;
    std::shared_ptr<eTexture> fColumnConnectionW;

    std::shared_ptr<eTexture> fBirdBath;
    eTextureCollection fBirdBathOverlay;

    std::shared_ptr<eTexture> fShortObelisk;
    std::shared_ptr<eTexture> fTallObelisk;
    std::shared_ptr<eTexture> fShellGarden;
    std::shared_ptr<eTexture> fOrrery;
    std::shared_ptr<eTexture> fSundial;
    std::shared_ptr<eTexture> fDolphinSculpture;

    eTextureCollection fSpring;

    std::shared_ptr<eTexture> fTopiary;

    std::shared_ptr<eTexture> fBaths;
    eTextureCollection fBathsOverlay;

    std::shared_ptr<eTexture> fStoneCircle;
    eTextureCollection fStoneCircleOverlay;

    eTextureCollection fZeusStatues;
    eTextureCollection fPoseidonStatues;
    eTextureCollection fHadesStatues;
    eTextureCollection fDemeterStatues;
    eTextureCollection fAthenaStatues;
    eTextureCollection fArtemisStatues;
    eTextureCollection fApolloStatues;
    eTextureCollection fAresStatues;
    eTextureCollection fHephaestusStatues;
    eTextureCollection fAphroditeStatues;
    eTextureCollection fHermesStatues;
    eTextureCollection fDionysusStatues;

    eTextureCollection fHeraStatues;
    eTextureCollection fAtlasStatues;

    eTextureCollection fSanctuaryTiles;
    eTextureCollection fSanctuarySpace;
    std::shared_ptr<eTexture> fSanctuaryAltar;
    eTextureCollection fAltarBullOverlay;
    eTextureCollection fAltarSheepOverlay;
    eTextureCollection fAltarGoodsOverlay;

    std::shared_ptr<eTexture> fHeroHall;
    std::shared_ptr<eTexture> fPoseidonHeroHall;
    // achilles, hercules, jason, odysseus,
    // perseus, theseus, bellerophon, atalanta
    eTextureCollection fHeroStatues;

    std::shared_ptr<eTexture> fBlankMonument;

    eTextureCollection fZeusMonuments;
    eTextureCollection fPoseidonMonuments;
    eTextureCollection fHadesMonuments;
    eTextureCollection fDemeterMonuments;
    eTextureCollection fAthenaMonuments;
    eTextureCollection fArtemisMonuments;
    eTextureCollection fApolloMonuments;
    eTextureCollection fAresMonuments;
    eTextureCollection fHephaestusMonuments;
    eTextureCollection fAphroditeMonuments;
    eTextureCollection fHermesMonuments;
    eTextureCollection fDionysusMonuments;

    eTextureCollection fHeraMonuments;
    eTextureCollection fAtlasMonuments;

    std::vector<eTextureCollection> fSanctuary;
    eTextureCollection fPoseidonSanctuary;
    eTextureCollection fPyramid;
    eTextureCollection fPyramid2;

    eTextureCollection fSanctuaryWOverlay;
    eTextureCollection fSanctuaryHOverlay;

    eTextureCollection fSanctuaryFire;

    eTextureCollection fFish;
    eTextureCollection fUrchin;

    std::shared_ptr<eTexture> fRoadblock;
    eTextureCollection fBridge;
    eTextureCollection fPoseidonBridge;

    eTextureCollection fColumn1;
    eTextureCollection fColumn2;
    eTextureCollection fColumn3;
    eTextureCollection fColumn4;
    eTextureCollection fColumn5;

    eTextureCollection fSpawner;
    std::shared_ptr<eTexture> fDisasterPoint;
    std::shared_ptr<eTexture> fLandInvasionPoint;
    std::shared_ptr<eTexture> fEntryPoint;
    std::shared_ptr<eTexture> fExitPoint;
    std::shared_ptr<eTexture> fRiverEntryPoint;
    std::shared_ptr<eTexture> fRiverExitPoint;
    std::shared_ptr<eTexture> fFishPoint;
    std::shared_ptr<eTexture> fUrchinPoint;
    std::shared_ptr<eTexture> fWolfPoint;
    std::shared_ptr<eTexture> fBoarPoint;
    std::shared_ptr<eTexture> fDeerPoint;
    std::shared_ptr<eTexture> fMonsterPoint;


    std::shared_ptr<eTexture> fSuppliesBg;
    std::shared_ptr<eTexture> fEliteSuppliesBg;

    std::shared_ptr<eTexture> fHasFood;
    std::shared_ptr<eTexture> fHasFleece;
    std::shared_ptr<eTexture> fHasOil;
    std::shared_ptr<eTexture> fHasWine;
    std::shared_ptr<eTexture> fHasArms;
    std::shared_ptr<eTexture> fHasHorses;

    std::shared_ptr<eTexture> fNHasFood;
    std::shared_ptr<eTexture> fNHasFleece;
    std::shared_ptr<eTexture> fNHasOil;
    std::shared_ptr<eTexture> fNHasWine;
    std::shared_ptr<eTexture> fNHasArms;
    std::shared_ptr<eTexture> fNHasHorses;
private:
    bool fFisheryOverlayLoaded = false;
    void loadFisheryOverlay();

    void loadGodMonuments(const std::vector<eSpriteData>& sd15,
                          const std::vector<eSpriteData>& sd30,
                          const std::vector<eSpriteData>& sd45,
                          const std::vector<eSpriteData>& sd60,
                          const std::string& name,
                          eTextureCollection& coll);
    void generateFlipped(const eTextureCollection& src,
                         eTextureCollection& dst);
};

#endif // EBUILDINGTEXTURES_H
