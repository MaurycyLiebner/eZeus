#include "egamewidget.h"

#include "eterraineditmenu.h"

#include "buildings/allbuildings.h"

#include "characters/esheep.h"
#include "characters/egoat.h"
#include "characters/actions/eanimalaction.h"
#include "characters/etrader.h"
#include "characters/etradeboat.h"

#include "spawners/eboarspawner.h"
#include "spawners/edeerspawner.h"
#include "spawners/esettlerspawner.h"
#include "spawners/elandinvasionpoint.h"

#include "ebuildingstoerase.h"

#include "widgets/equestionwidget.h"
#include "elanguage.h"

bool agoraRoadTile(eTile* const t) {
    if(!t) return false;
    if(!t->hasRoad()) return false;
    const auto ub = t->underBuilding();
    if(!ub) return false;
    const auto r = static_cast<eRoad*>(ub);
    return !r->underAgora();
}

std::vector<eTile*> eGameWidget::agoraBuildPlaceBR(
        eTile* const tile) const {
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
                if(!t || t->underBuilding() || t->isElevationTile()) {
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
        eTile* const tile) const {
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
                if(!t || t->underBuilding() || t->isElevationTile()) {
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
        eTile* const tile) const {
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
                if(!t || t->underBuilding() || t->isElevationTile()) {
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
        eTile* const tile) const {
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
                if(!t || t->underBuilding() || t->isElevationTile()) {
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
        eAgoraOrientation& bt) const {
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
                const auto r = agoraBuildPlaceBR(t);
                if(r.empty()) continue;
                bt = eAgoraOrientation::bottomRight;
                if(grand) {
                    const auto rr = agoraBuildPlaceTL(t);
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
                const auto r = agoraBuildPlaceTL(t);
                if(r.empty()) continue;

                if(grand) {
                    bt = eAgoraOrientation::bottomRight;
                    const auto rr = agoraBuildPlaceBR(t);
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
                const auto r = agoraBuildPlaceBL(t);
                if(r.empty()) continue;
                bt = eAgoraOrientation::bottomLeft;
                if(grand) {
                    const auto rr = agoraBuildPlaceTR(t);
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
                const auto r = agoraBuildPlaceTR(t);
                if(r.empty()) continue;
                if(grand) {
                    bt = eAgoraOrientation::bottomLeft;
                    const auto rr = agoraBuildPlaceBL(t);
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
                 const eResourceType resType) {
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
    const auto fv = e::make_shared<T>(brd);
    fv->setAgora(agoraP);
    agora->setBuilding(space, fv);
    return true;
}

bool eGameWidget::buildMouseRelease() {
    const auto& wrld = mBoard->getWorldBoard();
    std::function<void(eTile* const)> apply;
    if(mTem->visible()) {
        const auto mode = mTem->mode();
        const int modeId = mTem->modeId();
        if(mode == eTerrainEditMode::none) {
            return false;
        } else if(mode == eTerrainEditMode::scrub) {
            apply = [](eTile* const tile) {
                tile->incScrub(0.1);
            };
        } else if(mode == eTerrainEditMode::raise) {
            apply = [](eTile* const tile) {
                tile->setAltitude(tile->altitude() + 1);
            };
        } else if(mode == eTerrainEditMode::lower) {
            apply = [](eTile* const tile) {
                tile->setAltitude(tile->altitude() - 1);
            };
        } else if(mode == eTerrainEditMode::levelOut) {
            const auto t = mBoard->tile(mPressedTX, mPressedTY);
            if(t) {
                const int a = t->altitude();
                apply = [a](eTile* const tile) {
                    tile->setAltitude(a);
                };
            }
        } else if(mode == eTerrainEditMode::resetElev) {
            apply = [](eTile* const tile) {
                tile->setAltitude(0);
            };
        } else if(mode == eTerrainEditMode::makeWalkable) {
            apply = [](eTile* const tile) {
                tile->setWalkableElev(!tile->walkableElev());
            };
        } else if(mode == eTerrainEditMode::boar) {
            apply = [this](eTile* const tile) {
                const auto os = tile->banner();
                if(os) delete os;
                new eBoarSpawner(tile, *mBoard);
            };
        } else if(mode == eTerrainEditMode::fish) {
            apply = [](eTile* const tile) {
                tile->setHasFish(!tile->hasFish());
            };
        } else if(mode == eTerrainEditMode::deer) {
            apply = [this](eTile* const tile) {
                const auto os = tile->banner();
                if(os) delete os;
                new eDeerSpawner(tile, *mBoard);
            };
        } else if(mode == eTerrainEditMode::fire) {
            apply = [](eTile* const tile) {
                tile->setOnFire(true);
            };
        } else if(mode == eTerrainEditMode::ruins) {
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 1, 1,
                      [this]() { return e::make_shared<eRuins>(*mBoard); });
            };
        } else if(mode == eTerrainEditMode::settlers) {
            apply = [this](eTile* const tile) {
                const auto os = tile->banner();
                if(os) delete os;
                new eSettlerSpawner(tile, *mBoard);
            };
        } else if(mode == eTerrainEditMode::landInvasion) {
            apply = [this, modeId](eTile* const tile) {
                const auto os = tile->banner();
                if(os) delete os;
                new eLandInvasionPoint(modeId, tile, *mBoard);
            };
        } else {
            apply = [mode](eTile* const tile) {
                const auto terr = static_cast<eTerrain>(mode);
                tile->setTerrain(terr);
            };
        }
        mBoard->requestTileRenderingOrderUpdate();
        mBoard->updateMarbleTiles();
        mUpdateTerrain = true;
    } else {
        const auto mode = mGm->mode();
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

            const auto diff = mBoard->difficulty();
            const int cost = eDifficultyHelpers::buildingCost(
                                 diff, eBuildingType::erase);
            int totalCost = 0;
            for(int x = minX; x <= maxX; x++) {
                for(int y = minY; y <= maxY; y++) {
                    const auto tile = mBoard->tile(x, y);
                    if(!tile) continue;
                    if(const auto b = tile->underBuilding()) {
                        if(b->isOnFire()) continue;
                        eraser.addBuilding(b);
                    } else {
                        const auto t = tile->terrain();
                        if(t == eTerrain::forest || t == eTerrain::choppedForest) {
                            tile->setTerrain(eTerrain::dry);
                            totalCost += cost;
                        }
                    }
                }
            }

            const int nErased = eraser.erase(false);
            mBoard->requestTileRenderingOrderUpdate();
            mBoard->updateTileRenderingOrderIfNeeded();
            totalCost += cost*nErased;
            mBoard->incDrachmas(-totalCost);

            std::string titleT;
            std::string textT;
            if(eraser.hasImportantBuildings()) {
                titleT = "demolishing_title";
                textT = "demolishing_text";
            } else if(eraser.hasNonEmptyAgoras()) {
                titleT = "demolishing_agora_title";
                textT = "demolishing_agora_text";
            } else {
                return false;
            }
            const auto title = eLanguage::text(titleT);
            const auto text = eLanguage::text(textT);

            const auto cancelA = [this]() {
                mLocked = false;
            };

            const auto acceptA = [this, cost, eraser]() {
                auto e = eraser;
                const int nErased = e.erase(true);
                const int totalCost = cost*nErased;
                mBoard->incDrachmas(-totalCost);
                mLocked = false;
            };

            const auto qw = new eQuestionWidget(window());
            qw->initialize(title, text, acceptA, cancelA);
            addWidget(qw);
            qw->align(eAlignment::vcenter);
            const int vw = width() - mGm->width();
            const int w = qw->width();
            qw->setX((vw - w)/2);
            mLocked = true;
        } break;
        case eBuildingMode::commonAgora: {
            const auto t = mBoard->tile(mHoverTX, mHoverTY);
            if(!t) return false;
            eAgoraOrientation bt;
            const auto p = agoraBuildPlaceIter(t, false, bt);
            if(p.empty()) return false;
            const auto b = e::make_shared<eCommonAgora>(bt, *mBoard);
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

            const auto diff = mBoard->difficulty();
            const int cost = eDifficultyHelpers::buildingCost(diff, b->type());
            mBoard->incDrachmas(-cost);
        } break;
        case eBuildingMode::grandAgora: {
            const auto t = mBoard->tile(mHoverTX, mHoverTY);
            if(!t) return false;
            eAgoraOrientation bt;
            const auto p = agoraBuildPlaceIter(t, true, bt);
            if(p.empty()) return false;
            const auto b = e::make_shared<eGrandAgora>(bt, *mBoard);
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

            const auto diff = mBoard->difficulty();
            const int cost = eDifficultyHelpers::buildingCost(diff, b->type());
            mBoard->incDrachmas(-cost);
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
                    build(t->x(), t->y(), 1, 1,
                          [this]() { return e::make_shared<eRoad>(*mBoard); });
                    t = t->neighbour<eTile>(path[i]);
                }
                if(t) {
                    build(t->x(), t->y(), 1, 1,
                          [this]() { return e::make_shared<eRoad>(*mBoard); });
                }
            } else {
                build(startTile->x(), startTile->y(), 1, 1,
                      [this]() { return e::make_shared<eRoad>(*mBoard); });
            }
        }; break;
        case eBuildingMode::roadblock: {
            const auto t = mBoard->tile(mHoverTX, mHoverTY);
            if(t && t->hasRoad() && !t->hasBridge()) {
                const auto b = t->underBuilding();
                const auto r = static_cast<eRoad*>(b);
                const bool rb = r->isRoadblock();
                if(!rb) r->setRoadblock(true);
            }
        }; break;
        case eBuildingMode::bridge: {
            const auto startTile = mBoard->tile(mHoverTX, mHoverTY);
            if(!startTile) return false;
            std::vector<eTile*> path;
            bool rotated;
            const bool r = bridgeTiles(startTile, path, rotated);
            if(r) {
                for(const auto t : path) {
                    const auto b = e::make_shared<eRoad>(*mBoard);
                    const auto rend = e::make_shared<eBuildingRenderer>(b);
                    t->setBuilding(rend);
                    b->setCenterTile(t);
                    b->setTileRect({t->x(), t->y(), 1, 1});
                    t->setUnderBuilding(b);
                    b->addUnderBuilding(t);

                    const auto diff = mBoard->difficulty();
                    const int cost = eDifficultyHelpers::buildingCost(
                                         diff, eBuildingType::bridge);
                    mBoard->incDrachmas(-path.size()*cost);
                }
            }
        }; break;
        case eBuildingMode::commonHousing: {
            const int sMinX = std::min(mPressedTX, mHoverTX);
            const int sMinY = std::min(mPressedTY, mHoverTY);
            const int sMaxX = std::max(mPressedTX, mHoverTX);
            const int sMaxY = std::max(mPressedTY, mHoverTY);

            for(int x = sMinX; x <= sMaxX; x++) {
                for(int y = sMinY - 1; y <= sMaxY; y++) {
                    const bool cb = canBuildBase(x, x + 2, y, y + 2);
                    if(!cb) continue;
                    const auto t = mBoard->tile(x, y);
                    if(!t) continue;
                    build(t->x(), t->y() + 1, 2, 2,
                          [this]() { return e::make_shared<eSmallHouse>(*mBoard); });
                }
            }
        }; break;
        case eBuildingMode::gymnasium: {
            build(mHoverTX, mHoverTY, 3, 3,
                  [this]() { return e::make_shared<eGymnasium>(*mBoard); });
        }; break;
        case eBuildingMode::podium: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<ePodium>(*mBoard); });
        }; break;
        case eBuildingMode::fountain: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<eFountain>(*mBoard); });
        }; break;
        case eBuildingMode::watchpost: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<eWatchpost>(*mBoard); });
        }; break;
        case eBuildingMode::maintenanceOffice: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<eMaintenanceOffice>(*mBoard); });
        }; break;
        case eBuildingMode::college: {
            build(mHoverTX, mHoverTY, 3, 3,
                  [this]() { return e::make_shared<eCollege>(*mBoard); });
        }; break;
        case eBuildingMode::dramaSchool: {
            build(mHoverTX, mHoverTY, 3, 3,
                  [this]() { return e::make_shared<eDramaSchool>(*mBoard); });
        }; break;
        case eBuildingMode::theater: {
            build(mHoverTX, mHoverTY, 5, 5,
                  [this]() { return e::make_shared<eTheater>(*mBoard); });
        }; break;
        case eBuildingMode::hospital: {
            build(mHoverTX, mHoverTY, 4, 4,
                  [this]() { return e::make_shared<eHospital>(*mBoard); });
        }; break;
        case eBuildingMode::stadium: {
            if(mBoard->hasStadium()) return true;
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
            const bool cb1 = canBuild(t1->x(), t1->y(), 5, 5);
            if(!cb1) return true;
            const auto t2 = t1->tileRel<eTile>(dx, dy);
            if(!t2) return true;
            const bool cb2 = canBuild(t2->x(), t2->y(), 5, 5);
            if(!cb2) return true;
            stdsptr<eStadium> s;
            build(t1->x(), t1->y(), sw, sh, [&]() {
                s = e::make_shared<eStadium>(*mBoard, mRotate);
                return s;
            });
            const auto renderer1 = e::make_shared<eStadium1Renderer>(s);
            t1->setBuilding(renderer1);
            const auto renderer2 = e::make_shared<eStadium2Renderer>(s);
            t2->setBuilding(renderer2);
            mGm->clearMode();
        }; break;
        case eBuildingMode::palace: {
            if(mBoard->hasPalace()) return true;
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
                        const bool cb = canBuild(x, y, 1, 1);
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
            const bool cb1 = canBuild(t1->x(), t1->y(), 4, 4);
            if(!cb1) return true;
            const auto t2 = t1->tileRel<eTile>(dx, dy);
            if(!t2) return true;
            const bool cb2 = canBuild(t2->x(), t2->y(), 4, 4);
            if(!cb2) return true;
            const auto s = e::make_shared<ePalace>(*mBoard, mRotate);
            forAllTiles([&](const int x, const int y) {
                build(x, y, 1, 1, [&]() {
                    bool other = x == tminX && y == tminY;
                    if(!other) {
                        if(mRotate) {
                            other = x == tmaxX - 1 && y == tminY;
                        } else {
                            other = x == tminX && y == tmaxY - 1;
                        }
                    }
                    const auto t = e::make_shared<ePalaceTile>(
                                       *mBoard, other);
                    t->setPalace(s.get());
                    s->addTile(t);
                    return t;
                });
            });
            build(tx, ty, sw, sh, [&]() {
                return s;
            });
            const auto renderer1 = e::make_shared<ePalace1Renderer>(s);
            t1->setBuilding(renderer1);
            const auto renderer2 = e::make_shared<ePalace2Renderer>(s);
            t2->setBuilding(renderer2);
            mGm->clearMode();
        }; break;
        case eBuildingMode::eliteHousing: {
            const auto t1 = mBoard->tile(mHoverTX, mHoverTY);
            if(!t1) return true;
            const bool cb = canBuild(t1->x() + 1, t1->y() + 1, 4, 4);
            if(!cb) return true;
            const auto t2 = t1->tileRel<eTile>(2, 0);
            if(!t2) return true;
            const auto t3 = t1->tileRel<eTile>(2, 2);
            if(!t3) return true;
            const auto t4 = t1->tileRel<eTile>(0, 2);
            if(!t4) return true;
            stdsptr<eEliteHousing> s;
            build(t1->x() + 1, t1->y() + 1, 4, 4, [&]() {
                s = e::make_shared<eEliteHousing>(*mBoard);
                return s;
            });
            const auto renderer1 = e::make_shared<eEliteHousingRenderer>(
                                       eEliteRendererType::top, s);
            t1->setBuilding(renderer1);
            const auto renderer2 = e::make_shared<eEliteHousingRenderer>(
                                       eEliteRendererType::right, s);
            t2->setBuilding(renderer2);
            const auto renderer3 = e::make_shared<eEliteHousingRenderer>(
                                       eEliteRendererType::bottom, s);
            t3->setBuilding(renderer3);
            const auto renderer4 = e::make_shared<eEliteHousingRenderer>(
                                       eEliteRendererType::left, s);
            t4->setBuilding(renderer4);
        }; break;
        case eBuildingMode::taxOffice: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<eTaxOffice>(*mBoard); });
        }; break;
        case eBuildingMode::mint: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<eMint>(*mBoard); });
        }; break;
        case eBuildingMode::foundry: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<eFoundry>(*mBoard); });
        }; break;
        case eBuildingMode::timberMill: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<eTimberMill>(*mBoard); });
        }; break;
        case eBuildingMode::masonryShop: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<eMasonryShop>(*mBoard); });
        }; break;


        case eBuildingMode::oliveTree:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 1, 1,
                      [this]() { return e::make_shared<eResourceBuilding>(
                                *mBoard, eResourceBuildingType::oliveTree); },
                      sTileFertile);
            };
            break;
        case eBuildingMode::vine:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 1, 1,
                      [this]() { return e::make_shared<eResourceBuilding>(
                                *mBoard, eResourceBuildingType::vine); },
                      sTileFertile);
            };
            break;
        case eBuildingMode::orangeTree:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 1, 1,
                      [this]() { return e::make_shared<eResourceBuilding>(
                                *mBoard, eResourceBuildingType::orangeTree); },
                      sTileFertile);
            };
            break;


        case eBuildingMode::huntingLodge: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<eHuntingLodge>(*mBoard); });
        }; break;


        case eBuildingMode::fishery: {
            eOrientation o;
            const bool c = canBuildFishery(mHoverTX, mHoverTY, o);
            if(c) {
                const auto b = e::make_shared<eFishery>(*mBoard, o);
                const auto tile = mBoard->tile(mHoverTX, mHoverTY);
                const auto rend = e::make_shared<eBuildingRenderer>(b);
                tile->setBuilding(rend);
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
            }
        }; break;


        case eBuildingMode::pier: {
            eOrientation o;
            const bool c = canBuildPier(mHoverTX, mHoverTY, o);
            if(c) {
                const auto b = e::make_shared<ePier>(*mBoard, o);
                const auto tile = mBoard->tile(mHoverTX, mHoverTY);
                const auto rend = e::make_shared<eBuildingRenderer>(b);
                tile->setBuilding(rend);
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
                int tx = mHoverTX;
                int ty = mHoverTY;

                switch(o) {
                case eOrientation::topRight: {
                    ty += 3;
                } break;
                case eOrientation::bottomRight: {
                    tx -= 3;
                } break;
                case eOrientation::bottomLeft: {
                    ty -= 3;
                } break;
                default:
                case eOrientation::topLeft: {
                    tx += 3;
                } break;
                }
                const int ctid = mGm->cityId();
                const auto& cts = wrld.cities();
                const auto ct = cts[ctid];
                const auto tp = e::make_shared<eTradePost>(
                                    *mBoard, *ct, eTradePostType::pier);
                tp->setOrientation(o);
                tp->setUnpackBuilding(b.get());
                build(tx, ty, 4, 4, [&]() { return tp; });

                mGm->clearMode();
            }
        }; break;


        case eBuildingMode::dairy: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<eDairy>(*mBoard); });
        }; break;
        case eBuildingMode::cardingShed: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<eCardingShed>(*mBoard); });
        }; break;

        case eBuildingMode::sheep:
            apply = [this](eTile* const tile) {
                buildAnimal(tile, eBuildingType::sheep,
                            [](eGameBoard& board) {
                    return e::make_shared<eSheep>(board);
                });
            };
            break;
        case eBuildingMode::goat:
            apply = [this](eTile* const tile) {
                buildAnimal(tile, eBuildingType::goat,
                            [](eGameBoard& board) {
                    return e::make_shared<eGoat>(board);
                });
            };
            break;

        case eBuildingMode::wheatFarm: {
            build(mHoverTX, mHoverTY, 3, 3,
                  [this]() { return e::make_shared<eWheatFarm>(*mBoard); },
                  sTileFertile);
        }; break;
        case eBuildingMode::onionFarm: {
            build(mHoverTX, mHoverTY, 3, 3,
                  [this]() { return e::make_shared<eOnionFarm>(*mBoard); },
                  sTileFertile);
        }; break;
        case eBuildingMode::carrotFarm: {
            build(mHoverTX, mHoverTY, 3, 3,
                  [this]() { return e::make_shared<eCarrotFarm>(*mBoard); },
                  sTileFertile);
        }; break;
        case eBuildingMode::growersLodge: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<eGrowersLodge>(
                            *mBoard, eGrowerType::grapesAndOlives); });
        }; break;
        case eBuildingMode::orangeTendersLodge: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<eGrowersLodge>(
                            *mBoard, eGrowerType::oranges); });
        }; break;

        case eBuildingMode::granary: {
            build(mHoverTX, mHoverTY, 4, 4,
                  [this]() { return e::make_shared<eGranary>(*mBoard); });
        }; break;
        case eBuildingMode::warehouse: {
            build(mHoverTX, mHoverTY, 3, 3,
                  [this]() { return e::make_shared<eWarehouse>(*mBoard); });
        }; break;

        case eBuildingMode::tradePost: {
            const int ctid = mGm->cityId();
            const auto cts = wrld.cities();
            const auto ct = cts[ctid];
            build(mHoverTX, mHoverTY, 4, 4,
                  [this, wrld, ct]() {
                const auto tp = e::make_shared<eTradePost>(*mBoard, *ct);
                return tp;
            });
            mGm->clearMode();
        }; break;


        case eBuildingMode::wall:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 1, 1,
                      [this]() { return e::make_shared<eWall>(*mBoard); });
            };
            break;
        case eBuildingMode::tower: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<eTower>(*mBoard); });
        }; break;
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
            const bool cb1 = canBuild(tx, ty, 2, 2);
            if(!cb1) return true;
            const bool cb2 = canBuild(tx + dx/2, ty + dy/2, 2, 2);
            if(!cb2) return true;
            const bool cb3 = canBuild(tx + dx, ty + dy, 2, 2);
            if(!cb3) return true;
            const auto b1 = e::make_shared<eGatehouse>(*mBoard, mRotate);
            const auto r1 = e::make_shared<eGatehouseRenderer>(
                           eGatehouseRendererType::grt1, b1);
            const auto t1 = mBoard->tile(tx, ty + 1);
            if(!t1) return true;
            t1->setBuilding(r1);
            const auto r2 = e::make_shared<eGatehouseRenderer>(
                           eGatehouseRendererType::grt2, b1);
            const auto t2 = t1->tileRel<eTile>(dx, dy);
            if(!t2) return true;
            t2->setBuilding(r2);

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
            if(sw == 2) {
                const auto t2 = t1->tileRel<eTile>(0, 1);
                const auto r1 = e::make_shared<eRoad>(*mBoard);
                r1->addUnderBuilding(t2);
                t2->setUnderBuilding(r1);
                t2->setBuilding(e::make_shared<eBuildingRenderer>(r1));
                r1->setCenterTile(t2);

                const auto t3 = t2->tileRel<eTile>(1, 0);
                const auto r2 = e::make_shared<eRoad>(*mBoard);
                r2->addUnderBuilding(t3);
                t3->setUnderBuilding(r2);
                t3->setBuilding(e::make_shared<eBuildingRenderer>(r2));
                r2->setCenterTile(t3);
            } else {
                const auto t2 = t1->tileRel<eTile>(2, -1);
                const auto r1 = e::make_shared<eRoad>(*mBoard);
                r1->addUnderBuilding(t2);
                t2->setUnderBuilding(r1);
                t2->setBuilding(e::make_shared<eBuildingRenderer>(r1));
                r1->setCenterTile(t2);

                const auto t3 = t2->tileRel<eTile>(0, 1);
                const auto r2 = e::make_shared<eRoad>(*mBoard);
                r2->addUnderBuilding(t3);
                t3->setUnderBuilding(r2);
                t3->setBuilding(e::make_shared<eBuildingRenderer>(r2));
                r2->setCenterTile(t3);
            }
            const auto diff = mBoard->difficulty();
            const int cost = eDifficultyHelpers::buildingCost(
                                 diff, eBuildingType::gatehouse);
            mBoard->incDrachmas(-cost);
        }; break;

        case eBuildingMode::armory: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<eArmory>(*mBoard); });
        }; break;
        case eBuildingMode::horseRanch: {
            const int tx = mHoverTX;
            const int ty = mHoverTY;
            const bool cb1 = canBuild(tx, ty, 3, 3);
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
            const bool cb2 = canBuild(tx + dx, ty + dy, 4, 4);
            if(!cb2) return true;
            const auto hr = e::make_shared<eHorseRanch>(*mBoard);
            const auto hre = e::make_shared<eHorseRanchEnclosure>(*mBoard);
            hre->setRanch(hr.get());
            hr->setEnclosure(hre.get());
            build(tx, ty, 3, 3,
                  [hr]() { return hr; });
            build(tx + dx, ty + dy, 4, 4,
                  [hre]() { return hre; });
        }; break;
        case eBuildingMode::olivePress: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<eOlivePress>(*mBoard); });
        }; break;
        case eBuildingMode::winery: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<eWinery>(*mBoard); });
        }; break;
        case eBuildingMode::sculptureStudio: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<eSculptureStudio>(*mBoard); });
        }; break;

        case eBuildingMode::artisansGuild: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<eArtisansGuild>(*mBoard); });
        }; break;

        case eBuildingMode::foodVendor: {
            return buildVendor<eFoodVendor>(*mBoard, mHoverTX, mHoverTY,
                                            eResourceType::food);
        }; break;
        case eBuildingMode::fleeceVendor: {
            return buildVendor<eFleeceVendor>(*mBoard, mHoverTX, mHoverTY,
                                              eResourceType::fleece);
        }; break;
        case eBuildingMode::oilVendor: {
            return buildVendor<eOilVendor>(*mBoard, mHoverTX, mHoverTY,
                                           eResourceType::oliveOil);
        }; break;
        case eBuildingMode::wineVendor: {
            return buildVendor<eWineVendor>(*mBoard, mHoverTX, mHoverTY,
                                            eResourceType::wine);
        }; break;
        case eBuildingMode::armsVendor: {
            return buildVendor<eArmsVendor>(*mBoard, mHoverTX, mHoverTY,
                                            eResourceType::armor);
        }; break;
        case eBuildingMode::horseTrainer: {
            return buildVendor<eHorseVendor>(*mBoard, mHoverTX, mHoverTY,
                                             eResourceType::horse);
        }; break;

        case eBuildingMode::park:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 1, 1,
                      [this]() { return e::make_shared<ePark>(*mBoard); });
            };
            break;
        case eBuildingMode::doricColumn:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 1, 1,
                      [this]() { return e::make_shared<eDoricColumn>(*mBoard); });
            };
            break;
        case eBuildingMode::ionicColumn:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 1, 1,
                      [this]() { return e::make_shared<eIonicColumn>(*mBoard); });
            };
            break;
        case eBuildingMode::corinthianColumn:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 1, 1,
                      [this]() { return e::make_shared<eCorinthianColumn>(*mBoard); });
            };
            break;
        case eBuildingMode::avenue:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 1, 1,
                      [this]() { return e::make_shared<eAvenue>(*mBoard); });
            };
            break;

        case eBuildingMode::populationMonument: {
            build(mHoverTX, mHoverTY, 3, 3,
                  [this]() { return e::make_shared<eCommemorative>(0, *mBoard); });
        }; break;
        case eBuildingMode::commemorative2: {
            build(mHoverTX, mHoverTY, 3, 3,
                  [this]() { return e::make_shared<eCommemorative>(1, *mBoard); });
        }; break;
        case eBuildingMode::colonyMonument: {
            build(mHoverTX, mHoverTY, 3, 3,
                  [this]() { return e::make_shared<eCommemorative>(2, *mBoard); });
        }; break;
        case eBuildingMode::athleteMonument: {
            build(mHoverTX, mHoverTY, 3, 3,
                  [this]() { return e::make_shared<eCommemorative>(3, *mBoard); });
        }; break;
        case eBuildingMode::conquestMonument: {
            build(mHoverTX, mHoverTY, 3, 3,
                  [this]() { return e::make_shared<eCommemorative>(4, *mBoard); });
        }; break;
        case eBuildingMode::happinessMonument: {
            build(mHoverTX, mHoverTY, 3, 3,
                  [this]() { return e::make_shared<eCommemorative>(5, *mBoard); });
        }; break;
        case eBuildingMode::commemorative7: {
            build(mHoverTX, mHoverTY, 3, 3,
                  [this]() { return e::make_shared<eCommemorative>(6, *mBoard); });
        }; break;
        case eBuildingMode::commemorative8: {
            build(mHoverTX, mHoverTY, 3, 3,
                  [this]() { return e::make_shared<eCommemorative>(7, *mBoard); });
        }; break;
        case eBuildingMode::scholarMonument: {
            build(mHoverTX, mHoverTY, 3, 3,
                  [this]() { return e::make_shared<eCommemorative>(8, *mBoard); });
        }; break;


        case eBuildingMode::bench: {
            build(mHoverTX, mHoverTY, 1, 1,
                  [this]() { return e::make_shared<eBench>(*mBoard); });
        }; break;
        case eBuildingMode::flowerGarden: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<eFlowerGarden>(*mBoard); });
        }; break;
        case eBuildingMode::gazebo: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<eGazebo>(*mBoard); });
        }; break;
        case eBuildingMode::hedgeMaze: {
            build(mHoverTX, mHoverTY, 3, 3,
                  [this]() { return e::make_shared<eHedgeMaze>(*mBoard); });
        }; break;
        case eBuildingMode::fishPond: {
            build(mHoverTX, mHoverTY, 4, 4,
                  [this]() { return e::make_shared<eFishPond>(*mBoard); });
        }; break;

        case eBuildingMode::waterPark: {
            build(mHoverTX, mHoverTY, 2, 2, [this]() {
                const auto b = e::make_shared<eWaterPark>(*mBoard);
                b->setId(waterParkId());
                return b;
            });
        }; break;

        case eBuildingMode::birdBath: {
            build(mHoverTX, mHoverTY, 1, 1,
                  [this]() { return e::make_shared<eBirdBath>(*mBoard); });
        }; break;
        case eBuildingMode::shortObelisk: {
            build(mHoverTX, mHoverTY, 1, 1,
                  [this]() { return e::make_shared<eShortObelisk>(*mBoard); });
        }; break;
        case eBuildingMode::tallObelisk: {
            build(mHoverTX, mHoverTY, 1, 1,
                  [this]() { return e::make_shared<eTallObelisk>(*mBoard); });
        }; break;
        case eBuildingMode::shellGarden: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<eShellGarden>(*mBoard); });
        }; break;
        case eBuildingMode::sundial: {
            build(mHoverTX, mHoverTY, 2, 2,
                  [this]() { return e::make_shared<eSundial>(*mBoard); });
        }; break;
        case eBuildingMode::dolphinSculpture: {
            build(mHoverTX, mHoverTY, 3, 3,
                  [this]() { return e::make_shared<eDolphinSculpture>(*mBoard); });
        }; break;
        case eBuildingMode::spring: {
            build(mHoverTX, mHoverTY, 3, 3,
                  [this]() { return e::make_shared<eSpring>(*mBoard); });
        }; break;
        case eBuildingMode::topiary: {
            build(mHoverTX, mHoverTY, 3, 3,
                  [this]() { return e::make_shared<eTopiary>(*mBoard); });
        }; break;
        case eBuildingMode::baths: {
            build(mHoverTX, mHoverTY, 4, 4,
                  [this]() { return e::make_shared<eBaths>(*mBoard); });
        }; break;
        case eBuildingMode::stoneCircle: {
            build(mHoverTX, mHoverTY, 4, 4,
                  [this]() { return e::make_shared<eStoneCircle>(*mBoard); });
        }; break;
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
            build(mHoverTX, mHoverTY, 4, 4,
                  [this, heroType]() { return e::make_shared<eHerosHall>(heroType, *mBoard); });
        } break;
        case eBuildingMode::templeArtemis:
        case eBuildingMode::templeHephaestus: {
            const auto bt = eBuildingModeHelpers::toBuildingType(mode);
            const auto h = eSanctBlueprints::sSanctuaryBlueprint(bt, mRotate);

            const int sw = h->fW;
            const int sh = h->fH;

            const int minX = mHoverTX - sw/2;
            const int maxX = minX + sw;
            const int minY = mHoverTY - sh/2;
            const int maxY = minY + sh;
            const bool cb = canBuildBase(minX, maxX, minY, maxY);
            if(!cb) return true;

            eGodType god;
            stdsptr<eSanctuary> b;
            switch(mode) {
            case eBuildingMode::templeArtemis: {
                god = eGodType::artemis;
                b = e::make_shared<eArtemisSanctuary>(
                        sw, sh, *mBoard);
            } break;
            case eBuildingMode::templeHephaestus: {
                god = eGodType::hephaestus;
                b = e::make_shared<eHephaestusSanctuary>(
                        sw, sh, *mBoard);
            } break;
            }

            const bool r = canBuildBase(minX, maxX, minY, maxY);
            if(!r) return true;
            const auto mint = mBoard->tile(minX, minY);
            const int a = mint->altitude();
            b->setAltitude(a);

            b->setTileRect({minX, minY, sw, sh});
            const auto ct = mBoard->tile((minX + maxX)/2, (minY + maxY)/2);
            b->setCenterTile(ct);

            const auto tb = e::make_shared<eTempleBuilding>(*mBoard);
            tb->setSanctuary(b.get());
            b->registerElement(tb);
            int ts = 0;
            for(const auto& tv : h->fTiles) {
                for(const auto& t : tv) {
                    const int tx = minX + t.fX;
                    const int ty = minY + t.fY;
                    const auto tile = mBoard->tile(tx, ty);
                    switch(t.fType) {
                    case eSanctEleType::copper:
                        tile->setTerrain(eTerrain::copper);
                        break;
                    case eSanctEleType::statue: {
                        const auto tt = e::make_shared<eTempleStatueBuilding>(
                                           god, t.fId, *mBoard);
                        tt->setSanctuary(b.get());
                        build(tx, ty, 1, 1, [tt]() { return tt; });
                        b->registerElement(tt);
                    } break;
                    case eSanctEleType::monument: {
                        const auto tt = e::make_shared<eTempleMonumentBuilding>(
                                            god, t.fId, *mBoard);
                        tt->setSanctuary(b.get());
                        const int d = mRotate ? 1 : 0;
                        build(tx - d, ty + d, 2, 2, [tt]() { return tt; });
                        b->registerElement(tt);
                    } break;
                    case eSanctEleType::altar: {
                        const auto tt = e::make_shared<eTempleAltarBuilding>(
                                            *mBoard);
                        tt->setSanctuary(b.get());
                        const int d = mRotate ? 1 : 0;
                        build(tx - d, ty + d, 2, 2, [tt]() { return tt; });
                        b->registerElement(tt);
                    } break;
                    case eSanctEleType::sanctuary: {
                        ts++;
                        if(mRotate) {
                            build(tx - 2, ty + 2, 4, 4, [tb]() { return tb; },
                            nullptr,
                            [&]() { return e::make_shared<eTempleRenderer>(t.fId, tb); });
                        } else {
                            build(tx + 1, ty - 1, 4, 4, [tb]() { return tb; },
                            nullptr,
                            [&]() { return e::make_shared<eTempleRenderer>(t.fId, tb); });
                        }
                    } break;
                    case eSanctEleType::tile: {
                        const auto tt = e::make_shared<eTempleTileBuilding>(
                                            t.fId, *mBoard);
                        tt->setSanctuary(b.get());
                        build(tx, ty, 1, 1, [tt]() { return tt; });
                        b->registerElement(tt);
                    } break;
                    case eSanctEleType::stairs: {
                        tile->setSeed(t.fId);
                        tile->setWalkableElev(true);
//                            const auto s = e::make_shared<eStairsRenderer>(t.fId, b);
//                            tile->setBuilding(s);
                    } break;
                    case eSanctEleType::none:
                        break;
                    }
                }
            }
            tb->setCost({ts*5, ts*5, 0});
            for(const auto& tv : h->fTiles) {
                for(const auto& t : tv) {
                    const int tx = minX + t.fX;
                    const int ty = minY + t.fY;
                    const auto tile = mBoard->tile(tx, ty);
                    tile->setAltitude(tile->altitude() + t.fA);
                    const auto trr = tile->terrain();
                    const bool bldbl = static_cast<bool>(
                                           trr & eTerrain::buildable);
                    if(!tile->underBuilding() && bldbl) {
                        tile->setUnderBuilding(b);
                        b->addUnderBuilding(tile);
                    }
                }
            }
        }; break;
        default: break;
        }
    }

    actionOnSelectedTiles(apply);
    return true;
}
