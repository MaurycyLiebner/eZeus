#ifndef EMILITARYDATAWIDGET_H
#define EMILITARYDATAWIDGET_H

#include "edatawidget.h"
#include "pointers/estdselfref.h"

class eGameBoard;
class eSoldierBanner;

class eForcesWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(const std::string& title);

    using eSoldierBanners = std::vector<stdsptr<eSoldierBanner>>;
    void setBanners(const eSoldierBanners& ss);
private:
    eWidget* mWidget = nullptr;
};

class eMilitaryDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();
protected:
    void paintEvent(ePainter& p);
private:
    eViewModeButton* mSeeSecurity = nullptr;

    eForcesWidget* mInCity = nullptr;
    eForcesWidget* mStandingDown = nullptr;

    int mTime{0};
};

#endif // EMILITARYDATAWIDGET_H
