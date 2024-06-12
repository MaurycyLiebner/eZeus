#ifndef EBOARDSETTINGSMENU_H
#define EBOARDSETTINGSMENU_H

#include "eframedwidget.h"

class eGameBoard;

class eBoardSettingsMenu : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    void initialize(eGameBoard& board);
};

#endif // EBOARDSETTINGSMENU_H
