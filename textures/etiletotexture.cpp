#include "etiletotexture.h"

#include <algorithm>

#include "engine/etile.h"

#include "eterraintextures.h"

#include "ebeachtodry.h"
#include "ewatertodry.h"
#include "efertiletodry.h"
#include "eforesttodry.h"
#include "ewatertobeach.h"
#include "ewatercorner.h"
#include "estonestodry.h"

eTexture getStonesTexture(eTile* const tile,
                          const eTextureCollection& small,
                          const eTextureCollection& large) {
    const auto id = eStonesToDry::get(tile);
    switch(id) {
    case eStonesToDryId::outer: {
        const auto& coll = small;
        const int texId = tile->id() % coll.size();
        return coll.getTexture(texId);
    } break;
    case eStonesToDryId::inner: {
        const int smallFreq = 5;
        const int largeFreq = 1;
        const int t = tile->id() % (smallFreq + largeFreq);
        if(t < smallFreq) {
            const auto& coll = small;
            const int texId = tile->id() % coll.size();
            return coll.getTexture(texId);
        } else {
            const auto& coll = large;
            const int texId = tile->id() % coll.size();
            return coll.getTexture(texId);
        }
    } break;
    }
    return eTexture();
}

eTexture eTileToTexture::get(eTile* const tile,
                             const eTerrainTextures& textures) {
    const int tileId = tile->id();

    switch(tile->terrain()) {
    case eTerrain::dry: {
        const auto& vec = textures.fDryToScrubTerrainTexs;
        const int scrubCount = vec[0].size();
        const int scrub = tile->scrubId(scrubCount) - 1;
        if(scrub == -1) { // zero scrub
            const auto& coll = textures.fDryTerrainTexs;
            const int texId = tileId % coll.size();
            return coll.getTexture(texId);
        } else if(scrub == scrubCount - 1) { // full scrub
            const auto& coll = textures.fScrubTerrainTexs;
            const int texId = tileId % coll.size();
            return coll.getTexture(texId);
        } else { // partial scrub
            const int collId = tileId % vec.size();
            const auto& coll = vec[collId];
            return coll.getTexture(scrub);
        }
    } break;
    case eTerrain::beach: {
        const int toDryId = eBeachToDry::get(tile);
        if(toDryId != -1) {
            const auto& coll = textures.fBeachToDryTerrainTexs;
            return coll.getTexture(toDryId);
        }
        const auto& coll = textures.fBeachTerrainTexs;
        const int texId = tileId % coll.size();
        return coll.getTexture(texId);
    } break;
    case eTerrain::water: {
        const int cornerId = eWaterCorner::get(tile);
        if(cornerId != -1) {
            const auto& coll = textures.fWaterToBeachToDryTerrainTexs;
            return coll.getTexture(cornerId);
        }
        const int toBeachId = eWaterToBeach::get(tile);
        if(toBeachId != -1) {
            const auto& texs = textures.fWaterToBeachTerrainTexs[toBeachId];
            const int texId = tileId % texs.size();
            return texs.getTexture(texId);
        }
        const int toDryId = eWaterToDry::get(tile);
        if(toDryId != -1) {
            const auto& texs = textures.fWaterToDryTerrainTexs[toDryId];
            const int texId = tileId % texs.size();
            return texs.getTexture(texId);
        }

        const int texId = tileId % textures.fWaterTerrainTexs.size();
        const auto& coll = textures.fWaterTerrainTexs;
        return coll.getTexture(texId);
    } break;
    case eTerrain::fertile: {
        const auto id = eFertileToDry::get(tile);
        const int scrubCount = textures.fFertileToScrubTerrainTexs.size();
        const int scrub = tile->scrubId(scrubCount) - 1;
        switch(id) {
        case eFertileToDryId::none: {
            if(scrub == -1) {
                const auto& coll = textures.fFertileTerrainTexs;
                const int texId = tileId % coll.size();
                return coll.getTexture(texId);
            } else {
                const auto& coll = textures.fFertileToScrubTerrainTexs[2];
                return coll.getTexture(scrub);
            }
        } break;
        case eFertileToDryId::somewhere: {
            if(scrub == -1) {
                const auto& coll = textures.fFertileToDryTerrainTexs;
                const int texId = tileId % coll.size();
                return coll.getTexture(texId);
            } else {
                const int collId = tileId % 2;
                const auto& coll = textures.fFertileToScrubTerrainTexs[collId];
                return coll.getTexture(scrub);
            }
        } break;
        }
    } break;
    case eTerrain::forest: {
        const auto id = eForestToDry::get(tile);
        switch(id) {
        case eForestToDryId::none: {
            const auto& coll = textures.fForestTerrainTexs;
            const int texId = tileId % coll.size();
            return coll.getTexture(texId);
        } break;
        case eForestToDryId::somewhere: {
            const int scrubCount = textures.fForestToScrubTerrainTexs.size();
            const int scrub = tile->scrubId(scrubCount) - 1;
            if(scrub == -1) {
                const auto& vec = textures.fForestToDryTerrainTexs;
                const int collId = tileId % vec.size();
                const auto& coll = vec[collId];
                const int texId = tileId % coll.size();
                return coll.getTexture(texId);
            } else {
                const auto& coll = textures.fForestToScrubTerrainTexs;
                return coll.getTexture(scrub);
            }
        } break;
        }
    } break;
    case eTerrain::flatStones: {
        return getStonesTexture(tile, textures.fFlatStonesTerrainTexs,
                                textures.fLargeFlatStonesTerrainTexs);
    } break;
    case eTerrain::bronze: {
        return getStonesTexture(tile, textures.fBronzeTerrainTexs,
                                textures.fLargeBronzeTerrainTexs);
    } break;
    case eTerrain::silver: {
        return getStonesTexture(tile, textures.fSilverTerrainTexs,
                                textures.fLargeSilverTerrainTexs);
    } break;
    case eTerrain::tallStones: {
        return getStonesTexture(tile, textures.fTallStoneTerrainTexs,
                                textures.fLargeTallStoneTerrainTexs);
    } break;
    case eTerrain::tinyStones: {
        const auto& coll = textures.fTinyStones;
        const int texId = tileId % coll.size();
        return coll.getTexture(texId);
    } break;
    case eTerrain::dryBased:
        break;
    }
    return textures.fInvalidTex;
}
