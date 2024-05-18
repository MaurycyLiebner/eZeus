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

    std::vector<stdsptr<eWorldCity>> getTribute() const;

    void setHomeCity(const stdsptr<eWorldCity>& hc);
    void addCity(const stdsptr<eWorldCity>& c);

    const stdsptr<eWorldCity>& homeCity() const
    { return mHomeCity; }
    const std::vector<stdsptr<eWorldCity>>& cities() const
    { return mCities; }

    int cityId(const eWorldCity& city) const;

    stdsptr<eWorldCity> cityWithIOID(const int id) const;
    void setIOIDs() const;

    void write(eWriteStream& dst) const;
    void read(eReadStream& src);

    void attackedAlly();
private:
    stdsptr<eWorldCity> mHomeCity;
    std::vector<stdsptr<eWorldCity>> mCities;
};

#endif // EWORLDBOARD_H
