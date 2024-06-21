#ifndef EEDITORSETTINGSMENU_H
#define EEDITORSETTINGSMENU_H

#include "eframedwidget.h"

class eEpisode;
class eWorldBoard;

class eEditorSettingsMenu : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    void initialize(eEpisode* const ep,
                    eWorldBoard* const board);
};

#endif // EEDITORSETTINGSMENU_H
