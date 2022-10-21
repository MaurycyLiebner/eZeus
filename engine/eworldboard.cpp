#include "eworldboard.h"

eWorldBoard::eWorldBoard()
{

}

void eWorldBoard::incTime(const int by) {
    (void)by;
}

void eWorldBoard::nextYear() {
    for(const auto& c : mCities) {
        c->nextYear();
    }
}

void eWorldBoard::setHomeCity(const stdsptr<eWorldCityBase>& hc) {
    mHomeCity = hc;
}

void eWorldBoard::addCity(const stdsptr<eWorldCity>& c) {
    mCities.push_back(c);
}

int eWorldBoard::cityId(const eWorldCity& city) const {
    int id = -1;
    for(const auto& c : mCities) {
        id++;
        if(c.get() == &city) return id;
    }
    return id;
}
