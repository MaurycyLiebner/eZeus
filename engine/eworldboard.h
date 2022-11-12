#ifndef EWORLDBOARD_H
#define EWORLDBOARD_H

#include <vector>

#include "eworldcity.h"
#include "pointers/estdselfref.h"

class eWorldBoard {
public:
    eWorldBoard();

    void incTime(const int by);
    void nextYear();

    void setHomeCity(const stdsptr<eWorldCity>& hc);
    void addCity(const stdsptr<eWorldCity>& c);

    const stdsptr<eWorldCity>& homeCity() const
    { return mHomeCity; }
    const std::vector<stdsptr<eWorldCity>>& cities() const
    { return mCities; }

    int cityId(const eWorldCity& city) const;

    void write(eWriteStream& dst) const;
    void read(eReadStream& src);
private:
    stdsptr<eWorldCity> mHomeCity;
    std::vector<stdsptr<eWorldCity>> mCities;
};

#endif // EWORLDBOARD_H
