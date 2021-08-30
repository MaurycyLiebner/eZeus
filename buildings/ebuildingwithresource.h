#ifndef EBUILDINGWITHRESOURCE_H
#define EBUILDINGWITHRESOURCE_H

#include "eemployingbuilding.h"

#include "engine/eresourcetype.h"

class eCartTransporter;
enum class eCartActionType;

class eBuildingWithResource : public eEmployingBuilding {
public:
    using eEmployingBuilding::eEmployingBuilding;

    virtual int add(const eResourceType type, const int count) = 0;
    virtual int take(const eResourceType type, const int count) = 0;

    virtual int count(const eResourceType type) const = 0;
    virtual int spaceLeft(const eResourceType type) const = 0;

    bool spawnGiveCart(stdsptr<eCartTransporter>& cart,
                       int& spawnTime, const int waitTime,
                       const eResourceType resType);
    bool spawnTakeCart(stdsptr<eCartTransporter>& cart,
                       int& spawnTime, const int waitTime,
                       const eResourceType resType);
private:
    bool depositFromCart(stdsptr<eCartTransporter>& cart,
                         int& spawnTime, const int waitTime);
};

#endif // EBUILDINGWITHRESOURCE_H
