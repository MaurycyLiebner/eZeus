#ifndef EWORLDCITY_H
#define EWORLDCITY_H

#include <string>

#include "eresourcetype.h"

enum class eWorldCityType {
    mainCity,
    collony,
    disabledColony,

    foreignCity1,
    foreignCity2,
    foreignCity3,
    foreignCity4,
    foreignCity5,

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

    int army() const { return mArmy; }
    void setArmy(const int a) { mArmy = a; }

    int wealth() const { return mWealth; }
    void setWealth(const int w) { mWealth = w; }

    const std::vector<eResourceTrade>& buys() const
    { return mBuys; }
    void addBuys(const eResourceTrade& b);

    const std::vector<eResourceTrade>& sells() const
    { return mSells; }
    void addSells(const eResourceTrade& s);
private:
    int mArmy = 0;
    int mWealth = 0;

    std::vector<eResourceTrade> mBuys;
    std::vector<eResourceTrade> mSells;
};

#endif // EWORLDCITY_H
