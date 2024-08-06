#ifndef EWAGECHANGEEVENT_H
#define EWAGECHANGEEVENT_H

#include "egameevent.h"

class eWageChangeEvent : public eGameEvent {
public:
    eWageChangeEvent(const eGameEventBranch branch);

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    void trigger() override;
    std::string longName() const override;

    int by() const { return mBy; }
    void setBy(const int by) { mBy = by; }
private:
    int mBy = 0; // percent
};

#endif // EWAGECHANGEEVENT_H
