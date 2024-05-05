#ifndef EGODQUESTEVENTWIDGET_H
#define EGODQUESTEVENTWIDGET_H

#include "../ewidget.h"

#include "gameEvents/egodquestevent.h"

class eHeroButton;

class eGodQuestEventWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(eGodQuestEvent* const e);
private:
    void setDefaultHero();

    eGodQuestEvent* mE = nullptr;
    eHeroButton* mHeroButton = nullptr;
};

#endif // EGODQUESTEVENTWIDGET_H
