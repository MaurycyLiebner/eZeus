#include "etaxrate.h"

#include "elanguage.h"

std::string eTaxRateHelpers::name(const eTaxRate tr) {
    const int group = 286;
    int string = -1;
    switch(tr) {
    case eTaxRate::none:
        string = 0;
        break;
    case eTaxRate::low:
        string = 1;
        break;
    case eTaxRate::veryLow:
        string = 2;
        break;
    case eTaxRate::normal:
        string = 3;
        break;
    case eTaxRate::high:
        string = 4;
        break;
    case eTaxRate::veryHigh:
        string = 5;
        break;
    case eTaxRate::outrageous:
        string = 6;
        break;
    }
    return eLanguage::zeusText(group, string);
}

double eTaxRateHelpers::getRate(const eTaxRate tr) {
    switch(tr) {
    case eTaxRate::none:
        return 0.00;
    case eTaxRate::low:
        return 0.03;
    case eTaxRate::veryLow:
        return 0.07;
    case eTaxRate::normal:
        return 0.09;
    case eTaxRate::high:
        return 0.11;
    case eTaxRate::veryHigh:
        return 0.15;
    case eTaxRate::outrageous:
        return 0.20;
    }
}
