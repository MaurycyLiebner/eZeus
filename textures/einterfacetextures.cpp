#include "einterfacetextures.h"

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

#include "spriteData/interfaceNewBbuttons15.h"
#include "spriteData/interfaceNewBbuttons30.h"
#include "spriteData/interfaceNewBbuttons45.h"
#include "spriteData/interfaceNewBbuttons60.h"

#include "spriteData/interfaceNewParts15.h"
#include "spriteData/interfaceNewParts30.h"
#include "spriteData/interfaceNewParts45.h"
#include "spriteData/interfaceNewParts60.h"

#include "spriteData/interfaceParts15.h"
#include "spriteData/interfaceParts30.h"
#include "spriteData/interfaceParts45.h"
#include "spriteData/interfaceParts60.h"

#include "spriteData/interfaceWorldSide15.h"
#include "spriteData/interfaceWorldSide30.h"
#include "spriteData/interfaceWorldSide45.h"
#include "spriteData/interfaceWorldSide60.h"

#include "spriteData/interfaceMapEditor15.h"
#include "spriteData/interfaceMapEditor30.h"
#include "spriteData/interfaceMapEditor45.h"
#include "spriteData/interfaceMapEditor60.h"

#include "spriteData/poseidonUnits15.h"
#include "spriteData/poseidonUnits30.h"
#include "spriteData/poseidonUnits45.h"
#include "spriteData/poseidonUnits60.h"

#include "spriteData/poseidonQuestButtons15.h"
#include "spriteData/poseidonQuestButtons30.h"
#include "spriteData/poseidonQuestButtons45.h"
#include "spriteData/poseidonQuestButtons60.h"

#include "spriteData/interfaceRadar15.h"
#include "spriteData/interfaceRadar30.h"
#include "spriteData/interfaceRadar45.h"
#include "spriteData/interfaceRadar60.h"

#include "spriteData/poseidonCampaign115.h"
#include "spriteData/poseidonCampaign130.h"
#include "spriteData/poseidonCampaign145.h"
#include "spriteData/poseidonCampaign160.h"

#include "spriteData/poseidonCampaign215.h"
#include "spriteData/poseidonCampaign230.h"
#include "spriteData/poseidonCampaign245.h"
#include "spriteData/poseidonCampaign260.h"

#include "spriteData/poseidonCampaign315.h"
#include "spriteData/poseidonCampaign330.h"
#include "spriteData/poseidonCampaign345.h"
#include "spriteData/poseidonCampaign360.h"

#include "spriteData/poseidonCampaign415.h"
#include "spriteData/poseidonCampaign430.h"
#include "spriteData/poseidonCampaign445.h"
#include "spriteData/poseidonCampaign460.h"

#include "spriteData/poseidonCampaign515.h"
#include "spriteData/poseidonCampaign530.h"
#include "spriteData/poseidonCampaign545.h"
#include "spriteData/poseidonCampaign560.h"

#include "spriteData/poseidonCampaign615.h"
#include "spriteData/poseidonCampaign630.h"
#include "spriteData/poseidonCampaign645.h"
#include "spriteData/poseidonCampaign660.h"

#include "espriteloader.h"

#include "egamedir.h"

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
    fScience(renderer),
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

    fPoseidonCommonHousing(renderer),
    fPoseidonEliteHousing(renderer),

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

    fPoseidonBridge(renderer),

    fPhilosophy(renderer),
    fGymnasium(renderer),
    fDrama(renderer),
    fStadium(renderer),

    fBibliotheke(renderer),
    fAstronomy(renderer),
    fTechnology(renderer),
    fMuseum(renderer),

    fTemples(renderer),
    fHeroShrines(renderer),

    fPoseidonTemples(renderer),
    fPoseidonHeroShrines(renderer),

    fPiramids(renderer),
    fHipodrome(renderer),

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
    fMoreInfo(renderer),

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

    fMilitaryControlManual(renderer),
    fMilitaryControlAutomatic(renderer),

    fBuildingButton(renderer),
    fBuildingButtonHover(renderer),

    fCheckBox(renderer),
    fLargeCheckBox(renderer),

    fRequestWaitingBox(renderer),
    fRequestFulfilledBox(renderer),

    fSeeButton(renderer),

    fSmallUpButton(renderer),
    fSmallDownButton(renderer),

    fUpButton(renderer),
    fDownButton(renderer),

    fBigUpButton(renderer),
    fBigDownButton(renderer),

    fExclamationButton(renderer),
    fProceedButton(renderer),
    fOkButton(renderer),
    fHelpButton(renderer),

    fAcceptButton(renderer),
    fCancelButton(renderer),

    fButtonFrame(renderer),
    fButtonFrameHover(renderer),

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
    fInterfaceBannerTops(renderer),
    fPoseidonInterfaceBannerTops(renderer) {}

void eInterfaceTextures::load() {
    if(fLoaded) return;
    fLoaded = true;

    {
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

    {
        const auto& sds = spriteData(fTileH,
                                     eInterfaceNewBbuttonsSpriteData15,
                                     eInterfaceNewBbuttonsSpriteData30,
                                     eInterfaceNewBbuttonsSpriteData45,
                                     eInterfaceNewBbuttonsSpriteData60);
        eSpriteLoader loader(fTileH, "interfaceNewBbuttons", sds,
                             nullptr, fRenderer);
        for(int i = 4; i < 7; i++) {
            loader.load(1, i, fCommonHousing);
        }

        for(int i = 7; i < 10; i++) {
            loader.load(1, i, fEliteHousing);
        }

        for(int i = 10; i < 13; i++) {
            loader.load(1, i, fFoodFarming);
        }

        for(int i = 13; i < 16; i++) {
            loader.load(1, i, fOtherFarming);
        }

        for(int i = 16; i < 19; i++) {
            loader.load(1, i, fAnimalFarming);
        }

        for(int i = 19; i < 22; i++) {
            loader.load(1, i, fAnimalHunting);
        }

        for(int i = 22; i < 25; i++) {
            loader.load(1, i, fResources);
        }

        for(int i = 25; i < 28; i++) {
            loader.load(1, i, fProcessing);
        }

        for(int i = 28; i < 31; i++) {
            loader.load(1, i, fArtisansGuild);
        }

        for(int i = 31; i < 34; i++) {
            loader.load(1, i, fGranary);
        }

        for(int i = 34; i < 37; i++) {
            loader.load(1, i, fWarehouse);
        }

        for(int i = 37; i < 40; i++) {
            loader.load(1, i, fAgoras);
        }

        for(int i = 40; i < 43; i++) {
            loader.load(1, i, fTrade);
        }

        for(int i = 43; i < 46; i++) {
            loader.load(1, i, fFireFighter);
        }

        for(int i = 46; i < 49; i++) {
            loader.load(1, i, fFountain);
        }

        for(int i = 49; i < 52; i++) {
            loader.load(1, i, fPolice);
        }

        for(int i = 52; i < 55; i++) {
            loader.load(1, i, fHospital);
        }

        for(int i = 55; i < 58; i++) {
            loader.load(1, i, fPalace);
        }

        for(int i = 58; i < 61; i++) {
            loader.load(1, i, fTaxCollector);
        }

        for(int i = 61; i < 64; i++) {
            loader.load(1, i, fBridge);
        }

        for(int i = 67; i < 70; i++) {
            loader.load(1, i, fPhilosophy);
        }

        for(int i = 70; i < 73; i++) {
            loader.load(1, i, fGymnasium);
        }

        for(int i = 73; i < 76; i++) {
            loader.load(1, i, fDrama);
        }

        for(int i = 76; i < 79; i++) {
            loader.load(1, i, fStadium);
        }

        for(int i = 79; i < 82; i++) {
            loader.load(1, i, fTemples);
        }

        for(int i = 82; i < 85; i++) {
            loader.load(1, i, fHeroShrines);
        }

        for(int i = 85; i < 88; i++) {
            loader.load(1, i, fFortifications);
        }

        for(int i = 88; i < 91; i++) {
            loader.load(1, i, fMilitaryProduction);
        }

        for(int i = 91; i < 94; i++) {
            loader.load(1, i, fBeautification);
        }

        for(int i = 94; i < 97; i++) {
            loader.load(1, i, fRecreation);
        }

        for(int i = 97; i < 100; i++) {
            loader.load(1, i, fMonuments);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eInterfacePartsSpriteData15,
                                     eInterfacePartsSpriteData30,
                                     eInterfacePartsSpriteData45,
                                     eInterfacePartsSpriteData60);
        eSpriteLoader loader(fTileH, "interfaceParts", sds,
                             nullptr, fRenderer);
        fArmyStatus = loader.load(1, 2);

        for(int i = 11; i < 15; i++) {
            loader.load(1, i, fGoToCompany);
        }

        for(int i = 15; i < 19; i++) {
            loader.load(1, i, fRotateCompany);
        }

        for(int i = 19; i < 23; i++) {
            loader.load(1, i, fGoToBanner);
        }

        for(int i = 23; i < 27; i++) {
            loader.load(1, i, fGoHome);
        }

        for(int i = 27; i < 31; i++) {
            loader.load(1, i, fDefensiveTactics);
        }

        for(int i = 31; i < 35; i++) {
            loader.load(1, i, fOffensiveTactics);
        }

        for(int i = 35; i < 39; i++) {
            loader.load(1, i, fSpecialTactics);
        }
    }
    {
        const auto& sds = spriteData(fTileH,
                                     eInterfaceNewPartsSpriteData15,
                                     eInterfaceNewPartsSpriteData30,
                                     eInterfaceNewPartsSpriteData45,
                                     eInterfaceNewPartsSpriteData60);
        eSpriteLoader loader(fTileH, "interfaceNewParts", sds,
                             nullptr, fRenderer);

        fGameTopBar = loader.load(1, 1);
        fGameMenuBackground = loader.load(1, 2);
        fGameArmyBackground = loader.load(1, 3);

        for(int i = 5; i < 37; i++) {
            loader.load(1, i, fRotation);
        }

        loader.load(1, 40, fLargeCheckBox);
        loader.load(1, 37, fLargeCheckBox);

        for(int i = 37; i < 41; i++) {
            loader.load(1, i, fGoals);
        }

        for(int i = 41; i < 45; i++) {
            loader.load(1, i, fWorld);
        }

        for(int i = 45; i < 49; i++) {
            loader.load(1, i, fBuildRoad);
        }

        for(int i = 49; i < 53; i++) {
            loader.load(1, i, fRoadBlock);
        }

        for(int i = 53; i < 57; i++) {
            loader.load(1, i, fClear);
        }

        for(int i = 57; i < 61; i++) {
            loader.load(1, i, fUndo);
        }

        for(int i = 61; i < 65; i++) {
            loader.load(1, i, fMessages);
        }

        for(int i = 65; i < 69; i++) {
            loader.load(1, i, fMoreInfo);
        }

        for(int i = 89; i < 93; i++) {
            loader.load(1, i, fOverview);
        }

        for(int i = 93; i < 97; i++) {
            loader.load(1, i, fPopulation);
        }

        for(int i = 97; i < 101; i++) {
            loader.load(1, i, fHusbandry);
        }

        for(int i = 101; i < 105; i++) {
            loader.load(1, i, fIndustry);
        }

        for(int i = 105; i < 109; i++) {
            loader.load(1, i, fDistribution);
        }

        for(int i = 109; i < 113; i++) {
            loader.load(1, i, fHygieneSafety);
        }

        for(int i = 113; i < 117; i++) {
            loader.load(1, i, fAdministration);
        }

        for(int i = 117; i < 121; i++) {
            loader.load(1, i, fCulture);
        }

        for(int i = 121; i < 125; i++) {
            loader.load(1, i, fMythology);
        }

        for(int i = 125; i < 129; i++) {
            loader.load(1, i, fMilitary);
        }

        for(int i = 129; i < 133; i++) {
            loader.load(1, i, fAesthetics);
        }

        for(int i = 137; i < 140; i++) {
            loader.load(1, i, fSeeButton);
        }

        fSoldiersIcon = loader.load(1, 173);
        fShipsIcon = loader.load(1, 174);
        fTowersIcon = loader.load(1, 175);

        for(int i = 184; i < 187; i++) {
            loader.load(1, i, fFireAlert);
        }
        for(int i = 187; i < 190; i++) {
            loader.load(1, i, fGroundFissureAlert);
        }
        for(int i = 190; i < 193; i++) {
            loader.load(1, i, fFloodAlert);
        }
        for(int i = 193; i < 196; i++) {
            loader.load(1, i, fAvalancheAltert);
        }
        for(int i = 196; i < 199; i++) {
            loader.load(1, i, fLavaAltert);
        }
        for(int i = 199; i < 202; i++) {
            loader.load(1, i, fCollapseAltert);
        }
        for(int i = 202; i < 205; i++) {
            loader.load(1, i, fRoadBlockAltert);
        }
        for(int i = 205; i < 208; i++) {
            loader.load(1, i, fVirusAlert);
        }
        for(int i = 208; i < 211; i++) {
            loader.load(1, i, fIllnessAlert);
        }
        for(int i = 211; i < 214; i++) {
            loader.load(1, i, fInvasionAlert);
        }
        for(int i = 214; i < 217; i++) {
            loader.load(1, i, fMonsterAltert);
        }
        for(int i = 217; i < 220; i++) {
            loader.load(1, i, fGodAttackAlert);
        }
        for(int i = 220; i < 223; i++) {
            loader.load(1, i, fGodVisitAlert);
        }
        for(int i = 223; i < 226; i++) {
            loader.load(1, i, fHeroArrivalAlert);
        }
        for(int i = 226; i < 229; i++) {
            loader.load(1, i, fArmyComebackAlert);
        }

        for(int i = 230; i < 242;) {
            auto& coll = fMicroButton.emplace_back(fRenderer);
            for(int j = 0; j < 4; j++, i++) {
                loader.load(1, i, coll);
            }
        }

        for(int i = 248; i < 252; i++) {
            loader.load(1, i, fMilitaryControlManual);
        }

        for(int i = 252; i < 256; i++) {
            loader.load(1, i, fMilitaryControlAutomatic);
        }

        for(int i = 263; i < 267; i++) {
            loader.load(1, i, fShowInfo);
        }

        for(int i = 267; i < 271; i++) {
            loader.load(1, i, fShowMap);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eInterfaceWorldSideSpriteData15,
                                     eInterfaceWorldSideSpriteData30,
                                     eInterfaceWorldSideSpriteData45,
                                     eInterfaceWorldSideSpriteData60);
        eSpriteLoader loader(fTileH, "interfaceWorldSide", sds,
                             nullptr, fRenderer);
        fWorldMenuBackground = loader.load(1, 1);

        loader.load(1, 40, fLargeCheckBox);
        loader.load(1, 37, fLargeCheckBox);

        for(int i = 2; i < 6; i++) {
            loader.load(1, i, fWorldSmallButton);
        }
        for(int i = 6; i < 10; i++) {
            loader.load(1, i, fWorldBigButton);
        }
        for(int i = 10; i < 14; i++) {
            loader.load(1, i, fRequestButton);
        }
        for(int i = 14; i < 18; i++) {
            loader.load(1, i, fFulfillButton);
        }
        for(int i = 18; i < 22; i++) {
            loader.load(1, i, fGiftButton);
        }
        for(int i = 22; i < 26; i++) {
            loader.load(1, i, fRaidButton);
        }
        for(int i = 26; i < 30; i++) {
            loader.load(1, i, fConquerButton);
        }

        for(int i = 30; i < 34; i++) {
            loader.load(1, i, fWorldLeftArrowButton);
        }
        for(int i = 34; i < 38; i++) {
            loader.load(1, i, fWorldRightArrowButton);
        }
        for(int i = 38; i < 42; i++) {
            loader.load(1, i, fWorldHistoryButton);
        }

        for(int i = 42; i < 46; i++) {
            loader.load(1, i, fWorldBgsButton);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eInterfaceMapEditorSpriteData15,
                                     eInterfaceMapEditorSpriteData30,
                                     eInterfaceMapEditorSpriteData45,
                                     eInterfaceMapEditorSpriteData60);
        eSpriteLoader loader(fTileH, "interfaceMapEditor", sds,
                             nullptr, fRenderer);

        fMapEditMenuBackground = loader.load(1, 1);

        for(int i = 2; i < 6; i++) {
            loader.load(1, i, fBrushSize);
        }
        for(int i = 6; i < 10; i++) {
            loader.load(1, i, fEmptyLand);
        }
        for(int i = 10; i < 14; i++) {
            loader.load(1, i, fForest);
        }
        for(int i = 14; i < 18; i++) {
            loader.load(1, i, fWaterMarshBeach);
        }
        for(int i = 18; i < 22; i++) {
            loader.load(1, i, fMeadow);
        }
        for(int i = 22; i < 26; i++) {
            loader.load(1, i, fFishAndUrchin);
        }
        for(int i = 26; i < 30; i++) {
            loader.load(1, i, fRocks);
        }
        for(int i = 30; i < 34; i++) {
            loader.load(1, i, fScrub);
        }
        for(int i = 34; i < 38; i++) {
            loader.load(1, i, fElevation);
        }
        for(int i = 38; i < 42; i++) {
            loader.load(1, i, fDisasters);
        }
        for(int i = 42; i < 46; i++) {
            loader.load(1, i, fWaterPoints);
        }
        for(int i = 46; i < 50; i++) {
            loader.load(1, i, fLandInvasionPoints);
        }
        for(int i = 50; i < 54; i++) {
            loader.load(1, i, fExitEndEntryPoints);
        }
        for(int i = 54; i < 58; i++) {
            loader.load(1, i, fAnimalPoints);
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

        for(int i = 1; i < 4; i++) {
            loader.load(1, i, fBibliotheke);
        }
        for(int i = 4; i < 7; i++) {
            loader.load(1, i, fAstronomy);
        }
        for(int i = 7; i < 10; i++) {
            loader.load(1, i, fTechnology);
        }
        for(int i = 10; i < 13; i++) {
            loader.load(1, i, fMuseum);
        }

        for(int i = 13; i < 16; i++) {
            loader.load(1, i, fPoseidonTemples);
        }
        for(int i = 16; i < 19; i++) {
            loader.load(1, i, fPoseidonHeroShrines);
        }

        for(int i = 19; i < 22; i++) {
            loader.load(1, i, fPiramids);
        }
        for(int i = 22; i < 25; i++) {
            loader.load(1, i, fHipodrome);
        }
        for(int i = 25; i < 28; i++) {
            loader.load(1, i, fPoseidonBridge);
        }

        for(int i = 28; i < 31; i++) {
            loader.load(1, i, fPoseidonCommonHousing);
        }
        for(int i = 31; i < 34; i++) {
            loader.load(1, i, fPoseidonEliteHousing);
        }

        for(int i = 34; i < 38; i++) {
            loader.load(1, i, fScience);
        }

        for(int i = 38; i < 41; i++) {
            loader.load(1, i, fPoseidonInterfaceBannerTops);
        }

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

//        fDeerPoint = loader.load(1, 57);

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

        for(int i = 68; i < 72; i++) {
            loader.load(1, i, fProceedButton);
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

        for(int i = 376; i < 378; i++) {
            loader.load(1, i, fSmallUpButton);
        }
        for(int i = 378; i < 380; i++) {
            loader.load(1, i, fSmallDownButton);
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
        const auto& sds = spriteData(fTileH,
                                     eInterfaceRadarSpriteData15,
                                     eInterfaceRadarSpriteData30,
                                     eInterfaceRadarSpriteData45,
                                     eInterfaceRadarSpriteData60);
        eSpriteLoader loader(fTileH, "interfaceRadar", sds,
                             nullptr, fRenderer);

        for(int i = 262; i < 267; i++) {
            loader.load(262, i, fDiamond);
        }
    }

    {
        const std::string basedir{eGameDir::exeDir() + "../ZeusTextures/" + std::to_string(fTileH) + "/"};
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

        fIntroductionImage = std::make_shared<eTexture>();
        fIntroductionImage->load(fRenderer, dir + "Zeus_FE_MissionIntroduction.jpg");

        fDefeatImage = std::make_shared<eTexture>();
        fDefeatImage->load(fRenderer, dir + "Zeus_Defeat.jpg");
    }

    {
        const auto& sds = spriteData(fTileH,
                                     ePoseidonUnitsSpriteData15,
                                     ePoseidonUnitsSpriteData30,
                                     ePoseidonUnitsSpriteData45,
                                     ePoseidonUnitsSpriteData60);
        eSpriteLoader loader(fTileH, "poseidonUnits", sds,
                             nullptr, fRenderer);

        fOrangesUnit = loader.load(114, 114);
        fChariotUnit = loader.load(114, 117);
    }
    {
        const auto& sds = spriteData(fTileH,
                                     ePoseidonQuestButtonsSpriteData15,
                                     ePoseidonQuestButtonsSpriteData30,
                                     ePoseidonQuestButtonsSpriteData45,
                                     ePoseidonQuestButtonsSpriteData60);
        eSpriteLoader loader(fTileH, "poseidonQuestButtons", sds,
                             nullptr, fRenderer);

        fAtlasQuestIcon = loader.load(129, 129);
        fHeraQuestIcon = loader.load(129, 130);
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

        fTroopsRequestIcon = loader.load(1, 183);

        fDrachmasUnit = loader.load(1, 184);
        fDrachmasTopMenu = loader.load(1, 185);
        fPopulationTopMenu = loader.load(1, 186);
    }
}

std::string eInterfaceTextures::loadMapDirPath() const {
    const std::string basedir{eGameDir::exeDir() + "../ZeusTextures/" + std::to_string(fTileH) + "/"};
    const auto dir = basedir + "/Zeus_Data_Images/";
    return dir;
}

void eInterfaceTextures::loadMapOfGreece1() {
    if(fMapOfGreece1Loaded) return;
    fMapOfGreece1Loaded = true;
    const auto dir = loadMapDirPath();
    fMapOfGreece1 = std::make_shared<eTexture>();
    fMapOfGreece1->load(fRenderer, dir + "Zeus_MapOfGreece01.JPG");
}

void eInterfaceTextures::loadMapOfGreece2() {
    if(fMapOfGreece2Loaded) return;
    fMapOfGreece2Loaded = true;
    const auto dir = loadMapDirPath();
    fMapOfGreece2 = std::make_shared<eTexture>();
    fMapOfGreece2->load(fRenderer, dir + "Zeus_MapOfGreece02.JPG");
}

void eInterfaceTextures::loadMapOfGreece3() {
    if(fMapOfGreece3Loaded) return;
    fMapOfGreece3Loaded = true;
    const auto dir = loadMapDirPath();
    fMapOfGreece3 = std::make_shared<eTexture>();
    fMapOfGreece3->load(fRenderer, dir + "Zeus_MapOfGreece03.JPG");
}

void eInterfaceTextures::loadMapOfGreece4() {
    if(fMapOfGreece4Loaded) return;
    fMapOfGreece4Loaded = true;
    const auto dir = loadMapDirPath();
    fMapOfGreece4 = std::make_shared<eTexture>();
    fMapOfGreece4->load(fRenderer, dir + "Zeus_MapOfGreece04.JPG");
}

void eInterfaceTextures::loadMapOfGreece5() {
    if(fMapOfGreece5Loaded) return;
    fMapOfGreece5Loaded = true;
    const auto dir = loadMapDirPath();
    fMapOfGreece5 = std::make_shared<eTexture>();
    fMapOfGreece5->load(fRenderer, dir + "Zeus_MapOfGreece05.JPG");
}

void eInterfaceTextures::loadMapOfGreece6() {
    if(fMapOfGreece6Loaded) return;
    fMapOfGreece6Loaded = true;
    const auto dir = loadMapDirPath();
    fMapOfGreece6 = std::make_shared<eTexture>();
    fMapOfGreece6->load(fRenderer, dir + "Zeus_MapOfGreece06.JPG");
}

void eInterfaceTextures::loadMapOfGreece7() {
    if(fMapOfGreece7Loaded) return;
    fMapOfGreece7Loaded = true;
    const auto dir = loadMapDirPath();
    fMapOfGreece7 = std::make_shared<eTexture>();
    fMapOfGreece7->load(fRenderer, dir + "Zeus_MapOfGreece07.JPG");
}

void eInterfaceTextures::loadMapOfGreece8() {
    if(fMapOfGreece8Loaded) return;
    fMapOfGreece8Loaded = true;
    const auto dir = loadMapDirPath();
    fMapOfGreece8 = std::make_shared<eTexture>();
    fMapOfGreece8->load(fRenderer, dir + "Zeus_MapOfGreece08.JPG");
}

void eInterfaceTextures::loadPoseidonMap1() {
    if(fPoseidonMap1Loaded) return;
    fPoseidonMap1Loaded = true;
    const auto dir = loadMapDirPath();
    fPoseidonMap1 = std::make_shared<eTexture>();
    fPoseidonMap1->load(fRenderer, dir + "Poseidon_map01.jpg");
}

void eInterfaceTextures::loadPoseidonMap2() {
    if(fPoseidonMap2Loaded) return;
    fPoseidonMap2Loaded = true;
    const auto dir = loadMapDirPath();
    fPoseidonMap2 = std::make_shared<eTexture>();
    fPoseidonMap2->load(fRenderer, dir + "Poseidon_map02.jpg");
}

void eInterfaceTextures::loadPoseidonMap3() {
    if(fPoseidonMap3Loaded) return;
    fPoseidonMap3Loaded = true;
    const auto dir = loadMapDirPath();
    fPoseidonMap3 = std::make_shared<eTexture>();
    fPoseidonMap3->load(fRenderer, dir + "Poseidon_map03.jpg");
}

void eInterfaceTextures::loadPoseidonMap4() {
    if(fPoseidonMap4Loaded) return;
    fPoseidonMap4Loaded = true;
    const auto dir = loadMapDirPath();
    fPoseidonMap4 = std::make_shared<eTexture>();
    fPoseidonMap4->load(fRenderer, dir + "Poseidon_map04.jpg");
}

void eInterfaceTextures::loadPoseidonCampaign1() {
    if(fPoseidonCampaign1Loaded) return;
    fPoseidonCampaign1Loaded = true;
    const auto& sds = spriteData(fTileH,
                                 ePoseidonCampaign1SpriteData15,
                                 ePoseidonCampaign1SpriteData30,
                                 ePoseidonCampaign1SpriteData45,
                                 ePoseidonCampaign1SpriteData60);
    eSpriteLoader loader(fTileH, "poseidonCampaign1", sds,
                         nullptr, fRenderer);

    fPoseidonCampaign1 = loader.load(1, 1);
}

void eInterfaceTextures::loadPoseidonCampaign2() {
    if(fPoseidonCampaign2Loaded) return;
    fPoseidonCampaign2Loaded = true;
    const auto& sds = spriteData(fTileH,
                                 ePoseidonCampaign2SpriteData15,
                                 ePoseidonCampaign2SpriteData30,
                                 ePoseidonCampaign2SpriteData45,
                                 ePoseidonCampaign2SpriteData60);
    eSpriteLoader loader(fTileH, "poseidonCampaign2", sds,
                         nullptr, fRenderer);

    fPoseidonCampaign2 = loader.load(2, 2);
}

void eInterfaceTextures::loadPoseidonCampaign3() {
    if(fPoseidonCampaign3Loaded) return;
    fPoseidonCampaign3Loaded = true;
    const auto& sds = spriteData(fTileH,
                                 ePoseidonCampaign3SpriteData15,
                                 ePoseidonCampaign3SpriteData30,
                                 ePoseidonCampaign3SpriteData45,
                                 ePoseidonCampaign3SpriteData60);
    eSpriteLoader loader(fTileH, "poseidonCampaign3", sds,
                         nullptr, fRenderer);

    fPoseidonCampaign3 = loader.load(3, 3);
}

void eInterfaceTextures::loadPoseidonCampaign4() {
    if(fPoseidonCampaign4Loaded) return;
    fPoseidonCampaign4Loaded = true;
    const auto& sds = spriteData(fTileH,
                                 ePoseidonCampaign4SpriteData15,
                                 ePoseidonCampaign4SpriteData30,
                                 ePoseidonCampaign4SpriteData45,
                                 ePoseidonCampaign4SpriteData60);
    eSpriteLoader loader(fTileH, "poseidonCampaign4", sds,
                         nullptr, fRenderer);

    fPoseidonCampaign4 = loader.load(4, 4);
}

void eInterfaceTextures::loadPoseidonCampaign5() {
    if(fPoseidonCampaign5Loaded) return;
    fPoseidonCampaign5Loaded = true;
    const auto& sds = spriteData(fTileH,
                                 ePoseidonCampaign5SpriteData15,
                                 ePoseidonCampaign5SpriteData30,
                                 ePoseidonCampaign5SpriteData45,
                                 ePoseidonCampaign5SpriteData60);
    eSpriteLoader loader(fTileH, "poseidonCampaign5", sds,
                         nullptr, fRenderer);

    fPoseidonCampaign5 = loader.load(5, 5);
}

void eInterfaceTextures::loadPoseidonCampaign6() {
    if(fPoseidonCampaign6Loaded) return;
    fPoseidonCampaign6Loaded = true;
    const auto& sds = spriteData(fTileH,
                                 ePoseidonCampaign6SpriteData15,
                                 ePoseidonCampaign6SpriteData30,
                                 ePoseidonCampaign6SpriteData45,
                                 ePoseidonCampaign6SpriteData60);
    eSpriteLoader loader(fTileH, "poseidonCampaign6", sds,
                         nullptr, fRenderer);

    fPoseidonCampaign6 = loader.load(6, 6);
}
