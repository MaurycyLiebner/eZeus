#ifndef ESOLDIER_H
#define ESOLDIER_H

#include "efightingpatroler.h"

class eSoldierAction;
class eSoldierBanner;

class eSoldier : public eFightingPatroler {
public:
    using eCharTexs = eFightingCharacterTextures eCharacterTextures::*;
    eSoldier(eGameBoard& board,
             const eCharTexs charTexs,
             const eCharacterType type);
    ~eSoldier();

    bool selected() const { return mSelected; }
    void setSelected(const bool s) { mSelected = s; }

    eSoldierAction* soldierAction() const;
    void setSoldierAction(const stdsptr<eSoldierAction>& a);

    int range() const { return mRange; }
    void setRange(const int r) { mRange = r; }

    eSoldierBanner* banner() const;
    void setBanner(eSoldierBanner* const b);
private:
    eSoldierBanner* mBanner = nullptr;

    int mRange = 0;
    stdsptr<eSoldierAction> mAction;
    bool mSelected = false;
};

#endif // ESOLDIER_H
