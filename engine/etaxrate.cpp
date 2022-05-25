#include "etaxrate.h"

#include "elanguage.h"

std::string eTaxRateHelpers::name(const eTaxRate tr) {
    switch(tr) {
    case eTaxRate::none:
        return eLanguage::text("none");
    case eTaxRate::low:
        return eLanguage::text("low");;
    case eTaxRate::veryLow:
        return eLanguage::text("very_low");
    case eTaxRate::normal:
        return eLanguage::text("normal");
    case eTaxRate::high:
        return eLanguage::text("high");
    case eTaxRate::veryHigh:
        return eLanguage::text("very_high");
    case eTaxRate::outrageous:
        return eLanguage::text("outrageous");
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
