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

    populationMonument,
    commemorative2,
    commemorative3,
    athleteMonument,
    conquestMonument,
    happinessMonument,
    commemorative7,
    commemorative8,
    scholarMonument,

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
    stoneCircle,

    templeHephaestus
};

namespace eBuildingModeHelpers {
    eBuildingType toBuildingType(const eBuildingMode mode);
}

#endif // EBUILDINGMODE_H
