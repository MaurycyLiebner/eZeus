#ifndef ETERRAINTEXTURES_H
#define ETERRAINTEXTURES_H

#include "etexturecollection.h"

class eTerrainTextures {
public:
    eTerrainTextures(const int tileW, const int tileH,
                     SDL_Renderer* const renderer);

    void load();

    const int fTileW;
    const int fTileH;
    SDL_Renderer* const fRenderer;

    eTextureCollection fDryTerrainTexs;
    eTextureCollection fBeachTerrainTexs;
    eTextureCollection fBeachToDryTerrainTexs;
    eTextureCollection fWaterTerrainTexs;
    std::vector<eTextureCollection> fWaterToDryTerrainTexs;
    eTextureCollection fFertileTerrainTexs;
    eTextureCollection fFertileToDryTerrainTexs;
    std::vector<eTextureCollection> fDryToScrubTerrainTexs;
    eTextureCollection fScrubTerrainTexs;
    std::vector<eTextureCollection> fFertileToScrubTerrainTexs;
    std::vector<eTextureCollection> fForestToDryTerrainTexs;
    eTextureCollection fForestToScrubTerrainTexs;
    eTextureCollection fForestTerrainTexs;
    std::vector<eTextureCollection> fWaterToBeachTerrainTexs;
    eTexture fSelectedTex;
    eTextureCollection fWaterToBeachToDryTerrainTexs;
};

#endif // ETERRAINTEXTURES_H
