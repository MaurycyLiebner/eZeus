#include "etiletotexture.h"

#include <algorithm>

#include "engine/etile.h"

#include "eterraintextures.h"
#include "egametextures.h"

#include "ebeachtodry.h"
#include "ewatertodry.h"
#include "efertiletodry.h"
#include "eforesttodry.h"
#include "ewatertobeach.h"
#include "ewatercorner.h"
#include "estonestodry.h"
#include "emarshtodry.h"
#include "elavatodry.h"

#include "buildings/ebuilding.h"
#include "buildings/ebuildingrenderer.h"
#include "evaryingsizetex.h"
#include "ebuildingtextures.h"
#include "emarbletile.h"

#include "buildings/eresourcebuilding.h"

#include "buildings/sanctuaries/etempletilebuilding.h"

#include "textures/eparktexture.h"

#include "engine/egameboard.h"

std::shared_ptr<eTexture> getStonesTexture(eTile* const tile,
                          const eTextureCollection& small,
                          const eTextureCollection& large,
                          const eTextureCollection& huge,
                          int& drawDim,
                          const eWorldDirection dir) {
    return eVaryingSizeTex::getVaryingTexture(
                 eStonesToDry::get, tile,
                 small, large, huge,
                 drawDim,
                 dir);
}

std::shared_ptr<eTexture> eTileToTexture::get(eTile* const tile,
                             const eTerrainTextures& textures,
                             const eBuildingTextures& blds,
                             const eTileSize tileSize,
                             const bool drawElev,
                             int& drawDim,
                             const eTextureCollection** coll,
                             const eWorldDirection dir) {
    drawDim = 1;
    const int seed = tile->seed();

    const auto ut = tile->underBuildingType();
    switch(ut) {
    case eBuildingType::templeAphrodite:
    case eBuildingType::templeApollo:
    case eBuildingType::templeAres:
    case eBuildingType::templeArtemis:
    case eBuildingType::templeAthena:
    case eBuildingType::templeAtlas:
    case eBuildingType::templeDemeter:
    case eBuildingType::templeDionysus:
    case eBuildingType::templeHades:
    case eBuildingType::templeHephaestus:
    case eBuildingType::templeHera:
    case eBuildingType::templeHermes:
    case eBuildingType::templePoseidon:
    case eBuildingType::templeZeus: {
        const auto& coll = textures.fSanctuaryStairs;
        int texId = seed % coll.size();
        if(dir == eWorldDirection::N) {
        } else if(dir == eWorldDirection::E) {
            if(texId == 0) {
                texId = 6;
            } else if(texId == 1) {
                texId = 7;
            } else if(texId == 2) {
                texId = 0;
            } else if(texId == 3) {
                texId = 1;
            } else if(texId == 4) {
                texId = 2;
            } else if(texId == 5) {
                texId = 3;
            } else if(texId == 6) {
                texId = 4;
            } else if(texId == 7) {
                texId = 5;
            } else if(texId == 8) {
                texId = 11;
            } else if(texId == 9) {
                texId = 8;
            } else if(texId == 10) {
                texId = 9;
            } else if(texId == 11) {
                texId = 10;
            }
        } else if(dir == eWorldDirection::S) {
            if(texId == 0) {
                texId = 4;
            } else if(texId == 1) {
                texId = 5;
            } else if(texId == 2) {
                texId = 6;
            } else if(texId == 3) {
                texId = 7;
            } else if(texId == 4) {
                texId = 0;
            } else if(texId == 5) {
                texId = 1;
            } else if(texId == 6) {
                texId = 2;
            } else if(texId == 7) {
                texId = 3;
            } else if(texId == 8) {
                texId = 10;
            } else if(texId == 9) {
                texId = 11;
            } else if(texId == 10) {
                texId = 8;
            } else if(texId == 11) {
                texId = 9;
            }
        } else { // if(dir == eWorldDirection::W) {
            if(texId == 0) {
                texId = 2;
            } else if(texId == 1) {
                texId = 3;
            } else if(texId == 2) {
                texId = 4;
            } else if(texId == 3) {
                texId = 5;
            } else if(texId == 4) {
                texId = 6;
            } else if(texId == 5) {
                texId = 7;
            } else if(texId == 6) {
                texId = 0;
            } else if(texId == 7) {
                texId = 1;
            } else if(texId == 8) {
                texId = 9;
            } else if(texId == 9) {
                texId = 10;
            } else if(texId == 10) {
                texId = 11;
            } else if(texId == 11) {
                texId = 8;
            }
        }
        return coll.getTexture(texId);
    } break;
    case eBuildingType::oliveTree:
    case eBuildingType::vine:
    case eBuildingType::orangeTree:
    case eBuildingType::ruins:
    case eBuildingType::palaceTile:
    case eBuildingType::godMonumentTile: {
        const auto b = tile->underBuilding();
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
    case eBuildingType::park: {
        return eVaryingSizeTex::getVaryingTexture(
                             eParkTexture::get, tile,
                             blds.fPark,
                             blds.fLargePark,
                             blds.fHugePark,
                             drawDim,
                             dir);
    } break;
    default: break;
    }

    const bool hr = ut == eBuildingType::road;

    eTile* tr = nullptr;
    eTile* r = nullptr;
    eTile* br = nullptr;
    eTile* b = nullptr;
    eTile* bl = nullptr;
    eTile* l = nullptr;
    eTile* tl = nullptr;
    eTile* t = nullptr;
    tile->rotatedNeighbours(tr, r, br, b, bl, l, tl, t, dir);

    if(drawElev) {
        const bool halfSlope = tile->isHalfSlope();
        const int tx = tile->x();
        const int ty = tile->y();
        if(!halfSlope) {
            const int a = tile->altitude();

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
            if(ta - a == 2 && a == bra && ta - tra == 1) {
                return delev.getTexture(16);
            } else if(ta - a == 2 && a == bla && ta - tla == 1) {
                return delev.getTexture(15);
            } else if(tra > a && tla > a) {
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
        } else {
            int dx;
            int dy;
            eTile* const under = eVaryingSizeTex::hiddenByNeighbour(tile, dir, dx, dy);
            if(under) {
                tile->setUnderTile(under, dx, dy);
                drawDim = 0;
                return nullptr;
            }
            const int da = tile->doubleAltitude();

            const int tra = tr ? tr->doubleAltitude() : da;
            const int ra = r ? r->doubleAltitude() : da;
            const int bra = br ? br->doubleAltitude() : da;
            const int ba = b ? b->doubleAltitude() : da;
            const int bla = bl ? bl->doubleAltitude() : da;
            const int la = l ? l->doubleAltitude() : da;
            const int tla = tl ? tl->doubleAltitude() : da;
            const int ta = t ? t->doubleAltitude() : da;

            const bool canBe2A = da % 2 == 1 && (tx + ty) % 2;
            const bool canBe2B = da % 2 == 0 && (tx + ty) % 2;
            if(canBe2A || canBe2B) {
//                const bool trw = tr ? tr->walkableElev() : false;
//                const bool rw = r ? r->walkableElev() : false;
                const bool brw = br ? br->walkableElev() : false;
                const bool bw = b ? b->walkableElev() : false;
                const bool blw = bl ? bl->walkableElev() : false;
//                const bool lw = l ? l->walkableElev() : false;
//                const bool tlw = tl ? tl->walkableElev() : false;
//                const bool tw = t ? t->walkableElev() : false;

                int relId = 0;
                if(canBe2B && bra == da && !brw && bla == da + 1 && !blw && ba == da + 1 && !bw) {
                    relId = 1;
                } else if(canBe2A && bra == da - 1 && !brw && bla == da && !blw && ba == da - 1 && !bw) {
                    relId = 2;
                } else if(canBe2A && bra == da && !brw && bla == da - 1 && !blw && ba == da - 1 && !bw) {
                    relId = 3;
                } else if(canBe2B && bra == da + 1 && !brw && bla == da && !blw && ba == da + 1 && !bw) {
                    relId = 4;
                }
                const auto& elev = textures.fHalfElevation2;
                if(relId) {
                    drawDim = 2;
                    const int segmentId = (tx/2 + ty/2) % 3;
                    return elev.getTexture(segmentId*4 + relId - 1);
                }
            }
            {
                const auto& elev = textures.fElevation;
                if(ta == da + 1 && la == da + 2) {
                    return elev.getTexture(23 - 21);
                } else if(ra == da + 2) {
                    return elev.getTexture(27 - 21);
                }
            }

            int relId = 0;
            if(bla > da) {
                relId = 0;
            } else if(tla > da) {
                relId = 2;
            } else if(tra > da) {
                relId = 4;
            } else if(bra > da) {
                relId = 6;
            }
            if(da % 2 == 0) relId++;

            const bool w = tile->walkableElev();
            int id = 0;
            if(w) {
                const bool hr = tile->hasRoad();
                if(hr) {
                    const auto r = tile->underBuilding();
                    const auto& board = r->getBoard();
                    const int dx = tile->dx();
                    const int dy = tile->dy();
                    const double appeal = board.appeal(dx, dy);
                    const bool highAppeal = appeal > 3;
                    if(highAppeal) {
                        id = 93 + relId;
                    } else {
                        id = 85 + relId;
                    }
                } else {
                    id = 77 + relId;
                }
            } else {
                id = 69 + relId;
            }
            const auto& elev = textures.fHalfElevation;
            return elev.getTexture(id - 69);
        }
    }

    if(hr || ut == eBuildingType::avenue) {
        const auto b = tile->underBuilding();
        return b->getTexture(tileSize);
    }

    switch(tile->terrain()) {
    case eTerrain::quake: {
        int texId = 0;

        const bool trs = tr && tr->terrain() == eTerrain::quake;
        const bool brs = br && br->terrain() == eTerrain::quake;
        const bool bls = bl && bl->terrain() == eTerrain::quake;
        const bool tls = tl && tl->terrain() == eTerrain::quake;

        if(trs && brs && bls && tls) {
            texId = 29;
        } else if(trs && bls && brs) {
            texId = 25;
        } else if(tls && brs && bls) {
            texId = 26;
        } else if(trs && bls && tls) {
            texId = 27;
        } else if(trs && brs && tls) {
            texId = 28;
        } else if(trs && bls) {
            texId = seed % 4;
        } else if(tls && brs) {
            texId = 4 + (seed % 4);
        } else if(trs && brs) {
            texId = 8 + (seed % 2);
        } else if(brs && bls) {
            texId = 10 + (seed % 2);
        } else if(tls && bls) {
            texId = 12 + (seed % 2);
        } else if(tls && trs) {
            texId = 14 + (seed % 2);
        } else if(trs) {
            texId = 16 + (seed % 2);
        } else if(bls) {
            texId = 18 + (seed % 2);
        } else if(brs) {
            texId = 20 + (seed % 2);
        } else if(tls) {
            texId = 22 + (seed % 2);
        } else {
            texId = 24;
        }

        const auto& coll = textures.fQuakeTexs;
        return coll.getTexture(texId);
    } break;
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
        const int toDryId = eBeachToDry::get(tile, dir);
        if(toDryId != -1) {
            const auto& coll = textures.fBeachToDryTerrainTexs;
            return coll.getTexture(toDryId);
        }
        const auto& coll = textures.fBeachTerrainTexs;
        const int texId = seed % coll.size();
        return coll.getTexture(texId);
    } break;
    case eTerrain::lava: {
        const int toDryId = eLavaToDry::get(tile, dir);
        if(toDryId != -1) {
            const auto& texs = textures.fLavaToDry[toDryId];
            const int texId = seed % texs.size();
            return texs.getTexture(texId);
        }
        const auto& coll = textures.fLava;
        const int texId = seed % coll.size();
        return coll.getTexture(texId);
    } break;
    case eTerrain::marsh: {
        const int toDryId = eMarshToDry::get(tile, dir);
        if(toDryId != -1) {
            const auto& texs = textures.fMarshToDry[toDryId];
            const int texId = seed % texs.size();
            return texs.getTexture(texId);
        }

        const eTextureCollection* coll = nullptr;
        if(!tile->isShoreTile(eTerrain::marsh)) {
            coll = &textures.fDeepMarsh;
        } else {
            coll = &textures.fMarsh;
        }
        return coll->getTexture(seed % coll->size());
    } break;
    case eTerrain::water: {
        const int cornerId = eWaterCorner::get(tile, dir);
        if(cornerId != -1) {
            const auto& coll = textures.fWaterToBeachToDryTerrainTexs;
            return coll.getTexture(cornerId);
        }
        const int toBeachId = eWaterToBeach::get(tile, dir);
        if(toBeachId != -1) {
            const auto& texs = textures.fWaterToBeachTerrainTexs[toBeachId];
            const int texId = seed % texs.size();
            return texs.getTexture(texId);
        }
        const int toDryId = eWaterToDry::get(tile, dir);
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
        const auto id = eFertileToDry::get(tile, dir);
        const int scrubCount = 12;
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
        const bool rainforest = tile->rainforest();
        if(rainforest) eGameTextures::loadPoseidonTrees();
        const auto id = eForestToDry::get(tile, dir);
        switch(id) {
        case eForestToDryId::none: {
            const auto& coll = rainforest ? textures.fPoseidonForestTerrainTexs :
                                              textures.fForestTerrainTexs;
            const int texId = seed % coll.size();
            return coll.getTexture(texId);
        } break;
        case eForestToDryId::somewhere: {
            const auto& coll = rainforest ? textures.fPoseidonForestToScrubTerrainTexs :
                                              textures.fForestToScrubTerrainTexs;
            const int scrubCount = coll.size();
            const int scrub = tile->scrubId(scrubCount) - 1;
            if(scrub == -1) {
                const auto& vec = rainforest ? textures.fPoseidonForestToDryTerrainTexs :
                                                 textures.fForestToDryTerrainTexs;;
                const int collId = seed % vec.size();
                const auto& coll = vec[collId];
                const int texId = seed % coll.size();
                return coll.getTexture(texId);
            } else {
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
                                drawDim, dir);
    } break;
    case eTerrain::copper: {
        return getStonesTexture(tile, textures.fBronzeTerrainTexs,
                                textures.fLargeBronzeTerrainTexs,
                                textures.fHugeBronzeTerrainTexs,
                                drawDim, dir);
    } break;
    case eTerrain::orichalc: {
        eGameTextures::loadOrichalc();
        return getStonesTexture(tile, textures.fOrichalcTerrainTexs,
                                textures.fLargeOrichalcTerrainTexs,
                                textures.fHugeOrichalcTerrainTexs,
                                drawDim, dir);
    } break;
    case eTerrain::silver: {
        return getStonesTexture(tile, textures.fSilverTerrainTexs,
                                textures.fLargeSilverTerrainTexs,
                                textures.fHugeSilverTerrainTexs,
                                drawDim, dir);
    } break;
    case eTerrain::tallStones: {
        return getStonesTexture(tile, textures.fTallStoneTerrainTexs,
                                textures.fLargeTallStoneTerrainTexs,
                                textures.fHugeTallStoneTerrainTexs,
                                drawDim, dir);
    } break;
    case eTerrain::marble: {
        return eMarbleTile::get(tile, textures, dir);
    } break;
    case eTerrain::blackMarble: {
        eGameTextures::loadBlackMarble();
        return eMarbleTile::get(tile, textures, dir, true);
    } break;

    case eTerrain::dryBased:
        break;

    default:
        break;
    }
    return textures.fInvalidTex;
}
