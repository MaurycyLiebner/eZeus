#ifndef ETEMPLEALTARBUILDING_H
#define ETEMPLEALTARBUILDING_H

#include "esanctbuilding.h"

enum class eSacrifice {
    none,
    sheep,
    goods,
    bull
};

class eTempleAltarBuilding : public eSanctBuilding {
public:
    eTempleAltarBuilding(eGameBoard& board);

    std::shared_ptr<eTexture>
    getTexture(const eTileSize size) const override;

    std::vector<eOverlay>
    getOverlays(const eTileSize size) const override;

    void timeChanged(const int by) override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    void startSacrifice(const eSacrifice s);
    bool sacrificing() const { return mSacrifice != eSacrifice::none; }
private:
    eSacrifice mSacrifice = eSacrifice::none;
    int mSacrificeTime = 600000;
};

#endif // ETEMPLEALTARBUILDING_H
