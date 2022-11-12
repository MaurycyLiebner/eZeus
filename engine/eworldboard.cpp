#include "eworldboard.h"

eWorldBoard::eWorldBoard() {}

void eWorldBoard::incTime(const int by) {
    (void)by;
}

void eWorldBoard::nextYear() {
    for(const auto& c : mCities) {
        c->nextYear();
    }
}

void eWorldBoard::setHomeCity(const stdsptr<eWorldCity>& hc) {
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

void eWorldBoard::write(eWriteStream& dst) const {
    mHomeCity->write(dst);
    dst << mCities.size();
    for(const auto& c: mCities) {
        c->write(dst);
    }
}

void eWorldBoard::read(eReadStream& src) {
    mHomeCity = std::make_shared<eWorldCity>();
    mHomeCity->read(src);
    int nc;
    src >> nc;
    for(int i = 0; i < nc; i++) {
        const auto c = std::make_shared<eWorldCity>();
        c->read(src);
        addCity(c);
    }
}
