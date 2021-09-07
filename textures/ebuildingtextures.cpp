#include "ebuildingtextures.h"

#include "etextureloadinghelpers.h"
#include "offsets/SprAmbient.h"

eBuildingTextures::eBuildingTextures(const int tileW, const int tileH,
                                     SDL_Renderer* const renderer) :
    fTileW(tileW), fTileH(tileH),
    fRenderer(renderer),

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
    fUrchinQuay(renderer),
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

    fMaintenanceOfficeOverlay(renderer),
    fTaxOfficeOverlay(renderer),
    fWatchPostOverlay(renderer),

    fBeachRoad(renderer),
    fRoad(renderer),

    fPatrolGuides(renderer),

    fWaitingMeat(renderer),
    fWaitingCheese(renderer),
    fWaitingWheat(renderer),
    fWaitingOranges(renderer),
    fWaitingWood(renderer),
    fWaitingBronze(renderer),
    fWaitingGrapes(renderer),
    fWaitingOlives(renderer),
    fWaitingArmor(renderer),

//    fAgoraRoad(renderer),
//    fAgora(renderer),

    fWarehouseOverlay(renderer),

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

    fBirdBathOverlay(renderer),
    fSpring(renderer),
    fBathsOverlay(renderer),
    fStoneCircleOverlay(renderer),

    fClouds(renderer) {

}

void eBuildingTextures::load() {
    std::string basedir{"../ZeusTextures/"};
    basedir += std::to_string(fTileH) + "/";
    {
        const auto dir = basedir + "Zeus_General/";

        {
            const std::string pathBase{dir + "Zeus_Housing_"};

            fHouseSpace = std::make_shared<eTexture>();
            fHouseSpace->load(fRenderer, pathBase + "00015.png");
            for(int i = 1; i < 15;) {
                auto& coll = fCommonHouse.emplace_back(fRenderer);
                for(int j = 0; j < 2; j++, i++) {
                    eTextureLoadingHelpers::loadTex(pathBase, i, coll);
                }
            }
        }

        {
            const std::string pathBase{dir + "Zeus_Culture_"};

            fCollege = std::make_shared<eTexture>();
            fCollege->load(fRenderer, pathBase + "00001.png");

            for(int i = 2; i < 26; i++) {
                eTextureLoadingHelpers::loadTex(pathBase, i, fCollegeOverlay);
            }

            fGymnasium = std::make_shared<eTexture>();
            fGymnasium->load(fRenderer, pathBase + "00026.png");

            for(int i = 27; i < 59; i++) {
                eTextureLoadingHelpers::loadTex(pathBase, i, fGymnasiumOverlay);
            }

            fDramaSchool = std::make_shared<eTexture>();
            fDramaSchool->load(fRenderer, pathBase + "00059.png");

            for(int i = 60; i < 84; i++) {
                eTextureLoadingHelpers::loadTex(pathBase, i, fDramaSchoolOverlay);
            }

            fPodium = std::make_shared<eTexture>();
            fPodium->load(fRenderer, pathBase + "00084.png");

            for(int i = 85; i < 109; i++) {
                eTextureLoadingHelpers::loadTex(pathBase, i, fPodiumOverlay);
            }

            fTheater = std::make_shared<eTexture>();
            fTheater->load(fRenderer, pathBase + "00109.png");

            fStadium2H = std::make_shared<eTexture>();
            fStadium2H->load(fRenderer, pathBase + "00110.png");
            fStadium2H->setOffset(5, 0);
            fStadium1H = std::make_shared<eTexture>();
            fStadium1H->load(fRenderer, pathBase + "00111.png");
            fStadium1W = std::make_shared<eTexture>();
            fStadium1W->load(fRenderer, pathBase + "00112.png");
            fStadium2W = std::make_shared<eTexture>();
            fStadium2W->load(fRenderer, pathBase + "00113.png");
            fStadium2W->setOffset(-5, 0);

        }
    }

    {
        const auto dir = basedir + "Zeus_General/";

        const std::string pathBase{dir + "Zeus_HealthNSan_"};

        fFountain = std::make_shared<eTexture>();
        fFountain->load(fRenderer, pathBase + "00001.png");
        for(int i = 2; i < 8; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fFountainOverlay);
        }

        fHospital = std::make_shared<eTexture>();
        fHospital->load(fRenderer, pathBase + "00008.png");
        for(int i = 9; i < 21; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fHospitalOverlay);
        }
    }

    {
        const auto dir = basedir + "Zeus_General/";

        const std::string pathBase{dir + "Zeus_Husbandry_"};

        for(int i = 1; i < 7; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fOliveTree);
        }

        for(int i = 7; i < 13; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fVine);
        }

        fPlantation = std::make_shared<eTexture>();
        fPlantation->load(fRenderer, pathBase + "00013.png");

        for(int i = 14; i < 20; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWheat);
        }

        for(int i = 20; i < 26; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fCarrots);
        }

        for(int i = 26; i < 32; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fOnions);
        }

        fHuntingLodge = std::make_shared<eTexture>();
        fHuntingLodge->load(fRenderer, pathBase + "00032.png");
        for(int i = 33; i < 48; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fHuntingLodgeOverlay);
        }

        for(int i = 48; i < 52; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fFishery);
        }

        for(int i = 52; i < 56; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fUrchinQuay);
        }

        fCardingShed = std::make_shared<eTexture>();
        fCardingShed->load(fRenderer, pathBase + "00056.png");
        for(int i = 57; i < 69; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fCardingShedOverlay);
        }

        fDairy = std::make_shared<eTexture>();
        fDairy->load(fRenderer, pathBase + "00069.png");
        for(int i = 70; i < 91; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fDairyOverlay);
        }

        fGrowersLodge = std::make_shared<eTexture>();
        fGrowersLodge->load(fRenderer, pathBase + "00091.png");
        for(int i = 92; i < 102; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fGrowersLodgeOverlay);
        }
    }

    {
        const auto dir = basedir + "Zeus_General/";

        const std::string pathBase{dir + "Zeus_Industry_"};

        fTimberMill = std::make_shared<eTexture>();
        fTimberMill->load(fRenderer, pathBase + "00001.png");
        for(int i = 2; i < 12; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fTimberMillOverlay);
        }

        fMasonryShop = std::make_shared<eTexture>();
        fMasonryShop->load(fRenderer, pathBase + "00012.png");
        for(int i = 13; i < 21; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fMasonryShopStones);
        }

        fMint = std::make_shared<eTexture>();
        fMint->load(fRenderer, pathBase + "00021.png");
        for(int i = 22; i < 32; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fMintOverlay);
        }

        fFoundry = std::make_shared<eTexture>();
        fFoundry->load(fRenderer, pathBase + "00036.png");
        for(int i = 37; i < 49; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fFoundryOverlay);
        }

        fArtisansGuild = std::make_shared<eTexture>();
        fArtisansGuild->load(fRenderer, pathBase + "00049.png");
        for(int i = 50; i < 60; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fArtisansGuildOverlay);
        }

        fOlivePress = std::make_shared<eTexture>();
        fOlivePress->load(fRenderer, pathBase + "00060.png");
        for(int i = 61; i < 73; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fOlivePressOverlay);
        }

        fWinery = std::make_shared<eTexture>();
        fWinery->load(fRenderer, pathBase + "00073.png");
        for(int i = 74; i < 86; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWineryOverlay);
        }

        fSculptureStudio = std::make_shared<eTexture>();
        fSculptureStudio->load(fRenderer, pathBase + "00086.png");
        for(int i = 87; i < 122; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fSculptureStudioOverlay);
        }
    }

    {
        const auto dir = basedir + "Zeus_General/";

        const std::string pathBase{dir + "Zeus_Military_"};

        for(int i = 1; i < 5; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fTriremeWharf);
        }

        fHorseRanch = std::make_shared<eTexture>();
        fHorseRanch->load(fRenderer, pathBase + "00005.png");
        for(int i = 6; i < 22; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fHorseRanchOverlay);
        }
        fHorseRanchEnclosure = std::make_shared<eTexture>();
        fHorseRanchEnclosure->load(fRenderer, pathBase + "00041.png");

        fArmory = std::make_shared<eTexture>();
        fArmory->load(fRenderer, pathBase + "00022.png");
        for(int i = 23; i < 41; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fArmoryOverlay);
        }
    }

    {
        const auto dir = basedir + "Zeus_General/";

        const std::string pathBase{dir + "Zeus_Municipal_"};

        fMaintenanceOffice = std::make_shared<eTexture>();
        fMaintenanceOffice->load(fRenderer, pathBase + "00001.png");
        for(int i = 2; i < 46; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fMaintenanceOfficeOverlay);
        }

        fTaxOffice = std::make_shared<eTexture>();
        fTaxOffice->load(fRenderer, pathBase + "00046.png");
        for(int i = 47; i < 65; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fTaxOfficeOverlay);
        }

        fWatchPost = std::make_shared<eTexture>();
        fWatchPost->load(fRenderer, pathBase + "00065.png");

        {
            const std::string pathBase{dir + "Zeus_Mun-Palace_"};

            fPalace2H = std::make_shared<eTexture>();
            fPalace2H->load(fRenderer, pathBase + "00001.png");
            fPalace2H->setOffset(4, 0);
            fPalace1H = std::make_shared<eTexture>();
            fPalace1H->load(fRenderer, pathBase + "00012.png");
            fPalace1W = std::make_shared<eTexture>();
            fPalace1W->load(fRenderer, pathBase + "00013.png");
            fPalace2W = std::make_shared<eTexture>();
            fPalace2W->load(fRenderer, pathBase + "00014.png");
            fPalace2W->setOffset(-4, 0);

            eTextureLoadingHelpers::loadTex(pathBase, 25, fPalaceTiles);
            eTextureLoadingHelpers::loadTex(pathBase, 26, fPalaceTiles);
        }
    }

    {
        const auto dir = basedir + "SprAmbient/";

        const std::string pathBase{dir + "SprAmbient_"};

        for(int i = 269; i < 293; i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fWarehouseOverlay, eSprAmbientOffset);
        }

        for(int i = 656; i < 680; i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fTheaterOverlay, eSprAmbientOffset);
        }

        for(int i = 1492; i < 1510; i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fStadiumOverlay1, eSprAmbientOffset);
        }

        for(int i = 1510; i < 1530; i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fStadiumOverlay2, eSprAmbientOffset);
        }

        for(int i = 1530; i < 1547; i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fStadiumOverlay3, eSprAmbientOffset);
        }

        for(int i = 1547; i < 1629;) {
            for(int j = 0; j < 2; j++, i++) {
                eTextureCollection* coll;
                if(j == 0) {
                    coll = &fStadiumOverlay4W;
                } else {
                    coll = &fStadiumOverlay4H;
                }
                eTextureLoadingHelpers::loadTexWithOffset(
                            pathBase, i, *coll, eSprAmbientOffset);
            }
        }

        for(int i = 1629; i < 1653; i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fStadiumAudiance1W, eSprAmbientOffset);
        }

        for(int i = 1653; i < 1677; i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fStadiumAudiance2W, eSprAmbientOffset);
        }

        for(int i = 1677; i < 1701; i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fStadiumAudiance1H, eSprAmbientOffset);
        }

        for(int i = 1701; i < 1725; i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fStadiumAudiance2H, eSprAmbientOffset);
        }

        for(int i = 1773; i < 1937;) {
            for(int j = 0; j < 2; j++, i++) {
                eTextureCollection* coll;
                if(j == 0) {
                    coll = &fStadiumOverlay5W;
                } else {
                    coll = &fStadiumOverlay5H;
                }
                eTextureLoadingHelpers::loadTexWithOffset(
                            pathBase, i, *coll, eSprAmbientOffset);
            }
        }

        for(int i = 2958; i < 3011; i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fWatchPostOverlay, eSprAmbientOffset);
        }

        for(int i = 2759; i < 2790; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fFishPondOverlay);
        }
    }

    {
        const auto dir = basedir + "Zeus_Terrain/";

        const std::string pathBase{dir + "Zeus_Land3_"};

        for(int i = 81; i < 99; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fBeachRoad);
        }

        for(int i = 231; i < 302; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fRoad);
        }
    }

    {
        const auto dir = basedir + "Zeus_General/";
        const std::string pathBase{dir + "Zeus_Stor-bays_"};


        for(int i = 1; i < 5; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWarehouseUrchin);
        }
        for(int i = 5; i < 9; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWarehouseFish);
        }
        for(int i = 9; i < 13; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWarehouseMeat);
        }
        for(int i = 13; i < 17; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWarehouseCheese);
        }
        for(int i = 17; i < 21; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWarehouseCarrots);
        }
        for(int i = 21; i < 25; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWarehouseOnions);
        }
        for(int i = 25; i < 29; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWarehouseWheat);
        }
        for(int i = 29; i < 33; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWarehouseWood);
        }
        for(int i = 33; i < 37; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWarehouseBronze);
        }
        for(int i = 37; i < 41; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWarehouseMarble);
        }
        for(int i = 41; i < 45; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWarehouseGrapes);
        }
        for(int i = 45; i < 49; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWarehouseOlives);
        }
        for(int i = 49; i < 53; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWarehouseFleece);
        }
        for(int i = 53; i < 57; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWarehouseArmor);
        }
        fWarehouseSculpture = std::make_shared<eTexture>();
        fWarehouseSculpture->load(fRenderer, pathBase + "00057.png");
        for(int i = 58; i < 62; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWarehouseOliveOil);
        }
        for(int i = 62; i < 66; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWarehouseWine);
        }


        for(int i = 71; i < 76; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWaitingMeat);
        }
        for(int i = 76; i < 81; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWaitingCheese);
        }
        for(int i = 81; i < 89; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWaitingWheat);
        }
        for(int i = 89; i < 94; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWaitingWood);
        }
        for(int i = 94; i < 99; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWaitingBronze);
        }
        for(int i = 99; i < 102; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWaitingGrapes);
        }
        for(int i = 102; i < 105; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWaitingOlives);
        }
        for(int i = 105; i < 110; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWaitingArmor);
        }

        fWarehouseEmpty = std::make_shared<eTexture>();
        fWarehouseEmpty->load(fRenderer, pathBase + "00115.png");
    }

    {
        const auto dir = basedir + "Zeus_General/";
        const std::string pathBase{dir + "Zeus_StorNDist_"};

        fFoodVendor = std::make_shared<eTexture>();
        fFoodVendor->load(fRenderer, pathBase + "00001.png");
        fFoodVendorOverlay = std::make_shared<eTexture>();
        fFoodVendorOverlay->load(fRenderer, pathBase + "00002.png");
        fFleeceVendor = std::make_shared<eTexture>();
        fFleeceVendor->load(fRenderer, pathBase + "00003.png");
        fFleeceVendorOverlay = std::make_shared<eTexture>();
        fFleeceVendorOverlay->load(fRenderer, pathBase + "00004.png");
        fOilVendor = std::make_shared<eTexture>();
        fOilVendor->load(fRenderer, pathBase + "00005.png");
        fOilVendorOverlay = std::make_shared<eTexture>();
        fOilVendorOverlay->load(fRenderer, pathBase + "00006.png");
        fWineVendor = std::make_shared<eTexture>();
        fWineVendor->load(fRenderer, pathBase + "00007.png");
        fWineVendorOverlay = std::make_shared<eTexture>();
        fWineVendorOverlay->load(fRenderer, pathBase + "00008.png");
        fArmsVendor = std::make_shared<eTexture>();
        fArmsVendor->load(fRenderer, pathBase + "00009.png");
        fArmsVendorOverlay = std::make_shared<eTexture>();
        fArmsVendorOverlay->load(fRenderer, pathBase + "00010.png");
        fHorseTrainer = std::make_shared<eTexture>();
        fHorseTrainer->load(fRenderer, pathBase + "00011.png");
        fHorseTrainerOverlay = std::make_shared<eTexture>();
        fHorseTrainerOverlay->load(fRenderer, pathBase + "00012.png");

//        for(int i = 13; i < 16; i++) {
//            eTextureLoadingHelpers::loadTex(pathBase, i, fAgoraRoad);
//        }
//        for(int i = 16; i < 19; i++) {
//            eTextureLoadingHelpers::loadTex(pathBase, i, fAgora);
//        }

        fWarehouse = std::make_shared<eTexture>();
        fWarehouse->load(fRenderer, pathBase + "00023.png");
        fWarehouse->setOffset(-58, 60);

        fGranary = std::make_shared<eTexture>();
        fGranary->load(fRenderer, pathBase + "00029.png");;
        for(int i = 30; i < 46; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fGranaryOverlay);
        }

        fGranaryUrchin = std::make_shared<eTexture>();
        fGranaryUrchin->load(fRenderer, pathBase + "00046.png");
        fGranaryFish = std::make_shared<eTexture>();
        fGranaryFish->load(fRenderer, pathBase + "00047.png");
        fGranaryMeat = std::make_shared<eTexture>();
        fGranaryMeat->load(fRenderer, pathBase + "00048.png");
        fGranaryCheese = std::make_shared<eTexture>();
        fGranaryCheese->load(fRenderer, pathBase + "00049.png");
        fGranaryCheese->setOffset(-3, 2);
        fGranaryCarrots = std::make_shared<eTexture>();
        fGranaryCarrots->load(fRenderer, pathBase + "00050.png");
        fGranaryOnions = std::make_shared<eTexture>();
        fGranaryOnions->load(fRenderer, pathBase + "00051.png");
        fGranaryOnions->setOffset(-4, 0);
        fGranaryWheat = std::make_shared<eTexture>();
        fGranaryWheat->load(fRenderer, pathBase + "00052.png");
    }


    {
        const auto dir = basedir + "Zeus_General/";

        const std::string pathBase{dir + "Zeus_Beautification2_"};

        for(int i = 12; i < 16; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fPark);
        }
        for(int i = 16; i < 19; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fLargePark);
        }
        eTextureLoadingHelpers::loadTex(pathBase, 19, fHugePark);

        fBench = std::make_shared<eTexture>();
        fBench->load(fRenderer, pathBase + "00020.png");
        fFlowerGarden = std::make_shared<eTexture>();
        fFlowerGarden->load(fRenderer, pathBase + "00021.png");
        fGazebo = std::make_shared<eTexture>();
        fGazebo->load(fRenderer, pathBase + "00022.png");
        fHedgeMaze = std::make_shared<eTexture>();
        fHedgeMaze->load(fRenderer, pathBase + "00023.png");
        fFishPond = std::make_shared<eTexture>();
        fFishPond->load(fRenderer, pathBase + "00024.png");

        fDoricColumn = std::make_shared<eTexture>();
        fDoricColumn->load(fRenderer, pathBase + "00034.png");
        fIonicColumn = std::make_shared<eTexture>();
        fIonicColumn->load(fRenderer, pathBase + "00035.png");
        fCorinthianColumn = std::make_shared<eTexture>();
        fCorinthianColumn->load(fRenderer, pathBase + "00036.png");

        fColumnConnectionH = std::make_shared<eTexture>();
        fColumnConnectionH->load(fRenderer, pathBase + "00037.png");
        fColumnConnectionW = std::make_shared<eTexture>();
        fColumnConnectionW->load(fRenderer, pathBase + "00038.png");
    }
    {
        const auto dir = basedir + "Zeus_Added/";

        const std::string pathBase{dir + "Zeus_Added_"};

        for(int i = 1; i < 16; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fPatrolGuides);
        }

        const auto cloudPathBase{dir + "cloud_"};
        for(int i = 1; i < 5; i++) {
            eTextureLoadingHelpers::loadTex(cloudPathBase, i, fClouds);
        }
    }
    {
        const auto dir = basedir + "Poseidon_Loaded/";

        {
            const std::string pathBase{dir + "Poseidon_aesthetic_"};
            fTallObelisk = std::make_shared<eTexture>();
            fTallObelisk->load(fRenderer, pathBase + "00017.png");
            fSundial = std::make_shared<eTexture>();
            fSundial->load(fRenderer, pathBase + "00018.png");
            fTopiary = std::make_shared<eTexture>();
            fTopiary->load(fRenderer, pathBase + "00019.png");

            for(int i = 20; i < 27; i++) {
                eTextureLoadingHelpers::loadTex(pathBase, i, fSpring);
            }
            fStoneCircle = std::make_shared<eTexture>();
            fStoneCircle->load(fRenderer, pathBase + "00027.png");
            for(int i = 28; i < 33; i++) {
                eTextureLoadingHelpers::loadTex(pathBase, i, fStoneCircleOverlay);
            }
            fDolphinSculpture = std::make_shared<eTexture>();
            fDolphinSculpture->load(fRenderer, pathBase + "00033.png");
            fShellGarden = std::make_shared<eTexture>();
            fShellGarden->load(fRenderer, pathBase + "00035.png");

            fBaths = std::make_shared<eTexture>();
            fBaths->load(fRenderer, pathBase + "00036.png");
            for(int i = 37; i < 53; i++) {
                eTextureLoadingHelpers::loadTex(pathBase, i, fBathsOverlay);
            }

            fBirdBath = std::make_shared<eTexture>();
            fBirdBath->load(fRenderer, pathBase + "00053.png");
            for(int i = 54; i < 63; i++) {
                eTextureLoadingHelpers::loadTex(pathBase, i, fBirdBathOverlay);
            }

            fShortObelisk = std::make_shared<eTexture>();
            fShortObelisk->load(fRenderer, pathBase + "00063.png");
            const auto loadWaterPark = [&](const int i,
                                           std::shared_ptr<eTexture>& tex,
                                           eTextureCollection& overlay) {
                tex = std::make_shared<eTexture>();
                auto tn = std::to_string(i);
                tn = eTextureLoadingHelpers::addZeroes(tn);
                tex->load(fRenderer, pathBase + tn + ".png");
                const int jMax = i + 8;
                for(int j = i + 1; j < jMax; j++) {
                    eTextureLoadingHelpers::loadTex(pathBase, j, overlay);
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

        const std::string pathBase{dir + "Poseidon_Storage_"};

//        fCorral = std::make_shared<eTexture>();
//        fCorral->load(fRenderer, pathBase + "00001.png");

//        for(int i = 2; i < 49; i++) {
//            eTextureLoadingHelpers::loadTex(pathBase, i, fCorralOverlay);
//        }

        fOrangeTendersLodge = std::make_shared<eTexture>();
        fOrangeTendersLodge->load(fRenderer, pathBase + "00051.png");

        for(int i = 52; i < 87; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fOrangeTendersLodgeOverlay);
        }

        for(int i = 87; i < 91; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWarehouseOranges);
        }

        for(int i = 99; i < 104; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWaitingOranges);
        }

        fGranaryOranges = std::make_shared<eTexture>();
        fGranaryOranges->load(fRenderer, pathBase + "00122.png");

        for(int i = 123; i < 129; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fOrangeTree);
        }
    }
}
