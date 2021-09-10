#ifndef EVIEWMODE_H
#define EVIEWMODE_H

#include "buildings/ebuilding.h"
#include "engine/etile.h"
#include "characters/echaracter.h"

enum class eViewMode {
    defaultView = 1 << 0,

    patrolBuilding = 1 << 1,

    supplies = 1 << 2,

    water = 1 << 3,
    hygiene = 1 << 4,
    hazards = 1 << 5,
    unrest = 1 << 6,

    actors = 1 << 7,
    athletes = 1 << 8,
    philosophers = 1 << 9,
    allCulture = 1 << 10,

    appeal = 1 << 11
};

inline eViewMode operator|(const eViewMode a, const eViewMode b) {
    return static_cast<eViewMode>(static_cast<int>(a) | static_cast<int>(b));
}

inline eViewMode operator&(const eViewMode a, const eViewMode b) {
    return static_cast<eViewMode>(static_cast<int>(a) & static_cast<int>(b));
}

namespace eViewModeHelpers {
    bool buildingVisible(const eViewMode viewMode,
                         const eBuildingType b);
    bool characterVisible(const eViewMode viewMode,
                          const eCharacterType c);
}

#endif // EVIEWMODE_H
