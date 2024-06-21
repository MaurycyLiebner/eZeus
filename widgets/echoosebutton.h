#ifndef ECHOOSEBUTTON_H
#define ECHOOSEBUTTON_H

#include "eframedwidget.h"

class eChooseButton : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    using eLabels = std::vector<std::string>;
    using eButtonAction = std::function<void(int)>;
    void initialize(const int nRows,
                    const eLabels& labels,
                    const eButtonAction& act,
                    const bool small = false);
};

#endif // ECHOOSEBUTTON_H
