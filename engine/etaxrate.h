#ifndef ETAXRATE_H
#define ETAXRATE_H

#include <string>

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
    std::string name(const eTaxRate tr);
    double getRate(const eTaxRate tr);
}

#endif // ETAXRATE_H
