#include "etaxrate.h"

#include "elanguage.h"

std::string eTaxRateHelpers::name(const eTaxRate tr) {
    switch(tr) {
    case eTaxRate::none:
        return eLanguage::text("none_taxes");
    case eTaxRate::low:
        return eLanguage::text("low_taxes");;
    case eTaxRate::veryLow:
        return eLanguage::text("very_low_taxes");
    case eTaxRate::normal:
        return eLanguage::text("normal_taxes");
    case eTaxRate::high:
        return eLanguage::text("high_taxes");
    case eTaxRate::veryHigh:
        return eLanguage::text("very_high_taxes");
    case eTaxRate::outrageous:
        return eLanguage::text("outrageous_taxes");
    }
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
