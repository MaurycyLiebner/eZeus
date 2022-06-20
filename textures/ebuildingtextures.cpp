#include "ebuildingtextures.h"

#include "etextureloadinghelpers.h"
#include "offsets/SprAmbient.h"

#include "etextureloader.h"

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

    fGatehouseW(renderer),
    fGatehouseH(renderer),
    fWall(renderer),

    fMaintenanceOfficeOverlay(renderer),
    fTaxOfficeOverlay(renderer),
    fWatchPostOverlay(renderer),

    fBeachRoad(renderer),
    fToBeachRoad(renderer),
    fRoad(renderer),
    fPrettyRoad(renderer),

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

    fAgoraRoad(renderer),
    fAgora(renderer),

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

    fAppeal(renderer),
    fHouseAppeal(renderer),

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
    fSanctuaryStairs(renderer),
    fSanctuaryFire(renderer) {

}

void eBuildingTextures::load() {
    if(fLoaded) return;
    fLoaded = true;

    eTextureLoader texLoader(fRenderer);
    texLoader.initialize();

    std::string basedir{"../ZeusTextures/"};
    basedir += std::to_string(fTileH) + "/";
    {
        const auto dir = basedir + "Zeus_General/";

        {
            const std::string pathBase{dir + "Zeus_Housing_"};

            eTextureClass texClass(pathBase, texLoader);

            fHouseSpace = texClass.load(15);
            for(int i = 1; i < 15;) {
                auto& coll = fCommonHouse.emplace_back(fRenderer);
                for(int j = 0; j < 2; j++, i++) {
                    texClass.load(i, coll);
                }
            }

            for(int i = 16; i < 46;) {
                auto& coll = fEliteHouse.emplace_back(fRenderer);
                for(int j = 0; j < 5; j++, i++) {
                    texClass.load(i, coll);
                }
            }

            for(int i = 46; i < 50; i++) {
                texClass.load(i, fEliteHouseHorses);
            }
        }

        {
            const std::string pathBase{dir + "Zeus_Culture_"};

            eTextureClass texClass(pathBase, texLoader);

            fCollege = texClass.load(1);

            for(int i = 2; i < 26; i++) {
                texClass.load(i, fCollegeOverlay);
            }

            fGymnasium = texClass.load(26);

            for(int i = 27; i < 59; i++) {
                texClass.load(i, fGymnasiumOverlay);
            }

            fDramaSchool = texClass.load(59);

            for(int i = 60; i < 84; i++) {
                texClass.load(i, fDramaSchoolOverlay);
            }

            fPodium = texClass.load(84);

            for(int i = 85; i < 109; i++) {
                texClass.load(i, fPodiumOverlay);
            }

            fTheater = texClass.load(109);

            fStadium2H = texClass.load(110);
            fStadium2H->setOffset(5, 0);
            fStadium1H = texClass.load(111);
            fStadium1W = texClass.load(112);
            fStadium2W = texClass.load(113);
            fStadium2W->setOffset(-5, 0);

        }
    }

    {
        const auto dir = basedir + "Zeus_General/";

        const std::string pathBase{dir + "Zeus_HealthNSan_"};

        eTextureClass texClass(pathBase, texLoader);

        fFountain = texClass.load(1);
        for(int i = 2; i < 8; i++) {
            texClass.load(i, fFountainOverlay);
        }

        fHospital = texClass.load(8);
        for(int i = 9; i < 21; i++) {
            texClass.load(i, fHospitalOverlay);
        }
    }

    {
        const auto dir = basedir + "Zeus_General/";

        const std::string pathBase{dir + "Zeus_Husbandry_"};

        eTextureClass texClass(pathBase, texLoader);

        for(int i = 1; i < 7; i++) {
            texClass.load(i, fOliveTree);
        }

        for(int i = 7; i < 13; i++) {
            texClass.load(i, fVine);
        }

        fPlantation = texClass.load(13);

        for(int i = 14; i < 20; i++) {
            texClass.load(i, fWheat);
        }

        for(int i = 20; i < 26; i++) {
            texClass.load(i, fCarrots);
        }

        for(int i = 26; i < 32; i++) {
            texClass.load(i, fOnions);
        }

        fHuntingLodge = texClass.load(32);
        for(int i = 33; i < 48; i++) {
            texClass.load(i, fHuntingLodgeOverlay);
        }

        for(int i = 48; i < 52; i++) {
            texClass.load(i, fFishery);
        }

        for(int i = 52; i < 56; i++) {
            texClass.load(i, fUrchinQuay);
        }

        fCardingShed = texClass.load(56);
        for(int i = 57; i < 69; i++) {
            texClass.load(i, fCardingShedOverlay);
        }

        fDairy = texClass.load(69);
        for(int i = 70; i < 91; i++) {
            texClass.load(i, fDairyOverlay);
        }

        fGrowersLodge = texClass.load(91);
        for(int i = 92; i < 102; i++) {
            texClass.load(i, fGrowersLodgeOverlay);
        }
    }

    {
        const auto dir = basedir + "Zeus_General/";

        const std::string pathBase{dir + "Zeus_Industry_"};

        eTextureClass texClass(pathBase, texLoader);

        fTimberMill = texClass.load(1);
        for(int i = 2; i < 12; i++) {
            texClass.load(i, fTimberMillOverlay);
        }

        fMasonryShop = texClass.load(12);
        for(int i = 13; i < 21; i++) {
            texClass.load(i, fMasonryShopStones);
        }

        fMint = texClass.load(21);
        for(int i = 22; i < 32; i++) {
            texClass.load(i, fMintOverlay);
        }

        fFoundry = texClass.load(36);
        for(int i = 37; i < 49; i++) {
            texClass.load(i, fFoundryOverlay);
        }

        fArtisansGuild = texClass.load(49);
        for(int i = 50; i < 60; i++) {
            texClass.load(i, fArtisansGuildOverlay);
        }

        fOlivePress = texClass.load(60);
        for(int i = 61; i < 73; i++) {
            texClass.load(i, fOlivePressOverlay);
        }

        fWinery = texClass.load(73);
        for(int i = 74; i < 86; i++) {
            texClass.load(i, fWineryOverlay);
        }

        fSculptureStudio = texClass.load(86);
        for(int i = 87; i < 122; i++) {
            texClass.load(i, fSculptureStudioOverlay);
        }
    }

    {
        const auto dir = basedir + "Zeus_General/";

        const std::string pathBase{dir + "Zeus_Military_"};
        eTextureClass texClass(pathBase, texLoader);
        for(int i = 1; i < 5; i++) {
            texClass.load(i, fTriremeWharf);
        }

        fHorseRanch = texClass.load(5);
        for(int i = 6; i < 22; i++) {
            texClass.load(i, fHorseRanchOverlay);
        }
        fHorseRanchEnclosure = texClass.load(41);

        fArmory = texClass.load(22);
        for(int i = 23; i < 41; i++) {
            texClass.load(i, fArmoryOverlay);
        }

        texClass.load(50, fGatehouseW);
        texClass.load(52, fGatehouseW);
        texClass.load(54, fGatehouseW);
        texClass.load(57, fGatehouseW);

        texClass.load(51, fGatehouseH);
        texClass.load(53, fGatehouseH);
        texClass.load(55, fGatehouseH);
        texClass.load(58, fGatehouseH);

        fTower = texClass.load(56);

        for(int i = 59; i < 95; i++) {
            texClass.load(i, fWall);
        }
    }

    {
        const auto dir = basedir + "Zeus_General/";

        const std::string pathBase{dir + "Zeus_Municipal_"};

        eTextureClass texClass(pathBase, texLoader);

        fMaintenanceOffice = texClass.load(1);
        for(int i = 2; i < 46; i++) {
            texClass.load(i, fMaintenanceOfficeOverlay);
        }

        fTaxOffice = texClass.load(46);
        for(int i = 47; i < 65; i++) {
            texClass.load(i, fTaxOfficeOverlay);
        }

        fWatchPost = texClass.load(65);

        {
            const std::string pathBase{dir + "Zeus_Mun-Palace_"};
            eTextureClass texClass(pathBase, texLoader);

            fPalace2H = texClass.load(1);
            fPalace2H->setOffset(4, 0);
            fPalace1H = texClass.load(12);
            fPalace1W = texClass.load(13);
            fPalace2W = texClass.load(14);
            fPalace2W->setOffset(-4, 0);

            texClass.load(25, fPalaceTiles);
            texClass.load(26, fPalaceTiles);
        }
    }

    {
        const auto dir = basedir + "SprAmbient/";

        const std::string pathBase{dir + "SprAmbient_"};

        eTextureClass texClass(pathBase, texLoader, &eSprAmbientOffset);

        for(int i = 43; i < 82; i++) {
            texClass.load(i, fTradingPostOverlay);
        }

        for(int i = 269; i < 293; i++) {
            texClass.load(i, fWarehouseOverlay);
        }

        for(int i = 656; i < 680; i++) {
            texClass.load(i, fTheaterOverlay);
        }

        for(int i = 1492; i < 1510; i++) {
            texClass.load(i, fStadiumOverlay1);
        }

        for(int i = 1510; i < 1530; i++) {
            texClass.load(i, fStadiumOverlay2);
        }

        for(int i = 1530; i < 1547; i++) {
            texClass.load(i, fStadiumOverlay3);
        }

        for(int i = 1547; i < 1629;) {
            for(int j = 0; j < 2; j++, i++) {
                eTextureCollection* coll;
                if(j == 0) {
                    coll = &fStadiumOverlay4W;
                } else {
                    coll = &fStadiumOverlay4H;
                }
                texClass.load(i, *coll);
            }
        }

        for(int i = 1629; i < 1653; i++) {
            texClass.load(i, fStadiumAudiance1W);
        }

        for(int i = 1653; i < 1677; i++) {
            texClass.load(i, fStadiumAudiance2W);
        }

        for(int i = 1677; i < 1701; i++) {
            texClass.load(i, fStadiumAudiance1H);
        }

        for(int i = 1701; i < 1725; i++) {
            texClass.load(i, fStadiumAudiance2H);
        }

        for(int i = 1725; i < 1773; i++) {
            texClass.load(i, fSanctuaryHOverlay);
        }
        for(int i = 0; i < fSanctuaryHOverlay.size(); i++) {
            auto& tex = fSanctuaryWOverlay.addTexture();
            const auto& srcTex = fSanctuaryHOverlay.getTexture(i);
            tex->setFlipTex(srcTex);
        }

        for(int i = 1773; i < 1937;) {
            for(int j = 0; j < 2; j++, i++) {
                eTextureCollection* coll;
                if(j == 0) {
                    coll = &fStadiumOverlay5W;
                } else {
                    coll = &fStadiumOverlay5H;
                }
                texClass.load(i, *coll);
            }
        }

        for(int i = 2105; i < 2117; i++) {
            texClass.load(i, fSanctuaryFire);
        }

        texClass.loadSkipFlipped(fMasonryShopOverlay1, 1937, 2017);
        texClass.loadSkipFlipped(fMasonryShopOverlay2, 2017, 2097);
        texClass.loadSkipFlipped(fWaitingOverlay0, 2277, 2437);
        texClass.loadSkipFlipped(fWaitingOverlay1, 2437, 2533);

        for(int i = 2759; i < 2790; i++) {
            texClass.load(i, fFishPondOverlay);
        }
        for(int i = 2958; i < 3011; i++) {
            texClass.load(i, fWatchPostOverlay);
        }

        for(int i = 3011; i < 3035; i++) {
            texClass.load(i, fPalaceHOverlay);
        }
        for(int i = 0; i < fPalaceHOverlay.size(); i++) {
            auto& tex = fPalaceWOverlay.addTexture();
            const auto& srcTex = fPalaceHOverlay.getTexture(i);
            tex->setFlipTex(srcTex);
        }
    }

    {
        const auto dir = basedir + "Zeus_Terrain/";

        {
            const std::string pathBase{dir + "Zeus_Land3_"};
            eTextureClass texClass(pathBase, texLoader);

            for(int i = 81; i < 99; i++) {
                texClass.load(i, fBeachRoad);
            }

            for(int i = 231; i < 235; i++) {
                texClass.load(i, fToBeachRoad);
            }

            for(int i = 235; i < 253; i++) {
                texClass.load(i, fRoad);
            }

            for(int i = 253; i < 302; i++) {
                texClass.load(i, fPrettyRoad);
            }
        }

        {
            const std::string pathBase{dir + "Zeus_Overlay_"};
            eTextureClass texClass(pathBase, texLoader);

            for(int i = 1; i < 11; i++) {
                texClass.load(i, fAppeal);
            }

            for(int i = 11; i < 21; i++) {
                texClass.load(i, fHouseAppeal);
            }
        }

        {
            const std::string pathBase{dir + "Zeus_Religion_"};
            eTextureClass texClass(pathBase, texLoader);

            for(int i = 1; i < 13; i++) {
                texClass.load(i, fSanctuaryStairs);
            }
        }
    }

    {
        const auto dir = basedir + "Zeus_General/";
        const std::string pathBase{dir + "Zeus_Stor-bays_"};
        eTextureClass texClass(pathBase, texLoader);

        for(int i = 1; i < 5; i++) {
            texClass.load(i, fWarehouseUrchin);
        }
        for(int i = 5; i < 9; i++) {
            texClass.load(i, fWarehouseFish);
        }
        for(int i = 9; i < 13; i++) {
            texClass.load(i, fWarehouseMeat);
        }
        for(int i = 13; i < 17; i++) {
            texClass.load(i, fWarehouseCheese);
        }
        for(int i = 17; i < 21; i++) {
            texClass.load(i, fWarehouseCarrots);
        }
        for(int i = 21; i < 25; i++) {
            texClass.load(i, fWarehouseOnions);
        }
        for(int i = 25; i < 29; i++) {
            texClass.load(i, fWarehouseWheat);
        }
        for(int i = 29; i < 33; i++) {
            texClass.load(i, fWarehouseWood);
        }
        for(int i = 33; i < 37; i++) {
            texClass.load(i, fWarehouseBronze);
        }
        for(int i = 37; i < 41; i++) {
            texClass.load(i, fWarehouseMarble);
        }
        for(int i = 41; i < 45; i++) {
            texClass.load(i, fWarehouseGrapes);
        }
        for(int i = 45; i < 49; i++) {
            texClass.load(i, fWarehouseOlives);
        }
        for(int i = 49; i < 53; i++) {
            texClass.load(i, fWarehouseFleece);
        }
        for(int i = 53; i < 57; i++) {
            texClass.load(i, fWarehouseArmor);
        }
        fWarehouseSculpture = texClass.load(57);
        for(int i = 58; i < 62; i++) {
            texClass.load(i, fWarehouseOliveOil);
        }
        for(int i = 62; i < 66; i++) {
            texClass.load(i, fWarehouseWine);
        }


        for(int i = 71; i < 76; i++) {
            texClass.load(i, fWaitingMeat);
        }
        for(int i = 76; i < 81; i++) {
            texClass.load(i, fWaitingCheese);
        }
        for(int i = 81; i < 89; i++) {
            texClass.load(i, fWaitingWheat);
        }
        for(int i = 89; i < 94; i++) {
            texClass.load(i, fWaitingWood);
        }
        for(int i = 94; i < 99; i++) {
            texClass.load(i, fWaitingBronze);
        }
        for(int i = 99; i < 102; i++) {
            texClass.load(i, fWaitingGrapes);
        }
        for(int i = 102; i < 105; i++) {
            texClass.load(i, fWaitingOlives);
        }
        for(int i = 105; i < 110; i++) {
            texClass.load(i, fWaitingArmor);
        }

        fWarehouseEmpty = texClass.load(115);
    }

    {
        const auto dir = basedir + "Zeus_General/";
        const std::string pathBase{dir + "Zeus_StorNDist_"};
        eTextureClass texClass(pathBase, texLoader);

        fFoodVendor = texClass.load(1);
        fFoodVendorOverlay = texClass.load(2);
        fFleeceVendor = texClass.load(3);
        fFleeceVendorOverlay = texClass.load(4);
        fOilVendor = texClass.load(5);
        fOilVendorOverlay = texClass.load(6);
        fWineVendor = texClass.load(7);
        fWineVendorOverlay = texClass.load(8);
        fArmsVendor = texClass.load(9);
        fArmsVendorOverlay = texClass.load(10);
        fHorseTrainer = texClass.load(11);
        fHorseTrainerOverlay = texClass.load(12);

        for(int i = 13; i < 16; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fAgoraRoad);
        }
        for(int i = 16; i < 19; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fAgora);
        }

        fWarehouse = texClass.load(23);
        fWarehouse->setOffset(-58, 60);

        for(int i = 19; i < 23; i++) {
            texClass.load(i, fPier1);
        }

        fPier2 = texClass.load(25);

        fTradingPost = texClass.load(27);
        fTradingPost->setOffset(-88, 90);

        fGranary = texClass.load(29);
        for(int i = 30; i < 46; i++) {
            texClass.load(i, fGranaryOverlay);
        }

        fGranaryUrchin = texClass.load(46);
        fGranaryFish = texClass.load(47);
        fGranaryMeat = texClass.load(48);
        fGranaryCheese = texClass.load(49);
        fGranaryCheese->setOffset(-3, 2);
        fGranaryCarrots = texClass.load(50);
        fGranaryOnions = texClass.load(51);
        fGranaryOnions->setOffset(-4, 0);
        fGranaryWheat = texClass.load(52);
    }


    {
        const auto dir = basedir + "Zeus_General/";

        const std::string pathBase{dir + "Zeus_Beautification2_"};
        eTextureClass texClass(pathBase, texLoader);

        for(int i = 12; i < 16; i++) {
            texClass.load(i, fPark);
        }
        for(int i = 16; i < 19; i++) {
            texClass.load(i, fLargePark);
        }
        texClass.load(19, fHugePark);

        fBench = texClass.load(20);
        fFlowerGarden = texClass.load(21);
        fGazebo = texClass.load(22);
        fHedgeMaze = texClass.load(23);
        fFishPond = texClass.load(24);

        for(int i = 25; i < 34; i++) {
            texClass.load(i, fCommemorative);
        }

        fDoricColumn = texClass.load(34);
        fIonicColumn = texClass.load(35);
        fCorinthianColumn = texClass.load(36);

        fColumnConnectionH = texClass.load(37);
        fColumnConnectionW = texClass.load(38);

        for(int i = 39; i < 88; i++) {
            texClass.load(i, fAvenueRoad);
        }

        fAvenue.emplace_back(fRenderer);
        for(int i = 88; i < 97; i++) {
            texClass.load(i, fAvenue[0]);
        }

        fAvenue.emplace_back(fRenderer);
        for(int i = 97; i < 106; i++) {
            texClass.load(i, fAvenue[1]);
        }

        fAvenue.emplace_back(fRenderer);
        for(int i = 106; i < 115; i++) {
            texClass.load(i, fAvenue[2]);
        }

        fAvenue.emplace_back(fRenderer);
        for(int i = 115; i < 124; i++) {
            texClass.load(i, fAvenue[3]);
        }

        fAvenue.emplace_back(fRenderer);
        for(int i = 124; i < 132; i++) {
            texClass.load(i, fAvenue[4]);
        }
    }
    {
        const auto dir = basedir + "Zeus_Added/";

        const std::string pathBase{dir + "Zeus_Added_"};
        eTextureClass texClass(pathBase, texLoader);

        for(int i = 1; i < 16; i++) {
            texClass.load(i, fPatrolGuides);
        }
    }
    {
        const auto dir = basedir + "Zeus_General/";

        const std::string pathBase{dir + "Zeus_Religion_"};
        eTextureClass texClass(pathBase, texLoader);

        int i = 1;
        const auto loadStatues = [&](eTextureCollection& coll) {
            for(int j = 0; j < 4; j++, i++) {
                texClass.load(i, coll);
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
            texClass.load(i, fSanctuaryTiles);
        }
        for(int i = 55; i < 61; i++) {
            texClass.load(i, fSanctuarySpace);
        }

        fSanctuaryAltar = texClass.load(61);
        fHeroHall = texClass.load(62);
        for(int i = 63; i < 69; i++) {
            texClass.load(i, fHeroStatues);
        }
    }
    {
        const auto dir = basedir + "Poseidon_Loaded/";

        {
            const std::string pathBase{dir + "Poseidon_aesthetic_"};
            eTextureClass texClass(pathBase, texLoader);

            fTallObelisk = texClass.load(17);
            fSundial = texClass.load(18);
            fTopiary = texClass.load(19);

            for(int i = 20; i < 27; i++) {
                texClass.load(i, fSpring);
            }
            fStoneCircle = texClass.load(27);
            for(int i = 28; i < 33; i++) {
                texClass.load(i, fStoneCircleOverlay);
            }
            fDolphinSculpture = texClass.load(33);
            fShellGarden = texClass.load(35);

            fBaths = texClass.load(36);
            for(int i = 37; i < 53; i++) {
                texClass.load(i, fBathsOverlay);
            }

            fBirdBath = texClass.load(53);
            for(int i = 54; i < 63; i++) {
                texClass.load(i, fBirdBathOverlay);
            }

            fShortObelisk = texClass.load(63);
            const auto loadWaterPark = [&](const int i,
                                           std::shared_ptr<eTexture>& tex,
                                           eTextureCollection& overlay) {
                tex = texClass.load(i);
                const int jMax = i + 8;
                for(int j = i + 1; j < jMax; j++) {
                    texClass.load(j, overlay);
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
            const std::string pathBase{dir + "Poseidon_Statues_"};
            eTextureClass texClass(pathBase, texLoader);

            int i = 1;
            const auto loadStatues = [&](eTextureCollection& coll) {
                for(int j = 0; j < 4; j++, i++) {
                    texClass.load(i, coll);
                }
            };

            loadStatues(fHeraStatues);
            loadStatues(fAtlasStatues);
            for(int j = 0; j < 2; j++, i++) {
                texClass.load(i, fHeroStatues);
            }
            loadStatues(fPoseidonStatues);
        }

        const auto loadGodMonuments = [&](const int j, eTextureCollection& coll) {
            const auto nStr = (j < 10 ? "0" : "") + std::to_string(j);
            const auto dir = basedir + "Zeus_God" + nStr + "/";
            const std::string pathBase{dir + "Zeus_Rel-Statue-F_"};
            eTextureClass texClass(pathBase, texLoader);

            for(int i = 1; i < 5; i++) {
                texClass.load(i, coll);
            }
        };

        loadGodMonuments(1, fZeusMonuments);

        loadGodMonuments(2, fPoseidonMonuments);
        loadGodMonuments(3, fHadesMonuments);
        loadGodMonuments(4, fDemeterMonuments);
        loadGodMonuments(5, fAthenaMonuments);
        loadGodMonuments(6, fArtemisMonuments);
        loadGodMonuments(7, fApolloMonuments);
        loadGodMonuments(8, fAresMonuments);
        loadGodMonuments(9, fHephaestusMonuments);
        loadGodMonuments(10, fAphroditeMonuments);
        loadGodMonuments(11, fHermesMonuments);
        loadGodMonuments(12, fDionysusMonuments);

        {
            const auto dir = basedir + "zeus_statcon1/";
            const std::string pathBase{dir + "Zeus_Rel-Statue-R_"};
            eTextureClass texClass(pathBase, texLoader);
            fMonumentStone = texClass.load(1);
        }

        {
            const auto dir = basedir + "Zeus_Sanctuary1/";
            const std::string pathBase{dir + "Zeus_Religion_"};
            eTextureClass texClass(pathBase, texLoader);
            for(int i = 1; i < 5; i++) {
                auto& coll = fSanctuary.emplace_back(fRenderer);
                texClass.load(i, coll);
            }
        }

        {
            const auto dir = basedir + "Zeus_Sanctuary2/";
            const std::string pathBase{dir + "Zeus_Religion_"};
            eTextureClass texClass(pathBase, texLoader);
            for(int i = 1; i < 5; i++) {
                auto& coll = fSanctuary[i - 1];
                texClass.load(i, coll);
            }
        }

        {
            const auto dir = basedir + "Zeus_Sanctuary3/";
            const std::string pathBase{dir + "Zeus_Religion_"};
            eTextureClass texClass(pathBase, texLoader);
            for(int i = 1; i < 5; i++) {
                auto& coll = fSanctuary[i - 1];
                texClass.load(i, coll);
            }
        }

        {
            const auto dir = basedir + "Poseidon_AtlasStat/";
            const std::string pathBase{dir + "Poseidon_Statues_"};
            eTextureClass texClass(pathBase, texLoader);

            for(int i = 1; i < 5; i++) {
                texClass.load(i, fAtlasMonuments);
            }
        }

        {
            const auto dir = basedir + "Poseidon_HeraStat/";
            const std::string pathBase{dir + "Poseidon_Statues_"};
            eTextureClass texClass(pathBase, texLoader);

            for(int i = 1; i < 5; i++) {
                texClass.load(i, fHeraMonuments);
            }
        }

        {
            const auto dir = basedir + "zeus_statcon1/";
            const std::string pathBase{dir + "Zeus_Rel-Statue-R_"};
            eTextureClass texClass(pathBase, texLoader);
            fBlankMonument = texClass.load(1);
        }

        {
            const std::string pathBase{dir + "Poseidon_Storage_"};
            eTextureClass texClass(pathBase, texLoader);


    //        fCorral = std::make_shared<eTexture>();
    //        fCorral->load(fRenderer, pathBase + "00001.png");

    //        for(int i = 2; i < 49; i++) {
    //            eTextureLoadingHelpers::loadTex(pathBase, i, fCorralOverlay);
    //        }

            fOrangeTendersLodge = texClass.load(51);

            for(int i = 52; i < 87; i++) {
                texClass.load(i, fOrangeTendersLodgeOverlay);
            }

            for(int i = 87; i < 91; i++) {
                texClass.load(i, fWarehouseOranges);
            }

            for(int i = 99; i < 104; i++) {
                texClass.load(i, fWaitingOranges);
            }

            fGranaryOranges = texClass.load(122);
            fGranaryOranges->setOffset(-3, -3);

            for(int i = 123; i < 129; i++) {
                texClass.load(i, fOrangeTree);
            }
        }
    }

    texLoader.waitUntilFinished();
}
