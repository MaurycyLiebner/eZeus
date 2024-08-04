#ifndef ESANCTBUILDING_H
#define ESANCTBUILDING_H

#include "../ebuilding.h"

struct eSanctCost {
    int fWood;
    int fMarble;
    int fSculpture;

    eSanctCost& operator+=(const eSanctCost& c) {
        fWood += c.fWood;
        fMarble += c.fMarble;
        fSculpture += c.fSculpture;
        return *this;
    }

    eSanctCost& operator-=(const eSanctCost& c) {
        fWood -= c.fWood;
        fMarble -= c.fMarble;
        fSculpture -= c.fSculpture;
        return *this;
    }

    eSanctCost operator-(const eSanctCost& c1) const {
        eSanctCost c;
        c = *this;
        c.operator-=(c1);
        return c;
    }
};

class eSanctuary;

class eSanctBuilding : public eBuilding {
public:
    eSanctBuilding(const eSanctCost& cost,
                   const int maxProgress,
                   eGameBoard& board,
                   const eBuildingType type,
                   const int sw, const int sh);

    void erase() override;

    bool resourcesAvailable() const;

    bool finished() const;
    int progress() const { return mProgress; }
    int maxProgress() const { return mMaxProgress; }
    bool incProgress();
    void destroy();

    const eSanctCost& cost() const { return mCost; }

    bool workedOn() const { return mWorkedOn; }
    void setWorkedOn(const bool w) { mWorkedOn = w; }

    void setSanctuary(eSanctuary* const s);
    eSanctuary* sanctuary() const { return mSanctuary; }

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    void scheduleTerrainUpdate();

    const int mMaxProgress;
    const eSanctCost mCost{0, 0, 0};
    eSanctuary* mSanctuary = nullptr;
    eSanctCost mStored{0, 0, 0};
    bool mWorkedOn = false;
    int mProgress = 0;
};

#endif // ESANCTBUILDING_H
