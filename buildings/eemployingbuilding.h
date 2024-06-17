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

    int employed() const { return mEmployed; }
    void setEmployed(const int e);
    void setMaxEmployees(const int m) { mMaxEmployees = m; }
    int maxEmployees() const { return mMaxEmployees; }
    double employedFraction() const;
    double effectiveness() const;
    bool shutDown() const { return mShutDown; }
    void setShutDown(const bool sd);

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    bool mShutDown = false;
    int mMaxEmployees;
    int mEmployed = 0;
};

#endif // EEMPLOYINGBUILDING_H
