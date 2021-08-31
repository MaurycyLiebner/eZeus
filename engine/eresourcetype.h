#ifndef ERESOURCETYPE_H
#define ERESOURCETYPE_H

#include <vector>
#include <string>

enum class eResourceType {
    none = 0,

    urchin = 1 << 0,
    fish = 1 << 1,
    meat = 1 << 2,
    cheese = 1 << 3,
    carrots = 1 << 4,
    onions = 1 << 5,
    wheat = 1 << 6,

    food = (1 << 7) - 1,

    grapes = 1 << 7,
    olives = 1 << 8,
    wine = 1 << 9,
    oliveOil = 1 << 10,
    fleece = 1 << 11,

    wood = 1 << 12,
    bronze = 1 << 13,
    marble = 1 << 14,
    silver = 1 << 15,

    armor = 1 << 16,
    sculpture = 1 << 17,

    all = (1 << 18) - 1,
    warehouse = (all & ~food & ~silver) | wheat,

    horse = 1 << 19,
};

inline eResourceType operator|(const eResourceType a, const eResourceType b) {
    return static_cast<eResourceType>(static_cast<int>(a) | static_cast<int>(b));
}

inline eResourceType operator&(const eResourceType a, const eResourceType b) {
    return static_cast<eResourceType>(static_cast<int>(a) & static_cast<int>(b));
}

namespace eResourceTypeHelpers {
    std::vector<eResourceType> extractResourceTypes(
            const eResourceType from);
    std::string typeName(const eResourceType type);
}

#endif // ERESOURCETYPE_H
