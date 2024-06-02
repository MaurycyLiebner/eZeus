#include "eworldcity.h"

#include "elanguage.h"
#include "egifthelpers.h"
#include "evectorhelpers.h"

eWorldCityBase::eWorldCityBase(const eCityType type,
                               const std::string& name,
                               const double x, const double y) :
    mType(type), mName(name), mX(x), mY(y) {}

std::string eWorldCityBase::sTypeName(const eCityType type) {
    const int group = 39;
    int string = -1;
    switch(type) {
    case eCityType::parentCity:
        string = 0;
        break;
    case eCityType::colony:
        string = 1;
        break;
    case eCityType::foreignCity:
        string = 2;
        break;
    case eCityType::distantCity:
        string = 4;
        break;
    case eCityType::enchantedPlace:
        string = 5;
        break;
    case eCityType::destroyedCity:
        string = 6;
        break;
    }
    return eLanguage::zeusText(group, string);
}

bool eWorldCityBase::isDistant() const {
    return mType == eCityType::distantCity;
}

bool eWorldCityBase::isVassal() const {
    return mType == eCityType::foreignCity &&
           mRel == eForeignCityRelationship::vassal;
}

bool eWorldCityBase::isColony() const {
    return mType == eCityType::colony;
}

bool eWorldCityBase::isParentCity() const {
    return mType == eCityType::parentCity;
}

bool eWorldCityBase::isRival() const {
    return mType == eCityType::foreignCity &&
           mRel == eForeignCityRelationship::rival;
}

bool eWorldCityBase::isAlly() const {
    return mType == eCityType::foreignCity &&
            mRel == eForeignCityRelationship::ally;
}

std::string eWorldCityBase::sDirectionName(const eDistantDirection d) {
    switch(d) {
    case eDistantDirection::none: return "none";
    case eDistantDirection::N: return "N";
    case eDistantDirection::NE: return "NE";
    case eDistantDirection::E: return "E";
    case eDistantDirection::SE: return "SE";
    case eDistantDirection::S: return "S";
    case eDistantDirection::SW: return "SW";
    case eDistantDirection::W: return "W";
    case eDistantDirection::NW: return "NW";
    }
    return "none";
}

void eWorldCityBase::move(const double x, const double y) {
    mX = x;
    mY = y;
}

std::string eWorldCityBase::sRelationshipName(const eForeignCityRelationship r) {
    int group = 253;
    int string = -1;
    switch(r) {
    case eForeignCityRelationship::vassal:
        string = 2;
        break;
    case eForeignCityRelationship::ally:
        string = 0;
        break;
    case eForeignCityRelationship::rival:
        string = 1;
        break;
    }
    return eLanguage::zeusText(group, string);
}

void eWorldCityBase::setAttitude(const int a) {
    mAt = std::clamp(a, 0, 100);
}

void eWorldCityBase::incAttitude(const int a) {
    setAttitude(mAt + a);
}

std::vector<std::string> eWorldCityBase::sNames() {
    std::vector<std::string> cityNames;
    for(int i = 0; i < 82; i++) {
        cityNames.push_back(eLanguage::zeusText(21, i));
    }
    return cityNames;
}

void eWorldCityBase::setName(const std::string& name) {
    mName = name;
    const auto names = sNames();
    mNameString = eVectorHelpers::index(names, name);
}

std::string eWorldCityBase::sNationalityName(const eNationality type) {
    const int group = 37;
    int string = -1;
    switch(type) {
    case eNationality::greek:
        string = 0;
        break;
    case eNationality::trojan:
        string = 1;
        break;
    case eNationality::persian:
        string = 2;
        break;
    case eNationality::centaur:
        string = 3;
        break;
    case eNationality::amazon:
        string = 4;
        break;

    case eNationality::egyptian:
        string = 5;
        break;
    case eNationality::mayan:
        string = 6;
        break;
    case eNationality::phoenician:
        string = 7;
        break;
    case eNationality::oceanid:
        string = 8;
        break;
    case eNationality::atlantean:
        string = 9;
        break;
    default:
        break;
    }
    return eLanguage::zeusText(group, string);
}

std::string eWorldCityBase::anArmy() const {
    const int group  = 37;
    int string = -1;
    switch(mNationality) {
    case eNationality::greek:
        string = 0;
        break;
    case eNationality::trojan:
        string = 1;
        break;
    case eNationality::persian:
        string = 2;
        break;
    case eNationality::centaur:
        string = 3;
        break;
    case eNationality::amazon:
        string = 4;
        break;

    case eNationality::egyptian:
        string = 5;
        break;
    case eNationality::mayan:
        string = 6;
        break;
    case eNationality::phoenician:
        string = 7;
        break;
    case eNationality::oceanid:
        string = 8;
        break;
    case eNationality::atlantean:
        string = 9;
        break;
    default:
        break;
    }
    return eLanguage::zeusText(group, 22 + string);
}

void eWorldCityBase::write(eWriteStream& dst) const {
    dst << mIOID;
    dst << mType;
    dst << mName;
    dst << mNameString;
    dst << mLeader;
    dst << mX;
    dst << mY;
    dst << mRebellion;
    dst << mRel;
    dst << mAt;
}

void eWorldCityBase::read(eReadStream& src) {
    src >> mIOID;
    src >> mType;
    src >> mName;
    src >> mNameString;
    if(mNameString > -1 && mNameString < 82) {
        mName = eLanguage::zeusText(21, mNameString);
    }
    src >> mLeader;
    src >> mX;
    src >> mY;
    src >> mRebellion;
    src >> mRel;
    src >> mAt;
}

void eWorldCity::nextYear() {
    for(auto& b : mBuys) {
        b.fUsed = 0;
    }
    for(auto& s : mSells) {
        s.fUsed = 0;
    }
    mReceived.clear();
}

int eWorldCity::strength() const {
    return (10 + (rand() % 3))*mArmy;
}

bool eWorldCity::buys(const eResourceType type) const {
    for(const auto& rt : mBuys) {
        if(rt.fType == type) return true;
    }
    return false;
}

void eWorldCity::addBuys(const eResourceTrade& b) {
    mBuys.push_back(b);
}

bool eWorldCity::sells(const eResourceType type) const {
    for(const auto& rt : mSells) {
        if(rt.fType == type) return true;
    }
    return false;
}

void eWorldCity::addSells(const eResourceTrade& s) {
    mSells.push_back(s);
}

void swrite(eWriteStream& dst,
            const std::vector<eResourceTrade>& v) {
    dst << v.size();
    for(const auto& vv : v) {
        vv.write(dst);
    }
}

void eWorldCity::write(eWriteStream& dst) const {
    eWorldCityBase::write(dst);
    dst << mAbroad;
    dst << mArmy;
    dst << mWealth;
    dst << mWaterTrade;
    swrite(dst, mBuys);
    swrite(dst, mSells);
}

void sread(eReadStream& src,
            std::vector<eResourceTrade>& v) {
    int n;
    src >> n;
    for(int i = 0; i < n; i++) {
        auto& vv = v.emplace_back();
        vv.read(src);
    }
}

void eWorldCity::read(eReadStream& src) {
    eWorldCityBase::read(src);
    src >> mAbroad;
    src >> mArmy;
    src >> mWealth;
    src >> mWaterTrade;
    sread(src, mBuys);
    sread(src, mSells);
}

void eWorldCity::gifted(const eResourceType type, const int count) {
    const auto comp = [type](const std::pair<eResourceType, int>& r) {
        return r.first == type;
    };
    const auto it = std::find_if(mReceived.begin(), mReceived.end(), comp);
    if(it == mReceived.end()) {
        mReceived.push_back({type, count});
    } else {
        it->second += count;
    }
}

bool eWorldCity::acceptsGift(const eResourceType type,
                             const int count) const {
    if(type == eResourceType::drachmas) return true;
    (void)count;
    const auto comp = [type](const std::pair<eResourceType, int>& r) {
        return r.first == type;
    };
    const auto it = std::find_if(mReceived.begin(), mReceived.end(), comp);
    if(it == mReceived.end()) {
        return true;
    } else {
        const int max = 3 * eGiftHelpers::giftCount(type);
        return it->second < max;
    }
}

stdsptr<eWorldCity> eWorldCity::sCreateAthens() {
    const auto name = eLanguage::zeusText(21, 4); // athens
    const auto c = std::make_shared<eWorldCity>(eCityType::foreignCity, name, 0.464, 0.514);
    c->setNationality(eNationality::greek);
    return c;
}

stdsptr<eWorldCity> eWorldCity::sCreateSparta() {
    const auto name = eLanguage::zeusText(21, 57); // sparta
    const auto c = std::make_shared<eWorldCity>(
                       eCityType::foreignCity, name, 0.320, 0.615);
    c->setNationality(eNationality::greek);
    return c;
}

stdsptr<eWorldCity> eWorldCity::sCreateKnossos() {
    const auto name = eLanguage::zeusText(21, 29); // knossos
    const auto c = std::make_shared<eWorldCity>(
                       eCityType::foreignCity, name, 0.588, 0.825);
    c->setNationality(eNationality::greek);
    return c;
}

stdsptr<eWorldCity> eWorldCity::sCreateCorinth() {
    const auto name = eLanguage::zeusText(21, 10); // corinth
    const auto c = std::make_shared<eWorldCity>(
                       eCityType::foreignCity, name, 0.401, 0.522);
    c->setNationality(eNationality::greek);
    return c;
}

stdsptr<eWorldCity> eWorldCity::sCreateOlympia() {
    const auto name = eLanguage::zeusText(21, 45); // olympia
    const auto c = std::make_shared<eWorldCity>(
                       eCityType::foreignCity, name, 0.263, 0.542);
    c->setNationality(eNationality::greek);
    return c;
}


stdsptr<eWorldCity> eWorldCity::sCreateEgypt() {
    const auto name = eLanguage::zeusText(21, 16); // egypt
    const auto c = std::make_shared<eWorldCity>(
                       eCityType::foreignCity, name, 0.350, 0.820);
    c->setNationality(eNationality::egyptian);
    return c;
}

stdsptr<eWorldCity> eWorldCity::sCreateCyprus() {
    const auto name = eLanguage::zeusText(21, 13); // cyprus
    const auto c = std::make_shared<eWorldCity>(
                       eCityType::foreignCity, name, 0.790, 0.814);
    c->setNationality(eNationality::greek);
    return c;
}


stdsptr<eWorldCity> eWorldCity::sCreateTroy() {
    const auto name = eLanguage::zeusText(21, 68); // troy
    const auto c = std::make_shared<eWorldCity>(
                       eCityType::foreignCity, name, 0.693, 0.245);
    c->setNationality(eNationality::trojan);
    return c;
}


stdsptr<eWorldCity> eWorldCity::sCreateMtPelion() {
    const auto name = eLanguage::zeusText(21, 46); // mt. pelion
    const auto c = std::make_shared<eWorldCity>(
                       eCityType::foreignCity, name, 0.356, 0.276);
    c->setNationality(eNationality::centaur);
    return c;
}


stdsptr<eWorldCity> eWorldCity::sCreateSardis() {
    const auto name = eLanguage::zeusText(21, 54); // sardis
    const auto c = std::make_shared<eWorldCity>(
                       eCityType::foreignCity, name, 0.835, 0.443);
    c->setNationality(eNationality::persian);
    return c;
}

stdsptr<eWorldCity> eWorldCity::sCreateHattusas() {
    const auto name = eLanguage::zeusText(21, 24); // hattusas
    const auto c = std::make_shared<eWorldCity>(
                       eCityType::foreignCity, name, 0.835, 0.340);
    c->setNationality(eNationality::persian);
    return c;
}
