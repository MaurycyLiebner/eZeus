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
        const auto type = c->type();
        const auto rel = c->relationship();
        const bool e = type == eCityType::colony ||
                       (type == eCityType::foreignCity &&
                        rel == eForeignCityRelationship::vassal);
        if(e) r.push_back(c);
    }
    return r;
}

void eWorldBoard::addCity(const stdsptr<eWorldCity>& c) {
    mCities.push_back(c);
}

stdsptr<eWorldCity> eWorldBoard::currentCity() const {
    for(const auto& c : mCities) {
        const bool cc = c->isCurrentCity();
        if(cc) return c;
    }
    return nullptr;
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
    for(const auto& c : mCities) {
        const int i = c->ioID();
        if(id == i) return c;
    }
    return nullptr;
}

void eWorldBoard::setIOIDs() const {
    int id = 0;
    for(const auto& c : mCities) {
        c->setIOID(id++);
    }
}

void eWorldBoard::write(eWriteStream& dst) const {
    setIOIDs();

    dst << mPoseidonMode;
    dst << mMap;
    dst << mCities.size();
    for(const auto& c : mCities) {
        c->write(dst);
    }
}

void eWorldBoard::read(eReadStream& src) {
    src >> mPoseidonMode;
    src >> mMap;
    int nc;
    src >> nc;
    for(int i = 0; i < nc; i++) {
        const auto c = std::make_shared<eWorldCity>();
        c->read(src);
        addCity(c);
    }
}

void eWorldBoard::attackedAlly() {
    for(const auto& c : mCities) {
        const auto type = c->type();
        const auto rel = c->relationship();
        if(type == eCityType::foreignCity &&
           rel == eForeignCityRelationship::ally) {
            c->incAttitude(-25);
        }
    }
}

stdsptr<eWorldCity> eWorldBoard::colonyWithId(const int id) const {
    int i = 0;
    for(const auto& c : mCities) {
        const auto type = c->type();
        if(type != eCityType::colony) continue;
        if(i == id) return c;
        i++;
    }
    return nullptr;
}

void eWorldBoard::activateColony(const int id) {
    const auto c = colonyWithId(id);
    if(c) c->setState(eCityState::active);
}

void eWorldBoard::setColonyAsCurrentCity(const int id) {
    for(const auto& c : mCities) {
        c->setIsCurrentCity(false);
    }
    const auto c = colonyWithId(id);
    if(c) c->setIsCurrentCity(true);
}

void eWorldBoard::setParentAsCurrentCity() {
    for(const auto& c : mCities) {
        const auto type = c->type();
        if(type == eCityType::parentCity) {
            c->setIsCurrentCity(true);
        } else {
            c->setIsCurrentCity(false);
        }
    }
}
