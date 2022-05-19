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
};

class eSanctuary;

class eSanctBuilding : public eBuilding {
public:
    eSanctBuilding(eSanctuary* const s,
                   const eSanctCost& cost,
                   const int maxProgress,
                   eGameBoard& board,
                   const eBuildingType type,
                   const int sw, const int sh);

    bool resourcesAvailable() const;

    bool finished() const;
    int progress() const { return mProgress; }
    bool incProgress();
    void destroy() { mProgress = 0; }

    const eSanctCost& cost() const { return mCost; }

    void setCost(const eSanctCost& c);

    bool workedOn() const { return mWorkedOn; }
    void setWorkedOn(const bool w) { mWorkedOn = w; }
private:
    const int mMaxProgress;
    eSanctuary* const mSanctuary;
    eSanctCost mCost{0, 0, 0};
    eSanctCost mStored{0, 0, 0};
    bool mWorkedOn = false;
    int mProgress = 0;
};

#endif // ESANCTBUILDING_H
