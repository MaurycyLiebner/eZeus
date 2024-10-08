#ifndef EVIEWMODE_H
#define EVIEWMODE_H

#include "buildings/ebuilding.h"
#include "engine/etile.h"
#include "characters/echaracter.h"

enum class eViewMode {
    defaultView,

    patrolBuilding,

    supplies,

    husbandry,

    industry,

    distribution,

    water,
    hygiene,
    hazards,
    unrest,

    actors,
    athletes,
    philosophers,
    competitors,
    allCulture,

    astronomers,
    scholars,
    inventors,
    curators,
    allScience,

    taxes,

    immortals,

    security,

    appeal,

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
