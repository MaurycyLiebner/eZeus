#ifndef EDIFFICULTY_H
#define EDIFFICULTY_H

#include "buildings/ebuilding.h"

enum class eDifficulty {
    beginner, mortal, hero, titan, olympian
};

namespace eDifficultyHelpers {
    std::string name(const eDifficulty diff);
    double costMultiplier(const eDifficulty diff);
    int buildingCost(const eDifficulty diff,
                     const eBuildingType type);
}

#endif // EDIFFICULTY_H
