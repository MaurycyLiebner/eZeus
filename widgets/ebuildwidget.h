#ifndef EBUILDWIDGET_H
#define EBUILDWIDGET_H

#include "ebuildbutton.h"

class eBuildWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(const std::vector<eBuildButton*>& ws);
    void exec(const int x, const int y, eWidget* const w);
};

#endif // EBUILDWIDGET_H
