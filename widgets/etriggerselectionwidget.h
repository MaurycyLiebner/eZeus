#ifndef ETRIGGERSELECTIONWIDGET_H
#define ETRIGGERSELECTIONWIDGET_H

#include "eframedwidget.h"

class eTriggerSelectionWidget : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    using eLabels = std::vector<std::string>;
    using eTriggerAct = std::function<void(int)>;
    void initialize(const eLabels& labels,
                    const eTriggerAct& act);
};

#endif // ETRIGGERSELECTIONWIDGET_H
