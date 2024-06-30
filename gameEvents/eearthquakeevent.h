#ifndef EEARTHQUAKEEVENT_H
#define EEARTHQUAKEEVENT_H

#include "egameevent.h"

#include "characters/gods/egod.h"

class eEarthquakeEvent : public eGameEvent {
public:
    eEarthquakeEvent(const eGameEventBranch branch);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    int disasterPoint() const { return mDisasterPoint; }
    void setDisasterPoint(const int p) { mDisasterPoint = p; }

    void setGod(const eGodType god) { mGod = god; }
    eGodType god() const { return mGod; }

    void setSize(const int s) { mSize = s; }
    int size() const { return mSize; }
private:
    int mDisasterPoint = 0;
    eGodType mGod = eGodType::zeus;
    int mSize = 100;
};

#endif // EEARTHQUAKEEVENT_H
