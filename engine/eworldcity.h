#ifndef EWORLDCITY_H
#define EWORLDCITY_H

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

class eWorldCityBase {
public:
    eWorldCityBase(const eWorldCityType type,
                   const int x, const int y);

    eWorldCityType type() const { return mType; }

    int x() const { return mX; }
    int y() const { return mY; }
private:
    const eWorldCityType mType;

    const int mX;
    const int mY;
};

class eWorldCity : public eWorldCityBase {
public:
    using eWorldCityBase::eWorldCityBase;

    bool ally() const { return mAlly; }
    void setAlly(const bool a) { mAlly = a; }

    int army() const { return mArmy; }
    void setArmy(const int a) { mArmy = a; }

    int wealth() const { return mWealth; }
    void setWealth(const int w) { mWealth = w; }
private:
    bool mAlly = false;
    int mArmy = 0;
    int mWealth = 0;
};

#endif // EWORLDCITY_H
