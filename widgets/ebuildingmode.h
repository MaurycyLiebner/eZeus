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

    podium,
    college,

    theater,
    dramaSchool,

    gymnasium,
    stadium,

    granary,
    warehouse,

    maintenanceOffice,
    fountain,
    hospital,
    watchpost,

    taxOffice,
    palace
};

namespace eBuildingModeHelpers {
    eBuildingType toBuildingType(const eBuildingMode mode);
}

#endif // EBUILDINGMODE_H
