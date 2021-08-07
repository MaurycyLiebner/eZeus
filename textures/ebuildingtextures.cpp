#include "ebuildingtextures.h"

#include "etextureloadinghelpers.h"

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
    fRoad(renderer) {

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

        for(int i = 2958; i < 3011; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWatchPostOverlay);
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
}
