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

eTexture eTileToTexture::get(eTile* const tile,
                             const eTerrainTextures& textures) {
    const int tileId = tile->id();

    switch(tile->terrain()) {
    case eTerrain::dry: {
        const int scrubCount = textures.fDryToScrubTerrainTexs.size();
        const int scrub = tile->scrubId(scrubCount) - 1;
        if(scrub == -1) { // zero scrub
            const int texId = tileId % textures.fDryTerrainTexs.size();
            const auto& coll = textures.fDryTerrainTexs;
            return coll.getTexture(texId);
        } else if(scrub == scrubCount) { // full scrub
            const int texId = tileId % textures.fScrubTerrainTexs.size();
            const auto& coll = textures.fScrubTerrainTexs;
            return coll.getTexture(texId);
        } else { // partial scrub
            const int collId = tileId % textures.fDryToScrubTerrainTexs.size();
            const auto& coll = textures.fDryToScrubTerrainTexs[collId];
            return coll.getTexture(scrub);
        }
    } break;
    case eTerrain::beach: {
        const int toDryId = eBeachToDry::get(tile);
        if(toDryId != -1) {
            const auto& coll = textures.fBeachToDryTerrainTexs;
            return coll.getTexture(toDryId);
        }
        const int texId = tileId % textures.fBeachTerrainTexs.size();
        const auto& coll = textures.fBeachTerrainTexs;
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
                const int texId = tileId % textures.fFertileTerrainTexs.size();
                const auto& coll = textures.fFertileTerrainTexs;
                return coll.getTexture(texId);
            } else {
                const auto& coll = textures.fFertileToScrubTerrainTexs[2];
                return coll.getTexture(scrub);
            }
        } break;
        case eFertileToDryId::somewhere: {
            if(scrub == -1) {
                const int texId = tileId % textures.fFertileToDryTerrainTexs.size();
                const auto& coll = textures.fFertileToDryTerrainTexs;
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
            const int texId = tileId % textures.fForestTerrainTexs.size();
            const auto& coll = textures.fForestTerrainTexs;
            return coll.getTexture(texId);
        } break;
        case eForestToDryId::somewhere: {
            const int scrubCount = textures.fForestToScrubTerrainTexs.size();
            const int scrub = tile->scrubId(scrubCount) - 1;
            if(scrub == -1) {
                const int collId = tileId % textures.fForestToDryTerrainTexs.size();
                const auto& coll = textures.fForestToDryTerrainTexs[collId];
                const int texId = tileId % coll.size();
                return coll.getTexture(texId);
            } else {
                const auto& coll = textures.fForestToScrubTerrainTexs;
                return coll.getTexture(scrub);
            }
        } break;
        }
    } break;
    case eTerrain::dryBased:
        break;
    }
    return textures.fInvalidTex;
}
