#ifndef EDIFFICULTY_H
#define EDIFFICULTY_H

#include "buildings/ebuilding.h"

#include "etaxrate.h"
#include "ewagerate.h"

enum class eDifficulty {
    beginner, mortal, hero, titan, olympian
};

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
    int taxSentiment(const eDifficulty diff,
                     const eTaxRate taxRate);

    double workerFrac(const eDifficulty diff,
                      const eWageRate wageRate);
}

#endif // EDIFFICULTY_H
