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
    void setCity(eWorldCity* const c);

    eLabeledWidget* mInfantryButtonL = nullptr;
    eLabeledWidget* mCavalryButtonL = nullptr;
    eLabeledWidget* mArchersButtonL = nullptr;
};

#endif // EINVASIONEVENTWIDGET_H
