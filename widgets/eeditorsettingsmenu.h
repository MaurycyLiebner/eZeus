#ifndef EEDITORSETTINGSMENU_H
#define EEDITORSETTINGSMENU_H

#include "eframedwidget.h"

class eGameBoard;

class eEditorSettingsMenu : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    void initialize(eWidget* const parent,
                    eGameBoard& board);
};

#endif // EEDITORSETTINGSMENU_H
