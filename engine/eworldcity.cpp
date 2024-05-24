#include "eworldcity.h"

#include "elanguage.h"
#include "egifthelpers.h"

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
        setRelationship(eWorldCityRelationship::rival);
        break;
    }
}

void eWorldCityBase::setAttitude(const int a) {
    mAt = std::clamp(a, 0, 100);
}

void eWorldCityBase::incAttitude(const int a) {
    setAttitude(mAt + a);
}

std::string eWorldCityBase::nationality() const {
    const int group  = 37;
    int string = -1;
    switch(mType) {
    case eWorldCityType::greekCity:
        string = 0;
        break;
    case eWorldCityType::trojanCity:
        string = 1;
        break;
    case eWorldCityType::persianCity:
        string = 2;
        break;
    case eWorldCityType::centaurCity:
        string = 3;
        break;
    case eWorldCityType::amazonCity:
        string = 4;
        break;

    case eWorldCityType::egyptianCity:
        string = 5;
        break;
    case eWorldCityType::mayanCity:
        string = 6;
        break;
    case eWorldCityType::phoenicianCity:
        string = 7;
        break;
    case eWorldCityType::oceanidCity:
        string = 8;
        break;
    case eWorldCityType::atlanteanCity:
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
    switch(mType) {
    case eWorldCityType::greekCity:
        string = 0;
        break;
    case eWorldCityType::trojanCity:
        string = 1;
        break;
    case eWorldCityType::persianCity:
        string = 2;
        break;
    case eWorldCityType::centaurCity:
        string = 3;
        break;
    case eWorldCityType::amazonCity:
        string = 4;
        break;

    case eWorldCityType::egyptianCity:
        string = 5;
        break;
    case eWorldCityType::mayanCity:
        string = 6;
        break;
    case eWorldCityType::phoenicianCity:
        string = 7;
        break;
    case eWorldCityType::oceanidCity:
        string = 8;
        break;
    case eWorldCityType::atlanteanCity:
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

stdsptr<eWorldCity> eWorldCity::sCreateAthens(const eWorldCityType type) {
    const auto name = eLanguage::zeusText(21, 4); // athens
    return std::make_shared<eWorldCity>(type, name, 0.464, 0.514);
}

stdsptr<eWorldCity> eWorldCity::sCreateSparta(const eWorldCityType type) {
    const auto name = eLanguage::zeusText(21, 57); // sparta
    return std::make_shared<eWorldCity>(type, name, 0.320, 0.615);
}

stdsptr<eWorldCity> eWorldCity::sCreateKnossos(const eWorldCityType type) {
    const auto name = eLanguage::zeusText(21, 29); // knossos
    return std::make_shared<eWorldCity>(type, name, 0.588, 0.825);
}

stdsptr<eWorldCity> eWorldCity::sCreateCorinth(const eWorldCityType type) {
    const auto name = eLanguage::zeusText(21, 10); // corinth
    return std::make_shared<eWorldCity>(type, name, 0.401, 0.522);
}

stdsptr<eWorldCity> eWorldCity::sCreateOlympia(const eWorldCityType type) {
    const auto name = eLanguage::zeusText(21, 45); // olympia
    return std::make_shared<eWorldCity>(type, name, 0.263, 0.542);
}


stdsptr<eWorldCity> eWorldCity::sCreateEgypt(const eWorldCityType type) {
    const auto name = eLanguage::zeusText(21, 16); // egypt
    return std::make_shared<eWorldCity>(type, name, 0.350, 0.820);
}

stdsptr<eWorldCity> eWorldCity::sCreateCyprus(const eWorldCityType type) {
    const auto name = eLanguage::zeusText(21, 13); // cyprus
    return std::make_shared<eWorldCity>(type, name, 0.790, 0.814);
}


stdsptr<eWorldCity> eWorldCity::sCreateTroy(const eWorldCityType type) {
    const auto name = eLanguage::zeusText(21, 68); // troy
    return std::make_shared<eWorldCity>(type, name, 0.693, 0.245);
}


stdsptr<eWorldCity> eWorldCity::sCreateMtPelion(const eWorldCityType type) {
    const auto name = eLanguage::zeusText(21, 46); // mt. pelion
    return std::make_shared<eWorldCity>(type, name, 0.356, 0.276);
}


stdsptr<eWorldCity> eWorldCity::sCreateSardis(const eWorldCityType type) {
    const auto name = eLanguage::zeusText(21, 54); // sardis
    return std::make_shared<eWorldCity>(type, name, 0.835, 0.443);
}

stdsptr<eWorldCity> eWorldCity::sCreateHattusas(const eWorldCityType type) {
    const auto name = eLanguage::zeusText(21, 24); // hattusas
    return std::make_shared<eWorldCity>(type, name, 0.835, 0.340);
}
