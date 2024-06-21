#ifndef ETEMPLEBUILDING_H
#define ETEMPLEBUILDING_H

#include "esanctbuilding.h"

class eTempleBuilding : public eSanctBuilding {
public:
    eTempleBuilding(eGameBoard& board);
    eTempleBuilding(const int id, eGameBoard& board);

    std::shared_ptr<eTexture>
    getTexture(const eTileSize size) const override;

    std::vector<eOverlay>
    getOverlays(const eTileSize size) const override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    int mId;
};

#endif // ETEMPLEBUILDING_H
