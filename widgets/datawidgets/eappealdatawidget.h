#ifndef EAPPEALDATAWIDGET_H
#define EAPPEALDATAWIDGET_H

#include "../ewidget.h"

class eGameWidget;
class eViewModeButton;

class eAppealDataWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize();

    void setGameWidget(eGameWidget* const gw);
private:
    eViewModeButton* mSeeAppeal = nullptr;
};

#endif // EAPPEALDATAWIDGET_H
