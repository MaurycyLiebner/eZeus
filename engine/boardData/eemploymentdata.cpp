#include "eemploymentdata.h"

#include "epopulationdata.h"

#include <math.h>

eEmploymentData::eEmploymentData(const ePopulationData& popData) :
    mPopData(popData) {

}

void eEmploymentData::incTotalJobVacancies(const int v) {
    mTotalJobVacs += v;
}

int eEmploymentData::employable() const {
    return mPopData.population()/2;
}

int eEmploymentData::employed() const {
    return std::min(employable(), totalJobVacancies());
}

int eEmploymentData::pensions() const {
    return 2*employed();
}

int eEmploymentData::unemployed() const {
    return employable() - employed();
}

int eEmploymentData::freeJobVacancies() const {
    return totalJobVacancies() - employed();
}

int eEmploymentData::totalJobVacancies() const {
    return mTotalJobVacs;
}

double eEmploymentData::employedFraction() const {
    const int v = mTotalJobVacs;
    if(v == 0) return 1;
    return double(employed())/v;
}

