#ifndef EWORLDBOARD_H
#define EWORLDBOARD_H

#include <vector>

#include "eworldcity.h"
#include "pointers/estdselfref.h"

class eWorldBoard {
public:
    eWorldBoard();

    void setHomeCity(const stdsptr<eWorldCityBase>& hc);
    void addCity(const stdsptr<eWorldCity>& c);

    const stdsptr<eWorldCityBase>& homeCity() const
    { return mHomeCity; }
    const std::vector<stdsptr<eWorldCity>>& cities() const
    { return mCities; }
private:
    stdsptr<eWorldCityBase> mHomeCity;
    std::vector<stdsptr<eWorldCity>> mCities;
};

#endif // EWORLDBOARD_H
