#ifndef EARMYMENU_H
#define EARMYMENU_H

#include "elabel.h"

class eMiniMap;
class eGameBoard;
class eBasicButton;

class eArmyMenu : public eLabel {
public:
    using eLabel::eLabel;

    void initialize(eGameBoard& b);

    eMiniMap* miniMap() const { return mMiniMap; }
    void setSoldiersHome(const bool h);
private:
    eGameBoard* mBoard = nullptr;
    eMiniMap* mMiniMap = nullptr;
    eBasicButton* mGoToBanner = nullptr;
    eBasicButton* mGoHome = nullptr;
};

#endif // EARMYMENU_H
