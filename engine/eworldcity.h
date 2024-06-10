#ifndef EWORLDCITY_H
#define EWORLDCITY_H

#include <string>

#include "eresourcetype.h"
#include "pointers/estdselfref.h"
#include "fileIO/estreams.h"

enum class eNationality {
    greek,
    trojan,
    persian,
    centaur,
    amazon,

    egyptian,
    mayan,
    phoenician,
    oceanid,
    atlantean,
};

enum class eDistantDirection {
    none,
    N,
    NE,
    E,
    SE,
    S,
    SW,
    W,
    NW
};

enum class eCityType {
    parentCity,
    colony,
    foreignCity,
    distantCity,
    enchantedPlace,
    destroyedCity
};

enum class eForeignCityRelationship {
    vassal,
    ally,
    rival
};

enum class eCityAttitude {
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

enum class eCityState {
    active,
    inactive
};

class eWorldCityBase {
public:
    eWorldCityBase() {}
    eWorldCityBase(const eCityType type,
                   const std::string& name,
                   const double x, const double y);

    bool rebellion() const { return mRebellion; }
    void setRebellion(const bool r) { mRebellion = r; }

    static std::string sTypeName(const eCityType type);
    void setType(const eCityType type) { mType = type; }
    eCityType type() const { return mType; }

    bool isDistant() const;
    bool isVassal() const;
    bool isColony() const;
    bool isParentCity() const;
    bool isRival() const;
    bool isAlly() const;

    static std::string sNationalityName(const eNationality type);
    void setNationality(const eNationality n) { mNationality = n; }
    eNationality nationality() const { return mNationality; }

    static std::string sDirectionName(const eDistantDirection d);
    void setDirection(const eDistantDirection n) { mDirection = n; }
    eDistantDirection direction() const { return mDirection; }

    void move(const double x, const double y);

    double x() const { return mX; }
    double y() const { return mY; }

    bool isCurrentCity() const { return mIsCurrentCity; }
    void setIsCurrentCity(const bool c) { mIsCurrentCity = c; }

    static std::string sRelationshipName(
            const eForeignCityRelationship r);
    eForeignCityRelationship relationship() const { return mRel; }
    void setRelationship(const eForeignCityRelationship r) { mRel = r; }

    static std::string sStateName(const eCityState s);
    void setState(const eCityState state) { mState = state; }
    eCityState state() const { return mState; };
    bool active() const { return mType != eCityType::colony ||
                                 mState == eCityState::active; }

    static std::string sAttitudeName(const eCityAttitude at);
    eCityAttitude attitudeClass() const;
    int attitude() const { return mAt; }
    void setAttitude(const int a);
    void incAttitude(const int a);

    static std::vector<std::string> sNames();
    void setName(const std::string& name);
    const std::string& name() const { return mName; }

    static std::vector<std::string> sLeaders();
    void setLeader(const std::string& name);
    const std::string& leader() const { return mLeader; }

    std::string anArmy() const;

    void setIOID(const int id) { mIOID = id; }
    int ioID() const { return mIOID; }

    virtual void write(eWriteStream& dst) const;
    virtual void read(eReadStream& src);
private:
    int mIOID = -1;

    bool mIsCurrentCity = false;
    eCityType mType{eCityType::foreignCity};

    eNationality mNationality{eNationality::greek};
    eDistantDirection mDirection{eDistantDirection::none};
    eCityState mState{eCityState::active};

    std::string mName;
    int mNameString = -1;

    std::string mLeader;
    int mLeaderString = -1;

    double mX = 0.5;
    double mY = 0.5;

    bool mRebellion = false;

    eForeignCityRelationship mRel{eForeignCityRelationship::ally};
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

    void setTributeType(const eResourceType r) { mTributeType = r; }
    void setTributeCount(const int c) { mTributeCount = c; }

    eResourceType tributeType() const { return mTributeType; }
    int tributeCount() const { return mTributeCount; }

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    void gifted(const eResourceType type, const int count);
    bool acceptsGift(const eResourceType type, const int count) const;

    static stdsptr<eWorldCity> sCreateAthens();
    static stdsptr<eWorldCity> sCreateSparta();
    static stdsptr<eWorldCity> sCreateKnossos();
    static stdsptr<eWorldCity> sCreateCorinth();
    static stdsptr<eWorldCity> sCreateOlympia();

    static stdsptr<eWorldCity> sCreateEgypt();
    static stdsptr<eWorldCity> sCreateCyprus();

    static stdsptr<eWorldCity> sCreateTroy();

    static stdsptr<eWorldCity> sCreateMtPelion();

    static stdsptr<eWorldCity> sCreateSardis();
    static stdsptr<eWorldCity> sCreateHattusas();
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
