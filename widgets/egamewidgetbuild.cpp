#include "egamewidget.h"

#include "eiteratesquare.h"
#include "engine/egameboard.h"

#include "eterraineditmenu.h"

#include "buildings/allbuildings.h"

#include "characters/esheep.h"
#include "characters/egoat.h"
#include "characters/ecattle.h"

#include "evectorhelpers.h"
#include "spawners/eboarspawner.h"
#include "spawners/edeerspawner.h"
#include "spawners/eentrypoint.h"
#include "spawners/eexitpoint.h"
#include "spawners/emonsterpoint.h"
#include "spawners/elandinvasionpoint.h"
#include "spawners/eseainvasionpoint.h"
#include "spawners/edisembarkpoint.h"
#include "spawners/edisasterpoint.h"
#include "spawners/elandslidepoint.h"

#include "ebuildingstoerase.h"

#include "elanguage.h"
#include "estringhelpers.h"
#include "audio/esounds.h"

#include <algorithm>

bool agoraRoadTile(eTile* const t) {
    if(!t) return false;
    if(!t->hasRoad()) return false;
    const auto ub = t->underBuilding();
    if(!ub) return false;
    const auto r = static_cast<eRoad*>(ub);
    return !r->underAgora();
}

std::vector<eTile*> eGameWidget::agoraBuildPlaceBR(
        eTile* const tile, const eCityId cid,
        const ePlayerId pid) const {
    if(!agoraRoadTile(tile)) return {};
    const auto tr1 = tile->topRight<eTile>();
    if(!agoraRoadTile(tr1)) return {};
    const auto tr2 = tr1->topRight<eTile>();
    if(!agoraRoadTile(tr2)) return {};
    const auto tr3 = tr2->topRight<eTile>();
    if(!agoraRoadTile(tr3)) return {};
    const auto tr4 = tr3->topRight<eTile>();
    if(!agoraRoadTile(tr4)) return {};
    const auto tr5 = tr4->topRight<eTile>();
    if(!agoraRoadTile(tr5)) return {};
    std::vector<eTile*> brLobeTiles;
    brLobeTiles.push_back(tr5);
    brLobeTiles.push_back(tr4);
    brLobeTiles.push_back(tr3);
    brLobeTiles.push_back(tr2);
    brLobeTiles.push_back(tr1);
    brLobeTiles.push_back(tile);
    bool brLobe = true;
    {
        const int iMin = tile->x() + 1;
        const int iMax = iMin + 2;
        const int jMin = tile->y() - 5;
        const int jMax = jMin + 6;
        for(int i = iMin; i < iMax && brLobe; i++) {
            for(int j = jMin; j < jMax && brLobe; j++) {
                const auto t = mBoard->tile(i, j);
                brLobeTiles.push_back(t);
                const bool cb = mBoard->canBuild(i, j, 1, 1, mEditorMode, cid, pid);
                if(!cb) {
                    brLobe = false;
                    break;
                }
            }
        }
    }
    if(!brLobe) return {};
    return brLobeTiles;
}

std::vector<eTile*> eGameWidget::agoraBuildPlaceTL(
        eTile* const tile, const eCityId cid,
        const ePlayerId pid) const {
    if(!agoraRoadTile(tile)) return {};
    const auto tr1 = tile->topRight<eTile>();
    if(!agoraRoadTile(tr1)) return {};
    const auto tr2 = tr1->topRight<eTile>();
    if(!agoraRoadTile(tr2)) return {};
    const auto tr3 = tr2->topRight<eTile>();
    if(!agoraRoadTile(tr3)) return {};
    const auto tr4 = tr3->topRight<eTile>();
    if(!agoraRoadTile(tr4)) return {};
    const auto tr5 = tr4->topRight<eTile>();
    if(!agoraRoadTile(tr5)) return {};
    std::vector<eTile*> tlLobeTiles;
    tlLobeTiles.push_back(tr5);
    tlLobeTiles.push_back(tr4);
    tlLobeTiles.push_back(tr3);
    tlLobeTiles.push_back(tr2);
    tlLobeTiles.push_back(tr1);
    tlLobeTiles.push_back(tile);
    bool tlLobe = true;
    {
        const int iMin = tile->x() - 3;
        const int iMax = iMin + 2;
        const int jMin = tile->y() - 5;
        const int jMax = jMin + 6;
        for(int i = iMax; i > iMin && tlLobe; i--) {
            for(int j = jMin; j < jMax && tlLobe; j++) {
                const auto t = mBoard->tile(i, j);
                tlLobeTiles.push_back(t);
                const bool cb = mBoard->canBuild(i, j, 1, 1, mEditorMode, cid, pid);
                if(!cb) {
                    tlLobe = false;
                    break;
                }
            }
        }
    }
    if(!tlLobe) return {};
    return tlLobeTiles;
}

std::vector<eTile*> eGameWidget::agoraBuildPlaceBL(
        eTile* const tile, const eCityId cid,
        const ePlayerId pid) const {
    if(!agoraRoadTile(tile)) return {};
    const auto tl1 = tile->topLeft<eTile>();
    if(!agoraRoadTile(tl1)) return {};
    const auto tl2 = tl1->topLeft<eTile>();
    if(!agoraRoadTile(tl2)) return {};
    const auto tl3 = tl2->topLeft<eTile>();
    if(!agoraRoadTile(tl3)) return {};
    const auto tl4 = tl3->topLeft<eTile>();
    if(!agoraRoadTile(tl4)) return {};
    const auto tl5 = tl4->topLeft<eTile>();
    if(!agoraRoadTile(tl5)) return {};
    std::vector<eTile*> blLobeTiles;
    blLobeTiles.push_back(tl5);
    blLobeTiles.push_back(tl4);
    blLobeTiles.push_back(tl3);
    blLobeTiles.push_back(tl2);
    blLobeTiles.push_back(tl1);
    blLobeTiles.push_back(tile);
    bool blLobe = true;
    {
        const int iMin = tile->x() - 5;
        const int iMax = iMin + 6;
        const int jMin = tile->y() + 1;
        const int jMax = jMin + 2;
        for(int j = jMin; j < jMax && blLobe; j++) {
            for(int i = iMin; i < iMax && blLobe; i++) {
                const auto t = mBoard->tile(i, j);
                blLobeTiles.push_back(t);
                const bool cb = mBoard->canBuild(i, j, 1, 1, mEditorMode, cid, pid);
                if(!cb) {
                    blLobe = false;
                    break;
                }
            }
        }
    }
    if(!blLobe) return {};
    return blLobeTiles;
}

std::vector<eTile*> eGameWidget::agoraBuildPlaceTR(
        eTile* const tile, const eCityId cid,
        const ePlayerId pid) const {
    if(!agoraRoadTile(tile)) return {};
    const auto tl1 = tile->topLeft<eTile>();
    if(!agoraRoadTile(tl1)) return {};
    const auto tl2 = tl1->topLeft<eTile>();
    if(!agoraRoadTile(tl2)) return {};
    const auto tl3 = tl2->topLeft<eTile>();
    if(!agoraRoadTile(tl3)) return {};
    const auto tl4 = tl3->topLeft<eTile>();
    if(!agoraRoadTile(tl4)) return {};
    const auto tl5 = tl4->topLeft<eTile>();
    if(!agoraRoadTile(tl5)) return {};
    std::vector<eTile*> trLobeTiles;
    trLobeTiles.push_back(tl5);
    trLobeTiles.push_back(tl4);
    trLobeTiles.push_back(tl3);
    trLobeTiles.push_back(tl2);
    trLobeTiles.push_back(tl1);
    trLobeTiles.push_back(tile);
    bool trLobe = true;
    {
        const int iMin = tile->x() - 5;
        const int iMax = iMin + 6;
        const int jMin = tile->y() - 3;
        const int jMax = jMin + 2;
        for(int j = jMax; j > jMin && trLobe; j--) {
            for(int i = iMin; i < iMax && trLobe; i++) {
                const auto t = mBoard->tile(i, j);
                trLobeTiles.push_back(t);
                const bool cb = mBoard->canBuild(i, j, 1, 1, mEditorMode, cid, pid);
                if(!cb) {
                    trLobe = false;
                    break;
                }
            }
        }
    }
    if(!trLobe) return {};
    return trLobeTiles;
}

std::vector<eTile*> eGameWidget::agoraBuildPlaceIter(
        eTile* const tile, const bool grand,
        eAgoraOrientation& bt, const eCityId cid,
        const ePlayerId pid) const {
    if(!tile) return {};
    {
        const int xMin = tile->x() - 2;
        const int xMax = xMin + 3;
        const int yMin = tile->y() + 2;
        const int yMax = yMin + 3;
        for(int x = xMin; x < xMax; x++) {
            for(int y = yMin; y < yMax; y++) {
                const auto t = mBoard->tile(x, y);
                if(!t) continue;
                const auto r = agoraBuildPlaceBR(t, cid, pid);
                if(r.empty()) continue;
                bt = eAgoraOrientation::bottomRight;
                if(grand) {
                    const auto rr = agoraBuildPlaceTL(t, cid, pid);
                    if(rr.empty()) continue;
                    std::vector<eTile*> rrr;
                    rrr.reserve(r.size() + rr.size());
                    rrr.insert(rrr.end(), rr.begin(), rr.end());
                    rrr.insert(rrr.end(), r.begin(), r.end());
                    return rrr;
                }
                return r;
            }
        }
    }
    {
        const int xMin = tile->x();
        const int xMax = xMin + 3;
        const int yMin = tile->y() + 2;
        const int yMax = yMin + 3;
        for(int x = xMin; x < xMax; x++) {
            for(int y = yMin; y < yMax; y++) {
                const auto t = mBoard->tile(x, y);
                if(!t) continue;
                const auto r = agoraBuildPlaceTL(t, cid, pid);
                if(r.empty()) continue;

                if(grand) {
                    bt = eAgoraOrientation::bottomRight;
                    const auto rr = agoraBuildPlaceBR(t, cid, pid);
                    if(rr.empty()) continue;
                    std::vector<eTile*> rrr;
                    rrr.reserve(r.size() + rr.size());
                    rrr.insert(rrr.end(), r.begin(), r.end());
                    rrr.insert(rrr.end(), rr.begin(), rr.end());
                    return rrr;
                } else {
                    bt = eAgoraOrientation::topLeft;
                }
                return r;
            }
        }
    }
    {
        const int xMin = tile->x() + 2;
        const int xMax = xMin + 3;
        const int yMin = tile->y() - 2;
        const int yMax = yMin + 3;
        for(int x = xMin; x < xMax; x++) {
            for(int y = yMin; y < yMax; y++) {
                const auto t = mBoard->tile(x, y);
                if(!t) continue;
                const auto r = agoraBuildPlaceBL(t, cid, pid);
                if(r.empty()) continue;
                bt = eAgoraOrientation::bottomLeft;
                if(grand) {
                    const auto rr = agoraBuildPlaceTR(t, cid, pid);
                    if(rr.empty()) continue;
                    std::vector<eTile*> rrr;
                    rrr.reserve(r.size() + rr.size());
                    rrr.insert(rrr.end(), rr.begin(), rr.end());
                    rrr.insert(rrr.end(), r.begin(), r.end());
                    return rrr;
                }
                return r;
            }
        }
    }
    {
        const int xMin = tile->x() + 2;
        const int xMax = xMin + 3;
        const int yMin = tile->y();
        const int yMax = yMin + 3;
        for(int x = xMin; x < xMax; x++) {
            for(int y = yMin; y < yMax; y++) {
                const auto t = mBoard->tile(x, y);
                if(!t) continue;
                const auto r = agoraBuildPlaceTR(t, cid, pid);
                if(r.empty()) continue;
                if(grand) {
                    bt = eAgoraOrientation::bottomLeft;
                    const auto rr = agoraBuildPlaceBL(t, cid, pid);
                    if(rr.empty()) continue;
                    std::vector<eTile*> rrr;
                    rrr.reserve(r.size() + rr.size());
                    rrr.insert(rrr.end(), r.begin(), r.end());
                    rrr.insert(rrr.end(), rr.begin(), rr.end());
                    return rrr;
                } else {
                    bt = eAgoraOrientation::topRight;
                }
                return r;
            }
        }
    }
    return {};
}

template <class T>
bool buildVendor(eGameBoard& brd, const int tx, const int ty,
                 const eResourceType resType, const eCityId cid) {
    const auto t = brd.tile(tx, ty);
    if(!t) return false;
    const auto b = t->underBuilding();
    if(!b) return false;
    const auto bt = b->type();
    if(bt != eBuildingType::agoraSpace) return false;
    const auto space = static_cast<eAgoraSpace*>(b);
    const auto ct = space->centerTile();
    if(!ct) return false;
    if(ct->x() != tx || ct->y() != ty) return false;
    const auto agora = space->agora();
    if(agora->vendor(resType)) return false;
    const auto agoraP = agora->ref<eAgoraBase>();
    const auto fv = e::make_shared<T>(brd, cid);
    fv->setAgora(agoraP);
    agora->setBuilding(space, fv);
    const auto ppid = brd.personPlayer();
    const auto diff = brd.difficulty(ppid);
    const int cost = eDifficultyHelpers::buildingCost(diff, fv->type());
    brd.incDrachmas(ppid, -cost, eFinanceTarget::construction);
    return true;
}

eGameWidget::eApply eGameWidget::editFunc() {
    const auto mode = mTem->mode();
    const int modeId = mTem->modeId();
    if(mode == eTerrainEditMode::none) {
        return nullptr;
    } else if(mode == eTerrainEditMode::scrub) {
        return [](eTile* const tile) {
            tile->incScrub(0.1);
        };
    } else if(mode == eTerrainEditMode::scrubArea) {
        return [this](eTile* const tile) {
            int dist = 100;
            for(int k = 1; k < 100; k++) {
                eIterateSquare::iterateDistance(k, [&dist, k, this, tile](const int dx, const int dy) {
                    const auto t = tile->tileRel<eTile>(dx, dy);
                    const bool r = eVectorHelpers::contains(mInflTiles, t);
                    if(!r) {
                        dist = k;
                        return true;
                    }
                    return false;
                });
                if(dist != 100) break;
            }
            tile->incScrub(dist*0.05);
        };
    } else if(mode == eTerrainEditMode::removeScrub) {
        return [](eTile* const tile) {
            tile->incScrub(-0.1);
        };
    }  else if(mode == eTerrainEditMode::softenScrub) {
        return [](eTile* const tile) {
            const auto ns = tile->neighbours(nullptr);
            double ss = tile->scrub();
            for(const auto& t : ns) {
                const auto tt = static_cast<eTile*>(t.second);
                ss += tt->scrub();
            }
            ss = ss/(1 + ns.size());
            tile->setScrub(ss);
        };
    } else if(mode == eTerrainEditMode::rainforest) {
        return [](eTile* const tile) {
            tile->setRainforest(true);
        };
    } else if(mode == eTerrainEditMode::normalForest) {
        return [](eTile* const tile) {
            tile->setRainforest(false);
        };
    } else if(mode == eTerrainEditMode::raise) {
        return [](eTile* const tile) {
            tile->setAltitude(tile->altitude() + 1);
        };
    } else if(mode == eTerrainEditMode::lower) {
        return [](eTile* const tile) {
            tile->setAltitude(tile->altitude() - 1);
        };
    } else if(mode == eTerrainEditMode::raiseHigh) {
        return [](eTile* const tile) {
            tile->setAltitude(tile->altitude() + 2);
        };
    } else if(mode == eTerrainEditMode::lowerHigh) {
        return [](eTile* const tile) {
            tile->setAltitude(tile->altitude() - 2);
        };
    } else if(mode == eTerrainEditMode::quake) {
        return [](eTile* const tile) {
            tile->setTerrain(eTerrain::quake);
        };
    } else if(mode == eTerrainEditMode::lava) {
        return [](eTile* const tile) {
            tile->setLavaZone(!tile->lavaZone());
        };
    } else if(mode == eTerrainEditMode::tidalWave) {
        return [](eTile* const tile) {
            tile->setTidalWaveZone(!tile->tidalWaveZone());
        };
    } else if(mode == eTerrainEditMode::landSlide) {
        return [](eTile* const tile) {
            tile->setLandSlideZone(!tile->landSlideZone());
        };
    } else if(mode == eTerrainEditMode::levelOut) {
        const auto t = mBoard->tile(mPressedTX, mPressedTY);
        if(t) {
            const int a = t->altitude();
            return [a](eTile* const tile) {
                tile->setAltitude(a);
            };
        }
    } else if(mode == eTerrainEditMode::resetElev) {
        return [](eTile* const tile) {
            tile->setAltitude(0);
        };
    } else if(mode == eTerrainEditMode::makeWalkable) {
        return [](eTile* const tile) {
            tile->setWalkableElev(!tile->walkableElev());
        };
    } else if(mode == eTerrainEditMode::halfSlope) {
        return [](eTile* const tile) {
            const int a = tile->altitude();
            const auto ns = tile->diagonalNeighbours(nullptr);
            for(const auto& n : ns) {
                const auto ntile = static_cast<eTile*>(n.second);
                const int na = ntile->altitude();
                if(na > a && tile->doubleAltitude() % 2 == 0) {
                    tile->setDoubleAltitude(2*na - 1);
                } else {
                    tile->setDoubleAltitude(2*a);
                }
            }
        };
    } else if(mode == eTerrainEditMode::boar) {
        return [this, modeId](eTile* const tile) {
            const auto b = std::make_shared<eBoarSpawner>(
                               modeId, tile, *mBoard);
            tile->addBanner(b);
        };
    } else if(mode == eTerrainEditMode::fish) {
        return [](eTile* const tile) {
            tile->setHasFish(!tile->hasFish());
        };
    } else if(mode == eTerrainEditMode::urchin) {
        return [](eTile* const tile) {
            tile->setHasUrchin(!tile->hasUrchin());
        };
    } else if(mode == eTerrainEditMode::deer) {
        return [this, modeId](eTile* const tile) {
            const auto b = std::make_shared<eDeerSpawner>(
                               modeId, tile, *mBoard);
            tile->addBanner(b);
        };
    } else if(mode == eTerrainEditMode::fire) {
        return [](eTile* const tile) {
            tile->setOnFire(true);
        };
    } else if(mode == eTerrainEditMode::ruins) {
        return [this](eTile* const tile) {
            const auto pid = mBoard->personPlayer();
            mBoard->build(tile->x(), tile->y(), 1, 1, mViewedCityId, pid, false,
                  [this]() { return e::make_shared<eRuins>(*mBoard, mViewedCityId); });
        };
    } else if(mode == eTerrainEditMode::entryPoint) {
        return [this, modeId](eTile* const tile) {
            const auto b = std::make_shared<eEntryPoint>(
                               modeId, tile, *mBoard);
            tile->addBanner(b);
        };
    } else if(mode == eTerrainEditMode::exitPoint) {
        return [this, modeId](eTile* const tile) {
            const auto b = std::make_shared<eExitPoint>(
                               modeId, tile, *mBoard);
            tile->addBanner(b);
        };
    } else if(mode == eTerrainEditMode::riverEntryPoint) {
        return [this, modeId](eTile* const tile) {
            const auto b = std::make_shared<eRiverEntryPoint>(
                modeId, tile, *mBoard);
            tile->addBanner(b);
        };
    } else if(mode == eTerrainEditMode::riverExitPoint) {
        return [this, modeId](eTile* const tile) {
            const auto b = std::make_shared<eRiverExitPoint>(
                modeId, tile, *mBoard);
            tile->addBanner(b);
        };
    } else if(mode == eTerrainEditMode::landInvasion) {
        return [this, modeId](eTile* const tile) {
            const auto b = std::make_shared<eLandInvasionPoint>(
                               modeId, tile, *mBoard);
            tile->addBanner(b);
        };
    } else if(mode == eTerrainEditMode::seaInvasion) {
        return [this, modeId](eTile* const tile) {
            const auto b = std::make_shared<eSeaInvasionPoint>(
                               modeId, tile, *mBoard);
            tile->addBanner(b);
        };
    } else if(mode == eTerrainEditMode::disembarkPoint) {
        return [this, modeId](eTile* const tile) {
            const auto b = std::make_shared<eDisembarkPoint>(
                               modeId, tile, *mBoard);
            tile->addBanner(b);
        };
    } else if(mode == eTerrainEditMode::monsterPoint) {
        return [this, modeId](eTile* const tile) {
            const auto b = std::make_shared<eMonsterPoint>(
                               modeId, tile, *mBoard);
            tile->addBanner(b);
        };
    } else if(mode == eTerrainEditMode::disasterPoint) {
        return [this, modeId](eTile* const tile) {
            const auto b = std::make_shared<eDisasterPoint>(
                               modeId, tile, *mBoard);
            tile->addBanner(b);
        };
    } else if(mode == eTerrainEditMode::landSlidePoint) {
        return [this, modeId](eTile* const tile) {
            const auto b = std::make_shared<eLandSlidePoint>(
                modeId, tile, *mBoard);
            tile->addBanner(b);
        };
    } else if(mode == eTerrainEditMode::cityTerritory) {
        return [modeId](eTile* const tile) {
            const auto cid = static_cast<eCityId>(modeId);
            tile->setCityId(cid);
        };
    } else {
        return [mode](eTile* const tile) {
            const auto terr = static_cast<eTerrain>(mode);
            tile->setTerrain(terr);
        };
    }
    return nullptr;
}

bool eGameWidget::buildMouseRelease() {
    const auto cid = mViewedCityId;
    const auto pid = mBoard->personPlayer();

    const auto& wrld = mBoard->world();
    const auto ppid = mBoard->personPlayer();
    eApply apply;
    bool r = false;
    const auto mode = mGm->mode();
    if(mTem->visible()) {
//        const auto brushType = mTem->brushType();
//        if(brushType != eBrushType::apply) return true;
        apply = editFunc();
        if(!apply) {
            mInflTiles.clear();
            return true;
        }
    } else {
        const int d = mBoard->drachmas(ppid);
        if(mode != eBuildingMode::none && d < -1000) {
            showTip(pid, eLanguage::zeusText(19, 19)); // out of credit
            return false;
        }
        switch(mode) {
        case eBuildingMode::none: {
            return false;
        } break;
        case eBuildingMode::erase: {
            eBuildingsToErase eraser;

            const int minX = std::min(mPressedTX, mHoverTX);
            const int minY = std::min(mPressedTY, mHoverTY);
            const int maxX = std::max(mPressedTX, mHoverTX);
            const int maxY = std::max(mPressedTY, mHoverTY);

            const auto diff = mBoard->difficulty(ppid);
            const int cost = eDifficultyHelpers::buildingCost(
                                 diff, eBuildingType::erase);
            int totalCost = 0;
            for(int x = minX; x <= maxX; x++) {
                for(int y = minY; y <= maxY; y++) {
                    const auto tile = mBoard->tile(x, y);
                    if(!tile) continue;
                    const auto cid = tile->cityId();
                    const auto pid = mBoard->cityIdToPlayerId(cid);
                    if(pid != ppid && !mEditorMode) continue;
                    if(const auto b = tile->underBuilding()) {
                        if(b->isOnFire()) continue;
                        eraser.addBuilding(b);
                    } else {
                        const auto t = tile->terrain();
                        if(t == eTerrain::forest || t == eTerrain::choppedForest) {
                            tile->setTerrain(eTerrain::dry);
                            const auto c = mBoard->boardCityWithId(cid);
                            if(c) c->incForestsState();
                            totalCost += cost;
                        }
                    }
                }
            }

            const int nErased = eraser.erase(false);
            totalCost += cost*nErased;
            if(!mEditorMode) mBoard->incDrachmas(ppid, -totalCost, eFinanceTarget::construction);
            mBoard->scheduleTerrainUpdate();

            std::string title;
            std::string text;
            if(eraser.hasImportantBuildings()) {
                title = eLanguage::zeusText(5, 104);
                text = eLanguage::zeusText(5, 105);
            } else if(eraser.hasNonEmptyAgoras()) {
                title = eLanguage::zeusText(5, 16);
                text = eLanguage::zeusText(5, 17);
            } else {
                return false;
            }
            const auto acceptA = [this, ppid, cost, eraser]() {
                auto e = eraser;
                const int nErased = e.erase(true);
                const int totalCost = cost*nErased;
                if(!mEditorMode) mBoard->incDrachmas(ppid, -totalCost, eFinanceTarget::construction);
            };
            showQuestion(title, text, acceptA);
        } break;
        case eBuildingMode::commonAgora: {
            const auto t = mBoard->tile(mHoverTX, mHoverTY);
            if(!t) return false;
            eAgoraOrientation bt;
            const auto p = agoraBuildPlaceIter(t, false, bt, cid, pid);
            if(p.empty()) return false;
            const auto b = e::make_shared<eCommonAgora>(bt, *mBoard, mViewedCityId);
            r = true;
            int x = __INT_MAX__;
            int y = __INT_MAX__;
            int w;
            int h;
            int ri = 0;
            for(const auto t : p) {
                const int tx = t->x();
                const int ty = t->y();
                if(tx < x) x = tx;
                if(ty < y) y = ty;
                if(t->hasRoad()) {
                    const auto bb = t->underBuilding();
                    const auto r = static_cast<eRoad*>(bb);
                    r->setUnderAgora(b.get());
                    if(ri++ == 3) b->setCenterTile(t);
                } else {
                    b->addUnderBuilding(t);
                }
            }
            switch(bt) {
            case eAgoraOrientation::bottomLeft:
            case eAgoraOrientation::topRight:
                w = 6;
                h = 3;
                break;
            case eAgoraOrientation::bottomRight:
            case eAgoraOrientation::topLeft:
                w = 3;
                h = 6;
                break;
            }

            b->setTileRect(SDL_Rect{x, y, w, h});

            b->fillSpaces();

            if(!mEditorMode) {
                const auto diff = mBoard->difficulty(ppid);
                const int cost = eDifficultyHelpers::buildingCost(diff, b->type());
                mBoard->incDrachmas(ppid, -cost, eFinanceTarget::construction);
            }

            showTip(cid, eLanguage::zeusText(19, 228)); // add vendors
        } break;
        case eBuildingMode::grandAgora: {
            const auto t = mBoard->tile(mHoverTX, mHoverTY);
            if(!t) return false;
            eAgoraOrientation bt;
            const auto p = agoraBuildPlaceIter(t, true, bt, cid, pid);
            if(p.empty()) return false;
            const auto b = e::make_shared<eGrandAgora>(bt, *mBoard, mViewedCityId);
            r = true;
            int x = __INT_MAX__;
            int y = __INT_MAX__;
            int w;
            int h;
            int ri = 0;
            for(const auto t : p) {
                const int tx = t->x();
                const int ty = t->y();
                if(tx < x) x = tx;
                if(ty < y) y = ty;
                if(t->hasRoad()) {
                    const auto bb = t->underBuilding();
                    const auto r = static_cast<eRoad*>(bb);
                    r->setUnderAgora(b.get());
                    if(ri++ == 3) b->setCenterTile(t);
                } else {
                    b->addUnderBuilding(t);
                }
            }
            switch(bt) {
            case eAgoraOrientation::bottomLeft:
            case eAgoraOrientation::topRight:
                w = 6;
                h = 5;
                break;
            case eAgoraOrientation::bottomRight:
            case eAgoraOrientation::topLeft:
                w = 5;
                h = 6;
                break;
            }

            b->setTileRect(SDL_Rect{x, y, w, h});

            b->fillSpaces();

            if(!mEditorMode) {
                const auto diff = mBoard->difficulty(ppid);
                const int cost = eDifficultyHelpers::buildingCost(diff, b->type());
                mBoard->incDrachmas(ppid, -cost, eFinanceTarget::construction);
            }
            showTip(cid, eLanguage::zeusText(19, 228)); // add vendors
        } break;
        case eBuildingMode::road: {
            const auto startTile = mBoard->tile(mHoverTX, mHoverTY);
            if(!startTile) return false;
            std::vector<eOrientation> path;
            const bool r = roadPath(path);
            if(r) {
                eTile* t = startTile;
                for(int i = path.size() - 1; i >= 0; i--) {
                    if(!t) break;
                    mBoard->build(t->x(), t->y(), 1, 1, cid, pid, mEditorMode,
                          [this]() { return e::make_shared<eRoad>(*mBoard, mViewedCityId); },
                          false, true);
                    t = t->neighbour<eTile>(path[i]);
                }
                if(t) {
                    mBoard->build(t->x(), t->y(), 1, 1, cid, pid, mEditorMode,
                          [this]() { return e::make_shared<eRoad>(*mBoard, mViewedCityId); },
                          false, true);
                }
            } else {
                mBoard->build(startTile->x(), startTile->y(), 1, 1, cid, pid, mEditorMode,
                      [this]() { return e::make_shared<eRoad>(*mBoard, mViewedCityId); },
                      false, true);
            }
        } break;
        case eBuildingMode::roadblock: {
            const auto t = mBoard->tile(mHoverTX, mHoverTY);
            if(t && t->hasRoad() && !t->hasBridge()) {
                const auto b = t->underBuilding();
                const auto r = static_cast<eRoad*>(b);
                const bool rb = r->isRoadblock();
                if(!rb) r->setRoadblock(true);
            }
        } break;
        case eBuildingMode::bridge: {
            const auto startTile = mBoard->tile(mHoverTX, mHoverTY);
            if(!startTile) return false;
            std::vector<eTile*> path;
            bool rotated;
            bool r = bridgeTiles(startTile, eTerrain::water, path, rotated);
            if(!r) r = bridgeTiles(startTile, eTerrain::quake, path, rotated);
            if(r) {
                for(const auto t : path) {
                    const auto b = e::make_shared<eRoad>(*mBoard, mViewedCityId);
                    b->setCenterTile(t);
                    b->setTileRect({t->x(), t->y(), 1, 1});
                    t->setUnderBuilding(b);
                    b->addUnderBuilding(t);
                }

                if(!mEditorMode) {
                    const auto diff = mBoard->difficulty(ppid);
                    const int cost = eDifficultyHelpers::buildingCost(
                                         diff, eBuildingType::bridge);
                    mBoard->incDrachmas(ppid, -path.size()*cost, eFinanceTarget::construction);
                }
            }
        } break;
        case eBuildingMode::commonHousing: {
            const int sMinX = std::min(mPressedTX, mHoverTX);
            const int sMinY = std::min(mPressedTY, mHoverTY);
            const int sMaxX = std::max(mPressedTX, mHoverTX);
            const int sMaxY = std::max(mPressedTY, mHoverTY);

            for(int x = sMinX; x <= sMaxX; x++) {
                for(int y = sMinY - 1; y <= sMaxY; y++) {
                    const bool cb = mBoard->canBuildBase(x, x + 2, y, y + 2, mEditorMode, cid, pid);
                    if(!cb) continue;
                    const auto t = mBoard->tile(x, y);
                    if(!t) continue;
                    r = mBoard->build(t->x(), t->y() + 1, 2, 2, cid, pid, mEditorMode,
                          [this]() { return e::make_shared<eSmallHouse>(*mBoard, mViewedCityId); }) || r;
                }
            }
        } break;
        case eBuildingMode::gymnasium: {
            r = mBoard->build(mHoverTX, mHoverTY, 3, 3, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eGymnasium>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::podium: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<ePodium>(*mBoard, mViewedCityId); });

            if(!mBoard->hasBuilding(mViewedCityId, eBuildingType::college)) {
                showTip(cid, eLanguage::zeusText(19, 223)); // build college
            }
        } break;


        case eBuildingMode::bibliotheke: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eBibliotheke>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::observatory: {
            r = mBoard->build(mHoverTX, mHoverTY, 5, 5, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eObservatory>(*mBoard, mViewedCityId); });

            if(!mBoard->hasBuilding(mViewedCityId, eBuildingType::university)) {
                showTip(cid, eLanguage::zeusText(19, 244)); // build university
            }
        } break;
        case eBuildingMode::university: {
            r = mBoard->build(mHoverTX, mHoverTY, 3, 3, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eUniversity>(*mBoard, mViewedCityId); });

            if(!mBoard->hasBuilding(mViewedCityId, eBuildingType::observatory)) {
                showTip(cid, eLanguage::zeusText(19, 243)); // build observatory
            }
        } break;
        case eBuildingMode::laboratory: {
            r = mBoard->build(mHoverTX, mHoverTY, 4, 4, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eLaboratory>(*mBoard, mViewedCityId); });

            if(!mBoard->hasBuilding(mViewedCityId, eBuildingType::inventorsWorkshop)) {
                showTip(cid, eLanguage::zeusText(19, 247)); // build inventors' workshop
            }
        } break;
        case eBuildingMode::inventorsWorkshop: {
            r = mBoard->build(mHoverTX, mHoverTY, 3, 3, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eInventorsWorkshop>(*mBoard, mViewedCityId); });

            if(!mBoard->hasBuilding(mViewedCityId, eBuildingType::laboratory)) {
                showTip(cid, eLanguage::zeusText(19, 246)); // build laboratory
            }
        } break;
        case eBuildingMode::museum: {
            r = mBoard->build(mHoverTX, mHoverTY, 6, 6, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eMuseum>(*mBoard, mViewedCityId); });

            if(!mBoard->hasBuilding(mViewedCityId, eBuildingType::university)) {
                showTip(cid, eLanguage::zeusText(19, 248)); // build universities
            }
            mGm->clearMode();
        } break;

        case eBuildingMode::fountain: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eFountain>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::watchpost: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eWatchpost>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::maintenanceOffice: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eMaintenanceOffice>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::college: {
            r = mBoard->build(mHoverTX, mHoverTY, 3, 3, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eCollege>(*mBoard, mViewedCityId); });

            if(!mBoard->hasBuilding(mViewedCityId, eBuildingType::podium)) {
                showTip(cid, eLanguage::zeusText(19, 222)); // build podiums
            }
        } break;
        case eBuildingMode::dramaSchool: {
            r = mBoard->build(mHoverTX, mHoverTY, 3, 3, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eDramaSchool>(*mBoard, mViewedCityId); });

            if(!mBoard->hasBuilding(mViewedCityId, eBuildingType::theater)) {
                showTip(cid, eLanguage::zeusText(19, 225)); // build theater
            }
        } break;
        case eBuildingMode::theater: {
            r = mBoard->build(mHoverTX, mHoverTY, 5, 5, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eTheater>(*mBoard, mViewedCityId); });

            if(!mBoard->hasBuilding(mViewedCityId, eBuildingType::dramaSchool)) {
                showTip(cid, eLanguage::zeusText(19, 226)); // build a drama school
            }
        } break;
        case eBuildingMode::hospital: {
            r = mBoard->build(mHoverTX, mHoverTY, 4, 4, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eHospital>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::stadium: {
            if(mBoard->hasStadium(mViewedCityId)) return true;
            int dx;
            int dy;
            int sw;
            int sh;
            if(mRotate) {
                dx = 0;
                dy = 5;
                sw = 5;
                sh = 10;
            } else {
                dx = 5;
                dy = 0;
                sw = 10;
                sh = 5;
            }
            const auto t1 = mBoard->tile(mHoverTX, mHoverTY);
            if(!t1) return true;
            const bool cb1 = mBoard->canBuild(t1->x(), t1->y(), 5, 5, mEditorMode, cid, pid);
            if(!cb1) return true;
            const auto t2 = t1->tileRel<eTile>(dx, dy);
            if(!t2) return true;
            const bool cb2 = mBoard->canBuild(t2->x(), t2->y(), 5, 5, mEditorMode, cid, pid);
            if(!cb2) return true;
            r = mBoard->build(t1->x(), t1->y(), sw, sh, cid, pid, mEditorMode, [&]() {
                return e::make_shared<eStadium>(*mBoard, mRotate, mViewedCityId);
            });
            mGm->clearMode();

            if(!mBoard->hasBuilding(mViewedCityId, eBuildingType::gymnasium)) {
                showTip(cid, eLanguage::zeusText(19, 227)); // build gymnsaium
            }
        } break;
        case eBuildingMode::palace: {
            if(mBoard->hasPalace(mViewedCityId)) return true;
            if(mBoard->hasActiveInvasions(mViewedCityId)) {
                showTip(cid, eLanguage::zeusText(19, 33)); // too close to enemy
                return true;
            }
            const int tx = mHoverTX;
            const int ty = mHoverTY;
            int dx;
            int dy;
            int sw;
            int sh;
            const int tminX = tx - 2;
            const int tminY = ty - 3;
            int tmaxX;
            int tmaxY;
            const auto forAllTiles = [&](const std::function<void(int, int)>& prc) {
                const SDL_Rect rect{tminX + 1, tminY + 1, sw, sh};
                for(int x = tminX; x < tmaxX; x++) {
                    for(int y = tminY; y < tmaxY; y++) {
                        const SDL_Point pt{x, y};
                        const bool r = SDL_PointInRect(&pt, &rect);
                        if(r) continue;
                        const bool cb = mBoard->canBuild(x, y, 1, 1, mEditorMode, cid, pid);
                        if(!cb) return false;
                        if(prc) prc(x, y);
                    }
                }
                return true;
            };
            if(mRotate) {
                dx = 0;
                dy = 4;
                sw = 4;
                sh = 8;
                tmaxX = tminX + 6;
                tmaxY = tminY + 9;
            } else {
                dx = 4;
                dy = 0;
                sw = 8;
                sh = 4;
                tmaxX = tminX + 9;
                tmaxY = tminY + 6;
            }
            const bool cb0 = forAllTiles(nullptr);
            if(!cb0) return true;
            const auto t1 = mBoard->tile(tx, ty);
            if(!t1) return true;
            const bool cb1 = mBoard->canBuild(t1->x(), t1->y(), 4, 4, mEditorMode, cid, pid);
            if(!cb1) return true;
            const auto t2 = t1->tileRel<eTile>(dx, dy);
            if(!t2) return true;
            const bool cb2 = mBoard->canBuild(t2->x(), t2->y(), 4, 4, mEditorMode, cid, pid);
            if(!cb2) return true;
            const auto s = e::make_shared<ePalace>(*mBoard, mRotate, mViewedCityId);
            forAllTiles([&](const int x, const int y) {
                mBoard->build(x, y, 1, 1, cid, pid, mEditorMode, [&]() {
                    bool other = x == tminX && y == tminY;
                    if(!other) {
                        if(mRotate) {
                            other = x == tmaxX - 1 && y == tminY;
                        } else {
                            other = x == tminX && y == tmaxY - 1;
                        }
                    }
                    const auto t = e::make_shared<ePalaceTile>(
                                       *mBoard, other, mViewedCityId);
                    t->setPalace(s.get());
                    s->addTile(t.get());
                    return t;
                });
            });
            r = mBoard->build(tx, ty, sw, sh, cid, pid, mEditorMode, [&]() {
                return s;
            });

            mGm->clearMode();
        } break;
        case eBuildingMode::eliteHousing: {
            const auto t1 = mBoard->tile(mHoverTX, mHoverTY);
            if(!t1) return true;
            const bool cb = mBoard->canBuild(t1->x() + 1, t1->y() + 1, 4, 4, mEditorMode, cid, pid);
            if(!cb) return true;
            r = mBoard->build(t1->x() + 1, t1->y() + 1, 4, 4, cid, pid, mEditorMode, [&]() {
                return e::make_shared<eEliteHousing>(*mBoard, mViewedCityId);
            });
        } break;
        case eBuildingMode::taxOffice: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eTaxOffice>(*mBoard, mViewedCityId); });
            if(!mBoard->hasPalace(mViewedCityId)) {
                showTip(cid, eLanguage::zeusText(19, 221));
            }
        } break;
        case eBuildingMode::mint: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eMint>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::foundry: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eFoundry>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::timberMill: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eTimberMill>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::masonryShop: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eMasonryShop>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::refinery: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eRefinery>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::blackMarbleWorkshop: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eBlackMarbleWorkshop>(*mBoard, mViewedCityId); });
        } break;


        case eBuildingMode::oliveTree:
            apply = [this, cid, pid](eTile* const tile) {
                mBoard->build(tile->x(), tile->y(), 1, 1, cid, pid, mEditorMode,
                      [this]() { return e::make_shared<eResourceBuilding>(
                                *mBoard, eResourceBuildingType::oliveTree, mViewedCityId); },
                      true, true);
            };
            break;
        case eBuildingMode::vine:
            apply = [this, cid, pid](eTile* const tile) {
                mBoard->build(tile->x(), tile->y(), 1, 1, cid, pid, mEditorMode,
                      [this]() { return e::make_shared<eResourceBuilding>(
                                *mBoard, eResourceBuildingType::vine, mViewedCityId); },
                      true, true);
            };
            break;
        case eBuildingMode::orangeTree:
            apply = [this, cid, pid](eTile* const tile) {
                mBoard->build(tile->x(), tile->y(), 1, 1, cid, pid, mEditorMode,
                      [this]() { return e::make_shared<eResourceBuilding>(
                                *mBoard, eResourceBuildingType::orangeTree, mViewedCityId); },
                      true, true);
            };
            break;


        case eBuildingMode::huntingLodge: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eHuntingLodge>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::corral: {
            r = mBoard->build(mHoverTX, mHoverTY, 4, 4, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eCorral>(*mBoard, mViewedCityId); });

            if(!mBoard->hasBuilding(mViewedCityId, eBuildingType::cattle)) {
                showTip(cid, eLanguage::zeusText(19, 255));
                showTip(cid, eLanguage::zeusText(19, 256));
            }
        } break;


        case eBuildingMode::urchinQuay: {
            eDiagonalOrientation o;
            const bool c = canBuildFishery(mHoverTX, mHoverTY, o);
            if(c) {
                r = true;
                const auto b = e::make_shared<eUrchinQuay>(*mBoard, o, mViewedCityId);
                const auto tile = mBoard->tile(mHoverTX, mHoverTY);
                b->setCenterTile(tile);

                const int minY = mHoverTY - 1;
                b->setTileRect({mHoverTX, minY, 2, 2});
                for(int x = mHoverTX; x < mHoverTX + 2; x++) {
                    for(int y = minY; y < minY + 2; y++) {
                        const auto t = mBoard->tile(x, y);
                        if(t) {
                            t->setUnderBuilding(b);
                            b->addUnderBuilding(t);
                        }
                    }
                }

                if(!mEditorMode) {
                    const auto diff = mBoard->difficulty(ppid);
                    const int cost = eDifficultyHelpers::buildingCost(
                                         diff, eBuildingType::urchinQuay);
                    mBoard->incDrachmas(ppid, -cost, eFinanceTarget::construction);
                }
            }
        } break;
        case eBuildingMode::fishery: {
            eDiagonalOrientation o;
            const bool c = canBuildFishery(mHoverTX, mHoverTY, o);
            if(c) {
                r = true;
                const auto b = e::make_shared<eFishery>(*mBoard, o, mViewedCityId);
                const auto tile = mBoard->tile(mHoverTX, mHoverTY);
                b->setCenterTile(tile);

                const int minY = mHoverTY - 1;
                b->setTileRect({mHoverTX, minY, 2, 2});
                for(int x = mHoverTX; x < mHoverTX + 2; x++) {
                    for(int y = minY; y < minY + 2; y++) {
                        const auto t = mBoard->tile(x, y);
                        if(t) {
                            t->setUnderBuilding(b);
                            b->addUnderBuilding(t);
                        }
                    }
                }

                if(!mEditorMode) {
                    const auto diff = mBoard->difficulty(ppid);
                    const int cost = eDifficultyHelpers::buildingCost(
                                         diff, eBuildingType::fishery);
                    mBoard->incDrachmas(ppid, -cost, eFinanceTarget::construction);
                }
            }
        } break;
        case eBuildingMode::triremeWharf: {
            eDiagonalOrientation o;
            const bool c = canBuildTriremeWharf(mHoverTX, mHoverTY, o);
            if(c) {
                r = true;
                const int minX = mHoverTX - 1;
                const int minY = mHoverTY - 1;

                bool accessToSea = false;
                for(int x = minX; x < minX + 3; x++) {
                    for(int y = minY; y < minY + 3; y++) {
                        const auto t = mBoard->tile(x, y);
                        if(!t) continue;
                        if(t->hasWater()) {
                            accessToSea = waterTileHasAccessToSea(x, y);
                            x += 3;
                            break;
                        }
                    }
                }

                if(accessToSea) {
                    const auto b = e::make_shared<eTriremeWharf>(*mBoard, o, mViewedCityId);
                    const auto tile = mBoard->tile(mHoverTX, mHoverTY);
                    b->setCenterTile(tile);

                    b->setTileRect({minX, minY, 3, 3});
                    for(int x = minX; x < minX + 3; x++) {
                        for(int y = minY; y < minY + 3; y++) {
                            const auto t = mBoard->tile(x, y);
                            if(t) {
                                t->setUnderBuilding(b);
                                b->addUnderBuilding(t);
                            }
                        }
                    }

                    if(!mEditorMode) {
                        const auto diff = mBoard->difficulty(ppid);
                        const int cost = eDifficultyHelpers::buildingCost(
                                             diff, eBuildingType::triremeWharf);
                        mBoard->incDrachmas(ppid, -cost, eFinanceTarget::construction);
                    }
                } else {
                    showTip(cid, eLanguage::zeusText(19, 25));
                }
            }
        } break;


        case eBuildingMode::pier: {
            eDiagonalOrientation o;
            const bool c = canBuildPier(mHoverTX, mHoverTY, o, cid, pid, mEditorMode);
            if(c) {
                r = true;
                const int minX = mHoverTX;
                const int minY = mHoverTY - 1;

                bool accessToSea = false;
                for(int x = minX; x < minX + 2; x++) {
                    for(int y = minY; y < minY + 2; y++) {
                        const auto t = mBoard->tile(x, y);
                        if(!t) continue;
                        if(t->hasWater()) {
                            accessToSea = waterTileHasAccessToSea(x, y);
                            x += 2;
                            break;
                        }
                    }
                }

                if(accessToSea) {
                    const auto b = e::make_shared<ePier>(*mBoard, o, mViewedCityId);
                    const auto tile = mBoard->tile(mHoverTX, mHoverTY);
                    b->setCenterTile(tile);

                    b->setTileRect({mHoverTX, minY, 2, 2});
                    for(int x = minX; x < minX + 2; x++) {
                        for(int y = minY; y < minY + 2; y++) {
                            const auto t = mBoard->tile(x, y);
                            if(t) {
                                t->setUnderBuilding(b);
                                b->addUnderBuilding(t);
                            }
                        }
                    }
                    int tx = mHoverTX;
                    int ty = mHoverTY;

                    switch(o) {
                    case eDiagonalOrientation::topRight: {
                        ty += 3;
                    } break;
                    case eDiagonalOrientation::bottomRight: {
                        tx -= 3;
                    } break;
                    case eDiagonalOrientation::bottomLeft: {
                        ty -= 3;
                    } break;
                    default:
                    case eDiagonalOrientation::topLeft: {
                        tx += 3;
                    } break;
                    }
                    const int ctid = mGm->tradeCityId();
                    const auto& cts = wrld.cities();
                    const auto ct = cts[ctid];
                    const auto tp = e::make_shared<eTradePost>(
                                        *mBoard, *ct, mViewedCityId, eTradePostType::pier);
                    tp->setOrientation(o);
                    tp->setUnpackBuilding(b.get());
                    mBoard->build(tx, ty, 4, 4, cid, pid, mEditorMode, [&]() { return tp; });
                    b->setTradePost(tp.get());

                    mGm->clearMode();
                } else {
                    showTip(cid, eLanguage::zeusText(19, 25));
                }
            }
        } break;


        case eBuildingMode::dairy: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eDairy>(*mBoard, mViewedCityId); });

            if(!mBoard->hasBuilding(mViewedCityId, eBuildingType::goat)) {
                showTip(cid, eLanguage::zeusText(19, 219));
                showTip(cid, eLanguage::zeusText(19, 220));
            }
        } break;
        case eBuildingMode::cardingShed: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eCardingShed>(*mBoard, mViewedCityId); });

            if(!mBoard->hasBuilding(mViewedCityId, eBuildingType::sheep)) {
                showTip(cid, eLanguage::zeusText(19, 217));
                showTip(cid, eLanguage::zeusText(19, 218));
            }
        } break;

        case eBuildingMode::sheep: {
            const auto skip = std::make_shared<bool>(false);
            apply = [this, skip, pid, cid, &r](eTile* const tile) {
                if(*skip) return;
                const int allowed = mBoard->countAllowed(mViewedCityId, eBuildingType::sheep);
                if(allowed <= 0) {
                    showTip(cid, eLanguage::zeusText(19, 211));
                    showTip(cid, eLanguage::zeusText(19, 212));
                    *skip = true;
                    return;
                }
                r = mBoard->buildAnimal(tile, eBuildingType::sheep,
                            [](eGameBoard& board) {
                    return e::make_shared<eSheep>(board);
                }, mViewedCityId, pid, mEditorMode) || r;
            };
        } break;
        case eBuildingMode::goat: {
            const auto skip = std::make_shared<bool>(false);
            apply = [this, skip, pid, cid, &r](eTile* const tile) {
                if(*skip) return;
                const int allowed = mBoard->countAllowed(mViewedCityId, eBuildingType::goat);
                if(allowed <= 0) {
                    showTip(cid, eLanguage::zeusText(19, 215));
                    showTip(cid, eLanguage::zeusText(19, 216));
                    *skip = true;
                    return;
                }
                r = mBoard->buildAnimal(tile, eBuildingType::goat,
                            [](eGameBoard& board) {
                    return e::make_shared<eGoat>(board);
                }, mViewedCityId, pid, mEditorMode) || r;
            };
        } break;
        case eBuildingMode::cattle: {
            const auto skip = std::make_shared<bool>(false);
            apply = [this, skip, pid, cid, &r](eTile* const tile) {
                if(*skip) return;
                const int allowed = mBoard->countAllowed(mViewedCityId, eBuildingType::cattle);
                if(allowed <= 0) {
                    showTip(cid, eLanguage::zeusText(19, 252));
                    showTip(cid, eLanguage::zeusText(19, 253));
                    *skip = true;
                    return;
                }
                r = mBoard->buildAnimal(tile, eBuildingType::cattle,
                            [](eGameBoard& board) {
                    return e::make_shared<eCattle>(
                                board, eCharacterType::cattle2);
                }, mViewedCityId, pid, mEditorMode) || r;
            };
        } break;

        case eBuildingMode::wheatFarm: {
            r = mBoard->build(mHoverTX, mHoverTY, 3, 3, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eWheatFarm>(*mBoard, mViewedCityId); },
                  true);
        } break;
        case eBuildingMode::onionFarm: {
            r = mBoard->build(mHoverTX, mHoverTY, 3, 3, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eOnionFarm>(*mBoard, mViewedCityId); },
                  true);
        } break;
        case eBuildingMode::carrotFarm: {
            r = mBoard->build(mHoverTX, mHoverTY, 3, 3, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eCarrotFarm>(*mBoard, mViewedCityId); },
                  true);
        } break;
        case eBuildingMode::growersLodge: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eGrowersLodge>(
                            *mBoard, eGrowerType::grapesAndOlives, mViewedCityId); });
            if(mBoard->supportsBuilding(mViewedCityId, eBuildingMode::oliveTree) &&
               !mBoard->hasBuilding(mViewedCityId, eBuildingType::oliveTree)) {
                showTip(cid, eLanguage::zeusText(19, 200));
            }

            if(mBoard->supportsBuilding(mViewedCityId, eBuildingMode::vine) &&
               !mBoard->hasBuilding(mViewedCityId, eBuildingType::vine)) {
                showTip(cid, eLanguage::zeusText(19, 198));
            }
        } break;
        case eBuildingMode::orangeTendersLodge: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eGrowersLodge>(
                            *mBoard, eGrowerType::oranges, mViewedCityId); });
        } break;

        case eBuildingMode::granary: {
            r = mBoard->build(mHoverTX, mHoverTY, 4, 4, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eGranary>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::warehouse: {
            r = mBoard->build(mHoverTX, mHoverTY, 3, 3, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eWarehouse>(*mBoard, mViewedCityId); });
        } break;

        case eBuildingMode::tradePost: {
            const int ctid = mGm->tradeCityId();
            const auto cts = wrld.cities();
            const auto ct = cts[ctid];
            r = mBoard->build(mHoverTX, mHoverTY, 4, 4, cid, pid, mEditorMode,
                  [this, ct]() {
                const auto tp = e::make_shared<eTradePost>(*mBoard, *ct, mViewedCityId);
                return tp;
            });
            mGm->clearMode();
        } break;


        case eBuildingMode::wall:
            apply = [this, cid, pid, &r](eTile* const tile) {
                r = mBoard->build(tile->x(), tile->y(), 1, 1, cid, pid, mEditorMode,
                      [this]() { return e::make_shared<eWall>(*mBoard, mViewedCityId); }) || r;
            };
            break;
        case eBuildingMode::tower: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eTower>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::gatehouse: {
            int dx;
            int dy;
            int sw;
            int sh;
            if(mRotate) {
                dx = 0;
                dy = 3;
                sw = 2;
                sh = 5;
            } else {
                dx = 3;
                dy = 0;
                sw = 5;
                sh = 2;
            }
            const int tx = mHoverTX;
            const int ty = mHoverTY - 1;
            int ttx = tx;
            int tty = ty;
            const bool cb1 = mBoard->canBuildBase(ttx, ttx + 2, tty, tty + 2,
                                                  mEditorMode, cid, pid);
            if(!cb1) return true;
            std::vector<eTile*> roadTiles;

            if(sw == 2) {
                const auto t2 = mBoard->tile(tx, ty + 2);
                if(!t2) return true;
                roadTiles.push_back(t2);
                const auto t3 = t2->tileRel<eTile>(1, 0);
                if(!t3) return true;
                roadTiles.push_back(t3);
            } else {
                const auto t2 = mBoard->tile(tx + 2, ty);
                if(!t2) return true;
                roadTiles.push_back(t2);
                const auto t3 = t2->tileRel<eTile>(0, 1);
                if(!t3) return true;
                roadTiles.push_back(t3);
            }

            for(const auto t : roadTiles) {
                if(!t) return true;
                if(t->hasRoad()) continue;
                const bool cb = mBoard->canBuildBase(t->x(), t->x() + 1, t->y(), t->y() + 1,
                                                     mEditorMode, cid, pid);
                if(!cb) return true;
            }

            ttx = tx + dx;
            tty = ty + dy;
            const bool cb2 = mBoard->canBuildBase(ttx, ttx + 2, tty, tty + 2,
                                                  mEditorMode, cid, pid);
            if(!cb2) return true;
            const auto b1 = e::make_shared<eGatehouse>(*mBoard, mRotate, mViewedCityId);

            b1->setTileRect({tx, ty, sw, sh});
            const int minX = tx;
            const int maxX = tx + sw;
            const int minY = ty;
            const int maxY = ty + sh;
            for(int x = minX; x < maxX; x++) {
                for(int y = minY; y < maxY; y++) {
                    const auto t = mBoard->tile(x, y);
                    if(t) {
                        t->setUnderBuilding(b1);
                        b1->setCenterTile(t);
                        b1->addUnderBuilding(t);
                    }
                }
            }

            for(const auto r : roadTiles) {
                const auto r2 = e::make_shared<eRoad>(*mBoard, mViewedCityId);
                r2->setTileRect({r->x(), r->y(), 1, 1});
                r2->setUnderGatehouse(b1.get());
                r2->addUnderBuilding(r);
                r->setUnderBuilding(r2);
                r2->setCenterTile(r);
            }
            r = true;
            if(!mEditorMode) {
                const auto diff = mBoard->difficulty(ppid);
                const int cost = eDifficultyHelpers::buildingCost(
                                     diff, eBuildingType::gatehouse);
                mBoard->incDrachmas(ppid, -cost, eFinanceTarget::construction);
            }
        } break;

        case eBuildingMode::armory: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eArmory>(*mBoard, mViewedCityId); });
            showTip(cid, eLanguage::zeusText(19, 194));
            if(mBoard->supportsBuilding(mViewedCityId, eBuildingMode::foundry) &&
               !mBoard->hasBuilding(mViewedCityId, eBuildingType::foundry)) {
                showTip(cid, eLanguage::zeusText(19, 195));
            }
        } break;
        case eBuildingMode::horseRanch: {
            const int tx = mHoverTX;
            const int ty = mHoverTY;
            const bool cb1 = mBoard->canBuild(tx, ty, 3, 3, mEditorMode, cid, pid);
            if(!cb1) return true;
            int dx = 0;
            int dy = 0;
            if(mRotateId == 0) { // bottomRight
                dx = 3;
            } else if(mRotateId == 1) { // topRight
                dy = -3;
                dx = -1;
            } else if(mRotateId == 2) { // topLeft
                dx = -4;
                dy = 1;
            } else if(mRotateId == 3) { // bottomLeft
                dy = 4;
            }
            const bool cb2 = mBoard->canBuild(tx + dx, ty + dy, 4, 4, mEditorMode, cid, pid);
            if(!cb2) return true;
            r = true;
            const auto hr = e::make_shared<eHorseRanch>(*mBoard, mViewedCityId);
            const auto hre = e::make_shared<eHorseRanchEnclosure>(*mBoard, mViewedCityId);
            hre->setRanch(hr.get());
            hr->setEnclosure(hre.get());
            mBoard->build(tx, ty, 3, 3, cid, pid, mEditorMode,
                  [hr]() { return hr; });
            mBoard->build(tx + dx, ty + dy, 4, 4, cid, pid, mEditorMode,
                  [hre]() { return hre; });
            showTip(cid, eLanguage::zeusText(19, 187));
            if(mBoard->supportsBuilding(mViewedCityId, eBuildingMode::wheatFarm) &&
               !mBoard->hasBuilding(mViewedCityId, eBuildingType::wheatFarm)) {
                showTip(cid, eLanguage::zeusText(19, 188));
            }
        } break;
        case eBuildingMode::chariotFactory: {
           r = mBoard->build(mHoverTX, mHoverTY, 4, 4, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eChariotFactory>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::olivePress: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eOlivePress>(*mBoard, mViewedCityId); });
            showTip(cid, eLanguage::zeusText(19, 199));
            if(mBoard->supportsBuilding(mViewedCityId, eBuildingMode::oliveTree) &&
               !mBoard->hasBuilding(mViewedCityId, eBuildingType::oliveTree)) {
                showTip(cid, eLanguage::zeusText(19, 200));
            }
        } break;
        case eBuildingMode::winery: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eWinery>(*mBoard, mViewedCityId); });
            showTip(cid, eLanguage::zeusText(19, 197));
            if(mBoard->supportsBuilding(mViewedCityId, eBuildingMode::vine) &&
               !mBoard->hasBuilding(mViewedCityId, eBuildingType::vine)) {
                showTip(cid, eLanguage::zeusText(19, 198));
            }
        } break;
        case eBuildingMode::sculptureStudio: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eSculptureStudio>(*mBoard, mViewedCityId); });
            showTip(cid, eLanguage::zeusText(19, 196));
            if(mBoard->supportsBuilding(mViewedCityId, eBuildingMode::foundry) &&
               !mBoard->hasBuilding(mViewedCityId, eBuildingType::foundry)) {
                showTip(cid, eLanguage::zeusText(19, 195));
            }
        } break;

        case eBuildingMode::artisansGuild: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eArtisansGuild>(*mBoard, mViewedCityId); });
        } break;

        case eBuildingMode::foodVendor: {
            r = buildVendor<eFoodVendor>(*mBoard, mHoverTX, mHoverTY,
                                            eResourceType::food, mViewedCityId);
        } break;
        case eBuildingMode::fleeceVendor: {
            r = buildVendor<eFleeceVendor>(*mBoard, mHoverTX, mHoverTY,
                                              eResourceType::fleece, mViewedCityId);
        } break;
        case eBuildingMode::oilVendor: {
            r = buildVendor<eOilVendor>(*mBoard, mHoverTX, mHoverTY,
                                           eResourceType::oliveOil, mViewedCityId);
        } break;
        case eBuildingMode::wineVendor: {
            r = buildVendor<eWineVendor>(*mBoard, mHoverTX, mHoverTY,
                                            eResourceType::wine, mViewedCityId);
        } break;
        case eBuildingMode::armsVendor: {
            r = buildVendor<eArmsVendor>(*mBoard, mHoverTX, mHoverTY,
                                            eResourceType::armor, mViewedCityId);
        } break;
        case eBuildingMode::horseTrainer: {
            r = buildVendor<eHorseVendor>(*mBoard, mHoverTX, mHoverTY,
                                             eResourceType::horse, mViewedCityId);
        } break;
        case eBuildingMode::chariotVendor: {
            r = buildVendor<eChariotVendor>(*mBoard, mHoverTX, mHoverTY,
                                               eResourceType::chariot, mViewedCityId);
        } break;

        case eBuildingMode::park:
            apply = [this, cid, pid, &r](eTile* const tile) {
                r = mBoard->build(tile->x(), tile->y(), 1, 1, cid, pid, mEditorMode,
                      [this]() { return e::make_shared<ePark>(*mBoard, mViewedCityId); },
                      false, true) || r;
            };
            mBoard->scheduleTerrainUpdate();
            break;
        case eBuildingMode::doricColumn:
        case eBuildingMode::ionicColumn:
        case eBuildingMode::corinthianColumn: {
            switch(mode) {
            case eBuildingMode::doricColumn:
                apply = [this, cid, pid](eTile* const tile) {
                    mBoard->build(tile->x(), tile->y(), 1, 1, cid, pid, mEditorMode,
                          [this]() { return e::make_shared<eDoricColumn>(*mBoard, mViewedCityId); });
                };
                break;
            case eBuildingMode::ionicColumn:
                apply = [this, cid, pid](eTile* const tile) {
                    mBoard->build(tile->x(), tile->y(), 1, 1, cid, pid, mEditorMode,
                          [this]() { return e::make_shared<eIonicColumn>(*mBoard, mViewedCityId); });
                };
                break;
            case eBuildingMode::corinthianColumn:
            default:
                apply = [this, cid, pid](eTile* const tile) {
                    mBoard->build(tile->x(), tile->y(), 1, 1, cid, pid, mEditorMode,
                          [this]() { return e::make_shared<eCorinthianColumn>(*mBoard, mViewedCityId); });
                };
                break;
            }

            const auto startTile = mBoard->tile(mHoverTX, mHoverTY);
            if(!startTile) return false;
            std::vector<eOrientation> path;
            const bool r = columnPath(path);
            if(r) {
                eTile* t = startTile;
                for(int i = path.size() - 1; i >= 0; i--) {
                    if(!t) break;
                    apply(t);
                    t = t->neighbour<eTile>(path[i]);
                }
                if(t) apply(t);
            } else {
                apply(startTile);
            }
            return true;
        } break;
        case eBuildingMode::avenue:
            apply = [this, cid, pid, &r](eTile* const tile) {
                const bool hr = canBuildAvenue(tile, cid, pid, mEditorMode);
                if(!hr) return;
                r = mBoard->build(tile->x(), tile->y(), 1, 1, cid, pid, mEditorMode,
                      [this]() { return e::make_shared<eAvenue>(*mBoard, mViewedCityId); },
                      false, true) || r;
            };
            mBoard->scheduleTerrainUpdate();
            break;


        case eBuildingMode::populationMonument:
        case eBuildingMode::victoryMonument:
        case eBuildingMode::colonyMonument:
        case eBuildingMode::athleteMonument:
        case eBuildingMode::conquestMonument:
        case eBuildingMode::happinessMonument:
        case eBuildingMode::heroicFigureMonument:
        case eBuildingMode::diplomacyMonument:
        case eBuildingMode::scholarMonument: {
            int id = -1;
            switch(mode) {
            case eBuildingMode::populationMonument:
                id = 0;
                break;
            case eBuildingMode::victoryMonument:
                id = 1;
                break;
            case eBuildingMode::colonyMonument:
                id = 2;
                break;
            case eBuildingMode::athleteMonument:
                id = 3;
                break;
            case eBuildingMode::conquestMonument:
                id = 4;
                break;
            case eBuildingMode::happinessMonument:
                id = 5;
                break;
            case eBuildingMode::heroicFigureMonument:
                id = 6;
                break;
            case eBuildingMode::diplomacyMonument:
                id = 7;
                break;
            case eBuildingMode::scholarMonument:
                id = 8;
                break;
            default:
                id = -1;
                break;
            }
            const auto builder = [this, id]() {
                return e::make_shared<eCommemorative>(id, *mBoard, mViewedCityId);
            };
            const bool r = mBoard->build(mHoverTX, mHoverTY, 3, 3, cid, pid, mEditorMode, builder);
            if(r) {
                mBoard->built(mViewedCityId, eBuildingType::commemorative, id);
                const bool s = mBoard->supportsBuilding(mViewedCityId, mode);
                if(!s) mGm->clearMode();
            }
        } break;

        case eBuildingMode::aphroditeMonument:
        case eBuildingMode::apolloMonument:
        case eBuildingMode::aresMonument:
        case eBuildingMode::artemisMonument:
        case eBuildingMode::athenaMonument:
        case eBuildingMode::atlasMonument:
        case eBuildingMode::demeterMonument:
        case eBuildingMode::dionysusMonument:
        case eBuildingMode::hadesMonument:
        case eBuildingMode::hephaestusMonument:
        case eBuildingMode::heraMonument:
        case eBuildingMode::hermesMonument:
        case eBuildingMode::poseidonMonument:
        case eBuildingMode::zeusMonument: {
            const int tx = mHoverTX;
            const int ty = mHoverTY;
            const int tminX = tx - 1;
            const int tminY = ty - 2;
            const int tmaxX = tminX + 4;
            const int tmaxY = tminY + 4;

            const bool cb = mBoard->canBuild(tx, ty, 4, 4, mEditorMode, cid, pid);
            if(!cb) return true;

            const auto am = eBuildingMode::aphroditeMonument;
            const int id = static_cast<int>(mode) -
                           static_cast<int>(am);
            const auto gt = static_cast<eGodType>(id);
            const auto s = e::make_shared<eGodMonument>(
                               gt, eGodQuestId::godQuest1, *mBoard, mViewedCityId);
            const bool b = mBoard->build(tminX + 1, tminY + 2, 2, 2, cid, pid, mEditorMode, [&]() {
                return s;
            });
            for(int x = tminX; x < tmaxX; x++) {
                for(int y = tminY; y < tmaxY; y++) {
                    const bool cb = mBoard->canBuild(x, y, 1, 1, mEditorMode, cid, pid);
                    if(!cb) continue;
                    mBoard->build(x, y, 1, 1, cid, pid, mEditorMode, [&]() {
                        const auto t = e::make_shared<eGodMonumentTile>(
                                           *mBoard, mViewedCityId);
                        t->setMonument(s.get());
                        s->addTile(t.get());
                        return t;
                    });
                }
            }
            if(b) {
                mBoard->built(mViewedCityId, eBuildingType::godMonument, id);
                const bool ss = mBoard->supportsBuilding(mViewedCityId, mode);
                if(!ss) mGm->clearMode();
            }
        } break;

        case eBuildingMode::bench: {
            r = mBoard->build(mHoverTX, mHoverTY, 1, 1, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eBench>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::flowerGarden: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eFlowerGarden>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::gazebo: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eGazebo>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::hedgeMaze: {
            r = mBoard->build(mHoverTX, mHoverTY, 3, 3, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eHedgeMaze>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::fishPond: {
            r = mBoard->build(mHoverTX, mHoverTY, 4, 4, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eFishPond>(*mBoard, mViewedCityId); });
        } break;

        case eBuildingMode::waterPark: {
            r = mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode, [this]() {
                const auto b = e::make_shared<eWaterPark>(*mBoard, mViewedCityId);
                b->setId(rotationId());
                return b;
            });
        } break;

        case eBuildingMode::hippodromePiece: {
            updateHippodromeIds();
            const int hid = hippodromeId();
            if(hid == -1) {
                showTip(cid, eLanguage::zeusText(19, 257));
            } else {
                r = mBoard->build(mHoverTX, mHoverTY, 4, 4, cid, pid, mEditorMode, [this, hid]() {
                    const auto b = e::make_shared<eHippodromePiece>(*mBoard, mViewedCityId);
                    b->setId(hid);
                    return b;
                });
                if(r) {
                    const auto c = mBoard->boardCityWithId(cid);
                    c->updateHippodromes();
                }
            }
        } break;

        case eBuildingMode::crosswalk: {
            const auto b = mBoard->buildingAt(mHoverTX, mHoverTY);
            if(b && b->type() == eBuildingType::hippodromePiece) {
                for(int dx = -1; dx <= 1; dx++) {
                    for(int dy = -1; dy <= 1; dy++) {
                        if(dx == 0 && dy == 0) continue;
                        const auto bb = mBoard->buildingAt(mHoverTX + dx, mHoverTY + dy);
                        if(bb && bb->type() == eBuildingType::road) {
                            const auto r = static_cast<eRoad*>(bb);
                            if(r->aboveHippodrome() == b) return true;
                        }
                    }
                }
                const auto h = static_cast<eHippodromePiece*>(b);
                int id = h->id();
                if(id == 0) {
                    id = 4;
                } else if(id == 6) {
                    id = 2;
                } else if(id != 2 && id != 4) {
                    return true;
                }
                h->setId(id);
                const auto& r = h->tileRect();
                const auto buildCrosswalk = [&](eTile* const t) {
                    const auto b = e::make_shared<eRoad>(*mBoard, mViewedCityId);
                    b->setCenterTile(t);
                    b->setTileRect({t->x(), t->y(), 1, 1});
                    t->setUnderBuilding(b);
                    b->addUnderBuilding(t);
                    b->setAboveHippodrome(h);
                    return b.get();
                };
                if(id == 2) {
                    int i = 0;
                    for(int x = r.x; x < r.x + r.w; x++) {
                        const auto t = mBoard->tile(x, mHoverTY);
                        const auto r = buildCrosswalk(t);
                        if(i == 1 || i == 2) {
                            r->setCharacterAltitude(2);
                        }
                        i++;
                    }
                } else if(id == 4) {
                    int i = 0;
                    for(int y = r.y; y < r.y + r.h; y++) {
                        const auto t = mBoard->tile(mHoverTX, y);
                        const auto r = buildCrosswalk(t);
                        if(i == 1 || i == 2) {
                            r->setCharacterAltitude(2);
                        }
                        i++;
                    }
                } else {
                    return true;
                }

                if(!mEditorMode) {
                    const auto diff = mBoard->difficulty(ppid);
                    const int cost = eDifficultyHelpers::buildingCost(
                        diff, eBuildingType::crosswalk);
                    mBoard->incDrachmas(ppid, -cost, eFinanceTarget::construction);
                }
            }
        } break;

        case eBuildingMode::birdBath: {
            r = mBoard->build(mHoverTX, mHoverTY, 1, 1, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eBirdBath>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::shortObelisk: {
            mBoard->build(mHoverTX, mHoverTY, 1, 1, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eShortObelisk>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::tallObelisk: {
            mBoard->build(mHoverTX, mHoverTY, 1, 1, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eTallObelisk>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::shellGarden: {
            mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eShellGarden>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::sundial: {
            mBoard->build(mHoverTX, mHoverTY, 2, 2, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eSundial>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::dolphinSculpture: {
            mBoard->build(mHoverTX, mHoverTY, 3, 3, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eDolphinSculpture>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::orrery: {
            mBoard->build(mHoverTX, mHoverTY, 3, 3, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eOrrery>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::spring: {
            r = mBoard->build(mHoverTX, mHoverTY, 3, 3, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eSpring>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::topiary: {
            r = mBoard->build(mHoverTX, mHoverTY, 3, 3, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eTopiary>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::baths: {
            r = mBoard->build(mHoverTX, mHoverTY, 4, 4, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eBaths>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::stoneCircle: {
            r = mBoard->build(mHoverTX, mHoverTY, 4, 4, cid, pid, mEditorMode,
                  [this]() { return e::make_shared<eStoneCircle>(*mBoard, mViewedCityId); });
        } break;
        case eBuildingMode::achillesHall:
        case eBuildingMode::atalantaHall:
        case eBuildingMode::bellerophonHall:
        case eBuildingMode::herculesHall:
        case eBuildingMode::jasonHall:
        case eBuildingMode::odysseusHall:
        case eBuildingMode::perseusHall:
        case eBuildingMode::theseusHall: {
            const auto hallType = eBuildingModeHelpers::toBuildingType(mode);
            const auto heroType = eHerosHall::sHallTypeToHeroType(hallType);
            const auto builder = [this, heroType]() {
                return e::make_shared<eHerosHall>(heroType, *mBoard, mViewedCityId);
            };
            const bool r = mBoard->build(mHoverTX, mHoverTY, 4, 4, cid, pid, mEditorMode, builder);
            if(r) {
                mBoard->built(mViewedCityId, hallType);
                mGm->clearMode();
            }
        } break;
        case eBuildingMode::templeAphrodite:
        case eBuildingMode::templeApollo:
        case eBuildingMode::templeAres:
        case eBuildingMode::templeArtemis:
        case eBuildingMode::templeAthena:
        case eBuildingMode::templeAtlas:
        case eBuildingMode::templeDemeter:
        case eBuildingMode::templeDionysus:
        case eBuildingMode::templeHades:
        case eBuildingMode::templeHephaestus:
        case eBuildingMode::templeHera:
        case eBuildingMode::templeHermes:
        case eBuildingMode::templePoseidon:
        case eBuildingMode::templeZeus: {
            const int maxSancts = mBoard->maxSanctuaries(cid);
            const auto sancts = mBoard->sanctuaries(cid);
            const int nBuilt = sancts.size();
            if(!mEditorMode && nBuilt >= maxSancts) {
                if(maxSancts < 2) showTip(cid, eLanguage::zeusText(19, 230));
                if(maxSancts == 2) showTip(cid, eLanguage::zeusText(19, 231));
                if(maxSancts == 3) showTip(cid, eLanguage::zeusText(19, 232));
                if(maxSancts == 4) showTip(cid, eLanguage::zeusText(19, 233));
                return false;
            }

            const auto bt = eBuildingModeHelpers::toBuildingType(mode);
            const int m = eBuilding::sInitialMarbleCost(bt);
            const int hasM = mBoard->resourceCount(mViewedCityId, eResourceType::marble);
            if(!mEditorMode && hasM < m) {
                auto text = eLanguage::zeusText(19, 201);
                const auto mStr = std::to_string(m);
                eStringHelpers::replace(text, "[warning_amount]", mStr);
                showTip(cid, text);
                if(mBoard->supportsBuilding(mViewedCityId, eBuildingMode::masonryShop)) {
                    showTip(cid, eLanguage::zeusText(19, 202));
                }
                return false;
            }

            const auto h = eSanctBlueprints::sSanctuaryBlueprint(bt, mRotate);

            const int sw = h->fW;
            const int sh = h->fH;

            const int minX = mHoverTX - sw/2;
            const int maxX = minX + sw;
            const int minY = mHoverTY - sh/2;
            const int maxY = minY + sh;

            r = mBoard->buildSanctuary(
                minX, maxX, minY, maxY,
                bt, mRotate, mViewedCityId, pid, mEditorMode);
            if(r) mGm->clearMode();
        } break;
        case eBuildingMode::modestPyramid:
        case eBuildingMode::pyramid:
        case eBuildingMode::greatPyramid:
        case eBuildingMode::majesticPyramid:

        case eBuildingMode::smallMonumentToTheSky:
        case eBuildingMode::monumentToTheSky:
        case eBuildingMode::grandMonumentToTheSky:

        case eBuildingMode::minorShrineAphrodite:
        case eBuildingMode::minorShrineApollo:
        case eBuildingMode::minorShrineAres:
        case eBuildingMode::minorShrineArtemis:
        case eBuildingMode::minorShrineAthena:
        case eBuildingMode::minorShrineAtlas:
        case eBuildingMode::minorShrineDemeter:
        case eBuildingMode::minorShrineDionysus:
        case eBuildingMode::minorShrineHades:
        case eBuildingMode::minorShrineHephaestus:
        case eBuildingMode::minorShrineHera:
        case eBuildingMode::minorShrineHermes:
        case eBuildingMode::minorShrinePoseidon:
        case eBuildingMode::minorShrineZeus:

        case eBuildingMode::shrineAphrodite:
        case eBuildingMode::shrineApollo:
        case eBuildingMode::shrineAres:
        case eBuildingMode::shrineArtemis:
        case eBuildingMode::shrineAthena:
        case eBuildingMode::shrineAtlas:
        case eBuildingMode::shrineDemeter:
        case eBuildingMode::shrineDionysus:
        case eBuildingMode::shrineHades:
        case eBuildingMode::shrineHephaestus:
        case eBuildingMode::shrineHera:
        case eBuildingMode::shrineHermes:
        case eBuildingMode::shrinePoseidon:
        case eBuildingMode::shrineZeus:

        case eBuildingMode::majorShrineAphrodite:
        case eBuildingMode::majorShrineApollo:
        case eBuildingMode::majorShrineAres:
        case eBuildingMode::majorShrineArtemis:
        case eBuildingMode::majorShrineAthena:
        case eBuildingMode::majorShrineAtlas:
        case eBuildingMode::majorShrineDemeter:
        case eBuildingMode::majorShrineDionysus:
        case eBuildingMode::majorShrineHades:
        case eBuildingMode::majorShrineHephaestus:
        case eBuildingMode::majorShrineHera:
        case eBuildingMode::majorShrineHermes:
        case eBuildingMode::majorShrinePoseidon:
        case eBuildingMode::majorShrineZeus:

        case eBuildingMode::pyramidToThePantheon:
        case eBuildingMode::altarOfOlympus:
        case eBuildingMode::templeOfOlympus:
        case eBuildingMode::observatoryKosmika:
        case eBuildingMode::museumAtlantika: {
            const auto type = eBuildingModeHelpers::toBuildingType(mode);
            const int m = eBuilding::sInitialMarbleCost(type);
            const int hasM = mBoard->resourceCount(mViewedCityId, eResourceType::marble);
            if(!mEditorMode && hasM < m) {
                auto text = eLanguage::zeusText(19, 201);
                const auto mStr = std::to_string(m);
                eStringHelpers::replace(text, "[warning_amount]", mStr);
                showTip(cid, text);
                if(mBoard->supportsBuilding(mViewedCityId, eBuildingMode::masonryShop)) {
                    showTip(cid, eLanguage::zeusText(19, 202));
                }
                return false;
            }

            int sw;
            int sh;
            ePyramid::sDimensions(type, sw, sh);

            const int minX = mHoverTX - sw/2;
            const int maxX = minX + sw;
            const int minY = mHoverTY - sh/2;
            const int maxY = minY + sh;

            const bool r = mBoard->buildPyramid(
                               minX, maxX, minY, maxY,
                               type, mRotate, mViewedCityId, pid,
                               mEditorMode);
            if(!r) return true;
            mGm->clearMode();
        } break;
        default:
            break;
        }
    }

    if(apply) {
        const auto btype = mTem->brushType();
        if(btype == eBrushType::apply) {
            mInflTiles.clear();
            const int minX = std::min(mPressedTX, mHoverTX);
            const int minY = std::min(mPressedTY, mHoverTY);
            const int maxX = std::max(mPressedTX, mHoverTX);
            const int maxY = std::max(mPressedTY, mHoverTY);

            for(int x = minX; x <= maxX; x++) {
                for(int y = minY; y <= maxY; y++) {
                    const auto tile = mBoard->tile(x, y);
                    if(!tile) continue;
                    mInflTiles.push_back(tile);
                }
            }
        }
        for(const auto tile : mInflTiles) {
            apply(tile);
        }
        updateMaps(mInflTiles);
        mInflTiles.clear();
    }
    if(mTem->visible()) {
        const auto mode = mTem->mode();
        if(mode == eTerrainEditMode::raise ||
           mode == eTerrainEditMode::lower ||
           mode == eTerrainEditMode::raiseHigh ||
           mode == eTerrainEditMode::lowerHigh ||
           mode == eTerrainEditMode::levelOut ||
           mode == eTerrainEditMode::resetElev) {
            updateTopBottomAltitude();
            updateMinMaxAltitude();
        } else if(mode == eTerrainEditMode::cityTerritory) {
            mBoard->updateTerritoryBorders();
        }
        mBoard->updateMarbleTiles();
        mBoard->updateBlackMarbleTiles();
        mBoard->scheduleTerrainUpdate();
    }
    if(r) {
        const auto type = eBuildingModeHelpers::toBuildingType(mode);
        if(type != eBuildingType::road) {
            eSounds::playPlaceBuildingSound();
        }
        // eSounds::playSoundForBuilding(type);
    }
    return true;
}
