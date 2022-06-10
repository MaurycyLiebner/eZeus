#ifndef EWORLDCITY_H
#define EWORLDCITY_H

#include <string>

#include "eresourcetype.h"
#include "pointers/estdselfref.h"

enum class eWorldCityType {
    mainCity,
    collony,
    disabledColony,

    greekCity,
    trojanCity,
    persianCity,
    centaurCity,
    amazonCity,

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
    furious
};

class eWorldCityBase {
public:
    eWorldCityBase(const eWorldCityType type,
                   const std::string& name,
                   const double x, const double y);

    bool rebellion() const { return mRebellion; }
    void setRebellion(const bool r) { mRebellion = r; }

    eWorldCityType type() const { return mType; }

    double x() const { return mX; }
    double y() const { return mY; }

    eWorldCityRelationship relationship() const { return mRel; }
    void setRelationship(const eWorldCityRelationship r) { mRel = r; }

    eWorldCityAttitude attitude() const { return mAt; }
    void setAttitude(const eWorldCityAttitude a) { mAt = a; }

    const std::string& name() const { return mName; }
    const std::string& leader() const { return mLeader; }
private:
    const eWorldCityType mType;

    const std::string mName;
    const std::string mLeader;

    const double mX;
    const double mY;

    bool mRebellion = false;

    eWorldCityRelationship mRel;
    eWorldCityAttitude mAt;
};

struct eResourceTrade {
    eResourceType fType;
    int fUsed;
    int fMax;
    int fPrice;
};

class eWorldCity : public eWorldCityBase {
public:
    using eWorldCityBase::eWorldCityBase;

    void nextYear();

    int army() const { return mArmy; }
    void setArmy(const int a) { mArmy = a; }

    int wealth() const { return mWealth; }
    void setWealth(const int w) { mWealth = w; }

    const std::vector<eResourceTrade>& buys() const
    { return mBuys; }
    std::vector<eResourceTrade>& buys()
    { return mBuys; }
    void addBuys(const eResourceTrade& b);

    const std::vector<eResourceTrade>& sells() const
    { return mSells; }
    std::vector<eResourceTrade>& sells()
    { return mSells; }
    void addSells(const eResourceTrade& s);

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
    int mArmy = 0;
    int mWealth = 0;

    std::vector<eResourceTrade> mBuys;
    std::vector<eResourceTrade> mSells;
};

#endif // EWORLDCITY_H
