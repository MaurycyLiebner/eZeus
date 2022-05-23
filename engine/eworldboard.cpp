#include "eworldboard.h"

eWorldBoard::eWorldBoard()
{

}

void eWorldBoard::setHomeCity(const stdsptr<eWorldCityBase>& hc) {
    mHomeCity = hc;
}

void eWorldBoard::addCity(const stdsptr<eWorldCity>& c) {
    mCities.push_back(c);
}
