#ifndef EGAMEMAINMENU_H
#define EGAMEMAINMENU_H

#include "eframedwidget.h"

class eGameBoard;

class eGameMainMenu : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    using eAction = std::function<void()>;
    void initialize(const eAction& exitAct,
                    eGameBoard* const board);
};

#endif // EGAMEMAINMENU_H
