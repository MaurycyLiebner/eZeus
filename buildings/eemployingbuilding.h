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

    void timeChanged(const int by) override;

    int employed() const { return mEmployed; }
    void setMaxEmployees(const int m) { mMaxEmployees = m; }
    int maxEmployees() const { return mMaxEmployees; }
    double employedFraction() const;
    double effectiveness() const;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    int mMaxEmployees;
    int mEmployedUpdateWait = 1000;
    int mEmployedUpdate = mEmployedUpdateWait;
    int mEmployed = 0;
};

#endif // EEMPLOYINGBUILDING_H
