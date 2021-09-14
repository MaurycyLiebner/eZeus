#ifndef EGAMEMAINMENU_H
#define EGAMEMAINMENU_H

#include "eframedwidget.h"

class eGameMainMenu : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    using eAction = std::function<void()>;
    void initialize(const eAction& exitAct);
};

#endif // EGAMEMAINMENU_H
