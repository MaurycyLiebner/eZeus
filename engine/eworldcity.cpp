#include "eworldcity.h"

#include "elanguage.h"

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
}

void eWorldCity::addBuys(const eResourceTrade& b) {
    mBuys.push_back(b);
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
    src >> mArmy;
    src >> mWealth;
    src >> mWaterTrade;
    sread(src, mBuys);
    sread(src, mSells);
}

stdsptr<eWorldCity> eWorldCity::sCreateAthens(const eWorldCityType type) {
    const auto name = eLanguage::text("athens");
    return std::make_shared<eWorldCity>(type, name, 0.464, 0.514);
}

stdsptr<eWorldCity> eWorldCity::sCreateSparta(const eWorldCityType type) {
    const auto name = eLanguage::text("sparta");
    return std::make_shared<eWorldCity>(type, name, 0.320, 0.615);
}

stdsptr<eWorldCity> eWorldCity::sCreateKnossos(const eWorldCityType type) {
    const auto name = eLanguage::text("knossos");
    return std::make_shared<eWorldCity>(type, name, 0.588, 0.825);
}

stdsptr<eWorldCity> eWorldCity::sCreateCorinth(const eWorldCityType type) {
    const auto name = eLanguage::text("corinth");
    return std::make_shared<eWorldCity>(type, name, 0.401, 0.522);
}

stdsptr<eWorldCity> eWorldCity::sCreateOlympia(const eWorldCityType type) {
    const auto name = eLanguage::text("olympia");
    return std::make_shared<eWorldCity>(type, name, 0.263, 0.542);
}


stdsptr<eWorldCity> eWorldCity::sCreateEgypt(const eWorldCityType type) {
    const auto name = eLanguage::text("egypt");
    return std::make_shared<eWorldCity>(type, name, 0.350, 0.820);
}

stdsptr<eWorldCity> eWorldCity::sCreateCyprus(const eWorldCityType type) {
    const auto name = eLanguage::text("cyprus");
    return std::make_shared<eWorldCity>(type, name, 0.790, 0.814);
}


stdsptr<eWorldCity> eWorldCity::sCreateTroy(const eWorldCityType type) {
    const auto name = eLanguage::text("troy");
    return std::make_shared<eWorldCity>(type, name, 0.693, 0.245);
}


stdsptr<eWorldCity> eWorldCity::sCreateMtPelion(const eWorldCityType type) {
    const auto name = eLanguage::text("mt_pelion");
    return std::make_shared<eWorldCity>(type, name, 0.356, 0.276);
}


stdsptr<eWorldCity> eWorldCity::sCreateSardis(const eWorldCityType type) {
    const auto name = eLanguage::text("sardis");
    return std::make_shared<eWorldCity>(type, name, 0.835, 0.443);
}

stdsptr<eWorldCity> eWorldCity::sCreateHattusas(const eWorldCityType type) {
    const auto name = eLanguage::text("hattusas");
    return std::make_shared<eWorldCity>(type, name, 0.835, 0.340);
}
