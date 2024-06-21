#ifndef EMULTIPLESELECTIONWIDGET_H
#define EMULTIPLESELECTIONWIDGET_H

#include "eframedwidget.h"

class eButtonsListWidget;

class eMultipleSelectionWidget : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    using eSetAction = std::function<void(const std::vector<int>&)>;
    using eLabels = std::vector<std::string>;
    void initialize(const eLabels& labels,
                    const eSetAction& setAct,
                    const std::vector<int>& ini);
private:
    std::vector<int> mValues;
};

#endif // EMULTIPLESELECTIONWIDGET_H
