#ifndef EWORLDMENU_H
#define EWORLDMENU_H

#include "elabel.h"

#include "ebutton.h"
#include "engine/eworldcity.h"
#include "pointers/estdselfref.h"

class eWorldGoodsWidget;

class eWorldMenu : public eLabel {
public:
    using eLabel::eLabel;

    void initialize();

    void setCity(const stdsptr<eWorldCity>& c);
private:
    eWorldGoodsWidget* mGoodsWidget = nullptr;

    eButton* mRequestButton = nullptr;
    eButton* mFulfillButton = nullptr;
    eButton* mGiftButton = nullptr;
    eButton* mRaidButton = nullptr;
    eButton* mConquerButton = nullptr;

    stdsptr<eWorldCity> mCity;
};

#endif // EWORLDMENU_H
