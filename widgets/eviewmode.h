#ifndef EVIEWMODE_H
#define EVIEWMODE_H

#include "buildings/ebuilding.h"
#include "engine/etile.h"
#include "characters/echaracter.h"

enum class eViewMode {
    defaultView,

    patrolBuilding,

    supplies,

    water,
    hygiene,
    hazards,
    unrest,

    actors,
    athletes,
    philosophers,
    allCulture,

    appeal,

    taxes,

    industry,

    husbandry,

    immortals,

    distribution,

    problems,
    roads
};

inline eViewMode operator|(const eViewMode a, const eViewMode b) {
    return static_cast<eViewMode>(static_cast<int>(a) | static_cast<int>(b));
}

inline eViewMode operator&(const eViewMode a, const eViewMode b) {
    return static_cast<eViewMode>(static_cast<int>(a) & static_cast<int>(b));
}

namespace eViewModeHelpers {
    bool buildingVisible(const eViewMode viewMode,
                         const eBuilding* const b);
    bool characterVisible(const eViewMode viewMode,
                          const eCharacterType c);
}

#endif // EVIEWMODE_H
