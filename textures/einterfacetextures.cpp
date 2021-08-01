#include "einterfacetextures.h"

#include "etextureloadinghelpers.h"

eInterfaceTextures::eInterfaceTextures(const int tileW, const int tileH,
                                       SDL_Renderer* const renderer):
    fTileW(tileW), fTileH(tileH),
    fRenderer(renderer),

    fPopulationTexture(renderer),
    fHusbandryTexture(renderer),
    fIndustryTexture(renderer),
    fDistributionTexture(renderer),
    fHygieneSafetyTexture(renderer),
    fAdministrationTexture(renderer),
    fCultureTexture(renderer),
    fMythologyTexture(renderer),
    fMilitaryTexture(renderer),
    fAestheticsTexture(renderer),
    fOverviewTexture(renderer),

    fCommonHousingTexture(renderer),
    fEliteHousingTexture(renderer),

    fFoodFarmingTexture(renderer),
    fOtherFarmingTexture(renderer),
    fAnimalFarmingTexture(renderer),
    fAnimalHuntingTexture(renderer),

    fResourcesTexture(renderer),
    fProcessingTexture(renderer),
    fBuildersGuildTexture(renderer),

    fGranaryTexture(renderer),
    fWarehouseTexture(renderer),
    fAgorasTexture(renderer),
    fTradeTexture(renderer),

    fFireFighterTexture(renderer),
    fFountainTexture(renderer),
    fPoliceTexture(renderer),
    fHospitalTexture(renderer),

    fPalaceTexture(renderer),
    fTaxCollectorTexture(renderer),
    fBridgeTexture(renderer),

    fPhilosophyTexture(renderer),
    fGymnasiumTexture(renderer),
    fDramaTexture(renderer),
    fStadiumTexture(renderer),

    fTemplesTexture(renderer),
    fHeroShrinesTexture(renderer),

    fFortificationsTexture(renderer),
    fMilitaryProductionTexture(renderer),

    fBeautificationTexture(renderer),
    fRecreationTexture(renderer),
    fMonumentTexture(renderer),

    fBuildRoadTexture(renderer),
    fClearTexture(renderer) {

}

void eInterfaceTextures::load() {
    std::string dir{"../ZeusTextures/"};
    dir += std::to_string(fTileH) + "/";
    dir += "Zeus_Interface/";

    {
        const std::string pathBase{dir + "Zeus_Interface_New_Bbuttons_"};

        for(int i = 4; i < 7; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fCommonHousingTexture);
        }

        for(int i = 7; i < 10; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fEliteHousingTexture);
        }

        for(int i = 10; i < 13; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fFoodFarmingTexture);
        }

        for(int i = 13; i < 16; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fOtherFarmingTexture);
        }

        for(int i = 16; i < 19; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fAnimalFarmingTexture);
        }

        for(int i = 19; i < 22; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fAnimalHuntingTexture);
        }

        for(int i = 22; i < 25; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fResourcesTexture);
        }

        for(int i = 25; i < 28; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fProcessingTexture);
        }

        for(int i = 28; i < 31; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fBuildersGuildTexture);
        }

        for(int i = 31; i < 34; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fGranaryTexture);
        }

        for(int i = 34; i < 37; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWarehouseTexture);
        }

        for(int i = 37; i < 40; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fAgorasTexture);
        }

        for(int i = 40; i < 43; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fTradeTexture);
        }

        for(int i = 43; i < 46; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fFireFighterTexture);
        }

        for(int i = 46; i < 49; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fFountainTexture);
        }

        for(int i = 49; i < 52; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fPoliceTexture);
        }

        for(int i = 52; i < 55; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fHospitalTexture);
        }

        for(int i = 55; i < 58; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fPalaceTexture);
        }

        for(int i = 58; i < 61; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fTaxCollectorTexture);
        }

        for(int i = 61; i < 64; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fBridgeTexture);
        }

        for(int i = 67; i < 70; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fPhilosophyTexture);
        }

        for(int i = 70; i < 73; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fGymnasiumTexture);
        }

        for(int i = 73; i < 76; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fDramaTexture);
        }

        for(int i = 76; i < 79; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fStadiumTexture);
        }

        for(int i = 79; i < 82; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fTemplesTexture);
        }

        for(int i = 82; i < 85; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fHeroShrinesTexture);
        }

        for(int i = 85; i < 88; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fFortificationsTexture);
        }

        for(int i = 88; i < 91; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fMilitaryProductionTexture);
        }

        for(int i = 91; i < 94; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fBeautificationTexture);
        }

        for(int i = 94; i < 97; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fRecreationTexture);
        }

        for(int i = 97; i < 100; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fMonumentTexture);
        }
    }

    {
        const std::string pathBase{dir + "Zeus_Interface_New_parts_"};

        for(int i = 45; i < 49; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fBuildRoadTexture);
        }

        for(int i = 53; i < 57; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fClearTexture);
        }

        for(int i = 89; i < 93; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fOverviewTexture);
        }

        for(int i = 93; i < 97; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fPopulationTexture);
        }

        for(int i = 97; i < 101; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fHusbandryTexture);
        }

        for(int i = 101; i < 105; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fIndustryTexture);
        }

        for(int i = 105; i < 109; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fDistributionTexture);
        }

        for(int i = 109; i < 113; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fHygieneSafetyTexture);
        }

        for(int i = 113; i < 117; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fAdministrationTexture);
        }

        for(int i = 117; i < 121; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fCultureTexture);
        }

        for(int i = 121; i < 125; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fMythologyTexture);
        }

        for(int i = 125; i < 129; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fMilitaryTexture);
        }

        for(int i = 129; i < 133; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fAestheticsTexture);
        }
    }
}
