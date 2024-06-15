#ifndef EMILITARYDATAWIDGET_H
#define EMILITARYDATAWIDGET_H

#include "edatawidget.h"
#include "pointers/estdselfref.h"

class eGameBoard;
class eSoldierBanner;

using eSB = stdsptr<eSoldierBanner>;
using eSoldierBanners = std::vector<eSB>;
using eSoldierBannerAction = std::function<void(const eSB&)>;

class eForcesWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(const std::string& title);

    void setBanners(const eSoldierBanners& ss,
                    const eSoldierBannerAction& act);
private:
    eWidget* mWidget = nullptr;
    eSoldierBanners mBanners;
};

class eMilitaryDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();
protected:
    void paintEvent(ePainter& p);
private:
    eViewModeButton* mSeeSecurity = nullptr;

    eWidget* mForcesWidget = nullptr;

    eForcesWidget* mAbroad = nullptr;
    eForcesWidget* mInCity = nullptr;
    eForcesWidget* mStandingDown = nullptr;

    int mTime{0};
};

#endif // EMILITARYDATAWIDGET_H
