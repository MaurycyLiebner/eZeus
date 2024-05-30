#ifndef EWORLDCITY_H
#define EWORLDCITY_H

#include <string>

#include "eresourcetype.h"
#include "pointers/estdselfref.h"
#include "fileIO/estreams.h"

enum class eWorldCityType {
    mainCity,
    collony,
    disabledColony,

    greekCity,
    trojanCity,
    persianCity,
    centaurCity,
    amazonCity,

    egyptianCity,
    mayanCity,
    phoenicianCity,
    oceanidCity,
    atlanteanCity,

    place,
    ruins,

    distantCity,
    distantCityN,
    distantCityNE,
    distantCityE,
    distantCitySE,
    distantCityS,
    distantCitySW,
    distantCityW,
    distantCityNW
};

enum class eWorldCityRelationship {
    mainCity,
    collony,
    vassal,
    ally,
    rival
};

enum class eWorldCityAttitude {
    // ally, colony, vassal
    philanthropic, // - recently pleased
    resentful, // - recently displeased

    // ally
    helpful,
    congenial,
    sympathetic,
    apatheticA,
    annoyed,

    // colony, vassal
    devoted,
    dedicated,
    loyal,
    bitter,
    angry,

    // rival

    docile, // - recently pleased
    hostile, // - recently displeased

    admiring,
    respectful,
    apatheticR,
    displeased,
    furious,

    insubordinate
};

class eWorldCityBase {
public:
    eWorldCityBase() {}
    eWorldCityBase(const eWorldCityType type,
                   const std::string& name,
                   const double x, const double y);

    bool rebellion() const { return mRebellion; }
    void setRebellion(const bool r) { mRebellion = r; }

    eWorldCityType type() const { return mType; }

    double x() const { return mX; }
    double y() const { return mY; }

    bool isCurrentCity() const { return mIsCurrentCity; }
    void setIsCurrentCity(const bool c) { mIsCurrentCity = c; }

    eWorldCityRelationship relationship() const { return mRel; }
    void setRelationship(const eWorldCityRelationship r) { mRel = r; }

    int attitude() const { return mAt; }
    void setAttitude(const int a);
    void incAttitude(const int a);

    const std::string& name() const { return mName; }
    std::string nationality() const;
    const std::string& leader() const { return mLeader; }
    std::string anArmy() const;

    void setIOID(const int id) { mIOID = id; }
    int ioID() const { return mIOID; }

    virtual void write(eWriteStream& dst) const;
    virtual void read(eReadStream& src);
private:
    int mIOID = -1;

    bool mIsCurrentCity = false;
    eWorldCityType mType;

    std::string mName;
    std::string mLeader;

    double mX;
    double mY;

    bool mRebellion = false;

    eWorldCityRelationship mRel{eWorldCityRelationship::ally};
    int mAt{60};
};

struct eResourceTrade {
    eResourceType fType;
    int fUsed;
    int fMax;
    int fPrice;

    void write(eWriteStream& dst) const {
        dst << fType;
        dst << fUsed;
        dst << fMax;
        dst << fPrice;
    }

    void read(eReadStream& src) {
        src >> fType;
        src >> fUsed;
        src >> fMax;
        src >> fPrice;
    }
};

class eWorldCity : public eWorldCityBase {
public:
    using eWorldCityBase::eWorldCityBase;

    void nextYear();

    int strength() const;

    int army() const { return mArmy; }
    void setArmy(const int a) { mArmy = a; }

    int wealth() const { return mWealth; }
    void setWealth(const int w) { mWealth = w; }

    void setWaterTrade(const bool w) { mWaterTrade = w; }
    bool waterTrade() const { return mWaterTrade; }

    void setAbroad(const bool a) { mAbroad = a; }
    bool abroad() const { return mAbroad; }

    const std::vector<eResourceTrade>& buys() const
    { return mBuys; }
    std::vector<eResourceTrade>& buys()
    { return mBuys; }
    bool buys(const eResourceType type) const;
    void addBuys(const eResourceTrade& b);

    const std::vector<eResourceTrade>& sells() const
    { return mSells; }
    std::vector<eResourceTrade>& sells()
    { return mSells; }
    bool sells(const eResourceType type) const;
    void addSells(const eResourceTrade& s);

    eResourceType tributeType() const { return mTributeType; }
    int tributeCount() const { return mTributeCount; }

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    void gifted(const eResourceType type, const int count);
    bool acceptsGift(const eResourceType type, const int count) const;

    static stdsptr<eWorldCity> sCreateAthens(
            const eWorldCityType type = eWorldCityType::greekCity);
    static stdsptr<eWorldCity> sCreateSparta(
            const eWorldCityType type = eWorldCityType::greekCity);
    static stdsptr<eWorldCity> sCreateKnossos(
            const eWorldCityType type = eWorldCityType::greekCity);
    static stdsptr<eWorldCity> sCreateCorinth(
            const eWorldCityType type = eWorldCityType::greekCity);
    static stdsptr<eWorldCity> sCreateOlympia(
            const eWorldCityType type = eWorldCityType::greekCity);

    static stdsptr<eWorldCity> sCreateEgypt(
            const eWorldCityType type = eWorldCityType::distantCitySE);
    static stdsptr<eWorldCity> sCreateCyprus(
            const eWorldCityType type = eWorldCityType::distantCitySE);

    static stdsptr<eWorldCity> sCreateTroy(
            const eWorldCityType type = eWorldCityType::trojanCity);

    static stdsptr<eWorldCity> sCreateMtPelion(
            const eWorldCityType type = eWorldCityType::centaurCity);

    static stdsptr<eWorldCity> sCreateSardis(
            const eWorldCityType type = eWorldCityType::persianCity);
    static stdsptr<eWorldCity> sCreateHattusas(
            const eWorldCityType type = eWorldCityType::persianCity);
private:
    bool mAbroad = false;

    int mArmy = 1; // 1-5
    int mWealth = 1; // 1-5

    bool mWaterTrade = false;

    std::vector<eResourceTrade> mBuys;
    std::vector<eResourceTrade> mSells;

    std::vector<std::pair<eResourceType, int>> mReceived;

    eResourceType mTributeType = eResourceType::drachmas;
    int mTributeCount = 500;
};

#endif // EWORLDCITY_H
