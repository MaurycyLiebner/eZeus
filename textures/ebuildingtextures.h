#ifndef EBUILDINGTEXTURES_H
#define EBUILDINGTEXTURES_H

#include "etexturecollection.h"

class eBuildingTextures {
public:
    eBuildingTextures(const int tileW, const int tileH,
                     SDL_Renderer* const renderer);

    void load();

    const int fTileW;
    const int fTileH;
    SDL_Renderer* const fRenderer;

    std::shared_ptr<eTexture> fHouseSpace;
    std::vector<eTextureCollection> fCommonHouse;

    std::vector<eTextureCollection> fEliteHouse;
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
    eTextureCollection fUrchinQuay;

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
    std::vector<eTextureCollection> fMasonryShopOverlay0;
    std::vector<eTextureCollection> fMasonryShopOverlay1;
    std::vector<eTextureCollection> fMasonryShopOverlay2;

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

    std::shared_ptr<eTexture> fHorseRanch;
    eTextureCollection fHorseRanchOverlay;
    std::shared_ptr<eTexture> fHorseRanchEnclosure;

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

    eTextureCollection fBeachRoad;
    eTextureCollection fToBeachRoad;
    eTextureCollection fRoad;
    eTextureCollection fPrettyRoad;

    eTextureCollection fPatrolGuides;

    eTextureCollection fWaitingMeat;
    eTextureCollection fWaitingCheese;
    eTextureCollection fWaitingWheat;
    eTextureCollection fWaitingOranges;
    eTextureCollection fWaitingWood;
    eTextureCollection fWaitingBronze;
    eTextureCollection fWaitingGrapes;
    eTextureCollection fWaitingOlives;
    eTextureCollection fWaitingArmor;

//    eTextureCollection fAgoraRoad;
//    eTextureCollection fAgora;

    std::shared_ptr<eTexture> fFoodVendor;
    std::shared_ptr<eTexture> fFoodVendorOverlay;

    std::shared_ptr<eTexture> fFleeceVendor;
    std::shared_ptr<eTexture> fFleeceVendorOverlay;

    std::shared_ptr<eTexture> fOilVendor;
    std::shared_ptr<eTexture> fOilVendorOverlay;

    std::shared_ptr<eTexture> fArmsVendor;
    std::shared_ptr<eTexture> fArmsVendorOverlay;

    std::shared_ptr<eTexture> fWineVendor;
    std::shared_ptr<eTexture> fWineVendorOverlay;

    std::shared_ptr<eTexture> fHorseTrainer;
    std::shared_ptr<eTexture> fHorseTrainerOverlay;

    std::shared_ptr<eTexture> fWarehouse;
    eTextureCollection fWarehouseOverlay;

    std::shared_ptr<eTexture> fWarehouseEmpty;
    eTextureCollection fWarehouseUrchin;
    eTextureCollection fWarehouseFish;
    eTextureCollection fWarehouseMeat;
    eTextureCollection fWarehouseCheese;
    eTextureCollection fWarehouseCarrots;
    eTextureCollection fWarehouseOnions;
    eTextureCollection fWarehouseWheat;
    eTextureCollection fWarehouseOranges;

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
    std::shared_ptr<eTexture> fSundial;
    std::shared_ptr<eTexture> fDolphinSculpture;

    eTextureCollection fSpring;

    std::shared_ptr<eTexture> fTopiary;

    std::shared_ptr<eTexture> fBaths;
    eTextureCollection fBathsOverlay;

    std::shared_ptr<eTexture> fStoneCircle;
    eTextureCollection fStoneCircleOverlay;

    eTextureCollection fAppeal;
    eTextureCollection fHouseAppeal;

    eTextureCollection fClouds;

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

    std::shared_ptr<eTexture> fHeroHall;
    // achilles, hercules, jason
    eTextureCollection fHeroStatues;

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

    std::shared_ptr<eTexture> fMonumentStone;

    std::vector<eTextureCollection> fSanctuary;

    eTextureCollection fSanctuaryWOverlay;
    eTextureCollection fSanctuaryHOverlay;

    eTextureCollection fSanctuaryStairs;
};

#endif // EBUILDINGTEXTURES_H
