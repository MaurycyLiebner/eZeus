#ifndef EENLISTEDFORCES_H
#define EENLISTEDFORCES_H

#include "characters/esoldierbanner.h"
#include "characters/heroes/ehero.h"
#include "engine/eworldcity.h"

struct eEnlistedForces {
    std::vector<stdsptr<eSoldierBanner>> fSoldiers;
    std::vector<eHeroType> fHeroes;
    std::vector<stdsptr<eWorldCity>> fAllies;
    bool fAres = false;

    void read(eGameBoard& board, eWorldBoard& wboard,
              eReadStream& src);
    void write(eWriteStream& dst) const;

    void clear();

    void add(const eEnlistedForces& o);

    int strength() const;
    void kill(const double killFrac);
};

#endif // EENLISTEDFORCES_H
