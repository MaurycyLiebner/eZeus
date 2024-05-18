#ifndef EAPPEALDATAWIDGET_H
#define EAPPEALDATAWIDGET_H

#include "edatawidget.h"

class eGameWidget;
class eViewModeButton;
class eBuilding;
class eMultiLineLabel;

class eAppealDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();
protected:
    void paintEvent(ePainter& p);
private:
    eViewModeButton* mSeeAppeal = nullptr;

    eMultiLineLabel* mNoMonumentsWidget = nullptr;
    eWidget* mMonumentsWidget = nullptr;

    std::vector<eBuilding*> mBuildings;

    int mTime{0};
};

#endif // EAPPEALDATAWIDGET_H
