#include "eterraintextures.h"

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
    fWaterToBeachToDryTerrainTexs(renderer) {

}

std::string addZeroes(const std::string& str) {
    std::string result = str;
    while(result.size() < 3) {
        result.insert(0, "0");
    }
    return result;
}

void loadTex(const std::string& pathBase, const int i,
             eTextureCollection& coll) {
    const auto path = pathBase + addZeroes(std::to_string(i)) + ".png";
    const bool r = coll.loadTexture(path);
    if(!r) std::printf("Failed to load %s\n", path.c_str());
}

void loadWaterToX(SDL_Renderer* const renderer,
                  int i0, const std::string& pathBase,
                  std::vector<eTextureCollection>& result) {
    int i = i0;
    for(; i < i0 + 32;) {
        eTextureCollection coll(renderer);
        for(int j = 0; j < 4; j++, i++) {
            loadTex(pathBase, i, coll);
        }
        result.push_back(coll);
    }

    for(; i < i0 + 36;) {
        eTextureCollection coll(renderer);
        for(int j = 0; j < 2; j++, i++) {
            loadTex(pathBase, i, coll);
        }
        result.push_back(coll);
    }

    for(; i < i0 + 72; i++) {
        eTextureCollection coll(renderer);
        loadTex(pathBase, i, coll);
        result.push_back(coll);
    }
}

void eTerrainTextures::load() {
    std::string terrDir{"../ZeusTextures/"};
    terrDir += std::to_string(fTileH) + "/";
    terrDir += "Zeus_Terrain/";

    {
        const std::string pathBase{terrDir + "Zeus_land1_00"};

        for(int i = 2; i < 38;) {
            eTextureCollection coll(fRenderer);
            for(int j = 0; j < 12; j++, i++) {
                loadTex(pathBase, i, coll);
            }
            fDryToScrubTerrainTexs.push_back(coll);
        }

        for(int i = 38; i < 50; i++) {
            loadTex(pathBase, i, fScrubTerrainTexs);
        }

        for(int i = 62; i < 74; i++) {
            loadTex(pathBase, i, fScrubTerrainTexs);
        }

        {
            eTextureCollection coll(fRenderer);
            for(int i = 74; i < 86; i++) {
                loadTex(pathBase, i, coll);
            }
            fForestToDryTerrainTexs.push_back(coll);
        }

        for(int i = 86; i < 106; i++) {
            loadTex(pathBase, i, fForestTerrainTexs);
        }

        for(int i = 106; i < 164; i++) {
            loadTex(pathBase, i, fDryTerrainTexs);
        }

        for(int i = 164; i < 172; i++) {
            loadTex(pathBase, i, fWaterTerrainTexs);
        }

        loadWaterToX(fRenderer, 172, pathBase, fWaterToDryTerrainTexs);
    }

    {
        const std::string pathBase{terrDir + "Zeus_Land3_00"};

        fSelectedTex.load(fRenderer, pathBase + "007.png");
        fInvalidTex.load(fRenderer, pathBase + "007.png");

        loadWaterToX(fRenderer, 9, pathBase, fWaterToBeachTerrainTexs);

        for(int i = 189; i < 195; i++) {
            loadTex(pathBase, i, fBeachTerrainTexs);
        }

        for(int i = 195; i < 207; i++) {
            loadTex(pathBase, i, fBeachToDryTerrainTexs);
        }

        for(int i = 207; i < 231; i++) {
            loadTex(pathBase, i, fWaterToBeachToDryTerrainTexs);
        }
    }

    {
        const std::string pathBase{terrDir + "Zeus_Trees_00"};

        {
            eTextureCollection coll(fRenderer);
            for(int i = 1; i < 13; i++) {
                loadTex(pathBase, i, coll);
            }
            fForestToDryTerrainTexs.push_back(coll);
        }

        for(int i = 13; i < 33; i++) {
            loadTex(pathBase, i, fForestTerrainTexs);
        }

        for(int i = 33; i < 45; i++) {
            loadTex(pathBase, i, fForestToScrubTerrainTexs);
        }

        for(int i = 45; i < 97; i++) {
            loadTex(pathBase, i, fForestTerrainTexs);
        }

        for(int i = 121; i < 157;) {
            eTextureCollection coll(fRenderer);
            for(int j = 0; j < 12; j++, i++) {
                loadTex(pathBase, i, coll);
            }
            fFertileToScrubTerrainTexs.push_back(coll);
        }

        for(int i = 157; i < 165; i++) {
            loadTex(pathBase, i, fFertileTerrainTexs);
        }
        for(int i = 173; i < 181; i++) {
            loadTex(pathBase, i, fFertileToDryTerrainTexs);
        }
    }
}
