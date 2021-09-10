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
    eTextureCollection fChoppedForestToScrubTerrainTexs;
    eTextureCollection fChoppedForestTerrainTexs;
    std::vector<eTextureCollection> fWaterToBeachTerrainTexs;
    std::shared_ptr<eTexture> fInvalidTex;
    std::shared_ptr<eTexture> fSelectedTex;
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

    std::shared_ptr<eTexture> fBuildingBase;
    std::shared_ptr<eTexture> fSelectedBuildingBase;

    eTextureCollection fBuildingBase2;
    eTextureCollection fBuildingBase3;

    eTextureCollection fElevation;
};

#endif // ETERRAINTEXTURES_H
