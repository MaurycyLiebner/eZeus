#ifndef ERUINS_H
#define ERUINS_H

#include "ebuilding.h"

class eRuins : public eBuilding {
public:
    eRuins(eGameBoard& board);

    stdsptr<eTexture> getTexture(const eTileSize size) const override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    void setWasType(const eBuildingType type) { mWasType = type; }
    eBuildingType wasType() const { return mWasType; }
private:
    eBuildingType mWasType = eBuildingType::none;
};

#endif // ERUINS_H
