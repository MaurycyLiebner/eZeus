#include "etaxrate.h"

std::string eTaxRateHelpers::name(const eTaxRate tr) {
    switch(tr) {
    case eTaxRate::none:
        return "none";
    case eTaxRate::low:
        return "low";
    case eTaxRate::veryLow:
        return "very low";
    case eTaxRate::normal:
        return "normal";
    case eTaxRate::high:
        return "high";
    case eTaxRate::veryHigh:
        return "very high";
    case eTaxRate::outrageous:
        return "outrageous";
    }
}

double eTaxRateHelpers::getRate(const eTaxRate tr) {
    switch(tr) {
    case eTaxRate::none:
        return 0.03;
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
