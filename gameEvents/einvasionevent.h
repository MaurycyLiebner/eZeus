#ifndef EINVASIONEVENT_H
#define EINVASIONEVENT_H

#include "egameevent.h"

#include "engine/eworldcity.h"

class eInvasionHandler;

class eInvasionEvent : public eGameEvent {
public:
    eInvasionEvent(const eGameEventBranch branch);
    ~eInvasionEvent();

    void pointerCreated() override;

    void initialize(const stdsptr<eWorldCity>& city,
                    const int infantry,
                    const int cavalry,
                    const int archers);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    bool finished() const override;

    const stdsptr<eWorldCity>& city() const { return mCity; }
    void setCity(const stdsptr<eWorldCity>& c);

    int infantry() const { return mInfantry; }
    void setInfantry(const int i) { mInfantry = i; }
    int cavalry() const { return mCavalry; }
    void setCavalry(const int c) { mCavalry = c; }
    int archers() const { return mArchers; }
    void setArchers(const int a) { mArchers = a; }

    int invasionPoint() const { return mInvasionPoint; }
    void setInvasionPoint(const int p) { mInvasionPoint = p; }

    void setFirstWarning(const eDate& w);
    eDate firstWarning() const { return mFirstWarning; }
    bool warned() const { return mWarned; }

    bool hardcoded() const { return mHardcoded; }
    void setHardcoded(const bool h) { mHardcoded = h; }

    bool activeInvasions() const;
    void addInvasionHandler(eInvasionHandler* const i);
    void removeInvasionHandler(eInvasionHandler* const i);

    bool nearestSoldier(const int fromX, const int fromY,
                        int& toX,int& toY) const;
private:
    int bribeCost() const;

    stdsptr<eWorldCity> mCity;
    std::vector<eInvasionHandler*> mHandlers;

    bool mHardcoded = true;

    int mInfantry = 10;
    int mCavalry = 10;
    int mArchers = 10;

    int mInvasionPoint = 1;

    bool mWarned = false;
    eDate mFirstWarning;
};

#endif // EINVASIONEVENT_H
