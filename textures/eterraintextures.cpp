#include "eterraintextures.h"

#include "textures/espriteloader.h"

#include "spriteData/zeusLand115.h"
#include "spriteData/zeusLand130.h"
#include "spriteData/zeusLand145.h"
#include "spriteData/zeusLand160.h"

#include "spriteData/zeusOverlay15.h"
#include "spriteData/zeusOverlay30.h"
#include "spriteData/zeusOverlay45.h"
#include "spriteData/zeusOverlay60.h"

#include "spriteData/zeusElevationTiles15.h"
#include "spriteData/zeusElevationTiles30.h"
#include "spriteData/zeusElevationTiles45.h"
#include "spriteData/zeusElevationTiles60.h"

#include "spriteData/zeusElevationTiles215.h"
#include "spriteData/zeusElevationTiles230.h"
#include "spriteData/zeusElevationTiles245.h"
#include "spriteData/zeusElevationTiles260.h"

#include "spriteData/zeusLand315.h"
#include "spriteData/zeusLand330.h"
#include "spriteData/zeusLand345.h"
#include "spriteData/zeusLand360.h"

#include "spriteData/zeusTrees15.h"
#include "spriteData/zeusTrees30.h"
#include "spriteData/zeusTrees45.h"
#include "spriteData/zeusTrees60.h"

#include "spriteData/zeusQuarryTileSet15.h"
#include "spriteData/zeusQuarryTileSet30.h"
#include "spriteData/zeusQuarryTileSet45.h"
#include "spriteData/zeusQuarryTileSet60.h"

#include "spriteData/zeusStairs15.h"
#include "spriteData/zeusStairs30.h"
#include "spriteData/zeusStairs45.h"
#include "spriteData/zeusStairs60.h"

#include "spriteData/blackMarbleTerrain15.h"
#include "spriteData/blackMarbleTerrain30.h"
#include "spriteData/blackMarbleTerrain45.h"
#include "spriteData/blackMarbleTerrain60.h"

#include "spriteData/orichalcTerrain15.h"
#include "spriteData/orichalcTerrain30.h"
#include "spriteData/orichalcTerrain45.h"
#include "spriteData/orichalcTerrain60.h"

#include "spriteData/poseidonTrees15.h"
#include "spriteData/poseidonTrees30.h"
#include "spriteData/poseidonTrees45.h"
#include "spriteData/poseidonTrees60.h"

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
    fPoseidonForestToScrubTerrainTexs(renderer),
    fPoseidonForestTerrainTexs(renderer),
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

    fOrichalcTerrainTexs(renderer),
    fLargeOrichalcTerrainTexs(renderer),
    fHugeOrichalcTerrainTexs(renderer),

    fAppeal(renderer),
    fHouseAppeal(renderer),

    fBeachRoad(renderer),
    fToBeachRoad(renderer),
    fRoad(renderer),
    fPrettyRoad(renderer),

    fSanctuaryStairs(renderer),

    fTinyStones(renderer),

    fFlatMarble(renderer),
    fDryToMarble(renderer),
    fMarble(renderer),
    fDeepMarble(renderer),

    fFlatBlackMarble(renderer),
    fDryToBlackMarble(renderer),
    fBlackMarble(renderer),
    fDeepBlackMarble(renderer),

    fBuildingBase2(renderer),
    fBuildingBase3(renderer),

    fElevation(renderer),
    fDoubleElevation(renderer),
    fDoubleElevation2(renderer),

    fQuakeTexs(renderer) {}

void loadWaterToX(SDL_Renderer* const renderer, int i0,
                  std::vector<eTextureCollection>& result,
                  eSpriteLoader& loader) {
    int i = i0;
    for(; i < i0 + 32;) {
        eTextureCollection coll(renderer);
        for(int j = 0; j < 4; j++, i++) {
            loader.load(1, i, coll);
        }
        result.push_back(coll);
    }

    for(; i < i0 + 36;) {
        eTextureCollection coll(renderer);
        for(int j = 0; j < 2; j++, i++) {
            loader.load(1, i, coll);
        }
        result.push_back(coll);
    }

    for(; i < i0 + 72; i++) {
        eTextureCollection coll(renderer);
        loader.load(1, i, coll);
        result.push_back(coll);
    }
}

void loadStones(int i0, eTextureCollection& result,
                eTextureCollection& resultLarge,
                eTextureCollection& resultHuge,
                eSpriteLoader& loader,
                const int doff = 1) {
    int i = i0;
    for(; i < i0 + 8; i++) {
        loader.load(doff, i, result);
    }

    for(; i < i0 + 12; i++) {
        loader.load(doff, i, resultLarge);
    }

    for(; i < i0 + 14; i++) {
        loader.load(doff, i, resultHuge);
    }
}

void eTerrainTextures::load() {
    {
        const auto& sds = spriteData(fTileH,
                                     eZeusLand1SpriteData15,
                                     eZeusLand1SpriteData30,
                                     eZeusLand1SpriteData45,
                                     eZeusLand1SpriteData60);
        eSpriteLoader loader(fTileH, "zeusLand1", sds,
                             nullptr, fRenderer);

        for(int i = 2; i < 38;) {
            eTextureCollection coll(fRenderer);
            for(int j = 0; j < 12; j++, i++) {
                loader.load(1, i, coll);
            }
            fDryToScrubTerrainTexs.push_back(coll);
        }

        for(int i = 38; i < 50; i++) {
            loader.load(1, i, fScrubTerrainTexs);
        }

        for(int i = 62; i < 74; i++) {
            loader.load(1, i, fScrubTerrainTexs);
        }

        {
            eTextureCollection coll(fRenderer);
            for(int i = 74; i < 86; i++) {
                loader.load(1, i, coll);
            }
            fForestToDryTerrainTexs.push_back(coll);
        }

        for(int i = 86; i < 106; i++) {
            loader.load(1, i, fForestTerrainTexs);
        }

        for(int i = 106; i < 164; i++) {
            loader.load(1, i, fDryTerrainTexs);
        }

        for(int i = 164; i < 172; i++) {
            loader.load(1, i, fWaterTerrainTexs);
        }

        loadWaterToX(fRenderer, 172, fWaterToDryTerrainTexs, loader);

        for(int i = 244; i < 274; i++) {
            loader.load(1, i, fQuakeTexs);
        }

        loadStones(334, fFlatStonesTerrainTexs,
                   fLargeFlatStonesTerrainTexs,
                   fHugeFlatStonesTerrainTexs, loader);
        loadStones(348, fBronzeTerrainTexs,
                   fLargeBronzeTerrainTexs,
                   fHugeBronzeTerrainTexs, loader);
        loadStones(363, fSilverTerrainTexs,
                   fLargeSilverTerrainTexs,
                   fHugeSilverTerrainTexs, loader);
        loadStones(377, fTallStoneTerrainTexs,
                   fLargeTallStoneTerrainTexs,
                   fHugeTallStoneTerrainTexs, loader);
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eZeusOverlaySpriteData15,
                                     eZeusOverlaySpriteData30,
                                     eZeusOverlaySpriteData45,
                                     eZeusOverlaySpriteData60);
        eSpriteLoader loader(fTileH, "zeusOverlay", sds,
                             nullptr, fRenderer);

        for(int i = 1; i < 11; i++) {
            loader.load(1, i, fAppeal);
        }

        for(int i = 11; i < 21; i++) {
            loader.load(1, i, fHouseAppeal);
        }

        for(int i = 21; i < 29; i++) {
            loader.load(1, i, fTinyStones);
        }

        fBuildingBase = loader.load(1, 37);
        fSelectedBuildingBase = loader.load(1, 38);

        for(int i = 43; i < 53; i++) {
            loader.load(1, i, fBuildingBase2);
        }
        for(int i = 53; i < 63; i++) {
            loader.load(1, i, fBuildingBase3);
        }
    }

    {
        {
            const auto& sds = spriteData(fTileH,
                                         eZeusElevationTilesSpriteData15,
                                         eZeusElevationTilesSpriteData30,
                                         eZeusElevationTilesSpriteData45,
                                         eZeusElevationTilesSpriteData60);
            eSpriteLoader loader(fTileH, "zeusElevationTiles", sds,
                                 nullptr, fRenderer);

            for(int i = 1; i < 21; i++) {
                loader.load(1, i, fDoubleElevation);
            }

            for(int i = 21; i < 45; i++) {
                loader.load(1, i, fElevation);
            }
        }

        {
            const auto& sds = spriteData(fTileH,
                                         eZeusElevationTiles2SpriteData15,
                                         eZeusElevationTiles2SpriteData30,
                                         eZeusElevationTiles2SpriteData45,
                                         eZeusElevationTiles2SpriteData60);
            eSpriteLoader loader(fTileH, "zeusElevationTiles2", sds,
                                 nullptr, fRenderer);

            for(int i = 1; i < 15; i++) {
                loader.load(1, i, fDoubleElevation2);
            }
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eZeusLand3SpriteData15,
                                     eZeusLand3SpriteData30,
                                     eZeusLand3SpriteData45,
                                     eZeusLand3SpriteData60);
        eSpriteLoader loader(fTileH, "zeusLand3", sds,
                             nullptr, fRenderer);

        fSelectedTex = loader.load(1, 7);
        fInvalidTex = loader.load(1, 7);

        loadWaterToX(fRenderer, 9, fWaterToBeachTerrainTexs, loader);

        for(int i = 0; i < 15; i++) {
            fWaterTexs.emplace_back(fRenderer);
        }

        for(int i = 81; i < 99; i++) {
            loader.load(1, i, fBeachRoad);
        }

        for(int i = 231; i < 235; i++) {
            loader.load(1, i, fToBeachRoad);
        }

        for(int i = 235; i < 253; i++) {
            loader.load(1, i, fRoad);
        }

        for(int i = 253; i < 302; i++) {
            loader.load(1, i, fPrettyRoad);
        }

        for(int i = 99; i < 189;) {
            for(int j = 0; j < 15; j++, i++) {
                loader.load(1, i, fWaterTexs[j]);
            }
        }

        for(int i = 189; i < 195; i++) {
            loader.load(1, i, fBeachTerrainTexs);
        }

        for(int i = 195; i < 207; i++) {
            loader.load(1, i, fBeachToDryTerrainTexs);
        }

        for(int i = 207; i < 231; i++) {
            loader.load(1, i, fWaterToBeachToDryTerrainTexs);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eZeusTreesSpriteData15,
                                     eZeusTreesSpriteData30,
                                     eZeusTreesSpriteData45,
                                     eZeusTreesSpriteData60);
        eSpriteLoader loader(fTileH, "zeusTrees", sds,
                             nullptr, fRenderer);

        {
            eTextureCollection coll(fRenderer);
            for(int i = 1; i < 13; i++) {
                loader.load(1, i, coll);
            }
            fForestToDryTerrainTexs.push_back(coll);
        }

        for(int i = 13; i < 33; i++) {
            loader.load(1, i, fForestTerrainTexs);
        }

        for(int i = 33; i < 45; i++) {
            loader.load(1, i, fForestToScrubTerrainTexs);
        }

        for(int i = 45; i < 97; i++) {
            loader.load(1, i, fForestTerrainTexs);
        }

        for(int i = 97; i < 105; i++) {
            loader.load(1, i, fChoppedForestTerrainTexs);
        }

        for(int i = 105; i < 121; i++) {
            loader.load(1, i, fChoppedForestToScrubTerrainTexs);
        }

        for(int i = 121; i < 157;) {
            eTextureCollection coll(fRenderer);
            for(int j = 0; j < 12; j++, i++) {
                loader.load(1, i, coll);
            }
            fFertileToScrubTerrainTexs.push_back(coll);
        }

        for(int i = 157; i < 165; i++) {
            loader.load(1, i, fFertileTerrainTexs);
        }
        for(int i = 173; i < 181; i++) {
            loader.load(1, i, fFertileToDryTerrainTexs);
        }
    }


    {
        const auto& sds = spriteData(fTileH,
                                     eZeusQuarryTileSetSpriteData15,
                                     eZeusQuarryTileSetSpriteData30,
                                     eZeusQuarryTileSetSpriteData45,
                                     eZeusQuarryTileSetSpriteData60);
        eSpriteLoader loader(fTileH, "zeusQuarryTileSet", sds,
                             nullptr, fRenderer);

        for(int i = 1; i < 27; i++) {
            loader.load(1, i, fFlatMarble);
        }

        for(int i = 27; i < 35; i++) {
            loader.load(1, i, fDryToMarble);
        }

        for(int i = 35; i < 95; i++) {
            loader.load(1, i, fMarble);
        }

        for(int i = 95; i < 155; i++) {
            loader.load(1, i, fDeepMarble);
        }
    }

    {
        const auto& sds = spriteData(fTileH,
                                     eZeusStairsSpriteData15,
                                     eZeusStairsSpriteData30,
                                     eZeusStairsSpriteData45,
                                     eZeusStairsSpriteData60);
        eSpriteLoader loader(fTileH, "zeusStairs", sds,
                             nullptr, fRenderer);

        for(int i = 1; i < 13; i++) {
            loader.load(1, i, fSanctuaryStairs);
        }
    }
}

void eTerrainTextures::loadPoseidonTrees() {
    if(fPoseidonTreesLoaded) return;
    fPoseidonTreesLoaded = true;
    const auto& sds = spriteData(fTileH,
                                 ePoseidonTreesSpriteData15,
                                 ePoseidonTreesSpriteData30,
                                 ePoseidonTreesSpriteData45,
                                 ePoseidonTreesSpriteData60);
    eSpriteLoader loader(fTileH, "poseidonTrees", sds,
                         nullptr, fRenderer);

    {
        eTextureCollection coll(fRenderer);
        for(int i = 1; i < 13; i++) {
            loader.load(1, i, coll);
        }
        fPoseidonForestToDryTerrainTexs.push_back(coll);
    }

    for(int i = 13; i < 33; i++) {
        loader.load(1, i, fPoseidonForestTerrainTexs);
    }

    for(int i = 33; i < 45; i++) {
        loader.load(1, i, fPoseidonForestToScrubTerrainTexs);
    }

    for(int i = 45; i < 97; i++) {
        loader.load(1, i, fPoseidonForestTerrainTexs);
    }
}

void eTerrainTextures::loadBlackMarble() {
    if(fBlackMarbleLoaded) return;
    fBlackMarbleLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eBlackMarbleTerrainSpriteData15,
                                 eBlackMarbleTerrainSpriteData30,
                                 eBlackMarbleTerrainSpriteData45,
                                 eBlackMarbleTerrainSpriteData60);
    eSpriteLoader loader(fTileH, "blackMarbleTerrain", sds,
                         nullptr, fRenderer);

    for(int i = 1; i < 27; i++) {
        loader.load(1, i, fFlatBlackMarble);
    }

    for(int i = 27; i < 35; i++) {
        loader.load(1, i, fDryToBlackMarble);
    }

    for(int i = 35; i < 95; i++) {
        loader.load(1, i, fBlackMarble);
    }

    for(int i = 95; i < 155; i++) {
        loader.load(1, i, fDeepBlackMarble);
    }
}

void eTerrainTextures::loadOrichalc() {
    if(fOrichalcLoaded) return;
    fOrichalcLoaded = true;

    const auto& sds = spriteData(fTileH,
                                 eOrichalcTerrainSpriteData15,
                                 eOrichalcTerrainSpriteData30,
                                 eOrichalcTerrainSpriteData45,
                                 eOrichalcTerrainSpriteData60);
    eSpriteLoader loader(fTileH, "orichalcTerrain", sds,
                         nullptr, fRenderer);

    loadStones(155, fOrichalcTerrainTexs,
               fLargeOrichalcTerrainTexs,
               fHugeOrichalcTerrainTexs, loader, 155);
}
