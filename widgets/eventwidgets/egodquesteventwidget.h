#ifndef EGODQUESTEVENTWIDGET_H
#define EGODQUESTEVENTWIDGET_H

#include "../ewidget.h"

#include "gameEvents/egodquestevent.h"

class eHeroButton;

class eGodQuestEventWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(eGodQuestEventBase* const e);
private:
    void setDefaultHero();

    eGodQuestEventBase* mE = nullptr;
    eHeroButton* mHeroButton = nullptr;
};

#endif // EGODQUESTEVENTWIDGET_H
