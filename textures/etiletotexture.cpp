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

#include "buildings/ebuilding.h"
#include "buildings/ebuildingrenderer.h"
#include "evaryingsizetex.h"
#include "ebuildingtextures.h"
#include "emarbletile.h"

#include "buildings/eresourcebuilding.h"

#include "buildings/sanctuaries/etempletilebuilding.h"

std::shared_ptr<eTexture> getStonesTexture(eTile* const tile,
                          const eTextureCollection& small,
                          const eTextureCollection& large,
                          const eTextureCollection& huge,
                          int& futureDim, int& drawDim) {
    return eVaryingSizeTex::getVaryingTexture(
                 eStonesToDry::get, tile,
                 small, large, huge,
                 futureDim, drawDim);
}

std::shared_ptr<eTexture> eTileToTexture::get(eTile* const tile,
                             const eTerrainTextures& textures,
                             const eBuildingTextures& blds,
                             const eTileSize tileSize,
                             const bool drawElev,
                             int& futureDim,
                             int& drawDim,
                             const eTextureCollection** coll) {
    drawDim = 1;
    futureDim = 1;
    const int seed = tile->seed();

    const auto ut = tile->underBuildingType();
    switch(ut) {
    case eBuildingType::templeHephaestus:
    case eBuildingType::templeArtemis: {
        const auto& coll = blds.fSanctuaryStairs;
        return coll.getTexture(seed % coll.size());
    } break;
    case eBuildingType::oliveTree:
    case eBuildingType::vine:
    case eBuildingType::orangeTree:
    case eBuildingType::ruins:
    case eBuildingType::palaceTile: {
        const auto b = tile->building();
        return b->getTexture(tileSize);
    } break;
    case eBuildingType::templeTile: {
        const auto b = tile->underBuilding();
        const auto bt = static_cast<eTempleTileBuilding*>(b);
        const bool f = bt->finished();
        if(f) return bt->getTileTexture(tileSize);
        [[fallthrough]];
    }
    case eBuildingType::temple:
    case eBuildingType::templeStatue:
    case eBuildingType::templeMonument:
    case eBuildingType::templeAltar: {
        const auto& coll = blds.fSanctuarySpace;
        return coll.getTexture(seed % coll.size());
    } break;
    default: break;
    }

    const bool hr = ut == eBuildingType::road;

    const auto tr = tile->topRight();
    const auto r = tile->right();
    const auto br = tile->bottomRight();
    const auto b = tile->bottom();
    const auto bl = tile->bottomLeft();
    const auto l = tile->left();
    const auto tl = tile->topLeft();
    const auto t = tile->top();

    if(drawElev) {
        const int a = tile->altitude();

        const int tx = tile->x();
        const int ty = tile->y();

        const int tra = tr ? tr->altitude() : a;
        const int ra = r ? r->altitude() : a;
        const int bra = br ? br->altitude() : a;
        const int ba = b ? b->altitude() : a;
        const int bla = bl ? bl->altitude() : a;
        const int la = l ? l->altitude() : a;
        const int tla = tl ? tl->altitude() : a;
        const int ta = t ? t->altitude() : a;

        const auto& elev = textures.fElevation;
        const auto& delev = textures.fDoubleElevation;
        const auto& delev2 = textures.fDoubleElevation2;
        const bool w = tile->walkableElev();
        if(tra > a && tla > a) {
            if(tra - a == 2 || tla - a == 2) {
                return delev.getTexture(8);
            } else {
                return elev.getTexture(8);
            }
        } else if(tra > a && bra > a) {
            if(tra - a == 2 && bra - a == 2) {
                return delev.getTexture(9);
            } else {
                return elev.getTexture(9);
            }
        } else if(bla > a && bra > a) {
            if(bla - a == 2 && bra - a == 2) {
                return delev.getTexture(10);
            } else {
                return elev.getTexture(10);
            }
        } else if(bla > a && tla > a) {
            if(bla - a == 2 && tla - a == 2) {
                return delev.getTexture(11);
            } else {
                return elev.getTexture(11);
            }
        } else if(bla > a) {
            if(bla - a == 2) {
                return delev.getTexture(1);
            } else {
                if(w) return elev.getTexture(12 + (hr ? 4 : 0));
                else return elev.getTexture(1);
            }
        } else if(tla > a) {
            if(tla - a == 2) {
                if((tx + ty) % 2) {
                    return delev2.getTexture(std::abs(ty) % 3);
                } else {
                    return delev.getTexture(3);
                }
            } else {
                if(w) return elev.getTexture(13 + (hr ? 4 : 0));
                else return elev.getTexture(3);
            }
        } else if(tra > a) {
            if(tra - a == 2) {
                if((tx + ty) % 2) {
                    return delev2.getTexture(3 + (std::abs(tx) % 3));
                } else {
                    return delev.getTexture(5);
                }
            } else {
                if(w) return elev.getTexture(14 + (hr ? 4 : 0));
                else return elev.getTexture(5);
            }
        } else if(bra > a) {
            if(bra - a == 2) {
                return delev.getTexture(7);
            } else {
                if(w) return elev.getTexture(15 + (hr ? 4 : 0));
                else return elev.getTexture(7);
            }
        } else if(la > a) {
            if(la - a == 2) {
                return delev.getTexture(2);
            } else {
                return elev.getTexture(2);
            }
        } else if(ta > a) {
            if(ta - a == 2) {
                if((tx + ty) % 2) {
                    return delev2.getTexture(12);
                } else {
                    return delev.getTexture(4);
                }
            } else {
                return elev.getTexture(4);
            }
        } else if(ra > a) {
            if(ra - a == 2) {
                return delev.getTexture(6);
            } else {
                return elev.getTexture(6);
            }
        } else if(ba > a) {
            if(ba - a == 2) {
                return delev.getTexture(0);
            } else {
                return elev.getTexture(0);
            }
        }
    }

    if(hr) {
        const auto b = tile->building();
        return b->getTexture(tileSize);
    }

    switch(tile->terrain()) {
    case eTerrain::dry: {
        const auto& vec = textures.fDryToScrubTerrainTexs;
        const int scrubCount = vec[0].size();
        const int scrub = tile->scrubId(scrubCount) - 1;
        if(scrub == -1) { // zero scrub
            const auto& coll = textures.fDryTerrainTexs;
            const int texId = seed % coll.size();
            return coll.getTexture(texId);
        } else if(scrub == scrubCount - 1) { // full scrub
            const auto& coll = textures.fScrubTerrainTexs;
            const int texId = seed % coll.size();
            return coll.getTexture(texId);
        } else { // partial scrub
            const int collId = seed % vec.size();
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
        const int texId = seed % coll.size();
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
            const int texId = seed % texs.size();
            return texs.getTexture(texId);
        }
        const int toDryId = eWaterToDry::get(tile);
        if(toDryId != -1) {
            const auto& texs = textures.fWaterToDryTerrainTexs[toDryId];
            const int texId = seed % texs.size();
            return texs.getTexture(texId);
        }

        const bool trs = tr && tr->isShoreTile();
        const bool rs = r && r->isShoreTile();
        const bool brs = br && br->isShoreTile();
        const bool bs = b && b->isShoreTile();
        const bool bls = bl && bl->isShoreTile();
        const bool ls = l && l->isShoreTile();
        const bool tls = tl && tl->isShoreTile();
        const bool ts = t && t->isShoreTile();

        int n = 0;
        if(trs) n++;
        if(brs) n++;
        if(bls) n++;
        if(tls) n++;
        if(rs) n++;
        if(ts) n++;
        if(ls) n++;
        if(bs) n++;
        if(n > 5 || (trs && bls) || (tls && brs) ||
           (ls && rs && bs && ts) ||
           (trs && rs && bs && ls) ||
           (ts && rs && brs && ls) ||
           (ts && trs && bs && ls) ||
           (ts && brs && bs && ls) ||
           (rs && bls && ls && tls) ||
           (trs && rs && brs && ls) ||
           (rs && bs && ls && tls) ||
           (ts && brs && bs && bls) ||
           (ts && rs && bs && tls) ||
           (ts && trs && bs && tls) ||
           (ts && rs && bs && bls && tls) ||
           (rs && bs && bls && ls && tls) ||
           (ts && rs && bls && ls && tls) ||
           (ts && brs && bs && bls && ls) ||
           (ts && rs && brs && bs && bls)) {
            *coll = &textures.fWaterTerrainTexs;
        } else if(rs && ls && n == 2) {
            *coll = &textures.fWaterTexs[12];
        } else if(bs && ts && n == 2) {
            *coll = &textures.fWaterTexs[13];
        } else if(rs && n == 1) {
            *coll = &textures.fWaterTexs[8];
        } else if(bs && n == 1) {
            *coll = &textures.fWaterTexs[9];
        } else if(ls && n == 1) {
            *coll = &textures.fWaterTexs[10];
        } else if(ts && n == 1) {
            *coll = &textures.fWaterTexs[11];
        } else if((tls && trs) || (ls && rs && ts) ||
                  (trs && ls) || (tls && rs)) {
            *coll = &textures.fWaterTexs[7];
        } else if((trs || ts) && (brs || bs) && !tls && !bls && !ls) {
            *coll = &textures.fWaterTexs[1];
        } else if(trs || (ts && rs)) {
            *coll = &textures.fWaterTexs[0];
        } else if(((brs || bls) && (brs || rs) && (bls || ls)) ||
                  (rs && bs && ls)) {
            *coll = &textures.fWaterTexs[3];
        } else if(brs || (rs && bs)) {
            *coll = &textures.fWaterTexs[2];
        } else if((bls || bs) && (tls || ts)) {
            *coll = &textures.fWaterTexs[5];
        } else if(bls || (ls && bs)) {
            *coll = &textures.fWaterTexs[4];
        } else if(tls || (ls && ts)) {
            *coll = &textures.fWaterTexs[6];
        } else {
            *coll = &textures.fWaterTexs[14];
        }

        return nullptr;
    } break;
    case eTerrain::fertile: {
        const auto id = eFertileToDry::get(tile);
        const int scrubCount = textures.fFertileToScrubTerrainTexs.size();
        const int scrub = tile->scrubId(scrubCount) - 1;
        switch(id) {
        case eFertileToDryId::none: {
            if(scrub == -1) {
                const auto& coll = textures.fFertileTerrainTexs;
                const int texId = seed % coll.size();
                return coll.getTexture(texId);
            } else {
                const auto& coll = textures.fFertileToScrubTerrainTexs[2];
                return coll.getTexture(scrub);
            }
        } break;
        case eFertileToDryId::somewhere: {
            if(scrub == -1) {
                const auto& coll = textures.fFertileToDryTerrainTexs;
                const int texId = seed % coll.size();
                return coll.getTexture(texId);
            } else {
                const int collId = seed % 2;
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
            const int texId = seed % coll.size();
            return coll.getTexture(texId);
        } break;
        case eForestToDryId::somewhere: {
            const int scrubCount = textures.fForestToScrubTerrainTexs.size();
            const int scrub = tile->scrubId(scrubCount) - 1;
            if(scrub == -1) {
                const auto& vec = textures.fForestToDryTerrainTexs;
                const int collId = seed % vec.size();
                const auto& coll = vec[collId];
                const int texId = seed % coll.size();
                return coll.getTexture(texId);
            } else {
                const auto& coll = textures.fForestToScrubTerrainTexs;
                return coll.getTexture(scrub);
            }
        } break;
        }
    } break;
    case eTerrain::choppedForest: {
        const int scrubCount = textures.fChoppedForestToScrubTerrainTexs.size();
        const int scrub = tile->scrubId(scrubCount) - 1;
        if(scrub == -1) {
            const auto& coll = textures.fChoppedForestTerrainTexs;
            const int texId = seed % coll.size();
            return coll.getTexture(texId);
        } else {
            const auto& coll = textures.fChoppedForestToScrubTerrainTexs;
            return coll.getTexture(scrub);
        }
    } break;


    case eTerrain::flatStones: {
        return getStonesTexture(tile, textures.fFlatStonesTerrainTexs,
                                textures.fLargeFlatStonesTerrainTexs,
                                textures.fHugeFlatStonesTerrainTexs,
                                futureDim, drawDim);
    } break;
    case eTerrain::copper: {
        return getStonesTexture(tile, textures.fBronzeTerrainTexs,
                                textures.fLargeBronzeTerrainTexs,
                                textures.fHugeBronzeTerrainTexs,
                                futureDim, drawDim);
    } break;
    case eTerrain::silver: {
        return getStonesTexture(tile, textures.fSilverTerrainTexs,
                                textures.fLargeSilverTerrainTexs,
                                textures.fHugeSilverTerrainTexs,
                                futureDim, drawDim);
    } break;
    case eTerrain::tallStones: {
        return getStonesTexture(tile, textures.fTallStoneTerrainTexs,
                                textures.fLargeTallStoneTerrainTexs,
                                textures.fHugeTallStoneTerrainTexs,
                                futureDim, drawDim);
    } break;
    case eTerrain::marble: {
        return eMarbleTile::get(tile, textures);
    } break;

    case eTerrain::dryBased:
        break;

    default:
        break;
    }
    return textures.fInvalidTex;
}
