#ifndef EEMPLOYINGBUILDING_H
#define EEMPLOYINGBUILDING_H

#include "ebuildingwithresource.h"

class eEmployingBuilding : public eBuildingWithResource {
public:
    eEmployingBuilding(eGameBoard& board,
                       const eBuildingType type,
                       const int sw, const int sh,
                       const int maxEmployees);
    ~eEmployingBuilding();

    void timeChanged();

    int employed() const { return mEmployed; }
    int maxEmployees() const { return mMaxEmployees; }
    double employedFraction() const;
private:
    const int mMaxEmployees;
    int mEployedUpdate = 0;
    int mEmployed = 0;
};

#endif // EEMPLOYINGBUILDING_H
