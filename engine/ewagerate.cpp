#include "ewagerate.h"

std::string eWageRateHelpers::name(const eWageRate wr) {
    switch(wr) {
    case eWageRate::none: return "none";
    case eWageRate::veryLow: return "very low";
    case eWageRate::low: return "low";
    case eWageRate::normal: return "normal";
    case eWageRate::high: return "high";
    case eWageRate::veryHigh: return "very high";
    }
}

double eWageRateHelpers::wageMultiplier(const eWageRate wr) {
    switch(wr) {
    case eWageRate::none: return 0;
    case eWageRate::veryLow: return 2;
    case eWageRate::low: return 2.5;
    case eWageRate::normal: return 3;
    case eWageRate::high: return 3.4;
    case eWageRate::veryHigh: return 4;
    }
}
