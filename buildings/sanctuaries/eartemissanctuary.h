#ifndef EARTEMISSANCTUARY_H
#define EARTEMISSANCTUARY_H

#include "esanctuary.h"

class eSanctuaryWithWarriors : public eSanctuary {
public:
    using eSanctuary::eSanctuary;

    void timeChanged(const int by);
private:
    int mSoldierSpawn = 0;
    std::vector<stdsptr<eSoldierBanner>> mSoldierBanners;
};

class eArtemisSanctuary: public eSanctuaryWithWarriors  {
public:
    eArtemisSanctuary(const int sw, const int sh,
                      eGameBoard& board);
};

class eAresSanctuary: public eSanctuaryWithWarriors  {
public:
    eAresSanctuary(const int sw, const int sh,
                   eGameBoard& board);
};

#endif // EARTEMISSANCTUARY_H
