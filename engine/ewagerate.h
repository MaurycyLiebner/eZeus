#ifndef EWAGERATE_H
#define EWAGERATE_H

#include <string>

enum class eWageRate {
    none,
    veryLow,
    low,
    normal,
    high,
    veryHigh
};

namespace eWageRateHelpers {
    std::string name(const eWageRate wr);
    double wageMultiplier(const eWageRate wr);
};

#endif // EWAGERATE_H
