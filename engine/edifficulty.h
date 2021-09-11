#ifndef EDIFFICULTY_H
#define EDIFFICULTY_H

#include "buildings/ebuilding.h"

enum class eDifficulty {
    beginner, mortal, hero, titan, olympian
};

enum class eTaxRate {
    none,
    veryLow,
    low,
    normal,
    high,
    veryHigh,
    outrageous
};

namespace eTaxRateHelpers {
    double getRate(const eTaxRate tr);
}

namespace eDifficultyHelpers {
    std::string name(const eDifficulty diff);

    int buildingCost(const eDifficulty diff,
                     const eBuildingType type);

    int fireRisk(const eDifficulty diff,
                 const eBuildingType type);

    int damageRisk(const eDifficulty diff,
                   const eBuildingType type);

    int taxMultiplier(const eDifficulty diff,
                      const eBuildingType type,
                      const int level);
    int texSentiment(const eDifficulty diff,
                     const eTaxRate taxRate);
}

#endif // EDIFFICULTY_H
