#ifndef EAPPEALDATAWIDGET_H
#define EAPPEALDATAWIDGET_H

#include "edatawidget.h"

class eGameWidget;
class eViewModeButton;
class eBuilding;
class eLabel;

class eAppealDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();
protected:
    void paintEvent(ePainter& p);
private:
    eViewModeButton* mSeeAppeal = nullptr;

    eLabel* mNoMonumentsWidget = nullptr;
    eWidget* mMonumentsWidget = nullptr;

    std::vector<eBuilding*> mBuildings;
};

#endif // EAPPEALDATAWIDGET_H
