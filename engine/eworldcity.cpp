#include "eworldcity.h"

eWorldCityBase::eWorldCityBase(const eWorldCityType type,
                               const std::string& name,
                               const double x, const double y) :
    mType(type), mName(name), mX(x), mY(y) {
    switch(type) {
    case eWorldCityType::mainCity:
        setRelationship(eWorldCityRelationship::mainCity);
        break;
    case eWorldCityType::collony:
        setRelationship(eWorldCityRelationship::collony);
        break;
    default:
        setRelationship(eWorldCityRelationship::ally);
        break;
    }
}

void eWorldCity::addBuys(const eResourceTrade& b) {
    mBuys.push_back(b);
}

void eWorldCity::addSells(const eResourceTrade& s) {
    mSells.push_back(s);
}
