#include "einterfacetextures.h"

#include "etextureloadinghelpers.h"

#include "spriteData/interfaceBanners15.h"
#include "spriteData/interfaceBanners30.h"
#include "spriteData/interfaceBanners45.h"
#include "spriteData/interfaceBanners60.h"

#include "spriteData/stor_bays15.h"
#include "spriteData/stor_bays30.h"
#include "spriteData/stor_bays45.h"
#include "spriteData/stor_bays60.h"

#include "spriteData/paneling15.h"
#include "spriteData/paneling30.h"
#include "spriteData/paneling45.h"
#include "spriteData/paneling60.h"

#include "spriteData/empireBits15.h"
#include "spriteData/empireBits30.h"
#include "spriteData/empireBits45.h"
#include "spriteData/empireBits60.h"

#include "spriteData/empireFigures15.h"
#include "spriteData/empireFigures30.h"
#include "spriteData/empireFigures45.h"
#include "spriteData/empireFigures60.h"

#include "spriteData/poseidonInterface15.h"
#include "spriteData/poseidonInterface30.h"
#include "spriteData/poseidonInterface45.h"
#include "spriteData/poseidonInterface60.h"

#include "espriteloader.h"

eInterfaceTextures::eInterfaceTextures(const int tileW, const int tileH,
                                       SDL_Renderer* const renderer) :
    fTileW(tileW), fTileH(tileH),
    fRenderer(renderer),

    fGoToCompany(renderer),
    fRotateCompany(renderer),
    fGoToBanner(renderer),
    fGoHome(renderer),
    fDefensiveTactics(renderer),
    fOffensiveTactics(renderer),
    fSpecialTactics(renderer),

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

    fWorldSmallButton(renderer),
    fWorldBigButton(renderer),

    fRequestButton(renderer),
    fFulfillButton(renderer),
    fGiftButton(renderer),
    fRaidButton(renderer),
    fConquerButton(renderer),

    fWorldLeftArrowButton(renderer),
    fWorldRightArrowButton(renderer),
    fWorldHistoryButton(renderer),

    fWorldBgsButton(renderer),

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
    fArtisansGuild(renderer),

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
    fCollapseAltert(renderer),
    fRoadBlockAltert(renderer),
    fVirusAlert(renderer),
    fIllnessAlert(renderer),
    fInvasionAlert(renderer),
    fMonsterAltert(renderer),
    fGodAttackAlert(renderer),
    fGodVisitAlert(renderer),
    fHeroArrivalAlert(renderer),
    fArmyComebackAlert(renderer),

    fBuildingButton(renderer),
    fBuildingButtonHover(renderer),

    fCheckBox(renderer),
    fLargeCheckBox(renderer),

    fRequestWaitingBox(renderer),
    fRequestFulfilledBox(renderer),

    fSeeButton(renderer),

    fUpButton(renderer),
    fDownButton(renderer),

    fBigUpButton(renderer),
    fBigDownButton(renderer),

    fExclamationButton(renderer),
    fOkButton(renderer),
    fHelpButton(renderer),

    fAcceptButton(renderer),
    fCancelButton(renderer),

    fButtonFrame(renderer),
    fButtonFrameHover(renderer),

    fColumn1(renderer),
    fColumn2(renderer),
    fColumn3(renderer),
    fColumn4(renderer),
    fColumn5(renderer),

    fDiamond(renderer),

    fZeusPlayerArmy(renderer),
    fZeusGreekArmy(renderer),
    fZeusTrojanArmy(renderer),
    fZeusPersianArmy(renderer),
    fZeusCentaurArmy(renderer),
    fZeusAmazonArmy(renderer),

    fPoseidonPlayerArmy(renderer),
    fPoseidonEgyptianArmy(renderer),
    fPoseidonMayanArmy(renderer),
    fPoseidonPhoenicianArmy(renderer),
    fPoseidonOceanidArmy(renderer),
    fPoseidonAtlanteanArmy(renderer),

    fAllyCityFlag(renderer),

    fCityArmy(renderer),
    fCityWealth(renderer),
    fCityRebellion(renderer),

    fInterfaceBanners(renderer),
    fInterfaceBannerTops(renderer) {}

void eInterfaceTextures::load() {
    if(fLoaded) return;
    fLoaded = true;

    loadInterfaceBanners();

    const std::string basedir{"../ZeusTextures/" + std::to_string(fTileH) + "/"};
    const auto dir = basedir + "Zeus_Interface/";

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
            eTextureLoadingHelpers::loadTex(pathBase, i, fArtisansGuild);
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
        const std::string pathBase{dir + "Zeus_interfaceParts_"};

        fArmyStatus = std::make_shared<eTexture>();
        fArmyStatus->load(fRenderer, pathBase + "00002.png");

        for(int i = 11; i < 15; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fGoToCompany);
        }

        for(int i = 15; i < 19; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fRotateCompany);
        }

        for(int i = 19; i < 23; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fGoToBanner);
        }

        for(int i = 23; i < 27; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fGoHome);
        }

        for(int i = 27; i < 31; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fDefensiveTactics);
        }

        for(int i = 31; i < 35; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fOffensiveTactics);
        }

        for(int i = 35; i < 39; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fSpecialTactics);
        }
    }
    {
        const std::string pathBase{dir + "Zeus_Interface_New_parts_"};

        fGameTopBar = std::make_shared<eTexture>();
        fGameTopBar->load(fRenderer, pathBase + "00001.png");

        fGameMenuBackground = std::make_shared<eTexture>();
        fGameMenuBackground->load(fRenderer, pathBase + "00002.png");

        fGameArmyBackground = std::make_shared<eTexture>();
        fGameArmyBackground->load(fRenderer, pathBase + "00003.png");


        for(int i = 5; i < 37; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fRotation);
        }

        eTextureLoadingHelpers::loadTex(pathBase, 40, fLargeCheckBox);
        eTextureLoadingHelpers::loadTex(pathBase, 37, fLargeCheckBox);

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

        for(int i = 137; i < 140; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fSeeButton);
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
            eTextureLoadingHelpers::loadTex(pathBase, i, fCollapseAltert);
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
        const std::string pathBase{dir + "Zeus_WorldSide_"};

        fWorldMenuBackground = std::make_shared<eTexture>();
        fWorldMenuBackground->load(fRenderer, pathBase + "00001.png");

        eTextureLoadingHelpers::loadTex(pathBase, 40, fLargeCheckBox);
        eTextureLoadingHelpers::loadTex(pathBase, 37, fLargeCheckBox);

        for(int i = 2; i < 6; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWorldSmallButton);
        }
        for(int i = 6; i < 10; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWorldBigButton);
        }
        for(int i = 10; i < 14; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fRequestButton);
        }
        for(int i = 14; i < 18; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fFulfillButton);
        }
        for(int i = 18; i < 22; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fGiftButton);
        }
        for(int i = 22; i < 26; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fRaidButton);
        }
        for(int i = 26; i < 30; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fConquerButton);
        }

        for(int i = 30; i < 34; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWorldLeftArrowButton);
        }
        for(int i = 34; i < 38; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWorldRightArrowButton);
        }
        for(int i = 38; i < 42; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWorldHistoryButton);
        }

        for(int i = 42; i < 46; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWorldBgsButton);
        }
    }

    {
        const std::string pathBase{dir + "Zeus_MapEditor_"};

        fMapEditMenuBackground = std::make_shared<eTexture>();
        fMapEditMenuBackground->load(fRenderer, pathBase + "00001.png");

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
        const auto& sds = spriteData(fTileH,
                                     eEmpireBitsSpriteData15,
                                     eEmpireBitsSpriteData30,
                                     eEmpireBitsSpriteData45,
                                     eEmpireBitsSpriteData60);
        eSpriteLoader loader(fTileH, "empireBits", sds,
                             nullptr, fRenderer);

        fZeusMainCity = loader.load(1, 1);
        fZeusCollony = loader.load(1, 2);
        fZeusDisabledCollony = loader.load(1, 3);
        fZeusGreekCity = loader.load(1, 4);
        fZeusTrojanCity = loader.load(1, 5);
        fZeusPersianCity = loader.load(1, 6);
        fZeusCentaurCity = loader.load(1, 7);
        fZeusAmazonCity = loader.load(1, 8);

        fZeusPlace = loader.load(1, 17);
        fZeusRuins = loader.load(1, 18);

        fZeusDistantCity = loader.load(1, 19);
        fZeusDistantCityN = loader.load(1, 20);
        fZeusDistantCityNE = loader.load(1, 21);
        fZeusDistantCityE = loader.load(1, 22);
        fZeusDistantCitySE = loader.load(1, 23);
        fZeusDistantCityS = loader.load(1, 24);
        fZeusDistantCitySW = loader.load(1, 25);
        fZeusDistantCityW = loader.load(1, 26);
        fZeusDistantCityNW = loader.load(1, 27);

        fMainCityFlag = loader.load(1, 9);
        fEmpireCityFlag = loader.load(1, 10);

        for(int i = 11; i < 17; i++) {
            loader.load(1, i, fAllyCityFlag);
        }

        for(int i = 33; i < 38; i++) {
            loader.load(1, i, fCityArmy);
        }

        for(int i = 38; i < 43; i++) {
            loader.load(1, i, fCityWealth);
        }

        for(int i = 43; i < 49; i++) {
            loader.load(1, i, fCityRebellion);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eEmpireFiguresSpriteData15,
                                     eEmpireFiguresSpriteData30,
                                     eEmpireFiguresSpriteData45,
                                     eEmpireFiguresSpriteData60);
        eSpriteLoader loader(fTileH, "empireFigures", sds,
                             nullptr, fRenderer);

        for(int i = 1; i < 4; i++) {
            loader.load(1, i, fZeusPlayerArmy);
        }
        for(int i = 4; i < 7; i++) {
            loader.load(1, i, fZeusGreekArmy);
        }
        for(int i = 7; i < 10; i++) {
            loader.load(1, i, fZeusTrojanArmy);
        }
        for(int i = 10; i < 13; i++) {
            loader.load(1, i, fZeusPersianArmy);
        }
        for(int i = 13; i < 16; i++) {
            loader.load(1, i, fZeusCentaurArmy);
        }
        for(int i = 16; i < 19; i++) {
            loader.load(1, i, fZeusAmazonArmy);
        }

        fZeusAchilles = loader.load(1, 25);
        fZeusHercules = loader.load(1, 26);
        fZeusJason = loader.load(1, 27);
        fZeusOdysseus = loader.load(1, 28);
        fZeusPerseus = loader.load(1, 29);
        fZeusTheseus = loader.load(1, 30);
    }

    {
        const auto& sds = spriteData(fTileH,
                                     ePoseidonInterfaceSpriteData15,
                                     ePoseidonInterfaceSpriteData30,
                                     ePoseidonInterfaceSpriteData45,
                                     ePoseidonInterfaceSpriteData60);
        eSpriteLoader loader(fTileH, "poseidonInterface", sds,
                             nullptr, fRenderer);

        fPoseidonMainCity = loader.load(1, 47);
        fPoseidonCollony = loader.load(1, 48);
        fPoseidonDisabledCollony = loader.load(1, 49);
        fPoseidonEgyptianCity = loader.load(1, 50);
        fPoseidonMayanCity = loader.load(1, 51);
        fPoseidonPhoenicianCity = loader.load(1, 52);
        fPoseidonOceanidCity = loader.load(1, 53);
        fPoseidonAtlanteanCity = loader.load(1, 54);

        fPoseidonAtalanta = loader.load(1, 55);
        fPoseidonBellerophon = loader.load(1, 56);

        for(int i = 63; i < 66; i++) {
            loader.load(1, i, fPoseidonPlayerArmy);
        }
        for(int i = 66; i < 69; i++) {
            loader.load(1, i, fPoseidonAtlanteanArmy);
        }
        for(int i = 69; i < 72; i++) {
            loader.load(1, i, fPoseidonEgyptianArmy);
        }
        for(int i = 72; i < 75; i++) {
            loader.load(1, i, fPoseidonMayanArmy);
        }
        for(int i = 75; i < 78; i++) {
            loader.load(1, i, fPoseidonPhoenicianArmy);
        }
        for(int i = 78; i < 81; i++) {
            loader.load(1, i, fPoseidonOceanidArmy);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     ePanelingSpriteData15,
                                     ePanelingSpriteData30,
                                     ePanelingSpriteData45,
                                     ePanelingSpriteData60);
        eSpriteLoader loader(fTileH, "paneling", sds,
                             nullptr, fRenderer);

        for(int i = 0; i < 2; i++) {
            fComboBox.emplace_back(fRenderer);
        }

        for(int i = 11; i < 20; i++) {
            loader.load(1, i, fComboBox[0]);
        }
        for(int i = 20; i < 29; i++) {
            loader.load(1, i, fComboBox[1]);
        }

        for(int i = 34; i < 37; i++) {
            loader.load(1, i, fBuildingButtonHover);
        }

        for(int i = 37; i < 40; i++) {
            loader.load(1, i, fBuildingButton);
        }

        for(int i = 0; i < 9; i++) {
            fMessageBox.emplace_back(fRenderer);
        }

        loader.load(1, 140, fMessageBox[0]);

        for(int i = 141; i < 151; i++) {
            loader.load(1, i, fMessageBox[1]);
        }

        loader.load(1, 151, fMessageBox[2]);

        for(int i = 152; i < 272;) {
            loader.load(1, i++, fMessageBox[3]);
            for(int j = 0; j < 10; j++) {
                loader.load(1, i++, fMessageBox[4]);
            }
            loader.load(1, i++, fMessageBox[5]);
        }

        loader.load(1, 272, fMessageBox[6]);

        for(int i = 273; i < 283; i++) {
            loader.load(1, i, fMessageBox[7]);
        }

        loader.load(1, 283, fMessageBox[8]);



        for(int i = 0; i < 9; i++) {
            fInnerBox.emplace_back(fRenderer);
        }

        loader.load(1, 284, fInnerBox[0]);

        for(int i = 285; i < 290; i++) {
            loader.load(1, i, fInnerBox[1]);
        }

        loader.load(1, 290, fInnerBox[2]);

        for(int i = 291; i < 326;) {
            loader.load(1, i++, fInnerBox[3]);
            for(int j = 0; j < 5; j++) {
                loader.load(1, i++, fInnerBox[4]);
            }
            loader.load(1, i++, fInnerBox[5]);
        }

        loader.load(1, 326, fInnerBox[6]);

        for(int i = 327; i < 332; i++) {
            loader.load(1, i, fInnerBox[7]);
        }

        loader.load(1, 332, fInnerBox[8]);



        for(int i = 64; i < 68; i++) {
            loader.load(1, i, fExclamationButton);
        }

        for(int i = 333; i < 337; i++) {
            loader.load(1, i, fHelpButton);
        }

        for(int i = 337; i < 341; i++) {
            loader.load(1, i, fOkButton);
        }

        for(int i = 124; i < 128; i++) {
            loader.load(1, i, fAcceptButton);
        }

        for(int i = 128; i < 132; i++) {
            loader.load(1, i, fCancelButton);
        }

        for(int i = 132; i < 136; i++) {
            loader.load(1, i, fBigUpButton);
        }

        for(int i = 136; i < 140; i++) {
            loader.load(1, i, fBigDownButton);
        }

        for(int i = 348; i < 356; i++) {
            loader.load(1, i, fButtonFrame);
        }

        for(int i = 356; i < 364; i++) {
            loader.load(1, i, fButtonFrameHover);
        }

        for(int i = 388; i < 392; i++) {
            loader.load(1, i, fUpButton);
        }
        for(int i = 392; i < 396; i++) {
            loader.load(1, i, fDownButton);
        }

        for(int i = 407; i < 411; i++) {
            loader.load(1, i, fCheckBox);
        }

        for(int i = 415; i < 419; i++) {
            loader.load(1, i, fRequestWaitingBox);
        }
        for(int i = 419; i < 423; i++) {
            loader.load(1, i, fRequestFulfilledBox);
        }
    }

    {
        const std::string pathBase{dir + "Zeus_Radar_"};

        for(int i = 262; i < 267; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fDiamond);
        }
    }

    fSpawner = std::make_shared<eTexture>();
    fSpawner->load(fRenderer, dir + "Zeus_sprites_00026.png");

    {
        const auto pathBase = dir + "Zeus_sprites_";
        for(int i = 1; i < 4; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fColumn1);
        }
        for(int i = 4; i < 7; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fColumn2);
        }
        for(int i = 7; i < 10; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fColumn3);
        }
        for(int i = 10; i < 13; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fColumn4);
        }
        for(int i = 13; i < 16; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fColumn5);
        }
    }

    {
        const auto dir = basedir + "/Zeus_Data_Images/";

        fLoadImage1 = std::make_shared<eTexture>();
        fLoadImage1->load(fRenderer, dir + "Zeus_Load1.jpg");

        fLoadImage2 = std::make_shared<eTexture>();
        fLoadImage2->load(fRenderer, dir + "Zeus_Load2.jpg");

        fLoadImage3 = std::make_shared<eTexture>();
        fLoadImage3->load(fRenderer, dir + "Zeus_Load3.jpg");

        fLoadImage4 = std::make_shared<eTexture>();
        fLoadImage4->load(fRenderer, dir + "Zeus_Load4.jpg");

        fLoadImage5 = std::make_shared<eTexture>();
        fLoadImage5->load(fRenderer, dir + "Poseidon_Load1.jpg");

        fLoadImage6 = std::make_shared<eTexture>();
        fLoadImage6->load(fRenderer, dir + "Poseidon_Load2.jpg");

        fLoadImage7 = std::make_shared<eTexture>();
        fLoadImage7->load(fRenderer, dir + "Poseidon_Load3.jpg");

        fLoadImage8 = std::make_shared<eTexture>();
        fLoadImage8->load(fRenderer, dir + "Poseidon_Load4.jpg");

        fLoadImage9 = std::make_shared<eTexture>();
        fLoadImage9->load(fRenderer, dir + "Poseidon_Load5.jpg");

        fLoadImage10 = std::make_shared<eTexture>();
        fLoadImage10->load(fRenderer, dir + "Poseidon_Load6.jpg");

        fLoadImage11 = std::make_shared<eTexture>();
        fLoadImage11->load(fRenderer, dir + "Poseidon_Load7.jpg");

        fLoadImage12 = std::make_shared<eTexture>();
        fLoadImage12->load(fRenderer, dir + "Poseidon_Load8.jpg");

        fMainMenuImage = std::make_shared<eTexture>();
        fMainMenuImage->load(fRenderer, dir + "Zeus_FE_Registry.jpg");

        fMapOfGreece = std::make_shared<eTexture>();
        fMapOfGreece->load(fRenderer, dir + "Zeus_MapOfGreece08.JPG");
    }

    {
        const auto dir = basedir + "/Poseidon_Loaded/";
        const auto pathBase = dir + "Poseidon_Storage_";
        fOrangesUnit = std::make_shared<eTexture>();
        fOrangesUnit->load(fRenderer, pathBase + "00114.png");

        fAtlasQuestIcon = std::make_shared<eTexture>();
        fAtlasQuestIcon->load(fRenderer, pathBase + "00129.png");

        fHeraQuestIcon = std::make_shared<eTexture>();
        fHeraQuestIcon->load(fRenderer, pathBase + "00130.png");
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eStor_baysSpriteData15,
                                     eStor_baysSpriteData30,
                                     eStor_baysSpriteData45,
                                     eStor_baysSpriteData60);
        eSpriteLoader loader(fTileH, "stor_bays", sds,
                             nullptr, fRenderer);

        fUrchinUnit = loader.load(1, 117);
        fFishUnit = loader.load(1, 118);
        fMeatUnit = loader.load(1, 119);
        fCheeseUnit = loader.load(1, 120);
        fCarrotsUnit = loader.load(1, 121);
        fOnionsUnit = loader.load(1, 122);
        fWheatUnit = loader.load(1, 123);

        fWoodUnit = loader.load(1, 124);
        fBronzeUnit = loader.load(1, 125);
        fMarbleUnit = loader.load(1, 126);
        fGrapesUnit = loader.load(1, 127);
        fOlivesUnit = loader.load(1, 128);
        fFleeceUnit = loader.load(1, 129);
        fHorseUnit = loader.load(1, 130);
        fArmsUnit = loader.load(1, 131);
        fSculptureUnit = loader.load(1, 132);
        fOliveOilUnit = loader.load(1, 133);
        fWineUnit = loader.load(1, 134);
        fFoodUnit = loader.load(1, 135);

        fSuppliesBg = loader.load(1, 137);
        fEliteSuppliesBg = loader.load(1, 139);

        fHasFood = loader.load(1, 155);
        fHasFleece = loader.load(1, 153);
        fHasOil = loader.load(1, 156);
        fHasWine = loader.load(1, 157);
        fHasArms = loader.load(1, 154);
        fHasHorses = loader.load(1, 158);

        fNHasFood = loader.load(1, 161);
        fNHasFleece = loader.load(1, 159);
        fNHasOil = loader.load(1, 162);
        fNHasWine = loader.load(1, 163);
        fNHasArms = loader.load(1, 160);
        fNHasHorses = loader.load(1, 164);

        fZeusQuestIcon = loader.load(1, 171);
        fPoseidonQuestIcon = loader.load(1, 172);
        fDemeterQuestIcon = loader.load(1, 173);
        fApolloQuestIcon = loader.load(1, 174);
        fArtemisQuestIcon = loader.load(1, 175);
        fAresQuestIcon = loader.load(1, 176);
        fAphroditeQuestIcon = loader.load(1, 177);
        fHermesQuestIcon = loader.load(1, 178);
        fAthenaQuestIcon = loader.load(1, 179);
        fHephaestusQuestIcon = loader.load(1, 180);
        fDionysusQuestIcon = loader.load(1, 181);
        fHadesQuestIcon = loader.load(1, 182);

        fDrachmasUnit = loader.load(1, 184);
        fDrachmasTopMenu = loader.load(1, 185);
        fPopulationTopMenu = loader.load(1, 186);
    }
}

void eInterfaceTextures::loadInterfaceBanners() {
    if(fInterfaceBannersLoaded) return;
    fInterfaceBannersLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eInterfaceBannersSpriteData15,
                                 eInterfaceBannersSpriteData30,
                                 eInterfaceBannersSpriteData45,
                                 eInterfaceBannersSpriteData60);
    eSpriteLoader loader(fTileH, "interfaceBanners", sds,
                         nullptr, fRenderer);

    for(int i = 147; i < 167; i++) {
        loader.load(147, i, fInterfaceBanners);
    }

    for(int i = 167; i < 184; i++) {
        loader.load(147, i, fInterfaceBannerTops);
    }
}
