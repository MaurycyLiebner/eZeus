#ifndef ESANCTBUILDING_H
#define ESANCTBUILDING_H

#include "../ebuilding.h"

class eSanctBuilding : public eBuilding {
public:
    eSanctBuilding(eGameBoard& board,
                   const eBuildingType type,
                   const int sw, const int sh);

    int progress() const { return mProgress; }
    void incProgress() { mProgress++; }
    void destroy() { mProgress = 0; }
private:
    int mProgress = 0;
};

#endif // ESANCTBUILDING_H
