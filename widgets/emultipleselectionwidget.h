#ifndef EMULTIPLESELECTIONWIDGET_H
#define EMULTIPLESELECTIONWIDGET_H

#include "eframedwidget.h"

class eFramedButton;
class eSelectionButton;

class eMultipleSelectionWidget : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    using eSetAction = std::function<void(const std::vector<int>&)>;
    using eLabels = std::vector<std::string>;
    void initialize(const eLabels& labels,
                    const eSetAction& setAct,
                    const std::vector<int>& ini);
    void addButton(const eAction& setActAct,
                   const eLabels& labels, const int i);
private:
    void updateButtons();

    std::vector<eSelectionButton*> mButtons;
    eFramedButton* mNewButton = nullptr;
};

#endif // EMULTIPLESELECTIONWIDGET_H
