#ifndef EENLISTFORCESDIALOG_H
#define EENLISTFORCESDIALOG_H

#include "eclosabledialog.h"

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

class eEnlistForcesDialog : public eClosableDialog {
public:
    using eClosableDialog::eClosableDialog;

    using eEnlistAction = std::function<void(const eEnlistedForces&)>;
    void initialize(const eEnlistedForces& enlistable,
                    const eEnlistAction& action);
private:
    eEnlistedForces mSelected;
};

#endif // EENLISTFORCESDIALOG_H
