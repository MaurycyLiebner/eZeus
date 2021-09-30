#include "egamewidget.h"

#include "eterraineditmenu.h"

#include "buildings/ebuildingrenderer.h"

#include "buildings/esmallhouse.h"
#include "buildings/egymnasium.h"
#include "buildings/eroad.h"
#include "buildings/epodium.h"
#include "buildings/ecollege.h"
#include "buildings/efountain.h"
#include "buildings/ewatchpost.h"
#include "buildings/ehospital.h"
#include "buildings/etheater.h"
#include "buildings/edramaschool.h"
#include "buildings/estadium.h"
#include "buildings/estadiumrenderer.h"
#include "buildings/epalace.h"
#include "buildings/epalacerenderer.h"
#include "buildings/emint.h"
#include "buildings/efoundry.h"
#include "buildings/etimbermill.h"
#include "buildings/emasonryshop.h"
#include "buildings/etaxoffice.h"
#include "buildings/eresourcebuilding.h"
#include "buildings/ehuntinglodge.h"
#include "buildings/emaintenanceoffice.h"

#include "buildings/egranary.h"
#include "buildings/ewarehouse.h"

#include "buildings/egrowerslodge.h"

#include "buildings/ewinery.h"
#include "buildings/eolivepress.h"
#include "buildings/esculpturestudio.h"
#include "buildings/earmory.h"

#include "buildings/ewall.h"
#include "buildings/etower.h"
#include "buildings/egatehouse.h"
#include "buildings/egatehouserenderer.h"

#include "buildings/ewheatfarm.h"
#include "buildings/eonionfarm.h"
#include "buildings/ecarrotfarm.h"

#include "buildings/edairy.h"
#include "buildings/ecardingshed.h"

#include "buildings/efoodvendor.h"
#include "buildings/efleecevendor.h"
#include "buildings/eoilvendor.h"
#include "buildings/ewinevendor.h"
#include "buildings/earmsvendor.h"
#include "buildings/ehorsevendor.h"

#include "buildings/epark.h"
#include "buildings/ecolumn.h"
#include "buildings/eavenue.h"

#include "buildings/eanimalbuilding.h"

#include "buildings/eelitehousing.h"
#include "buildings/eelitehousingrenderer.h"

#include "buildings/sanctuaries/ehephaestussanctuary.h"
#include "buildings/sanctuaries/eartemissanctuary.h"
#include "buildings/sanctuaries/estairsrenderer.h"
#include "buildings/sanctuaries/etempletilebuilding.h"
#include "buildings/sanctuaries/etemplestatuebuilding.h"
#include "buildings/sanctuaries/etemplemonumentbuilding.h"
#include "buildings/sanctuaries/etemplealtarbuilding.h"
#include "buildings/sanctuaries/etemplebuilding.h"
#include "buildings/sanctuaries/etemplerenderer.h"

#include "characters/esheep.h"
#include "characters/egoat.h"
#include "characters/actions/eanimalaction.h"

#include "spawners/eboarspawner.h"
#include "spawners/edeerspawner.h"
#include "spawners/esettlerspawner.h"

const eSanctBlueprint* eGameWidget::sanctuaryBlueprint(
        const eBuildingType type, const bool rotate) {
    const auto& i = eSanctBlueprints::instance;
    switch(type) {
    case eBuildingType::templeArtemis: {
        if(rotate) {
            return &i.fArtemisH;
        } else {
            return &i.fArtemisW;
        }
    } break;
    case eBuildingType::templeHephaestus: {
        if(rotate) {
            return &i.fHephaestusH;
        } else {
            return &i.fHephaestusW;
        }
    } break;
    }
    return nullptr;
}

void eGameWidget::buildMouseRelease() {
    std::function<void(eTile* const)> apply;
    if(mTem->visible()) {
        const auto mode = mTem->mode();
        if(mode == eTerrainEditMode::scrub) {
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
            const auto t = mBoard.tile(mHoverX, mHoverY);
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
                const auto os = tile->spawner();
                if(os) delete os;
                new eBoarSpawner(tile, mBoard);
            };
        } else if(mode == eTerrainEditMode::deer) {
            apply = [this](eTile* const tile) {
                const auto os = tile->spawner();
                if(os) delete os;
                new eDeerSpawner(tile, mBoard);
            };
        } else if(mode == eTerrainEditMode::fire) {
            apply = [](eTile* const tile) {
                tile->setOnFire(true);
            };
        } else if(mode == eTerrainEditMode::settlers) {
            apply = [this](eTile* const tile) {
                const auto os = tile->spawner();
                if(os) delete os;
                new eSettlerSpawner(tile, mBoard);
            };
        } else {
            apply = [mode](eTile* const tile) {
                const auto terr = static_cast<eTerrain>(mode);
                tile->setTerrain(terr);
            };
        }
    } else {
        const auto mode = mGm->mode();
        switch(mode) {
        case eBuildingMode::none: {
            const auto tile = mBoard.tile(mHoverX, mHoverY);
            if(!mPatrolBuilding && tile) {
                if(const auto b = tile->underBuilding()) {
                    if(const auto pb = dynamic_cast<ePatrolBuilding*>(b)) {
                        setViewMode(eViewMode::patrolBuilding);
                        mPatrolBuilding = pb;
                    }
                }
            }
        } break;
        case eBuildingMode::erase:
            apply = [this](eTile* const tile) {
                erase(tile);

                const auto diff = mBoard.difficulty();
                const int cost = eDifficultyHelpers::buildingCost(diff, eBuildingType::erase);
                mBoard.incDrachmas(-cost);
            };
            break;
        case eBuildingMode::road:
            apply = [this](eTile*) {
                const auto startTile = mBoard.tile(mHoverX, mHoverY);
                std::vector<eOrientation> path;
                const bool r = roadPath(path);
                if(r) {
                    eTile* t = startTile;
                    for(int i = path.size() - 1; i >= 0; i--) {
                        if(!t) break;
                        build(t->x(), t->y(), 1, 1,
                              [this]() { return e::make_shared<eRoad>(mBoard); });
                        t = t->neighbour<eTile>(path[i]);
                    }
                    if(t) {
                        build(t->x(), t->y(), 1, 1,
                              [this]() { return e::make_shared<eRoad>(mBoard); });
                    }
                } else {
                    build(startTile->x(), startTile->y(), 1, 1,
                          [this]() { return e::make_shared<eRoad>(mBoard); });
                }
            };
            break;
        case eBuildingMode::commonHousing:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 2, 2,
                      [this]() { return e::make_shared<eSmallHouse>(mBoard); });
            };
            break;
        case eBuildingMode::gymnasium:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 3, 3,
                      [this]() { return e::make_shared<eGymnasium>(mBoard); });
            };
            break;
        case eBuildingMode::podium:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<ePodium>(mBoard); });
            };
            break;
        case eBuildingMode::fountain:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eFountain>(mBoard); });
            };
            break;
        case eBuildingMode::watchpost:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eWatchpost>(mBoard); });
            };
            break;
        case eBuildingMode::maintenanceOffice:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eMaintenanceOffice>(mBoard); });
            };
            break;
        case eBuildingMode::college:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 3, 3,
                      [this]() { return e::make_shared<eCollege>(mBoard); });
            };
            break;
        case eBuildingMode::dramaSchool:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 3, 3,
                      [this]() { return e::make_shared<eDramaSchool>(mBoard); });
            };
            break;
        case eBuildingMode::theater:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 5, 5,
                      [this]() { return e::make_shared<eTheater>(mBoard); });
            };
            break;
        case eBuildingMode::hospital:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 4, 4,
                      [this]() { return e::make_shared<eHospital>(mBoard); });
            };
            break;
        case eBuildingMode::stadium:
            apply = [this](eTile*) {
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
                const auto t1 = mBoard.tile(mHoverX, mHoverY);
                if(!t1) return;
                const bool cb1 = canBuild(t1->x(), t1->y(), 5, 5);
                if(!cb1) return;
                const auto t2 = t1->tileRel<eTile>(dx, dy);
                if(!t2) return;
                const bool cb2 = canBuild(t2->x(), t2->y(), 5, 5);
                if(!cb2) return;
                stdsptr<eStadium> s;
                build(t1->x(), t1->y(), sw, sh, [&]() {
                    s = e::make_shared<eStadium>(mBoard, mRotate);
                    return s;
                });
                const auto renderer1 = e::make_shared<eStadium1Renderer>(s);
                t1->setBuilding(renderer1);
                const auto renderer2 = e::make_shared<eStadium2Renderer>(s);
                t2->setBuilding(renderer2);
            };
            break;
        case eBuildingMode::palace:
            apply = [this](eTile*) {
                int dx;
                int dy;
                int sw;
                int sh;
                if(mRotate) {
                    dx = 0;
                    dy = 4;
                    sw = 4;
                    sh = 8;
                } else {
                    dx = 4;
                    dy = 0;
                    sw = 8;
                    sh = 4;
                }
                const auto t1 = mBoard.tile(mHoverX, mHoverY);
                if(!t1) return;
                const bool cb1 = canBuild(t1->x(), t1->y(), 4, 4);
                if(!cb1) return;
                const auto t2 = t1->tileRel<eTile>(dx, dy);
                if(!t2) return;
                const bool cb2 = canBuild(t2->x(), t2->y(), 4, 4);
                if(!cb2) return;
                stdsptr<ePalace> s;
                build(t1->x(), t1->y(), sw, sh, [&]() {
                    s = e::make_shared<ePalace>(mBoard, mRotate);
                    return s;
                });
                const auto renderer1 = e::make_shared<ePalace1Renderer>(s);
                t1->setBuilding(renderer1);
                const auto renderer2 = e::make_shared<ePalace2Renderer>(s);
                t2->setBuilding(renderer2);
            };
            break;
        case eBuildingMode::eliteHousing:
            apply = [this](eTile*) {
                const auto t1 = mBoard.tile(mHoverX, mHoverY);
                if(!t1) return;
                const bool cb = canBuild(t1->x() + 1, t1->y() + 1, 4, 4);
                if(!cb) return;
                const auto t2 = t1->tileRel<eTile>(2, 0);
                if(!t2) return;
                const auto t3 = t1->tileRel<eTile>(2, 2);
                if(!t3) return;
                const auto t4 = t1->tileRel<eTile>(0, 2);
                if(!t4) return;
                stdsptr<eEliteHousing> s;
                build(t1->x() + 1, t1->y() + 1, 4, 4, [&]() {
                    s = e::make_shared<eEliteHousing>(mBoard);
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
            };
            break;
        case eBuildingMode::taxOffice:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eTaxOffice>(mBoard); });
            };
            break;
        case eBuildingMode::mint:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eMint>(mBoard); });
            };
            break;
        case eBuildingMode::foundry:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eFoundry>(mBoard); });
            };
            break;
        case eBuildingMode::timberMill:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eTimberMill>(mBoard); });
            };
            break;
        case eBuildingMode::masonryShop:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eMasonryShop>(mBoard); });
            };
            break;


        case eBuildingMode::oliveTree:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 1, 1,
                      [this]() { return e::make_shared<eResourceBuilding>(
                                mBoard, eResourceBuildingType::oliveTree); },
                      sTileFertile);
            };
            break;
        case eBuildingMode::vine:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 1, 1,
                      [this]() { return e::make_shared<eResourceBuilding>(
                                mBoard, eResourceBuildingType::vine); },
                      sTileFertile);
            };
            break;
        case eBuildingMode::orangeTree:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 1, 1,
                      [this]() { return e::make_shared<eResourceBuilding>(
                                mBoard, eResourceBuildingType::orangeTree); },
                      sTileFertile);
            };
            break;


        case eBuildingMode::huntingLodge:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eHuntingLodge>(mBoard); });
            };
            break;


        case eBuildingMode::dairy:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eDairy>(mBoard); });
            };
            break;
        case eBuildingMode::cardingShed:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eCardingShed>(mBoard); });
            };
            break;

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

        case eBuildingMode::wheatFarm:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 3, 3,
                      [this]() { return e::make_shared<eWheatFarm>(mBoard); },
                      sTileFertile);
            };
            break;
        case eBuildingMode::onionFarm:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 3, 3,
                      [this]() { return e::make_shared<eOnionFarm>(mBoard); },
                      sTileFertile);
            };
            break;
        case eBuildingMode::carrotFarm:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 3, 3,
                      [this]() { return e::make_shared<eCarrotFarm>(mBoard); },
                      sTileFertile);
            };
            break;
        case eBuildingMode::growersLodge:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eGrowersLodge>(
                                mBoard, eGrowerType::grapesAndOlives); });
            };
            break;
        case eBuildingMode::orangeTendersLodge:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eGrowersLodge>(
                                mBoard, eGrowerType::oranges); });
            };
            break;

        case eBuildingMode::granary:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 4, 4,
                      [this]() { return e::make_shared<eGranary>(mBoard); });
            };
            break;
        case eBuildingMode::warehouse:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 3, 3,
                      [this]() { return e::make_shared<eWarehouse>(mBoard); });
            };
            break;


        case eBuildingMode::wall:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 1, 1,
                      [this]() { return e::make_shared<eWall>(mBoard); });
            };
            break;
        case eBuildingMode::tower:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eTower>(mBoard); });
            };
            break;
        case eBuildingMode::gatehouse:
            apply = [this](eTile*) {
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
                const int tx = mHoverX;
                const int ty = mHoverY - 1;
                const bool cb1 = canBuild(tx, ty, 2, 2);
                if(!cb1) return;
                const bool cb2 = canBuild(tx + dx/2, ty + dy/2, 2, 2);
                if(!cb2) return;
                const bool cb3 = canBuild(tx + dx, ty + dy, 2, 2);
                if(!cb3) return;
                const auto b1 = e::make_shared<eGatehouse>(mBoard, mRotate);
                const auto r1 = e::make_shared<eGatehouseRenderer>(
                               eGatehouseRendererType::grt1, b1);
                const auto t1 = mBoard.tile(tx, ty + 1);
                if(!t1) return;
                t1->setBuilding(r1);
                const auto r2 = e::make_shared<eGatehouseRenderer>(
                               eGatehouseRendererType::grt2, b1);
                const auto t2 = t1->tileRel<eTile>(dx, dy);
                if(!t2) return;
                t2->setBuilding(r2);

                sClearScrub(tx, ty, sw, sh, mBoard);
                b1->setTileRect({tx, ty, sw, sh});
                const int minX = tx;
                const int maxX = tx + sw;
                const int minY = ty;
                const int maxY = ty + sh;
                for(int x = minX; x < maxX; x++) {
                    for(int y = minY; y < maxY; y++) {
                        const auto t = mBoard.tile(x, y);
                        if(t) {
                            t->setUnderBuilding(b1);
                            b1->addUnderBuilding(t);
                        }
                    }
                }
                if(sw == 2) {
                    const auto t2 = t1->tileRel<eTile>(0, 1);
                    const auto r1 = e::make_shared<eRoad>(mBoard);
                    r1->addUnderBuilding(t2);
                    t2->setUnderBuilding(r1);
                    t2->setBuilding(e::make_shared<eBuildingRenderer>(r1));

                    const auto t3 = t2->tileRel<eTile>(1, 0);
                    const auto r2 = e::make_shared<eRoad>(mBoard);
                    r2->addUnderBuilding(t3);
                    t3->setUnderBuilding(r2);
                    t3->setBuilding(e::make_shared<eBuildingRenderer>(r2));
                } else {
                    const auto t2 = t1->tileRel<eTile>(2, -1);
                    const auto r1 = e::make_shared<eRoad>(mBoard);
                    r1->addUnderBuilding(t2);
                    t2->setUnderBuilding(r1);
                    t2->setBuilding(e::make_shared<eBuildingRenderer>(r1));

                    const auto t3 = t2->tileRel<eTile>(0, 1);
                    const auto r2 = e::make_shared<eRoad>(mBoard);
                    r2->addUnderBuilding(t3);
                    t3->setUnderBuilding(r2);
                    t3->setBuilding(e::make_shared<eBuildingRenderer>(r2));
                }
                const auto diff = mBoard.difficulty();
                const int cost = eDifficultyHelpers::buildingCost(
                                     diff, eBuildingType::gatehouse);
                mBoard.incDrachmas(-cost);
            };
            break;

        case eBuildingMode::armory:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eArmory>(mBoard); });
            };
            break;
        case eBuildingMode::olivePress:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eOlivePress>(mBoard); });
            };
            break;
        case eBuildingMode::winery:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eWinery>(mBoard); });
            };
            break;
        case eBuildingMode::sculptureStudio:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eSculptureStudio>(mBoard); });
            };
            break;

        case eBuildingMode::foodVendor:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eFoodVendor>(mBoard); });
            };
            break;
        case eBuildingMode::fleeceVendor:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eFleeceVendor>(mBoard); });
            };
            break;
        case eBuildingMode::oilVendor:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eOilVendor>(mBoard); });
            };
            break;
        case eBuildingMode::wineVendor:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eWineVendor>(mBoard); });
            };
            break;
        case eBuildingMode::armsVendor:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eArmsVendor>(mBoard); });
            };
            break;
        case eBuildingMode::horseTrainer:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eHorseVendor>(mBoard); });
            };
            break;

        case eBuildingMode::park:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 1, 1,
                      [this]() { return e::make_shared<ePark>(mBoard); });
            };
            break;
        case eBuildingMode::doricColumn:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 1, 1,
                      [this]() { return e::make_shared<eDoricColumn>(mBoard); });
            };
            break;
        case eBuildingMode::ionicColumn:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 1, 1,
                      [this]() { return e::make_shared<eIonicColumn>(mBoard); });
            };
            break;
        case eBuildingMode::corinthianColumn:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 1, 1,
                      [this]() { return e::make_shared<eCorinthianColumn>(mBoard); });
            };
            break;
        case eBuildingMode::avenue:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 1, 1,
                      [this]() { return e::make_shared<eAvenue>(mBoard); });
            };
            break;

        case eBuildingMode::populationMonument:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 3, 3,
                      [this]() { return e::make_shared<eCommemorative>(0, mBoard); });
            };
            break;
        case eBuildingMode::commemorative2:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 3, 3,
                      [this]() { return e::make_shared<eCommemorative>(1, mBoard); });
            };
            break;
        case eBuildingMode::colonyMonument:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 3, 3,
                      [this]() { return e::make_shared<eCommemorative>(2, mBoard); });
            };
            break;
        case eBuildingMode::athleteMonument:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 3, 3,
                      [this]() { return e::make_shared<eCommemorative>(3, mBoard); });
            };
            break;
        case eBuildingMode::conquestMonument:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 3, 3,
                      [this]() { return e::make_shared<eCommemorative>(4, mBoard); });
            };
            break;
        case eBuildingMode::happinessMonument:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 3, 3,
                      [this]() { return e::make_shared<eCommemorative>(5, mBoard); });
            };
            break;
        case eBuildingMode::commemorative7:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 3, 3,
                      [this]() { return e::make_shared<eCommemorative>(6, mBoard); });
            };
            break;
        case eBuildingMode::commemorative8:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 3, 3,
                      [this]() { return e::make_shared<eCommemorative>(7, mBoard); });
            };
            break;
        case eBuildingMode::scholarMonument:
            apply = [this](eTile* const tile) {
                build(tile->x(), tile->y(), 3, 3,
                      [this]() { return e::make_shared<eCommemorative>(8, mBoard); });
            };
            break;


        case eBuildingMode::bench:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 1, 1,
                      [this]() { return e::make_shared<eBench>(mBoard); });
            };
            break;
        case eBuildingMode::flowerGarden:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eFlowerGarden>(mBoard); });
            };
            break;
        case eBuildingMode::gazebo:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eGazebo>(mBoard); });
            };
            break;
        case eBuildingMode::hedgeMaze:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 3, 3,
                      [this]() { return e::make_shared<eHedgeMaze>(mBoard); });
            };
            break;
        case eBuildingMode::fishPond:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 4, 4,
                      [this]() { return e::make_shared<eFishPond>(mBoard); });
            };
            break;

        case eBuildingMode::waterPark:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2, [this]() {
                    const auto b = e::make_shared<eWaterPark>(mBoard);
                    b->setId(waterParkId());
                    return b;
                });
            };
            break;

        case eBuildingMode::birdBath:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 1, 1,
                      [this]() { return e::make_shared<eBirdBath>(mBoard); });
            };
            break;
        case eBuildingMode::shortObelisk:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 1, 1,
                      [this]() { return e::make_shared<eShortObelisk>(mBoard); });
            };
            break;
        case eBuildingMode::tallObelisk:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 1, 1,
                      [this]() { return e::make_shared<eTallObelisk>(mBoard); });
            };
            break;
        case eBuildingMode::shellGarden:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eShellGarden>(mBoard); });
            };
            break;
        case eBuildingMode::sundial:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 2, 2,
                      [this]() { return e::make_shared<eSundial>(mBoard); });
            };
            break;
        case eBuildingMode::dolphinSculpture:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 3, 3,
                      [this]() { return e::make_shared<eDolphinSculpture>(mBoard); });
            };
            break;
        case eBuildingMode::spring:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 3, 3,
                      [this]() { return e::make_shared<eSpring>(mBoard); });
            };
            break;
        case eBuildingMode::topiary:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 3, 3,
                      [this]() { return e::make_shared<eTopiary>(mBoard); });
            };
            break;
        case eBuildingMode::baths:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 4, 4,
                      [this]() { return e::make_shared<eBaths>(mBoard); });
            };
            break;
        case eBuildingMode::stoneCircle:
            apply = [this](eTile*) {
                build(mHoverX, mHoverY, 4, 4,
                      [this]() { return e::make_shared<eStoneCircle>(mBoard); });
            };
            break;
        case eBuildingMode::templeArtemis:
        case eBuildingMode::templeHephaestus:
            apply = [this, mode](eTile*) {
                const auto bt = eBuildingModeHelpers::toBuildingType(mode);
                const auto h = sanctuaryBlueprint(bt, mRotate);

                const int sw = h->fW;
                const int sh = h->fH;

                eGodType god;
                stdsptr<eSanctuary> b;
                switch(mode) {
                case eBuildingMode::templeArtemis: {
                    god = eGodType::artemis;
                    b = e::make_shared<eArtemisSanctuary>(
                            sw, sh, mBoard);
                } break;
                case eBuildingMode::templeHephaestus: {
                    god = eGodType::hephaestus;
                    b = e::make_shared<eHephaestusSanctuary>(
                            sw, sh, mBoard);
                } break;
                }

                const int minX = mHoverX - sw/2;
                const int maxX = minX + sw;
                const int minY = mHoverY - sh/2;
                const int maxY = minY + sh;
                const bool r = canBuildBase(minX, maxX, minY, maxY);
                if(!r) return;
                sClearScrub(minX, minY, sw, sh, mBoard);
                b->setTileRect({minX, minY, sw, sh});

                const auto tb = e::make_shared<eTempleBuilding>(mBoard);
                b->registerElement(tb);
                int ts = 0;
                for(const auto& tv : h->fTiles) {
                    for(const auto& t : tv) {
                        const int tx = minX + t.fX;
                        const int ty = minY + t.fY;
                        const auto tile = mBoard.tile(tx, ty);
                        switch(t.fType) {
                        case eSanctEleType::copper:
                            tile->setTerrain(eTerrain::copper);
                            break;
                        case eSanctEleType::statue: {
                            const auto tt = e::make_shared<eTempleStatueBuilding>(
                                                god, t.fId, mBoard);
                            const auto r = e::make_shared<eBuildingRenderer>(tt);
                            tile->setBuilding(r);
                            tile->setUnderBuilding(tt);
                            tt->addUnderBuilding(tile);
                            b->registerElement(tt);
                        } break;
                        case eSanctEleType::monument: {
                            const auto tt = e::make_shared<eTempleMonumentBuilding>(
                                                god, t.fId, mBoard);
                            const int d = mRotate ? 1 : 0;
                            build(tx - d, ty + d, 2, 2, [tt]() { return tt; });
                            b->registerElement(tt);
                        } break;
                        case eSanctEleType::altar: {
                            const auto tt = e::make_shared<eTempleAltarBuilding>(
                                                mBoard);
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
                            const auto tt = e::make_shared<eTempleTileBuilding>(t.fId, mBoard);
                            const auto r = e::make_shared<eBuildingRenderer>(tt);
                            tile->setBuilding(r);
                            tile->setUnderBuilding(tt);
                            tt->addUnderBuilding(tile);
                            b->registerElement(tt);
                        } break;
                        case eSanctEleType::stairs: {
                            tile->setSeed(t.fId);
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
                        const auto tile = mBoard.tile(tx, ty);
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
            };
            break;
        default: break;
        }
    }

    actionOnSelectedTiles(apply);
}
