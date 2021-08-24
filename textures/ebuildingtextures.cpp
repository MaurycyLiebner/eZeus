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

    fPalaceTiles(renderer),

    fFountainOverlay(renderer),
    fHospitalOverlay(renderer),

    fOliveTree(renderer),
    fVine(renderer),
    fWheat(renderer),
    fCarrots(renderer),
    fOnions(renderer),

    fHuntingLodgeOverlay(renderer),
    fFishery(renderer),
    fUrchinQuay(renderer),
    fCardingShedOverlay(renderer),
    fDairyOverlay(renderer),
    fGrowersLodgeOverlay(renderer),

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
    fWaitingWood(renderer),
    fWaitingBronze(renderer),
    fWaitingGrape(renderer),
    fWaitingOlives(renderer),
    fWaitingArmor(renderer),

    fWarehouseOverlay(renderer),

    fWarehouseUrchin(renderer),
    fWarehouseFish(renderer),
    fWarehouseMeat(renderer),
    fWarehouseCheese(renderer),
    fWarehouseCarrots(renderer),
    fWarehouseOnions(renderer),
    fWarehouseWheat(renderer),
    fWarehouseWood(renderer),
    fWarehouseBronze(renderer),
    fWarehouseMarble(renderer),
    fWarehouseGrapes(renderer),
    fWarehouseOlives(renderer),
    fWarehouseFleece(renderer),
    fWarehouseArmor(renderer),
    fWarehouseOliveOil(renderer),
    fWarehouseWine(renderer),

    fGranaryOverlay(renderer) {

}

void eBuildingTextures::load() {
    std::string basedir{"../ZeusTextures/"};
    basedir += std::to_string(fTileH) + "/";
    {
        const auto dir = basedir + "Zeus_General/";

        {
            const std::string pathBase{dir + "Zeus_Housing_"};

            fHouseSpace.load(fRenderer, pathBase + "00015.png");
            for(int i = 1; i < 15;) {
                auto& coll = fCommonHouse.emplace_back(fRenderer);
                for(int j = 0; j < 2; j++, i++) {
                    eTextureLoadingHelpers::loadTex(pathBase, i, coll);
                }
            }
        }

        {
            const std::string pathBase{dir + "Zeus_Culture_"};

            fCollege.load(fRenderer, pathBase + "00001.png");

            for(int i = 2; i < 26; i++) {
                eTextureLoadingHelpers::loadTex(pathBase, i, fCollegeOverlay);
            }

            fGymnasium.load(fRenderer, pathBase + "00026.png");

            for(int i = 27; i < 59; i++) {
                eTextureLoadingHelpers::loadTex(pathBase, i, fGymnasiumOverlay);
            }

            fDramaSchool.load(fRenderer, pathBase + "00059.png");

            for(int i = 60; i < 84; i++) {
                eTextureLoadingHelpers::loadTex(pathBase, i, fDramaSchoolOverlay);
            }

            fPodium.load(fRenderer, pathBase + "00084.png");

            for(int i = 85; i < 109; i++) {
                eTextureLoadingHelpers::loadTex(pathBase, i, fPodiumOverlay);
            }

            fTheater.load(fRenderer, pathBase + "00109.png");

            fStadium2H.load(fRenderer, pathBase + "00110.png");
            fStadium2H.setOffset(5, 0);
            fStadium1H.load(fRenderer, pathBase + "00111.png");
            fStadium1W.load(fRenderer, pathBase + "00112.png");
            fStadium2W.load(fRenderer, pathBase + "00113.png");
            fStadium2W.setOffset(-5, 0);

        }
    }

    {
        const auto dir = basedir + "Zeus_General/";

        const std::string pathBase{dir + "Zeus_HealthNSan_"};

        fFountain.load(fRenderer, pathBase + "00001.png");
        for(int i = 2; i < 8; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fFountainOverlay);
        }

        fHospital.load(fRenderer, pathBase + "00008.png");
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

        fPlantation.load(fRenderer, pathBase + "00013.png");

        for(int i = 14; i < 20; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWheat);
        }

        for(int i = 20; i < 26; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fCarrots);
        }

        for(int i = 26; i < 32; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fOnions);
        }

        fHuntingLodge.load(fRenderer, pathBase + "00032.png");
        for(int i = 33; i < 48; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fHuntingLodgeOverlay);
        }

        for(int i = 48; i < 52; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fFishery);
        }

        for(int i = 52; i < 56; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fUrchinQuay);
        }

        fCardingShed.load(fRenderer, pathBase + "00056.png");
        for(int i = 57; i < 69; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fCardingShedOverlay);
        }

        fDairy.load(fRenderer, pathBase + "00069.png");
        for(int i = 70; i < 91; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fDairyOverlay);
        }

        fGrowersLodge.load(fRenderer, pathBase + "00091.png");
        for(int i = 92; i < 102; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fGrowersLodgeOverlay);
        }
    }

    {
        const auto dir = basedir + "Zeus_General/";

        const std::string pathBase{dir + "Zeus_Industry_"};

        fTimberMill.load(fRenderer, pathBase + "00001.png");
        for(int i = 2; i < 12; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fTimberMillOverlay);
        }

        fMasonryShop.load(fRenderer, pathBase + "00012.png");
        for(int i = 13; i < 21; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fMasonryShopStones);
        }

        fMint.load(fRenderer, pathBase + "00021.png");
        for(int i = 22; i < 32; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fMintOverlay);
        }

        fFoundry.load(fRenderer, pathBase + "00036.png");
        for(int i = 37; i < 49; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fFoundryOverlay);
        }

        fArtisansGuild.load(fRenderer, pathBase + "00049.png");
        for(int i = 50; i < 60; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fArtisansGuildOverlay);
        }

        fOlivePress.load(fRenderer, pathBase + "00060.png");
        for(int i = 61; i < 73; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fOlivePressOverlay);
        }

        fWinery.load(fRenderer, pathBase + "00073.png");
        for(int i = 74; i < 86; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWineryOverlay);
        }

        fSculptureStudio.load(fRenderer, pathBase + "00086.png");
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

        fHorseRanch.load(fRenderer, pathBase + "00005.png");
        for(int i = 6; i < 22; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fHorseRanchOverlay);
        }
        fHorseRanchEnclosure.load(fRenderer, pathBase + "00041.png");

        fArmory.load(fRenderer, pathBase + "00022.png");
        for(int i = 23; i < 41; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fArmoryOverlay);
        }
    }

    {
        const auto dir = basedir + "Zeus_General/";

        const std::string pathBase{dir + "Zeus_Municipal_"};

        fMaintenanceOffice.load(fRenderer, pathBase + "00001.png");
        for(int i = 2; i < 46; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fMaintenanceOfficeOverlay);
        }

        fTaxOffice.load(fRenderer, pathBase + "00046.png");
        for(int i = 47; i < 65; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fTaxOfficeOverlay);
        }

        fWatchPost.load(fRenderer, pathBase + "00065.png");

        {
            const std::string pathBase{dir + "Zeus_Mun-Palace_"};

            fPalace2H.load(fRenderer, pathBase + "00001.png");
            fPalace2H.setOffset(4, 0);
            fPalace1H.load(fRenderer, pathBase + "00012.png");
            fPalace1W.load(fRenderer, pathBase + "00013.png");
            fPalace2W.load(fRenderer, pathBase + "00014.png");
            fPalace2W.setOffset(-4, 0);

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

        for(int i = 2958; i < 3011; i++) {
            eTextureLoadingHelpers::loadTexWithOffset(
                        pathBase, i, fWatchPostOverlay, eSprAmbientOffset);
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
        fWarehouseSculpture.load(fRenderer, pathBase + "00057.png");
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
            eTextureLoadingHelpers::loadTex(pathBase, i, fWaitingGrape);
        }
        for(int i = 102; i < 105; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWaitingOlives);
        }
        for(int i = 105; i < 110; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWaitingArmor);
        }

        fWarehouseEmpty.load(fRenderer, pathBase + "00115.png");
    }

    {
        const auto dir = basedir + "Zeus_General/";
        const std::string pathBase{dir + "Zeus_StorNDist_"};

        fWarehouse.load(fRenderer, pathBase + "00023.png");
        fWarehouse.setOffset(-58, 60);

        fGranary.load(fRenderer, pathBase + "00029.png");;
        for(int i = 30; i < 46; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fGranaryOverlay);
        }

        fGranaryUrchin.load(fRenderer, pathBase + "00046.png");
        fGranaryFish.load(fRenderer, pathBase + "00047.png");
        fGranaryMeat.load(fRenderer, pathBase + "00048.png");
        fGranaryCheese.load(fRenderer, pathBase + "00049.png");
        fGranaryCheese.setOffset(-3, 2);
        fGranaryCarrots.load(fRenderer, pathBase + "00050.png");
        fGranaryOnions.load(fRenderer, pathBase + "00051.png");
        fGranaryOnions.setOffset(-4, 0);
        fGranaryWheat.load(fRenderer, pathBase + "00052.png");
    }

    {
        const auto dir = basedir + "Zeus_Added/";

        const std::string pathBase{dir + "Zeus_Added_"};

        for(int i = 1; i < 16; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fPatrolGuides);
        }
    }
}
