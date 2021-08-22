#include "eemploymentdata.h"

#include "epopulationdata.h"

eEmploymentData::eEmploymentData(const ePopulationData& popData) :
    mPopData(popData) {

}

void eEmploymentData::incEmployed(const int p) {
    mEmployed += p;
}

int eEmploymentData::pensions() const {
    return 2*employed();
}

int eEmploymentData::unemployed() const {
    return mPopData.population()/2 - employed();
}

int eEmploymentData::jobVacancies() const {
    return -unemployed();
}

