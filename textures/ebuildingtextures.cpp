#include "ebuildingtextures.h"

#include "offsets/SprAmbient.h"

#include "spriteData/beautification215.h"
#include "spriteData/beautification230.h"
#include "spriteData/beautification245.h"
#include "spriteData/beautification260.h"

#include "spriteData/culture15.h"
#include "spriteData/culture30.h"
#include "spriteData/culture45.h"
#include "spriteData/culture60.h"

#include "spriteData/healthNSan15.h"
#include "spriteData/healthNSan30.h"
#include "spriteData/healthNSan45.h"
#include "spriteData/healthNSan60.h"

#include "spriteData/housing15.h"
#include "spriteData/housing30.h"
#include "spriteData/housing45.h"
#include "spriteData/housing60.h"

#include "spriteData/husbandry15.h"
#include "spriteData/husbandry30.h"
#include "spriteData/husbandry45.h"
#include "spriteData/husbandry60.h"

#include "spriteData/industry15.h"
#include "spriteData/industry30.h"
#include "spriteData/industry45.h"
#include "spriteData/industry60.h"

#include "spriteData/military15.h"
#include "spriteData/military30.h"
#include "spriteData/military45.h"
#include "spriteData/military60.h"

#include "spriteData/municipal15.h"
#include "spriteData/municipal30.h"
#include "spriteData/municipal45.h"
#include "spriteData/municipal60.h"

#include "spriteData/mun_Palace15.h"
#include "spriteData/mun_Palace30.h"
#include "spriteData/mun_Palace45.h"
#include "spriteData/mun_Palace60.h"

#include "spriteData/religion15.h"
#include "spriteData/religion30.h"
#include "spriteData/religion45.h"
#include "spriteData/religion60.h"

#include "spriteData/stor_bays15.h"
#include "spriteData/stor_bays30.h"
#include "spriteData/stor_bays45.h"
#include "spriteData/stor_bays60.h"

#include "spriteData/storNDist15.h"
#include "spriteData/storNDist30.h"
#include "spriteData/storNDist45.h"
#include "spriteData/storNDist60.h"

#include "spriteData/aesthetic15.h"
#include "spriteData/aesthetic30.h"
#include "spriteData/aesthetic45.h"
#include "spriteData/aesthetic60.h"

#include "spriteData/storage15.h"
#include "spriteData/storage30.h"
#include "spriteData/storage45.h"
#include "spriteData/storage60.h"

#include "spriteData/tradingPostOverlay15.h"
#include "spriteData/tradingPostOverlay30.h"
#include "spriteData/tradingPostOverlay45.h"
#include "spriteData/tradingPostOverlay60.h"

#include "spriteData/warehouseOverlay15.h"
#include "spriteData/warehouseOverlay30.h"
#include "spriteData/warehouseOverlay45.h"
#include "spriteData/warehouseOverlay60.h"

#include "spriteData/fish15.h"
#include "spriteData/fish30.h"
#include "spriteData/fish45.h"
#include "spriteData/fish60.h"

#include "spriteData/urchin15.h"
#include "spriteData/urchin30.h"
#include "spriteData/urchin45.h"
#include "spriteData/urchin60.h"

#include "spriteData/theaterOverlay15.h"
#include "spriteData/theaterOverlay30.h"
#include "spriteData/theaterOverlay45.h"
#include "spriteData/theaterOverlay60.h"

#include "spriteData/fisheryBoatBuilding15.h"
#include "spriteData/fisheryBoatBuilding30.h"
#include "spriteData/fisheryBoatBuilding45.h"
#include "spriteData/fisheryBoatBuilding60.h"

#include "spriteData/fisheryOverlay15.h"
#include "spriteData/fisheryOverlay30.h"
#include "spriteData/fisheryOverlay45.h"
#include "spriteData/fisheryOverlay60.h"

#include "spriteData/urchinUnpackingOverlay15.h"
#include "spriteData/urchinUnpackingOverlay30.h"
#include "spriteData/urchinUnpackingOverlay45.h"
#include "spriteData/urchinUnpackingOverlay60.h"

#include "spriteData/fisheryUnpackingOverlay15.h"
#include "spriteData/fisheryUnpackingOverlay30.h"
#include "spriteData/fisheryUnpackingOverlay45.h"
#include "spriteData/fisheryUnpackingOverlay60.h"

#include "spriteData/stadiumOverlays15.h"
#include "spriteData/stadiumOverlays30.h"
#include "spriteData/stadiumOverlays45.h"
#include "spriteData/stadiumOverlays60.h"

#include "spriteData/sanctuaryFire15.h"
#include "spriteData/sanctuaryFire30.h"
#include "spriteData/sanctuaryFire45.h"
#include "spriteData/sanctuaryFire60.h"

#include "spriteData/masonryShopOverlays15.h"
#include "spriteData/masonryShopOverlays30.h"
#include "spriteData/masonryShopOverlays45.h"
#include "spriteData/masonryShopOverlays60.h"

#include "spriteData/waitingOverlay15.h"
#include "spriteData/waitingOverlay30.h"
#include "spriteData/waitingOverlay45.h"
#include "spriteData/waitingOverlay60.h"

#include "spriteData/vendorOverlays15.h"
#include "spriteData/vendorOverlays30.h"
#include "spriteData/vendorOverlays45.h"
#include "spriteData/vendorOverlays60.h"

#include "spriteData/wineVendorOverlay15.h"
#include "spriteData/wineVendorOverlay30.h"
#include "spriteData/wineVendorOverlay45.h"
#include "spriteData/wineVendorOverlay60.h"

#include "spriteData/fishPondOverlay15.h"
#include "spriteData/fishPondOverlay30.h"
#include "spriteData/fishPondOverlay45.h"
#include "spriteData/fishPondOverlay60.h"

#include "spriteData/watchPostOverlay15.h"
#include "spriteData/watchPostOverlay30.h"
#include "spriteData/watchPostOverlay45.h"
#include "spriteData/watchPostOverlay60.h"

#include "spriteData/palaceOverlay15.h"
#include "spriteData/palaceOverlay30.h"
#include "spriteData/palaceOverlay45.h"
#include "spriteData/palaceOverlay60.h"

#include "spriteData/zeusStatue15.h"
#include "spriteData/zeusStatue30.h"
#include "spriteData/zeusStatue45.h"
#include "spriteData/zeusStatue60.h"

#include "spriteData/poseidonStatue15.h"
#include "spriteData/poseidonStatue30.h"
#include "spriteData/poseidonStatue45.h"
#include "spriteData/poseidonStatue60.h"

#include "spriteData/hadesStatue15.h"
#include "spriteData/hadesStatue30.h"
#include "spriteData/hadesStatue45.h"
#include "spriteData/hadesStatue60.h"

#include "spriteData/demeterStatue15.h"
#include "spriteData/demeterStatue30.h"
#include "spriteData/demeterStatue45.h"
#include "spriteData/demeterStatue60.h"

#include "spriteData/athenaStatue15.h"
#include "spriteData/athenaStatue30.h"
#include "spriteData/athenaStatue45.h"
#include "spriteData/athenaStatue60.h"

#include "spriteData/artemisStatue15.h"
#include "spriteData/artemisStatue30.h"
#include "spriteData/artemisStatue45.h"
#include "spriteData/artemisStatue60.h"

#include "spriteData/apolloStatue15.h"
#include "spriteData/apolloStatue30.h"
#include "spriteData/apolloStatue45.h"
#include "spriteData/apolloStatue60.h"

#include "spriteData/aresStatue15.h"
#include "spriteData/aresStatue30.h"
#include "spriteData/aresStatue45.h"
#include "spriteData/aresStatue60.h"

#include "spriteData/hephaestusStatue15.h"
#include "spriteData/hephaestusStatue30.h"
#include "spriteData/hephaestusStatue45.h"
#include "spriteData/hephaestusStatue60.h"

#include "spriteData/aphroditeStatue15.h"
#include "spriteData/aphroditeStatue30.h"
#include "spriteData/aphroditeStatue45.h"
#include "spriteData/aphroditeStatue60.h"

#include "spriteData/hermesStatue15.h"
#include "spriteData/hermesStatue30.h"
#include "spriteData/hermesStatue45.h"
#include "spriteData/hermesStatue60.h"

#include "spriteData/dionysusStatue15.h"
#include "spriteData/dionysusStatue30.h"
#include "spriteData/dionysusStatue45.h"
#include "spriteData/dionysusStatue60.h"

#include "spriteData/blankStatue15.h"
#include "spriteData/blankStatue30.h"
#include "spriteData/blankStatue45.h"
#include "spriteData/blankStatue60.h"

#include "spriteData/atlasStatue15.h"
#include "spriteData/atlasStatue30.h"
#include "spriteData/atlasStatue45.h"
#include "spriteData/atlasStatue60.h"

#include "spriteData/heraStatue15.h"
#include "spriteData/heraStatue30.h"
#include "spriteData/heraStatue45.h"
#include "spriteData/heraStatue60.h"

#include "spriteData/zeusSanctuary115.h"
#include "spriteData/zeusSanctuary130.h"
#include "spriteData/zeusSanctuary145.h"
#include "spriteData/zeusSanctuary160.h"

#include "spriteData/zeusSanctuary215.h"
#include "spriteData/zeusSanctuary230.h"
#include "spriteData/zeusSanctuary245.h"
#include "spriteData/zeusSanctuary260.h"

#include "spriteData/zeusSanctuary315.h"
#include "spriteData/zeusSanctuary330.h"
#include "spriteData/zeusSanctuary345.h"
#include "spriteData/zeusSanctuary360.h"

#include "spriteData/poseidonStatues15.h"
#include "spriteData/poseidonStatues30.h"
#include "spriteData/poseidonStatues45.h"
#include "spriteData/poseidonStatues60.h"

#include "textures/espriteloader.h"

eBuildingTextures::eBuildingTextures(const int tileW, const int tileH,
                                     SDL_Renderer* const renderer) :
    fTileW(tileW), fTileH(tileH),
    fRenderer(renderer),

    fEliteHouseHorses(renderer),

    fGymnasiumOverlay(renderer),
    fCollegeOverlay(renderer),
    fDramaSchoolOverlay(renderer),
    fPodiumOverlay(renderer),
    fTheaterOverlay(renderer),
    fStadiumOverlay1(renderer),
    fStadiumOverlay2(renderer),
    fStadiumOverlay3(renderer),
    fStadiumOverlay4W(renderer),
    fStadiumOverlay4H(renderer),
    fStadiumOverlay5W(renderer),
    fStadiumOverlay5H(renderer),
    fStadiumAudiance1W(renderer),
    fStadiumAudiance2W(renderer),
    fStadiumAudiance1H(renderer),
    fStadiumAudiance2H(renderer),

    fPalaceHOverlay(renderer),
    fPalaceWOverlay(renderer),

    fPalaceTiles(renderer),

    fFountainOverlay(renderer),
    fHospitalOverlay(renderer),

    fOliveTree(renderer),
    fVine(renderer),
    fOrangeTree(renderer),

    fWheat(renderer),
    fCarrots(renderer),
    fOnions(renderer),

    fHuntingLodgeOverlay(renderer),
    fFishery(renderer),
    fFisheryBoatBuildingW(renderer),
    fFisheryBoatBuildingH(renderer),
    fFisheryUnpackingOverlayTL(renderer),
    fFisheryUnpackingOverlayTR(renderer),
    fFisheryUnpackingOverlayBL(renderer),
    fFisheryUnpackingOverlayBR(renderer),
    fUrchinQuay(renderer),
    fUrchinQuayUnpackingOverlayTL(renderer),
    fUrchinQuayUnpackingOverlayTR(renderer),
    fUrchinQuayUnpackingOverlayBL(renderer),
    fUrchinQuayUnpackingOverlayBR(renderer),
    fCardingShedOverlay(renderer),
    fDairyOverlay(renderer),
    fGrowersLodgeOverlay(renderer),
//    fCorralOverlay(renderer),
    fOrangeTendersLodgeOverlay(renderer),

    fTimberMillOverlay(renderer),
    fMasonryShopStones(renderer),
    fMintOverlay(renderer),
    fFoundryOverlay(renderer),
    fArtisansGuildOverlay(renderer),
    fOlivePressOverlay(renderer),
    fWineryOverlay(renderer),
    fSculptureStudioOverlay(renderer),

    fTriremeWharf(renderer),
    fHorseRanchOverlay(renderer),
    fArmoryOverlay(renderer),

    fGatehouseW(renderer),
    fGatehouseH(renderer),
    fWall(renderer),

    fMaintenanceOfficeOverlay(renderer),
    fTaxOfficeOverlay(renderer),
    fWatchPostOverlay(renderer),

    fWaitingMeat(renderer),
    fWaitingCheese(renderer),
    fWaitingWheat(renderer),
    fWaitingOranges(renderer),
    fWaitingWood(renderer),
    fWaitingBronze(renderer),
    fWaitingGrapes(renderer),
    fWaitingOlives(renderer),
    fWaitingArmor(renderer),

    fAgoraRoad(renderer),
    fAgora(renderer),

    fFoodVendorOverlay2(renderer),
    fFleeceVendorOverlay2(renderer),
    fOilVendorOverlay2(renderer),
    fArmsVendorOverlay2(renderer),
    fWineVendorOverlay2(renderer),
    fHorseTrainerOverlay2(renderer),

    fWarehouseOverlay(renderer),

    fPier1(renderer),
    fTradingPostOverlay(renderer),

    fWarehouseUrchin(renderer),
    fWarehouseFish(renderer),
    fWarehouseMeat(renderer),
    fWarehouseCheese(renderer),
    fWarehouseCarrots(renderer),
    fWarehouseOnions(renderer),
    fWarehouseWheat(renderer),
    fWarehouseOranges(renderer),
    fWarehouseWood(renderer),
    fWarehouseBronze(renderer),
    fWarehouseMarble(renderer),
    fWarehouseGrapes(renderer),
    fWarehouseOlives(renderer),
    fWarehouseFleece(renderer),
    fWarehouseArmor(renderer),
    fWarehouseOliveOil(renderer),
    fWarehouseWine(renderer),

    fGranaryOverlay(renderer),

    fPark(renderer),
    fLargePark(renderer),
    fHugePark(renderer),

    fWaterPark1Overlay(renderer),
    fWaterPark2Overlay(renderer),
    fWaterPark3Overlay(renderer),
    fWaterPark4Overlay(renderer),
    fWaterPark5Overlay(renderer),
    fWaterPark6Overlay(renderer),
    fWaterPark7Overlay(renderer),
    fWaterPark8Overlay(renderer),

    fFishPondOverlay(renderer),

    fAvenueRoad(renderer),

    fCommemorative(renderer),

    fBirdBathOverlay(renderer),
    fSpring(renderer),
    fBathsOverlay(renderer),
    fStoneCircleOverlay(renderer),

    fZeusStatues(renderer),
    fPoseidonStatues(renderer),
    fHadesStatues(renderer),
    fDemeterStatues(renderer),
    fAthenaStatues(renderer),
    fArtemisStatues(renderer),
    fApolloStatues(renderer),
    fAresStatues(renderer),
    fHephaestusStatues(renderer),
    fAphroditeStatues(renderer),
    fHermesStatues(renderer),
    fDionysusStatues(renderer),

    fHeraStatues(renderer),
    fAtlasStatues(renderer),

    fSanctuaryTiles(renderer),
    fSanctuarySpace(renderer),

    fHeroStatues(renderer),

    fZeusMonuments(renderer),
    fPoseidonMonuments(renderer),
    fHadesMonuments(renderer),
    fDemeterMonuments(renderer),
    fAthenaMonuments(renderer),
    fArtemisMonuments(renderer),
    fApolloMonuments(renderer),
    fAresMonuments(renderer),
    fHephaestusMonuments(renderer),
    fAphroditeMonuments(renderer),
    fHermesMonuments(renderer),
    fDionysusMonuments(renderer),

    fHeraMonuments(renderer),
    fAtlasMonuments(renderer),

    fSanctuaryWOverlay(renderer),
    fSanctuaryHOverlay(renderer),
    fSanctuaryFire(renderer),

    fFish(renderer),
    fUrchin(renderer),

    fBridge(renderer) {

}

void eBuildingTextures::load() {
    if(fLoaded) return;
    fLoaded = true;

    {
        {
            const auto& sds = spriteData(fTileH,
                                         eHousingSpriteData15,
                                         eHousingSpriteData30,
                                         eHousingSpriteData45,
                                         eHousingSpriteData60);
            eSpriteLoader loader(fTileH, "housing", sds,
                                 nullptr, fRenderer);

            fHouseSpace = loader.load(1, 15);
            for(int i = 1; i < 15;) {
                auto& coll = fCommonHouse.emplace_back(fRenderer);
                for(int j = 0; j < 2; j++, i++) {
                    loader.load(1, i, coll);
                }
            }

            for(int i = 16; i < 46;) {
                auto& coll = fEliteHouse.emplace_back(fRenderer);
                for(int j = 0; j < 5; j++, i++) {
                    loader.load(1, i, coll);
                }
            }

            for(int i = 46; i < 50; i++) {
                loader.load(1, i, fEliteHouseHorses);
            }
        }

        {
            const auto& sds = spriteData(fTileH,
                                         eCultureSpriteData15,
                                         eCultureSpriteData30,
                                         eCultureSpriteData45,
                                         eCultureSpriteData60);
            eSpriteLoader loader(fTileH, "culture", sds,
                                 nullptr, fRenderer);

            fCollege = loader.load(1, 1);

            for(int i = 2; i < 26; i++) {
                loader.load(1, i, fCollegeOverlay);
            }

            fGymnasium = loader.load(1, 26);

            for(int i = 27; i < 59; i++) {
                loader.load(1, i, fGymnasiumOverlay);
            }

            fDramaSchool = loader.load(1, 59);

            for(int i = 60; i < 84; i++) {
                loader.load(1, i, fDramaSchoolOverlay);
            }

            fPodium = loader.load(1, 84);

            for(int i = 85; i < 109; i++) {
                loader.load(1, i, fPodiumOverlay);
            }

            fTheater = loader.load(1, 109);

            fStadium2H = loader.load(1, 110);
            fStadium1H = loader.load(1, 111);
            fStadium1W = loader.load(1, 112);
            fStadium2W = loader.load(1, 113);
        }
    }

    {

        const auto& sds = spriteData(fTileH,
                                     eHealthNSanSpriteData15,
                                     eHealthNSanSpriteData30,
                                     eHealthNSanSpriteData45,
                                     eHealthNSanSpriteData60);
        eSpriteLoader loader(fTileH, "healthNSan", sds,
                             nullptr, fRenderer);

        fFountain = loader.load(1, 1);
        for(int i = 2; i < 8; i++) {
            loader.load(1, i, fFountainOverlay);
        }

        fHospital = loader.load(1, 8);
        for(int i = 9; i < 21; i++) {
            loader.load(1, i, fHospitalOverlay);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eHusbandrySpriteData15,
                                     eHusbandrySpriteData30,
                                     eHusbandrySpriteData45,
                                     eHusbandrySpriteData60);
        eSpriteLoader loader(fTileH, "husbandry", sds,
                             nullptr, fRenderer);

        for(int i = 1; i < 7; i++) {
            loader.load(1, i, fOliveTree);
        }

        for(int i = 7; i < 13; i++) {
            loader.load(1, i, fVine);
        }

        fPlantation = loader.load(1, 13);

        for(int i = 14; i < 20; i++) {
            loader.load(1, i, fWheat);
        }

        for(int i = 20; i < 26; i++) {
            loader.load(1, i, fCarrots);
        }

        for(int i = 26; i < 32; i++) {
            loader.load(1, i, fOnions);
        }

        fHuntingLodge = loader.load(1, 32);
        for(int i = 33; i < 48; i++) {
            loader.load(1, i, fHuntingLodgeOverlay);
        }

        for(int i = 48; i < 52; i++) {
            loader.load(1, i, fFishery);
        }

        for(int i = 52; i < 56; i++) {
            loader.load(1, i, fUrchinQuay);
        }

        fCardingShed = loader.load(1, 56);
        for(int i = 57; i < 69; i++) {
            loader.load(1, i, fCardingShedOverlay);
        }

        fDairy = loader.load(1, 69);
        for(int i = 70; i < 91; i++) {
            loader.load(1, i, fDairyOverlay);
        }

        fGrowersLodge = loader.load(1, 91);
        for(int i = 92; i < 102; i++) {
            loader.load(1, i, fGrowersLodgeOverlay);
        }
    }

    {

        const auto& sds = spriteData(fTileH,
                                     eIndustrySpriteData15,
                                     eIndustrySpriteData30,
                                     eIndustrySpriteData45,
                                     eIndustrySpriteData60);
        eSpriteLoader loader(fTileH, "industry", sds,
                             nullptr, fRenderer);

        fTimberMill = loader.load(1, 1);
        for(int i = 2; i < 12; i++) {
            loader.load(1, i, fTimberMillOverlay);
        }

        fMasonryShop = loader.load(1, 12);
        for(int i = 13; i < 21; i++) {
            loader.load(1, i, fMasonryShopStones);
        }

        fMint = loader.load(1, 21);
        for(int i = 22; i < 32; i++) {
            loader.load(1, i, fMintOverlay);
        }

        fFoundry = loader.load(1, 36);
        for(int i = 37; i < 49; i++) {
            loader.load(1, i, fFoundryOverlay);
        }

        fArtisansGuild = loader.load(1, 49);
        for(int i = 50; i < 60; i++) {
            loader.load(1, i, fArtisansGuildOverlay);
        }

        fOlivePress = loader.load(1, 60);
        for(int i = 61; i < 73; i++) {
            loader.load(1, i, fOlivePressOverlay);
        }

        fWinery = loader.load(1, 73);
        for(int i = 74; i < 86; i++) {
            loader.load(1, i, fWineryOverlay);
        }

        fSculptureStudio = loader.load(1, 86);
        for(int i = 87; i < 122; i++) {
            loader.load(1, i, fSculptureStudioOverlay);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eMilitarySpriteData15,
                                     eMilitarySpriteData30,
                                     eMilitarySpriteData45,
                                     eMilitarySpriteData60);
        eSpriteLoader loader(fTileH, "military", sds,
                             nullptr, fRenderer);

        for(int i = 1; i < 5; i++) {
            loader.load(1, i, fTriremeWharf);
        }

        fHorseRanch = loader.load(1, 5);
        for(int i = 6; i < 22; i++) {
            loader.load(1, i, fHorseRanchOverlay);
        }
        fHorseRanchEnclosure = loader.load(1, 41);

        fArmory = loader.load(1, 22);
        for(int i = 23; i < 41; i++) {
            loader.load(1, i, fArmoryOverlay);
        }

        loader.load(1, 50, fGatehouseW);
        loader.load(1, 52, fGatehouseW);
        loader.load(1, 54, fGatehouseW);
        loader.load(1, 57, fGatehouseW);

        loader.load(1, 51, fGatehouseH);
        loader.load(1, 53, fGatehouseH);
        loader.load(1, 55, fGatehouseH);
        loader.load(1, 58, fGatehouseH);

        fTower = loader.load(1, 56);

        for(int i = 59; i < 95; i++) {
            loader.load(1, i, fWall);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eMunicipalSpriteData15,
                                     eMunicipalSpriteData30,
                                     eMunicipalSpriteData45,
                                     eMunicipalSpriteData60);
        eSpriteLoader loader(fTileH, "municipal", sds,
                             nullptr, fRenderer);

        fMaintenanceOffice = loader.load(1, 1);
        for(int i = 2; i < 46; i++) {
            loader.load(1, i, fMaintenanceOfficeOverlay);
        }

        fTaxOffice = loader.load(1, 46);
        for(int i = 47; i < 65; i++) {
            loader.load(1, i, fTaxOfficeOverlay);
        }

        fWatchPost = loader.load(1, 65);

        fRoadblock = loader.load(1, 76);

        for(int i = 77; i < 89; i++) {
            loader.load(1, i, fBridge);
        }

        {
            const auto& sds = spriteData(fTileH,
                                         eMun_PalaceSpriteData15,
                                         eMun_PalaceSpriteData30,
                                         eMun_PalaceSpriteData45,
                                         eMun_PalaceSpriteData60);
            eSpriteLoader loader(fTileH, "mun_Palace", sds,
                                 nullptr, fRenderer);

            fPalace2H = loader.load(1, 1);
            fPalace1H = loader.load(1, 12);
            fPalace1W = loader.load(1, 13);
            fPalace2W = loader.load(1, 14);

            loader.load(1, 25, fPalaceTiles);
            loader.load(1, 26, fPalaceTiles);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eTradingPostOverlaySpriteData15,
                                     eTradingPostOverlaySpriteData30,
                                     eTradingPostOverlaySpriteData45,
                                     eTradingPostOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "tradingPostOverlay", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 43; i < 82; i++) {
            loader.load(43, i, fTradingPostOverlay);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eWarehouseOverlaySpriteData15,
                                     eWarehouseOverlaySpriteData30,
                                     eWarehouseOverlaySpriteData45,
                                     eWarehouseOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "warehouseOverlay", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 269; i < 293; i++) {
            loader.load(269, i, fWarehouseOverlay);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eFishSpriteData15,
                                     eFishSpriteData30,
                                     eFishSpriteData45,
                                     eFishSpriteData60);
        eSpriteLoader loader(fTileH, "fish", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 453; i < 493; i++) {
            loader.load(453, i, fFish);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eUrchinSpriteData15,
                                     eUrchinSpriteData30,
                                     eUrchinSpriteData45,
                                     eUrchinSpriteData60);
        eSpriteLoader loader(fTileH, "urchin", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 3035; i < 3051; i++) {
            loader.load(3035, i, fUrchin);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eTheaterOverlaySpriteData15,
                                     eTheaterOverlaySpriteData30,
                                     eTheaterOverlaySpriteData45,
                                     eTheaterOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "theaterOverlay", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 656; i < 680; i++) {
            loader.load(656, i, fTheaterOverlay);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eFisheryBoatBuildingSpriteData15,
                                     eFisheryBoatBuildingSpriteData30,
                                     eFisheryBoatBuildingSpriteData45,
                                     eFisheryBoatBuildingSpriteData60);
        eSpriteLoader loader(fTileH, "fisheryBoatBuilding", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 982; i < 992; i++) {
            loader.load(982, i, fFisheryBoatBuildingW);
        }
        for(int i = 992; i < 1002; i++) {
            loader.load(982, i, fFisheryBoatBuildingH);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eFisheryOverlaySpriteData15,
                                     eFisheryOverlaySpriteData30,
                                     eFisheryOverlaySpriteData45,
                                     eFisheryOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "fisheryOverlay", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int j = 0; j < 8; j++) {
            fFisheryOverlay.emplace_back(fRenderer);
        }

        for(int i = 2117; i < 2213;) {
            for(int j = 0; j < 8; j++, i++) {
                if(j > 3 && j < 7) continue;
                loader.load(2117, i, fFisheryOverlay[j]);
            }
        }
        for(int i = 2117; i < 2213;) {
            for(int j = 0; j < 8; j++, i++) {
                if(j > 3 && j < 7) continue;
                loader.load(2117, i, fFisheryOverlay[j]);
            }
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eUrchinUnpackingOverlaySpriteData15,
                                     eUrchinUnpackingOverlaySpriteData30,
                                     eUrchinUnpackingOverlaySpriteData45,
                                     eUrchinUnpackingOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "urchinUnpackingOverlay", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 680; i < 730; i++) {
            loader.load(680, i, fUrchinQuayUnpackingOverlayTL);
        }

        for(int i = 730; i < 780; i++) {
            loader.load(680, i, fUrchinQuayUnpackingOverlayTR);
        }

        for(int i = 780; i < 830; i++) {
            loader.load(680, i, fUrchinQuayUnpackingOverlayBL);
        }

        for(int i = 830; i < 880; i++) {
            loader.load(680, i, fUrchinQuayUnpackingOverlayBR);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eFisheryUnpackingOverlaySpriteData15,
                                     eFisheryUnpackingOverlaySpriteData30,
                                     eFisheryUnpackingOverlaySpriteData45,
                                     eFisheryUnpackingOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "fisheryUnpackingOverlay", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 890; i < 910; i++) {
            loader.load(890, i, fFisheryUnpackingOverlayTL);
        }

        for(int i = 910; i < 930; i++) {
            loader.load(890, i, fFisheryUnpackingOverlayTR);
        }

        for(int i = 930; i < 950; i++) {
            loader.load(890, i, fFisheryUnpackingOverlayBL);
        }

        for(int i = 950; i < 970; i++) {
            loader.load(890, i, fFisheryUnpackingOverlayBR);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eStadiumOverlaysSpriteData15,
                                     eStadiumOverlaysSpriteData30,
                                     eStadiumOverlaysSpriteData45,
                                     eStadiumOverlaysSpriteData60);
        eSpriteLoader loader(fTileH, "stadiumOverlays", sds,
                             &eSprAmbientOffset, fRenderer);


        for(int i = 1492; i < 1510; i++) {
            loader.load(1492, i, fStadiumOverlay1);
        }

        for(int i = 1510; i < 1530; i++) {
            loader.load(1492, i, fStadiumOverlay2);
        }

        for(int i = 1530; i < 1547; i++) {
            loader.load(1492, i, fStadiumOverlay3);
        }

        for(int i = 1547; i < 1629;) {
            for(int j = 0; j < 2; j++, i++) {
                eTextureCollection* coll;
                if(j == 0) {
                    coll = &fStadiumOverlay4W;
                } else {
                    coll = &fStadiumOverlay4H;
                }
                loader.load(1492, i, *coll);
            }
        }

        for(int i = 1629; i < 1653; i++) {
            loader.load(1492, i, fStadiumAudiance1W);
        }

        for(int i = 1653; i < 1677; i++) {
            loader.load(1492, i, fStadiumAudiance2W);
        }

        for(int i = 1677; i < 1701; i++) {
            loader.load(1492, i, fStadiumAudiance1H);
        }

        for(int i = 1701; i < 1725; i++) {
            loader.load(1492, i, fStadiumAudiance2H);
        }

        for(int i = 1725; i < 1773; i++) {
            loader.load(1492, i, fSanctuaryHOverlay);
        }

        for(int i = 1773; i < 1937;) {
            for(int j = 0; j < 2; j++, i++) {
                eTextureCollection* coll;
                if(j == 0) {
                    coll = &fStadiumOverlay5W;
                } else {
                    coll = &fStadiumOverlay5H;
                }
                loader.load(1492, i, *coll);
            }
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eSanctuaryFireSpriteData15,
                                     eSanctuaryFireSpriteData30,
                                     eSanctuaryFireSpriteData45,
                                     eSanctuaryFireSpriteData60);
        eSpriteLoader loader(fTileH, "sanctuaryFire", sds,
                             &eSprAmbientOffset, fRenderer);


        for(int i = 2105; i < 2117; i++) {
            loader.load(2105, i, fSanctuaryFire);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eMasonryShopOverlaysSpriteData15,
                                     eMasonryShopOverlaysSpriteData30,
                                     eMasonryShopOverlaysSpriteData45,
                                     eMasonryShopOverlaysSpriteData60);
        eSpriteLoader loader(fTileH, "masonryShopOverlays", sds,
                             &eSprAmbientOffset, fRenderer);

        loader.loadSkipFlipped(1937, 1937, 2017, fMasonryShopOverlay1);
        loader.loadSkipFlipped(1937, 2017, 2097, fMasonryShopOverlay2);
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eWaitingOverlaySpriteData15,
                                     eWaitingOverlaySpriteData30,
                                     eWaitingOverlaySpriteData45,
                                     eWaitingOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "waitingOverlay", sds,
                             &eSprAmbientOffset, fRenderer);

        loader.loadSkipFlipped(2277, 2277, 2437, fWaitingOverlay0);
        loader.loadSkipFlipped(2277, 2437, 2533, fWaitingOverlay1);
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eVendorOverlaysSpriteData15,
                                     eVendorOverlaysSpriteData30,
                                     eVendorOverlaysSpriteData45,
                                     eVendorOverlaysSpriteData60);
        eSpriteLoader loader(fTileH, "vendorOverlays", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 2639; i < 2651; i++) {
            loader.load(2639, i, fFleeceVendorOverlay2);
        }

        for(int i = 2651; i < 2663; i++) {
            loader.load(2639, i, fFoodVendorOverlay2);
        }

        for(int i = 2663; i < 2679; i++) {
            loader.load(2639, i, fHorseTrainerOverlay2);
        }

        for(int i = 2679; i < 2719; i++) {
            loader.load(2639, i, fOilVendorOverlay2);
        }

        for(int i = 2719; i < 2759; i++) {
            loader.load(2639, i, fArmsVendorOverlay2);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eWineVendorOverlaySpriteData15,
                                     eWineVendorOverlaySpriteData30,
                                     eWineVendorOverlaySpriteData45,
                                     eWineVendorOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "wineVendorOverlay", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 429; i < 453; i++) {
            loader.load(429, i, fWineVendorOverlay2);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eFishPondOverlaySpriteData15,
                                     eFishPondOverlaySpriteData30,
                                     eFishPondOverlaySpriteData45,
                                     eFishPondOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "fishPondOverlay", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 2759; i < 2790; i++) {
            loader.load(2759, i, fFishPondOverlay);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eWatchPostOverlaySpriteData15,
                                     eWatchPostOverlaySpriteData30,
                                     eWatchPostOverlaySpriteData45,
                                     eWatchPostOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "watchPostOverlay", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 2958; i < 3011; i++) {
            loader.load(2958, i, fWatchPostOverlay);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     ePalaceOverlaySpriteData15,
                                     ePalaceOverlaySpriteData30,
                                     ePalaceOverlaySpriteData45,
                                     ePalaceOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "palaceOverlay", sds,
                             &eSprAmbientOffset, fRenderer);

        for(int i = 3011; i < 3035; i++) {
            loader.load(3011, i, fPalaceHOverlay);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eStor_baysSpriteData15,
                                     eStor_baysSpriteData30,
                                     eStor_baysSpriteData45,
                                     eStor_baysSpriteData60);
        eSpriteLoader loader(fTileH, "stor_bays", sds,
                             nullptr, fRenderer);

        for(int i = 1; i < 5; i++) {
            loader.load(1, i, fWarehouseUrchin);
        }
        for(int i = 5; i < 9; i++) {
            loader.load(1, i, fWarehouseFish);
        }
        for(int i = 9; i < 13; i++) {
            loader.load(1, i, fWarehouseMeat);
        }
        for(int i = 13; i < 17; i++) {
            loader.load(1, i, fWarehouseCheese);
        }
        for(int i = 17; i < 21; i++) {
            loader.load(1, i, fWarehouseCarrots);
        }
        for(int i = 21; i < 25; i++) {
            loader.load(1, i, fWarehouseOnions);
        }
        for(int i = 25; i < 29; i++) {
            loader.load(1, i, fWarehouseWheat);
        }
        for(int i = 29; i < 33; i++) {
            loader.load(1, i, fWarehouseWood);
        }
        for(int i = 33; i < 37; i++) {
            loader.load(1, i, fWarehouseBronze);
        }
        for(int i = 37; i < 41; i++) {
            loader.load(1, i, fWarehouseMarble);
        }
        for(int i = 41; i < 45; i++) {
            loader.load(1, i, fWarehouseGrapes);
        }
        for(int i = 45; i < 49; i++) {
            loader.load(1, i, fWarehouseOlives);
        }
        for(int i = 49; i < 53; i++) {
            loader.load(1, i, fWarehouseFleece);
        }
        for(int i = 53; i < 57; i++) {
            loader.load(1, i, fWarehouseArmor);
        }
        fWarehouseSculpture = loader.load(1, 57);
        for(int i = 58; i < 62; i++) {
            loader.load(1, i, fWarehouseOliveOil);
        }
        for(int i = 62; i < 66; i++) {
            loader.load(1, i, fWarehouseWine);
        }


        for(int i = 71; i < 76; i++) {
            loader.load(1, i, fWaitingMeat);
        }
        for(int i = 76; i < 81; i++) {
            loader.load(1, i, fWaitingCheese);
        }
        for(int i = 81; i < 89; i++) {
            loader.load(1, i, fWaitingWheat);
        }
        for(int i = 89; i < 94; i++) {
            loader.load(1, i, fWaitingWood);
        }
        for(int i = 94; i < 99; i++) {
            loader.load(1, i, fWaitingBronze);
        }
        for(int i = 99; i < 102; i++) {
            loader.load(1, i, fWaitingGrapes);
        }
        for(int i = 102; i < 105; i++) {
            loader.load(1, i, fWaitingOlives);
        }
        for(int i = 105; i < 110; i++) {
            loader.load(1, i, fWaitingArmor);
        }

        fWarehouseEmpty = loader.load(1, 115);
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eStorNDistSpriteData15,
                                     eStorNDistSpriteData30,
                                     eStorNDistSpriteData45,
                                     eStorNDistSpriteData60);
        eSpriteLoader loader(fTileH, "storNDist", sds,
                             nullptr, fRenderer);

        fFoodVendor = loader.load(1, 1);
        fFoodVendorOverlay = loader.load(1, 2);
        fFleeceVendor = loader.load(1, 3);
        fFleeceVendorOverlay = loader.load(1, 4);
        fOilVendor = loader.load(1, 5);
        fOilVendorOverlay = loader.load(1, 6);
        fWineVendor = loader.load(1, 7);
        fWineVendorOverlay = loader.load(1, 8);
        fArmsVendor = loader.load(1, 9);
        fArmsVendorOverlay = loader.load(1, 10);
        fHorseTrainer = loader.load(1, 11);
        fHorseTrainerOverlay = loader.load(1, 12);

        for(int i = 13; i < 16; i++) {
            loader.load(1, i, fAgoraRoad);
        }
        for(int i = 16; i < 19; i++) {
            loader.load(1, i, fAgora);
        }

        fWarehouse = loader.load(1, 23);
        fWarehouse->setOffset(-58, 60);

        for(int i = 19; i < 23; i++) {
            loader.load(1, i, fPier1);
        }

        fPier2 = loader.load(1, 25);
        fPier2->setOffset(-88, 90);

        fTradingPost = loader.load(1, 27);
        fTradingPost->setOffset(-88, 90);

        fGranary = loader.load(1, 29);
        for(int i = 30; i < 46; i++) {
            loader.load(1, i, fGranaryOverlay);
        }

        fGranaryUrchin = loader.load(1, 46);
        fGranaryFish = loader.load(1, 47);
        fGranaryMeat = loader.load(1, 48);
        fGranaryCheese = loader.load(1, 49);
        fGranaryCheese->setOffset(-3, 2);
        fGranaryCarrots = loader.load(1, 50);
        fGranaryOnions = loader.load(1, 51);
        fGranaryOnions->setOffset(-4, 0);
        fGranaryWheat = loader.load(1, 52);
    }


    {
        const auto& sds = spriteData(fTileH,
                                     eBeautification2SpriteData15,
                                     eBeautification2SpriteData30,
                                     eBeautification2SpriteData45,
                                     eBeautification2SpriteData60);
        eSpriteLoader loader(fTileH, "beautification2", sds,
                             nullptr, fRenderer);

        for(int i = 12; i < 16; i++) {
            loader.load(1, i, fPark);
        }
        for(int i = 16; i < 19; i++) {
            loader.load(1, i, fLargePark);
        }
        loader.load(1, 19, fHugePark);

        fBench = loader.load(1, 20);
        fFlowerGarden = loader.load(1, 21);
        fGazebo = loader.load(1, 22);
        fHedgeMaze = loader.load(1, 23);
        fFishPond = loader.load(1, 24);

        for(int i = 25; i < 34; i++) {
            loader.load(1, i, fCommemorative);
        }

        fDoricColumn = loader.load(1, 34);
        fIonicColumn = loader.load(1, 35);
        fCorinthianColumn = loader.load(1, 36);

        fColumnConnectionH = loader.load(1, 37);
        fColumnConnectionW = loader.load(1, 38);

        for(int i = 39; i < 88; i++) {
            loader.load(1, i, fAvenueRoad);
        }

        fAvenue.emplace_back(fRenderer);
        for(int i = 88; i < 97; i++) {
            loader.load(1, i, fAvenue[0]);
        }

        fAvenue.emplace_back(fRenderer);
        for(int i = 97; i < 106; i++) {
            loader.load(1, i, fAvenue[1]);
        }

        fAvenue.emplace_back(fRenderer);
        for(int i = 106; i < 115; i++) {
            loader.load(1, i, fAvenue[2]);
        }

        fAvenue.emplace_back(fRenderer);
        for(int i = 115; i < 124; i++) {
            loader.load(1, i, fAvenue[3]);
        }

        fAvenue.emplace_back(fRenderer);
        for(int i = 124; i < 132; i++) {
            loader.load(1, i, fAvenue[4]);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eReligionSpriteData15,
                                     eReligionSpriteData30,
                                     eReligionSpriteData45,
                                     eReligionSpriteData60);
        eSpriteLoader loader(fTileH, "religion", sds,
                             nullptr, fRenderer);

        int i = 1;
        const auto loadStatues = [&](eTextureCollection& coll) {
            for(int j = 0; j < 4; j++, i++) {
                loader.load(1, i, coll);
            }
        };
        loadStatues(fZeusStatues);
        {
            // loadStatues(fPoseidonStatues);
            i += 4;
        }
        loadStatues(fHadesStatues);
        loadStatues(fDemeterStatues);
        loadStatues(fAthenaStatues);
        loadStatues(fArtemisStatues);
        loadStatues(fApolloStatues);
        loadStatues(fAresStatues);
        loadStatues(fHephaestusStatues);
        loadStatues(fAphroditeStatues);
        loadStatues(fHermesStatues);
        loadStatues(fDionysusStatues);

        for(int i = 49; i < 55; i++) {
            loader.load(1, i, fSanctuaryTiles);
        }
        for(int i = 55; i < 61; i++) {
            loader.load(1, i, fSanctuarySpace);
        }

        fSanctuaryAltar = loader.load(1, 61);
        fHeroHall = loader.load(1, 62);
        for(int i = 63; i < 69; i++) {
            loader.load(1, i, fHeroStatues);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eAestheticSpriteData15,
                                     eAestheticSpriteData30,
                                     eAestheticSpriteData45,
                                     eAestheticSpriteData60);
        eSpriteLoader loader(fTileH, "aesthetic", sds,
                             nullptr, fRenderer);

        fTallObelisk = loader.load(1, 17);
        fSundial = loader.load(1, 18);
        fTopiary = loader.load(1, 19);

        for(int i = 20; i < 27; i++) {
            loader.load(1, i, fSpring);
        }
        fStoneCircle = loader.load(1, 27);
        for(int i = 28; i < 33; i++) {
            loader.load(1, i, fStoneCircleOverlay);
        }
        fDolphinSculpture = loader.load(1, 33);
        fOrrery = loader.load(1, 34);
        fShellGarden = loader.load(1, 35);

        fBaths = loader.load(1, 36);
        for(int i = 37; i < 53; i++) {
            loader.load(1, i, fBathsOverlay);
        }

        fBirdBath = loader.load(1, 53);
        for(int i = 54; i < 63; i++) {
            loader.load(1, i, fBirdBathOverlay);
        }

        fShortObelisk = loader.load(1, 63);
        const auto loadWaterPark = [&](const int i,
                                       std::shared_ptr<eTexture>& tex,
                                       eTextureCollection& overlay) {
            tex = loader.load(1, i);
            const int jMax = i + 8;
            for(int j = i + 1; j < jMax; j++) {
                loader.load(1, j, overlay);
            }
        };
        loadWaterPark(64, fWaterPark1, fWaterPark1Overlay);
        loadWaterPark(72, fWaterPark2, fWaterPark2Overlay);
        loadWaterPark(80, fWaterPark3, fWaterPark3Overlay);
        loadWaterPark(88, fWaterPark4, fWaterPark4Overlay);
        loadWaterPark(96, fWaterPark5, fWaterPark5Overlay);
        loadWaterPark(104, fWaterPark6, fWaterPark6Overlay);
        loadWaterPark(112, fWaterPark7, fWaterPark7Overlay);
        loadWaterPark(120, fWaterPark8, fWaterPark8Overlay);
    }

    {
        const auto& sds = spriteData(fTileH,
                                     ePoseidonStatuesSpriteData15,
                                     ePoseidonStatuesSpriteData30,
                                     ePoseidonStatuesSpriteData45,
                                     ePoseidonStatuesSpriteData60);
        eSpriteLoader loader(fTileH, "poseidonStatues", sds,
                             nullptr, fRenderer);

        int i = 1;
        const auto loadStatues = [&](eTextureCollection& coll) {
            for(int j = 0; j < 4; j++, i++) {
                loader.load(1, i, coll);
            }
        };

        loadStatues(fHeraStatues);
        loadStatues(fAtlasStatues);
        for(int j = 0; j < 2; j++, i++) {
            loader.load(1, i, fHeroStatues);
        }
        loadStatues(fPoseidonStatues);
    }

    const auto loadGodMonuments = [&](const std::vector<eSpriteData>& sd15,
                                      const std::vector<eSpriteData>& sd30,
                                      const std::vector<eSpriteData>& sd45,
                                      const std::vector<eSpriteData>& sd60,
                                      const std::string& name,
                                      eTextureCollection& coll) {
        const auto& sds = spriteData(fTileH, sd15, sd30, sd45, sd60);
        eSpriteLoader loader(fTileH, name, sds,
                             nullptr, fRenderer);
        for(int i = 1; i < 5; i++) {
            loader.load(1, i, coll);
        }
    };

    loadGodMonuments(eZeusStatueSpriteData15,
                     eZeusStatueSpriteData30,
                     eZeusStatueSpriteData45,
                     eZeusStatueSpriteData60,
                     "zeusStatue",
                     fZeusMonuments);
    loadGodMonuments(ePoseidonStatueSpriteData15,
                     ePoseidonStatueSpriteData30,
                     ePoseidonStatueSpriteData45,
                     ePoseidonStatueSpriteData60,
                     "poseidonStatue",
                     fPoseidonMonuments);
    loadGodMonuments(eHadesStatueSpriteData15,
                     eHadesStatueSpriteData30,
                     eHadesStatueSpriteData45,
                     eHadesStatueSpriteData60,
                     "hadesStatue",
                     fHadesMonuments);
    loadGodMonuments(eDemeterStatueSpriteData15,
                     eDemeterStatueSpriteData30,
                     eDemeterStatueSpriteData45,
                     eDemeterStatueSpriteData60,
                     "demeterStatue",
                     fDemeterMonuments);
    loadGodMonuments(eAthenaStatueSpriteData15,
                     eAthenaStatueSpriteData30,
                     eAthenaStatueSpriteData45,
                     eAthenaStatueSpriteData60,
                     "athenaStatue",
                     fAthenaMonuments);
    loadGodMonuments(eArtemisStatueSpriteData15,
                     eArtemisStatueSpriteData30,
                     eArtemisStatueSpriteData45,
                     eArtemisStatueSpriteData60,
                     "artemisStatue",
                     fArtemisMonuments);
    loadGodMonuments(eApolloStatueSpriteData15,
                     eApolloStatueSpriteData30,
                     eApolloStatueSpriteData45,
                     eApolloStatueSpriteData60,
                     "apolloStatue",
                     fApolloMonuments);
    loadGodMonuments(eAresStatueSpriteData15,
                     eAresStatueSpriteData30,
                     eAresStatueSpriteData45,
                     eAresStatueSpriteData60,
                     "aresStatue",
                     fAresMonuments);
    loadGodMonuments(eHephaestusStatueSpriteData15,
                     eHephaestusStatueSpriteData30,
                     eHephaestusStatueSpriteData45,
                     eHephaestusStatueSpriteData60,
                     "hephaestusStatue",
                     fHephaestusMonuments);
    loadGodMonuments(eAphroditeStatueSpriteData15,
                     eAphroditeStatueSpriteData30,
                     eAphroditeStatueSpriteData45,
                     eAphroditeStatueSpriteData60,
                     "aphroditeStatue",
                     fAphroditeMonuments);
    loadGodMonuments(eHermesStatueSpriteData15,
                     eHermesStatueSpriteData30,
                     eHermesStatueSpriteData45,
                     eHermesStatueSpriteData60,
                     "hermesStatue",
                     fHermesMonuments);
    loadGodMonuments(eDionysusStatueSpriteData15,
                     eDionysusStatueSpriteData30,
                     eDionysusStatueSpriteData45,
                     eDionysusStatueSpriteData60,
                     "dionysusStatue",
                     fDionysusMonuments);

    {
        const auto& sds = spriteData(fTileH,
                                     eBlankStatueSpriteData15,
                                     eBlankStatueSpriteData30,
                                     eBlankStatueSpriteData45,
                                     eBlankStatueSpriteData60);
        eSpriteLoader loader(fTileH, "blankStatue", sds,
                             nullptr, fRenderer);

        fBlankMonument = loader.load(1, 1);
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eZeusSanctuary1SpriteData15,
                                     eZeusSanctuary1SpriteData30,
                                     eZeusSanctuary1SpriteData45,
                                     eZeusSanctuary1SpriteData60);
        eSpriteLoader loader(fTileH, "zeusSanctuary1", sds,
                             nullptr, fRenderer);

        for(int i = 1; i < 5; i++) {
            auto& coll = fSanctuary.emplace_back(fRenderer);
            loader.load(1, i, coll);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eZeusSanctuary2SpriteData15,
                                     eZeusSanctuary2SpriteData30,
                                     eZeusSanctuary2SpriteData45,
                                     eZeusSanctuary2SpriteData60);
        eSpriteLoader loader(fTileH, "zeusSanctuary2", sds,
                             nullptr, fRenderer);

        for(int i = 1; i < 5; i++) {
            auto& coll = fSanctuary[i - 1];
            loader.load(1, i, coll);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eZeusSanctuary3SpriteData15,
                                     eZeusSanctuary3SpriteData30,
                                     eZeusSanctuary3SpriteData45,
                                     eZeusSanctuary3SpriteData60);
        eSpriteLoader loader(fTileH, "zeusSanctuary3", sds,
                             nullptr, fRenderer);

        for(int i = 1; i < 5; i++) {
            auto& coll = fSanctuary[i - 1];
            loader.load(1, i, coll);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eAtlasStatueSpriteData15,
                                     eAtlasStatueSpriteData30,
                                     eAtlasStatueSpriteData45,
                                     eAtlasStatueSpriteData60);
        eSpriteLoader loader(fTileH, "atlasStatue", sds,
                             nullptr, fRenderer);

        for(int i = 1; i < 5; i++) {
            loader.load(1, i, fAtlasMonuments);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eHeraStatueSpriteData15,
                                     eHeraStatueSpriteData30,
                                     eHeraStatueSpriteData45,
                                     eHeraStatueSpriteData60);
        eSpriteLoader loader(fTileH, "heraStatue", sds,
                             nullptr, fRenderer);

        for(int i = 1; i < 5; i++) {
            loader.load(1, i, fHeraMonuments);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eStorageSpriteData15,
                                     eStorageSpriteData30,
                                     eStorageSpriteData45,
                                     eStorageSpriteData60);
        eSpriteLoader loader(fTileH, "storage", sds,
                             nullptr, fRenderer);


//        fCorral = std::make_shared<eTexture>();
//        fCorral->load(fRenderer, pathBase + "00001.png");

//        for(int i = 2; i < 49; i++) {
//            eTextureLoadingHelpers::loadTex(pathBase, i, fCorralOverlay);
//        }

        fOrangeTendersLodge = loader.load(51, 51);

        for(int i = 52; i < 87; i++) {
            loader.load(51, i, fOrangeTendersLodgeOverlay);
        }

        for(int i = 87; i < 91; i++) {
            loader.load(51, i, fWarehouseOranges);
        }

        for(int i = 99; i < 104; i++) {
            loader.load(51, i, fWaitingOranges);
        }

        fGranaryOranges = loader.load(51, 122);
        fGranaryOranges->setOffset(-3, -3);

        for(int i = 123; i < 129; i++) {
            loader.load(51, i, fOrangeTree);
        }
    }

    const auto generateFlipped = [](const eTextureCollection& src,
                                    eTextureCollection& dst) {
        for(int i = 0; i < src.size(); i++) {
            auto& tex = dst.addTexture();
            const auto& srcTex = src.getTexture(i);
            const int w = srcTex->width();
            const int ox = srcTex->offsetX();
            const int oy = srcTex->offsetY();
            tex->setOffset(w - ox, oy);
            tex->setFlipTex(srcTex);
        }
    };
    generateFlipped(fPalaceHOverlay, fPalaceWOverlay);
    generateFlipped(fSanctuaryHOverlay, fSanctuaryWOverlay);

    generateFlipped(fFisheryOverlay[0], fFisheryOverlay[6]);
    generateFlipped(fFisheryOverlay[1], fFisheryOverlay[5]);
    generateFlipped(fFisheryOverlay[2], fFisheryOverlay[4]);
}
