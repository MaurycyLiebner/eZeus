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
};

class eSanctBuilding : public eBuilding {
public:
    eSanctBuilding(const eSanctCost& cost,
                   const int maxProgress,
                   eGameBoard& board,
                   const eBuildingType type,
                   const int sw, const int sh);

    int progress() const { return mProgress; }
    bool incProgress();
    void destroy() { mProgress = 0; }

    const eSanctCost& cost() const { return mCost; }

    void setCost(const eSanctCost& c);
private:
    const int mMaxProgress;
    eSanctCost mCost;
    int mProgress = 0;
};

#endif // ESANCTBUILDING_H
