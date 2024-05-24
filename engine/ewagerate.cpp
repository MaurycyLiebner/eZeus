#include "ewagerate.h"

#include "elanguage.h"

std::string eWageRateHelpers::name(const eWageRate wr) {
    const int group = 285;
    int string = -1;
    switch(wr) {
    case eWageRate::none:
        string = 0;
        break;
    case eWageRate::veryLow:
        string = 1;
        break;
    case eWageRate::low:
        string = 2;
        break;
    case eWageRate::normal:
        string = 3;
        break;
    case eWageRate::high:
        string = 4;
        break;
    case eWageRate::veryHigh:
        string = 5;
        break;
    }
    return eLanguage::zeusText(group, string);
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
