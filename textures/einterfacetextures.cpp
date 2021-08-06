#include "einterfacetextures.h"

#include "etextureloadinghelpers.h"

eInterfaceTextures::eInterfaceTextures(const int tileW, const int tileH,
                                       SDL_Renderer* const renderer):
    fTileW(tileW), fTileH(tileH),
    fRenderer(renderer),

    fShowInfo(renderer),
    fShowMap(renderer),

    fPopulation(renderer),
    fHusbandry(renderer),
    fIndustry(renderer),
    fDistribution(renderer),
    fHygieneSafety(renderer),
    fAdministration(renderer),
    fCulture(renderer),
    fMythology(renderer),
    fMilitary(renderer),
    fAesthetics(renderer),
    fOverview(renderer),

    fBrushSize(renderer),
    fEmptyLand(renderer),
    fForest(renderer),
    fWaterMarshBeach(renderer),
    fMeadow(renderer),
    fFishAndUrchin(renderer),
    fRocks(renderer),
    fScrub(renderer),
    fElevation(renderer),
    fDisasters(renderer),
    fWaterPoints(renderer),
    fLandInvasionPoints(renderer),
    fExitEndEntryPoints(renderer),
    fAnimalPoints(renderer),

    fCommonHousing(renderer),
    fEliteHousing(renderer),

    fFoodFarming(renderer),
    fOtherFarming(renderer),
    fAnimalFarming(renderer),
    fAnimalHunting(renderer),

    fResources(renderer),
    fProcessing(renderer),
    fBuildersGuild(renderer),

    fGranary(renderer),
    fWarehouse(renderer),
    fAgoras(renderer),
    fTrade(renderer),

    fFireFighter(renderer),
    fFountain(renderer),
    fPolice(renderer),
    fHospital(renderer),

    fPalace(renderer),
    fTaxCollector(renderer),
    fBridge(renderer),

    fPhilosophy(renderer),
    fGymnasium(renderer),
    fDrama(renderer),
    fStadium(renderer),

    fTemples(renderer),
    fHeroShrines(renderer),

    fFortifications(renderer),
    fMilitaryProduction(renderer),

    fBeautification(renderer),
    fRecreation(renderer),
    fMonuments(renderer),

    fBuildRoad(renderer),
    fRoadBlock(renderer),
    fClear(renderer),
    fUndo(renderer),

    fMessages(renderer),

    fGoals(renderer),
    fRotation(renderer),
    fWorld(renderer),

    fFireAlert(renderer),
    fGroundFissureAlert(renderer),
    fFloodAlert(renderer),
    fAvalancheAltert(renderer),
    fLavaAltert(renderer),
    fBuildingCollapseAltert(renderer),
    fRoadBlockAltert(renderer),
    fVirusAlert(renderer),
    fIllnessAlert(renderer),
    fInvasionAlert(renderer),
    fMonsterAltert(renderer),
    fGodAttackAlert(renderer),
    fGodVisitAlert(renderer),
    fHeroArrivalAlert(renderer),
    fArmyComebackAlert(renderer),

    fCheckBox(renderer) {
}

void eInterfaceTextures::load() {
    std::string dir{"../ZeusTextures/"};
    dir += std::to_string(fTileH) + "/";
    dir += "Zeus_Interface/";

    {
        const std::string pathBase{dir + "Zeus_Interface_New_Bbuttons_"};

        for(int i = 4; i < 7; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fCommonHousing);
        }

        for(int i = 7; i < 10; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fEliteHousing);
        }

        for(int i = 10; i < 13; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fFoodFarming);
        }

        for(int i = 13; i < 16; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fOtherFarming);
        }

        for(int i = 16; i < 19; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fAnimalFarming);
        }

        for(int i = 19; i < 22; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fAnimalHunting);
        }

        for(int i = 22; i < 25; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fResources);
        }

        for(int i = 25; i < 28; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fProcessing);
        }

        for(int i = 28; i < 31; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fBuildersGuild);
        }

        for(int i = 31; i < 34; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fGranary);
        }

        for(int i = 34; i < 37; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWarehouse);
        }

        for(int i = 37; i < 40; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fAgoras);
        }

        for(int i = 40; i < 43; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fTrade);
        }

        for(int i = 43; i < 46; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fFireFighter);
        }

        for(int i = 46; i < 49; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fFountain);
        }

        for(int i = 49; i < 52; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fPolice);
        }

        for(int i = 52; i < 55; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fHospital);
        }

        for(int i = 55; i < 58; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fPalace);
        }

        for(int i = 58; i < 61; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fTaxCollector);
        }

        for(int i = 61; i < 64; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fBridge);
        }

        for(int i = 67; i < 70; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fPhilosophy);
        }

        for(int i = 70; i < 73; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fGymnasium);
        }

        for(int i = 73; i < 76; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fDrama);
        }

        for(int i = 76; i < 79; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fStadium);
        }

        for(int i = 79; i < 82; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fTemples);
        }

        for(int i = 82; i < 85; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fHeroShrines);
        }

        for(int i = 85; i < 88; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fFortifications);
        }

        for(int i = 88; i < 91; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fMilitaryProduction);
        }

        for(int i = 91; i < 94; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fBeautification);
        }

        for(int i = 94; i < 97; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fRecreation);
        }

        for(int i = 97; i < 100; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fMonuments);
        }
    }

    {
        const std::string pathBase{dir + "Zeus_Interface_New_parts_"};

        fGameMenuBackground.load(fRenderer, pathBase + "00002.png");


        for(int i = 5; i < 37; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fRotation);
        }

        for(int i = 37; i < 41; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fGoals);
        }

        for(int i = 41; i < 45; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWorld);
        }

        for(int i = 45; i < 49; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fBuildRoad);
        }

        for(int i = 49; i < 53; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fRoadBlock);
        }

        for(int i = 53; i < 57; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fClear);
        }

        for(int i = 57; i < 61; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fUndo);
        }

        for(int i = 61; i < 65; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fMessages);
        }

        for(int i = 89; i < 93; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fOverview);
        }

        for(int i = 93; i < 97; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fPopulation);
        }

        for(int i = 97; i < 101; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fHusbandry);
        }

        for(int i = 101; i < 105; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fIndustry);
        }

        for(int i = 105; i < 109; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fDistribution);
        }

        for(int i = 109; i < 113; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fHygieneSafety);
        }

        for(int i = 113; i < 117; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fAdministration);
        }

        for(int i = 117; i < 121; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fCulture);
        }

        for(int i = 121; i < 125; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fMythology);
        }

        for(int i = 125; i < 129; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fMilitary);
        }

        for(int i = 129; i < 133; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fAesthetics);
        }



        for(int i = 184; i < 187; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fFireAlert);
        }
        for(int i = 187; i < 190; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fGroundFissureAlert);
        }
        for(int i = 190; i < 193; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fFloodAlert);
        }
        for(int i = 193; i < 196; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fAvalancheAltert);
        }
        for(int i = 196; i < 199; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fLavaAltert);
        }
        for(int i = 199; i < 202; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fBuildingCollapseAltert);
        }
        for(int i = 202; i < 205; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fRoadBlockAltert);
        }
        for(int i = 205; i < 208; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fVirusAlert);
        }
        for(int i = 208; i < 211; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fIllnessAlert);
        }
        for(int i = 211; i < 214; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fInvasionAlert);
        }
        for(int i = 214; i < 217; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fMonsterAltert);
        }
        for(int i = 217; i < 220; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fGodAttackAlert);
        }
        for(int i = 220; i < 223; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fGodVisitAlert);
        }
        for(int i = 223; i < 226; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fHeroArrivalAlert);
        }
        for(int i = 226; i < 229; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fArmyComebackAlert);
        }


        for(int i = 263; i < 267; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fShowInfo);
        }

        for(int i = 267; i < 271; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fShowMap);
        }
    }

    {
        const std::string pathBase{dir + "Zeus_MapEditor_"};

        fMapEditMenuBackground.load(fRenderer, pathBase + "00001.png");

        for(int i = 2; i < 6; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fBrushSize);
        }
        for(int i = 6; i < 10; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fEmptyLand);
        }
        for(int i = 10; i < 14; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fForest);
        }
        for(int i = 14; i < 18; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWaterMarshBeach);
        }
        for(int i = 18; i < 22; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fMeadow);
        }
        for(int i = 22; i < 26; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fFishAndUrchin);
        }
        for(int i = 26; i < 30; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fRocks);
        }
        for(int i = 30; i < 34; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fScrub);
        }
        for(int i = 34; i < 38; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fElevation);
        }
        for(int i = 38; i < 42; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fDisasters);
        }
        for(int i = 42; i < 46; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWaterPoints);
        }
        for(int i = 46; i < 50; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fLandInvasionPoints);
        }
        for(int i = 50; i < 54; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fExitEndEntryPoints);
        }
        for(int i = 54; i < 58; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fAnimalPoints);
        }
    }

    {
        const std::string pathBase{dir + "Zeus_Paneling_"};


        for(int i = 0; i < 2; i++) {
            fComboBox.emplace_back(fRenderer);
        }

        for(int i = 11; i < 20; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fComboBox[0]);
        }
        for(int i = 20; i < 29; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fComboBox[1]);
        }

        for(int i = 407; i < 409; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fCheckBox);
        }
    }

    {
        std::string dir{"../ZeusTextures/"};
        dir += std::to_string(fTileH) + "/Zeus_Data_Images/";

        fLoadImage.load(fRenderer, dir + "Zeus_Load1.jpg");
    }
}
