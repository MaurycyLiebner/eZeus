#ifndef EENLISTEDFORCES_H
#define EENLISTEDFORCES_H

#include "characters/esoldierbanner.h"
#include "characters/heroes/ehero.h"
#include "engine/eworldcity.h"

struct eEnlistedForces {
    std::vector<stdsptr<eSoldierBanner>> fSoldiers;
    std::vector<eHeroType> fHeroes;
    std::vector<stdsptr<eWorldCity>> fAllies;

    void read(eGameBoard& board, eReadStream& src);
    void write(eWriteStream& dst) const;

    void clear();

    void add(const eEnlistedForces& o);
};

#endif // EENLISTEDFORCES_H
