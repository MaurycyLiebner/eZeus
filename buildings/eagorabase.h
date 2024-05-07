#ifndef EAGORABASE_H
#define EAGORABASE_H

#include "buildings/epatrolbuildingbase.h"
#include "engine/eresourcetype.h"

enum class eAgoraOrientation {
    bottomRight,
    topLeft,
    bottomLeft,
    topRight
};

class eVendor;

class eAgoraBase : public ePatrolBuildingBase {
public:
    eAgoraBase(eGameBoard& board,
               const eBuildingType type,
               const int sw, const int sh,
               const int nPts);

    virtual SDL_Point pt(const int id) const = 0;

    std::shared_ptr<eTexture> getTexture(const eTileSize size) const override {
        (void)size;
        return nullptr;
    }

    void erase() override;
    void read(eReadStream& src) override;

    int add(const eResourceType type, const int count) override;
    int spaceLeft(const eResourceType type) const override;

    SDL_Point pt(const int rx, const int ry,
                 const eAgoraOrientation o,
                 const int id) const;

    eBuilding* building(const int id) const;
    void setBuilding(const int id, const stdsptr<eBuilding>& b);
    void setBuilding(eBuilding* const space, const stdsptr<eBuilding>& b);
    int buildingId(const eBuilding* const b) const;

    void fillSpaces();

    bool hasVendors() const;

    void agoraProvide(eBuilding* const b);
    int agoraCount(const eResourceType r) const;
    eVendor* vendor(const eResourceType r) const;
private:
    const int mNPts;
    std::vector<stdsptr<eBuilding>> mBs;
};

#endif // EAGORABASE_H
