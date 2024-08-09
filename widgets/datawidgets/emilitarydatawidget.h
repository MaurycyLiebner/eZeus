#ifndef EMILITARYDATAWIDGET_H
#define EMILITARYDATAWIDGET_H

#include "edatawidget.h"
#include "pointers/estdselfref.h"

class eGameBoard;
class eSoldierBanner;
class eMicroButton;

using eSB = stdptr<eSoldierBanner>;
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
    void openMoreInfoWiget();
private:
    void updateWidgets();

    eViewModeButton* mSeeSecurity = nullptr;

    eWidget* mForcesWidget = nullptr;

    eForcesWidget* mAbroad = nullptr;
    eForcesWidget* mInCity = nullptr;
    eForcesWidget* mStandingDown = nullptr;

    eMicroButton* mAtPalace = nullptr;
    eMicroButton* mNoShips = nullptr;
    eMicroButton* mNoTowers = nullptr;
};

#endif // EMILITARYDATAWIDGET_H
