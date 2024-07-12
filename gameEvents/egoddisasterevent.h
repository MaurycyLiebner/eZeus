#ifndef EGODDISASTEREVENT_H
#define EGODDISASTEREVENT_H

#include "egameevent.h"

#include "characters/gods/egod.h"

class eGodDisasterEvent : public eGameEvent {
public:
    eGodDisasterEvent(const eGameEventBranch branch);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    void setCity(const stdsptr<eWorldCity>& c) { mCity = c; }
    const stdsptr<eWorldCity>& city() const { return mCity; }

    void setEnd(const int e) { mEnd = e; }
    bool end() const { return mEnd; }

    void setGod(const eGodType god) { mGod = god; }
    eGodType god() const { return mGod; }

    void setDuration(const int d) { mDuration = d; }
    int duration() const { return mDuration; }
private:
    int mDuration = 180;
    bool mEnd = false;
    eGodType mGod = eGodType::zeus;
    stdsptr<eWorldCity> mCity;
};

#endif // EGODDISASTEREVENT_H
