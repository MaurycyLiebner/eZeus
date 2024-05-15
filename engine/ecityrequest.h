#ifndef ECITYREQUEST_H
#define ECITYREQUEST_H

#include "eworldcity.h"
#include "eresourcetype.h"

struct eCityRequest {
    void write(eWriteStream& dst) const {
        dst.writeCity(fCity.get());
        dst << fType;
        dst << fCount;
    }

    void read(eGameBoard& board, eReadStream& src) {
        src.readCity(&board, [this](const stdsptr<eWorldCity>& city) {
            fCity = city;
        });
        src >> fType;
        src >> fCount;
    }

    bool operator==(const eCityRequest& o) const {
        return fCity == o.fCity &&
               fType == o.fType &&
               fCount == o.fCount;
    }

    stdsptr<eWorldCity> fCity;
    eResourceType fType;
    int fCount;
};

#endif // ECITYREQUEST_H
