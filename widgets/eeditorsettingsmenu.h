#ifndef EEDITORSETTINGSMENU_H
#define EEDITORSETTINGSMENU_H

#include "eframedwidget.h"

class eEpisode;

class eEditorSettingsMenu : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    void initialize(eEpisode* const ep);
};

#endif // EEDITORSETTINGSMENU_H
