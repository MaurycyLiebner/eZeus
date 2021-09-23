#ifndef EBUILDINGMODE_H
#define EBUILDINGMODE_H

#include "buildings/ebuilding.h"

enum class eBuildingMode {
    none,
    erase,

    road,

    commonHousing,
    eliteHousing,

    wheatFarm,
    carrotFarm,
    onionFarm,

    vine,
    oliveTree,
    orangeTree,
    orangeTendersLodge,
    growersLodge,

    dairy,
    goat,
    cardingShed,
    sheep,

    fishery,
    urchinQuay,
    huntingLodge,

    mint,
    foundry,
    timberMill,
    masonryShop,

    winery,
    olivePress,
    sculptureStudio,
    artisansGuild,
    armory,

    wall,
    tower,
    gatehouse,

    podium,
    college,

    theater,
    dramaSchool,

    gymnasium,
    stadium,

    granary,
    warehouse,

    foodVendor,
    fleeceVendor,
    oilVendor,
    wineVendor,
    armsVendor,
    horseTrainer,

    maintenanceOffice,
    fountain,
    hospital,
    watchpost,

    taxOffice,
    palace,

    park,
    doricColumn,
    ionicColumn,
    corinthianColumn,
    avenue,

    commemorative1,
    commemorative2,
    commemorative3,
    commemorative4,
    commemorative5,
    commemorative6,
    commemorative7,
    commemorative8,
    commemorative9,

    bench,
    flowerGarden,
    gazebo,
    hedgeMaze,
    fishPond,

    waterPark,

    birdBath,
    shortObelisk,
    tallObelisk,
    shellGarden,
    sundial,
    dolphinSculpture,
    spring,
    topiary,
    baths,
    stoneCircle
};

namespace eBuildingModeHelpers {
    eBuildingType toBuildingType(const eBuildingMode mode);
}

#endif // EBUILDINGMODE_H
