#ifndef EWORLDMENU_H
#define EWORLDMENU_H

#include "elabel.h"

#include "ebutton.h"
#include "engine/eworldcity.h"
#include "pointers/estdselfref.h"

class eWorldGoodsWidget;
class eWorldTributeWidget;

class eWorldMenu : public eLabel {
public:
    using eLabel::eLabel;

    void initialize(const eAction& openRequest,
                    const eAction& openGift,
                    const eAction& openRaid,
                    const eAction& openConquer);

    void setCity(const stdsptr<eWorldCity>& c);
    void updateRelationshipLabel() const;
private:
    eLabel* mRelationshipLabel = nullptr;
    eLabel* mNameLabel = nullptr;
    eLabel* mLeaderLabel = nullptr;

    eLabel* mAttitudeLabel = nullptr;

    eWorldGoodsWidget* mGoodsWidget = nullptr;
    eWorldTributeWidget* mTributeWidget = nullptr;

    eButton* mRequestButton = nullptr;
    eButton* mFulfillButton = nullptr;
    eButton* mGiftButton = nullptr;
    eButton* mRaidButton = nullptr;
    eButton* mConquerButton = nullptr;

    stdsptr<eWorldCity> mCity;
};

#endif // EWORLDMENU_H
