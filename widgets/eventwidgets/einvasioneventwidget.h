#ifndef EINVASIONEVENTWIDGET_H
#define EINVASIONEVENTWIDGET_H

#include "../ewidget.h"

#include "gameEvents/einvasionevent.h"

class eLabeledWidget;

class eInvasionEventWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(eInvasionEvent* const e);
private:
    void updateVisibility();

    bool mHardcoded = true;
    stdsptr<eWorldCity> mCity;

    eLabeledWidget* mInfantryButtonL = nullptr;
    eLabeledWidget* mCavalryButtonL = nullptr;
    eLabeledWidget* mArchersButtonL = nullptr;
};

#endif // EINVASIONEVENTWIDGET_H
