#include "eterraintextures.h"

#include "etextureloadinghelpers.h"

#include "etextureloader.h"

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
    fChoppedForestToScrubTerrainTexs(renderer),
    fChoppedForestTerrainTexs(renderer),
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

    fTinyStones(renderer),

    fFlatMarble(renderer),
    fDryToMarble(renderer),
    fMarble(renderer),

    fBuildingBase2(renderer),
    fBuildingBase3(renderer),

    fElevation(renderer) {

}

void loadWaterToX(SDL_Renderer* const renderer, int i0,
                  std::vector<eTextureCollection>& result,
                  eTextureClass& texClass) {
    int i = i0;
    for(; i < i0 + 32;) {
        eTextureCollection coll(renderer);
        for(int j = 0; j < 4; j++, i++) {
            texClass.load(i, coll);
        }
        result.push_back(coll);
    }

    for(; i < i0 + 36;) {
        eTextureCollection coll(renderer);
        for(int j = 0; j < 2; j++, i++) {
            texClass.load(i, coll);
        }
        result.push_back(coll);
    }

    for(; i < i0 + 72; i++) {
        eTextureCollection coll(renderer);
        texClass.load(i, coll);
        result.push_back(coll);
    }
}

void loadStones(int i0, eTextureCollection& result,
                eTextureCollection& resultLarge,
                eTextureCollection& resultHuge,
                eTextureClass& texClass) {
    int i = i0;
    for(; i < i0 + 8; i++) {
        texClass.load(i, result);
    }

    for(; i < i0 + 12; i++) {
        texClass.load(i, resultLarge);
    }

    for(; i < i0 + 14; i++) {
        texClass.load(i, resultHuge);
    }
}

void eTerrainTextures::load() {
    eTextureLoader texLoader(fRenderer);
    texLoader.initialize();

    std::string terrDir{"../ZeusTextures/"};
    terrDir += std::to_string(fTileH) + "/";
    terrDir += "Zeus_Terrain/";

    {
        const std::string pathBase{terrDir + "Zeus_land1_"};
        eTextureClass texClass(pathBase, texLoader);

        for(int i = 2; i < 38;) {
            eTextureCollection coll(fRenderer);
            for(int j = 0; j < 12; j++, i++) {
                texClass.load(i, coll);
            }
            fDryToScrubTerrainTexs.push_back(coll);
        }

        for(int i = 38; i < 50; i++) {
            texClass.load(i, fScrubTerrainTexs);
        }

        for(int i = 62; i < 74; i++) {
            texClass.load(i, fScrubTerrainTexs);
        }

        {
            eTextureCollection coll(fRenderer);
            for(int i = 74; i < 86; i++) {
                texClass.load(i, coll);
            }
            fForestToDryTerrainTexs.push_back(coll);
        }

        for(int i = 86; i < 106; i++) {
            texClass.load(i, fForestTerrainTexs);
        }

        for(int i = 106; i < 164; i++) {
            texClass.load(i, fDryTerrainTexs);
        }

        for(int i = 164; i < 172; i++) {
            texClass.load(i, fWaterTerrainTexs);
        }

        loadWaterToX(fRenderer, 172, fWaterToDryTerrainTexs, texClass);

        loadStones(334, fFlatStonesTerrainTexs,
                   fLargeFlatStonesTerrainTexs,
                   fHugeFlatStonesTerrainTexs, texClass);
        loadStones(348, fBronzeTerrainTexs,
                   fLargeBronzeTerrainTexs,
                   fHugeBronzeTerrainTexs, texClass);
        loadStones(363, fSilverTerrainTexs,
                   fLargeSilverTerrainTexs,
                   fHugeSilverTerrainTexs, texClass);
        loadStones(377, fTallStoneTerrainTexs,
                   fLargeTallStoneTerrainTexs,
                   fHugeTallStoneTerrainTexs, texClass);
    }

    {
        const std::string pathBase{terrDir + "Zeus_Overlay_"};
        eTextureClass texClass(pathBase, texLoader);

        for(int i = 21; i < 29; i++) {
            texClass.load(i, fTinyStones);
        }

        fBuildingBase = texClass.load(37);
        fSelectedBuildingBase = texClass.load(38);

        for(int i = 43; i < 53; i++) {
            texClass.load(i, fBuildingBase2);
        }
        for(int i = 53; i < 63; i++) {
            texClass.load(i, fBuildingBase3);
        }
    }

    {
        const std::string pathBase{terrDir + "Zeus_Elevation_Tiles_"};
        eTextureClass texClass(pathBase, texLoader);

        for(int i = 21; i < 45; i++) {
            texClass.load(i, fElevation);
        }
    }

    {
        const std::string pathBase{terrDir + "Zeus_Land3_"};
        eTextureClass texClass(pathBase, texLoader);

        fSelectedTex = texClass.load(7);
        fInvalidTex = texClass.load(7);

        loadWaterToX(fRenderer, 9, fWaterToBeachTerrainTexs, texClass);

        for(int i = 189; i < 195; i++) {
            texClass.load(i, fBeachTerrainTexs);
        }

        for(int i = 195; i < 207; i++) {
            texClass.load(i, fBeachToDryTerrainTexs);
        }

        for(int i = 207; i < 231; i++) {
            texClass.load(i, fWaterToBeachToDryTerrainTexs);
        }
    }

    {
        const std::string pathBase{terrDir + "Zeus_Trees_"};
        eTextureClass texClass(pathBase, texLoader);

        {
            eTextureCollection coll(fRenderer);
            for(int i = 1; i < 13; i++) {
                texClass.load(i, coll);
            }
            fForestToDryTerrainTexs.push_back(coll);
        }

        for(int i = 13; i < 33; i++) {
            texClass.load(i, fForestTerrainTexs);
        }

        for(int i = 33; i < 45; i++) {
            texClass.load(i, fForestToScrubTerrainTexs);
        }

        for(int i = 45; i < 97; i++) {
            texClass.load(i, fForestTerrainTexs);
        }

        for(int i = 97; i < 105; i++) {
            texClass.load(i, fChoppedForestTerrainTexs);
        }

        for(int i = 105; i < 121; i++) {
            texClass.load(i, fChoppedForestToScrubTerrainTexs);
        }

        for(int i = 121; i < 157;) {
            eTextureCollection coll(fRenderer);
            for(int j = 0; j < 12; j++, i++) {
                texClass.load(i, coll);
            }
            fFertileToScrubTerrainTexs.push_back(coll);
        }

        for(int i = 157; i < 165; i++) {
            texClass.load(i, fFertileTerrainTexs);
        }
        for(int i = 173; i < 181; i++) {
            texClass.load(i, fFertileToDryTerrainTexs);
        }
    }


    {
        const std::string pathBase{terrDir + "Zeus_QuarryTileSet_"};
        eTextureClass texClass(pathBase, texLoader);

        for(int i = 1; i < 27; i++) {
            texClass.load(i, fFlatMarble);
        }

        for(int i = 27; i < 35; i++) {
            texClass.load(i, fDryToMarble);
        }

        for(int i = 35; i < 95; i++) {
            texClass.load(i, fMarble);
        }
    }

    texLoader.waitUntilFinished();
}
