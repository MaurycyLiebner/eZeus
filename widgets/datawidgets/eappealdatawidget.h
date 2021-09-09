#ifndef EAPPEALDATAWIDGET_H
#define EAPPEALDATAWIDGET_H

#include "../ewidget.h"

class eGameWidget;
class eCheckableButton;

class eAppealDataWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize();

    void setGameWidget(eGameWidget* const gw);

    void paintEvent(ePainter& p);
private:
    eCheckableButton* mSeeAppeal = nullptr;

    eGameWidget* mGW = nullptr;
};

#endif // EAPPEALDATAWIDGET_H
