#ifndef EBOARDSETTINGSMENU_H
#define EBOARDSETTINGSMENU_H

#include "eframedwidget.h"

class eGameBoard;
class eGameWidget;

class eBoardSettingsMenu : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    void initialize(eGameWidget* const gw, eGameBoard& board);
};

#endif // EBOARDSETTINGSMENU_H
