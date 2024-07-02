#ifndef ECITYBECOMESEVENT_H
#define ECITYBECOMESEVENT_H

#include "egameevent.h"

enum class eCityBecomesType {
    ally, rival, vassal
};

class eCityBecomesEvent : public eGameEvent {
public:
    eCityBecomesEvent(const eGameEventBranch branch);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    void setCity(const stdsptr<eWorldCity>& c) { mCity = c; }
    const stdsptr<eWorldCity>& city() const { return mCity; }

    void setType(const eCityBecomesType t) { mType = t; }
    eCityBecomesType type() const { return mType; }
private:
    eCityBecomesType mType = eCityBecomesType::ally;
    stdsptr<eWorldCity> mCity;
};

#endif // ECITYBECOMESEVENT_H
