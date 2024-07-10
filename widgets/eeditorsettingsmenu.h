#ifndef EEDITORSETTINGSMENU_H
#define EEDITORSETTINGSMENU_H

#include "eframedwidget.h"

class eEpisode;
class eCampaign;
class eWorldBoard;

class eEditorSettingsMenu : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    void initialize(const bool first,
                    eCampaign* const c,
                    eEpisode* const ep,
                    eWorldBoard* const board);
};

#endif // EEDITORSETTINGSMENU_H
