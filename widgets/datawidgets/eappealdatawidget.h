#ifndef EAPPEALDATAWIDGET_H
#define EAPPEALDATAWIDGET_H

#include "edatawidget.h"

class eGameWidget;
class eViewModeButton;

class eAppealDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();
private:
    eViewModeButton* mSeeAppeal = nullptr;
};

#endif // EAPPEALDATAWIDGET_H
