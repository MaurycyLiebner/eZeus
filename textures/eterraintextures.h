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
    eTexture fInvalidTex;
    eTexture fSelectedTex;
    eTextureCollection fWaterToBeachToDryTerrainTexs;

    eTextureCollection fFlatStonesTerrainTexs;
    eTextureCollection fLargeFlatStonesTerrainTexs;
    eTextureCollection fHugeFlatStonesTerrainTexs;

    eTextureCollection fBronzeTerrainTexs;
    eTextureCollection fLargeBronzeTerrainTexs;
    eTextureCollection fHugeBronzeTerrainTexs;

    eTextureCollection fSilverTerrainTexs;
    eTextureCollection fLargeSilverTerrainTexs;
    eTextureCollection fHugeSilverTerrainTexs;

    eTextureCollection fTallStoneTerrainTexs;
    eTextureCollection fLargeTallStoneTerrainTexs;
    eTextureCollection fHugeTallStoneTerrainTexs;

    eTextureCollection fTinyStones;

    eTexture fBuildingBase;
    eTexture fSelectedBuildingBase;

    eTextureCollection fElevation;
};

#endif // ETERRAINTEXTURES_H
