#ifndef EBUILDINGWITHRESOURCE_H
#define EBUILDINGWITHRESOURCE_H

#include "ebuilding.h"

#include "engine/eresourcetype.h"

class eTransporterBase;
enum class eCartActionType;

class eBuildingWithResource : public eBuilding {
public:
    using eBuilding::eBuilding;

    virtual int add(const eResourceType type, const int count) {
        (void)type;
        (void)count;
        return 0;
    }
    virtual int take(const eResourceType type, const int count) {
        (void)type;
        (void)count;
        return 0;
    }

    virtual int count(const eResourceType type) const {
        (void)type;
        return 0;
    }

    virtual int spaceLeft(const eResourceType type) const {
        (void)type;
        return 0;
    }
protected:
    bool spawnGiveCart(stdsptr<eTransporterBase>& cart,
                       int& spawnTime, const int waitTime,
                       const eResourceType resType);
    bool spawnTakeCart(stdsptr<eTransporterBase>& cart,
                       int& spawnTime, const int waitTime,
                       const eResourceType resType);
private:
    bool depositFromCart(stdsptr<eTransporterBase>& cart,
                         int& spawnTime, const int waitTime);
};

#endif // EBUILDINGWITHRESOURCE_H
