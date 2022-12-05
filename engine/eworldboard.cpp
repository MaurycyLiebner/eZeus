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

std::vector<stdsptr<eWorldCity>> eWorldBoard::getTribute() const {
    std::vector<stdsptr<eWorldCity>> r;
    for(const auto& c : mCities) {
        const auto rel = c->relationship();
        if(rel == eWorldCityRelationship::collony ||
           rel == eWorldCityRelationship::vassal) {
            r.push_back(c);
        }
    }
    return r;
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

stdsptr<eWorldCity> eWorldBoard::cityWithIOID(const int id) const {
    if(mHomeCity) {
        const int i = mHomeCity->ioID();
        if(id == i) {
            return mHomeCity;
        }
    }
    for(const auto& c : mCities) {
        const int i = c->ioID();
        if(id == i) return c;
    }
    return nullptr;
}

void eWorldBoard::setIOIDs() const {
    int id = 0;
    mHomeCity->setIOID(id++);
    for(const auto& c : mCities) {
        c->setIOID(id++);
    }
}

void eWorldBoard::write(eWriteStream& dst) const {
    mHomeCity->write(dst);
    dst << mCities.size();
    for(const auto& c : mCities) {
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
