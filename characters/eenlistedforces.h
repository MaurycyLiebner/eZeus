#ifndef EENLISTEDFORCES_H
#define EENLISTEDFORCES_H

#include "characters/esoldierbanner.h"
#include "characters/heroes/ehero.h"
#include "engine/eworldcity.h"

struct eEnlistedForces {
    std::vector<stdsptr<eSoldierBanner>> fSoldiers;
    std::vector<eHeroType> fHeroes;
    std::vector<stdsptr<eWorldCity>> fAllies;

    void clear() {
        fSoldiers.clear();
        fHeroes.clear();
        fAllies.clear();
    }

    void add(const eEnlistedForces& o) {
        for(const auto& s : o.fSoldiers) {
            fSoldiers.push_back(s);
        }
        for(const auto& h : o.fHeroes) {
            fHeroes.push_back(h);
        }
        for(const auto& a : o.fAllies) {
            fAllies.push_back(a);
        }
    }
};

#endif // EENLISTEDFORCES_H
