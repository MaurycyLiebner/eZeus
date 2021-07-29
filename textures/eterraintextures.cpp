#include "eterraintextures.h"

#include "etextureloadinghelpers.h"

eTerrainTextures::eTerrainTextures(const int tileW, const int tileH,
                                   SDL_Renderer* const renderer) :
    fTileW(tileW), fTileH(tileH),
    fRenderer(renderer),
    fDryTerrainTexs(renderer),
    fBeachTerrainTexs(renderer),
    fBeachToDryTerrainTexs(renderer),
    fWaterTerrainTexs(renderer),
    fFertileTerrainTexs(renderer),
    fFertileToDryTerrainTexs(renderer),
    fScrubTerrainTexs(renderer),
    fForestToScrubTerrainTexs(renderer),
    fForestTerrainTexs(renderer),
    fWaterToBeachToDryTerrainTexs(renderer),

    fFlatStonesTerrainTexs(renderer),
    fLargeFlatStonesTerrainTexs(renderer),
    fHugeFlatStonesTerrainTexs(renderer),

    fBronzeTerrainTexs(renderer),
    fLargeBronzeTerrainTexs(renderer),
    fHugeBronzeTerrainTexs(renderer),

    fSilverTerrainTexs(renderer),
    fLargeSilverTerrainTexs(renderer),
    fHugeSilverTerrainTexs(renderer),

    fTallStoneTerrainTexs(renderer),
    fLargeTallStoneTerrainTexs(renderer),
    fHugeTallStoneTerrainTexs(renderer),

    fTinyStones(renderer) {

}

void loadWaterToX(SDL_Renderer* const renderer,
                  int i0, const std::string& pathBase,
                  std::vector<eTextureCollection>& result) {
    int i = i0;
    for(; i < i0 + 32;) {
        eTextureCollection coll(renderer);
        for(int j = 0; j < 4; j++, i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, coll);
        }
        result.push_back(coll);
    }

    for(; i < i0 + 36;) {
        eTextureCollection coll(renderer);
        for(int j = 0; j < 2; j++, i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, coll);
        }
        result.push_back(coll);
    }

    for(; i < i0 + 72; i++) {
        eTextureCollection coll(renderer);
        eTextureLoadingHelpers::loadTex(pathBase, i, coll);
        result.push_back(coll);
    }
}

void loadStones(int i0, const std::string& pathBase,
                eTextureCollection& result,
                eTextureCollection& resultLarge,
                eTextureCollection& resultHuge) {
    int i = i0;
    for(; i < i0 + 8; i++) {
        eTextureLoadingHelpers::loadTex(pathBase, i, result);
    }

    for(; i < i0 + 11; i++) {
        eTextureLoadingHelpers::loadTex(pathBase, i, resultLarge);
    }

    for(; i < i0 + 14; i++) {
        eTextureLoadingHelpers::loadTex(pathBase, i, resultHuge);
    }
}

void eTerrainTextures::load() {
    std::string terrDir{"../ZeusTextures/"};
    terrDir += std::to_string(fTileH) + "/";
    terrDir += "Zeus_Terrain/";

    {
        const std::string pathBase{terrDir + "Zeus_land1_"};

        for(int i = 2; i < 38;) {
            eTextureCollection coll(fRenderer);
            for(int j = 0; j < 12; j++, i++) {
                eTextureLoadingHelpers::loadTex(pathBase, i, coll);
            }
            fDryToScrubTerrainTexs.push_back(coll);
        }

        for(int i = 38; i < 50; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fScrubTerrainTexs);
        }

        for(int i = 62; i < 74; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fScrubTerrainTexs);
        }

        {
            eTextureCollection coll(fRenderer);
            for(int i = 74; i < 86; i++) {
                eTextureLoadingHelpers::loadTex(pathBase, i, coll);
            }
            fForestToDryTerrainTexs.push_back(coll);
        }

        for(int i = 86; i < 106; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fForestTerrainTexs);
        }

        for(int i = 106; i < 164; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fDryTerrainTexs);
        }

        for(int i = 164; i < 172; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWaterTerrainTexs);
        }

        loadWaterToX(fRenderer, 172, pathBase, fWaterToDryTerrainTexs);

        loadStones(334, pathBase, fFlatStonesTerrainTexs,
                   fLargeFlatStonesTerrainTexs, fHugeFlatStonesTerrainTexs);
        loadStones(348, pathBase, fBronzeTerrainTexs,
                   fLargeBronzeTerrainTexs, fHugeBronzeTerrainTexs);
        loadStones(363, pathBase, fSilverTerrainTexs,
                   fLargeSilverTerrainTexs, fHugeSilverTerrainTexs);
        loadStones(377, pathBase, fTallStoneTerrainTexs,
                   fLargeTallStoneTerrainTexs, fHugeTallStoneTerrainTexs);
    }

    {
        const std::string pathBase{terrDir + "Zeus_Overlay_"};

        for(int i = 21; i < 29; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fTinyStones);
        }
    }

    {
        const std::string pathBase{terrDir + "Zeus_Land3_"};

        fSelectedTex.load(fRenderer, pathBase + "00007.png");
        fInvalidTex.load(fRenderer, pathBase + "00007.png");

        loadWaterToX(fRenderer, 9, pathBase, fWaterToBeachTerrainTexs);

        for(int i = 189; i < 195; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fBeachTerrainTexs);
        }

        for(int i = 195; i < 207; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fBeachToDryTerrainTexs);
        }

        for(int i = 207; i < 231; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fWaterToBeachToDryTerrainTexs);
        }
    }

    {
        const std::string pathBase{terrDir + "Zeus_Trees_"};

        {
            eTextureCollection coll(fRenderer);
            for(int i = 1; i < 13; i++) {
                eTextureLoadingHelpers::loadTex(pathBase, i, coll);
            }
            fForestToDryTerrainTexs.push_back(coll);
        }

        for(int i = 13; i < 33; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fForestTerrainTexs);
        }

        for(int i = 33; i < 45; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fForestToScrubTerrainTexs);
        }

        for(int i = 45; i < 97; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fForestTerrainTexs);
        }

        for(int i = 121; i < 157;) {
            eTextureCollection coll(fRenderer);
            for(int j = 0; j < 12; j++, i++) {
                eTextureLoadingHelpers::loadTex(pathBase, i, coll);
            }
            fFertileToScrubTerrainTexs.push_back(coll);
        }

        for(int i = 157; i < 165; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fFertileTerrainTexs);
        }
        for(int i = 173; i < 181; i++) {
            eTextureLoadingHelpers::loadTex(pathBase, i, fFertileToDryTerrainTexs);
        }
    }
}
