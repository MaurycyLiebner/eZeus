#ifndef ESTORAGEDATAWIDGET_H
#define ESTORAGEDATAWIDGET_H

#include "edatawidget.h"

#include "engine/eresourcetype.h"

class eGameBoard;
class eLabel;
class eViewModeButton;

class eStorageDataWidget : public eDataWidget {
public:
    using eDataWidget::eDataWidget;

    void initialize();
protected:
    void paintEvent(ePainter& p);
private:
    eWidget* sdwColumn(const eUIScale uiScale,
            const int iMin, const int iMax,
            const std::vector<eResourceType>& tps,
            std::vector<eLabel*>& lbls);

    eViewModeButton* mSeeDistribution = nullptr;

    std::vector<eLabel*> mResourceLabels;
};

#endif // ESTORAGEDATAWIDGET_H
