#ifndef EREQUESTSTRIKEEVENT_H
#define EREQUESTSTRIKEEVENT_H

#include "egameevent.h"

class eRequestStrikeEvent : public eGameEvent {
public:
    eRequestStrikeEvent(const eGameEventBranch branch);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    void setEnd(const int e) { mEnd = e; }
    bool end() const { return mEnd; }

    void setCity(const stdsptr<eWorldCity>& c) { mCity = c; }
    const stdsptr<eWorldCity>& city() const { return mCity; }

    void setRivalCity(const stdsptr<eWorldCity>& c) { mRivalCity = c; }
    const stdsptr<eWorldCity>& rivalCity() const { return mRivalCity; }
private:
    bool mEnd = false;
    stdsptr<eWorldCity> mCity;
    stdsptr<eWorldCity> mRivalCity;
};

#endif // EREQUESTSTRIKEEVENT_H
