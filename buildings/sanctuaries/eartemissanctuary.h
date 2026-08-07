#ifndef EARTEMISSANCTUARY_H
#define EARTEMISSANCTUARY_H

#include "esanctuary.h"

class eSanctuaryWithWarriors : public eSanctuary {
public:
    using eSanctuary::eSanctuary;

    void erase() override;

    void timeChanged(const int by) override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    int mSoldierSpawn = 0;
    std::vector<stdsptr<eSoldierBanner>> mSoldierBanners;
};

class eArtemisSanctuary: public eSanctuaryWithWarriors  {
public:
    eArtemisSanctuary(const int sw, const int sh,
                      eGameBoard& board, const eCityId cid);
};

class eAresSanctuary: public eSanctuaryWithWarriors  {
public:
    eAresSanctuary(const int sw, const int sh,
                   eGameBoard& board, const eCityId cid);
};

#endif // EARTEMISSANCTUARY_H
