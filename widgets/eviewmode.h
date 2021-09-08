#ifndef EVIEWMODE_H
#define EVIEWMODE_H

enum class eViewMode {
    defaultView = 1 << 0,
    patrolBuilding = 1 << 1,
    appeal = 1 << 2,

    displayBuildings = eViewMode::defaultView
};

inline eViewMode operator|(const eViewMode a, const eViewMode b) {
    return static_cast<eViewMode>(static_cast<int>(a) | static_cast<int>(b));
}

inline eViewMode operator&(const eViewMode a, const eViewMode b) {
    return static_cast<eViewMode>(static_cast<int>(a) & static_cast<int>(b));
}

#endif // EVIEWMODE_H
