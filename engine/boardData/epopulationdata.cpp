#include "epopulationdata.h"

ePopulationData::ePopulationData() {

}

void ePopulationData::incPopulation(const int p) {
    mPop += p;
}

void ePopulationData::incVacancies(const int v) {
    mVacs += v;
}

void ePopulationData::incSettlers(const int s) {
    mSettlers += s;
}
