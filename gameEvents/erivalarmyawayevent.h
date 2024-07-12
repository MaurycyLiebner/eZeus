#ifndef ERIVALARMYAWAYEVENT_H
#define ERIVALARMYAWAYEVENT_H

#include "egameevent.h"

class eRivalArmyAwayEvent : public eGameEvent {
public:
    eRivalArmyAwayEvent(const eGameEventBranch branch);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    void setCity(const stdsptr<eWorldCity>& c) { mCity = c; }
    const stdsptr<eWorldCity>& city() const { return mCity; }

    void setEnd(const int e) { mEnd = e; }
    bool end() const { return mEnd; }

    void setDuration(const int d) { mDuration = d; }
    bool duration() const { return mDuration; }
private:
    bool mEnd = false;
    int mDuration = 12;
    int mTroopsTaken = 0;
    stdsptr<eWorldCity> mCity;
};

#endif // ERIVALARMYAWAYEVENT_H
