#ifndef EGODQUESTEVENTWIDGET_H
#define EGODQUESTEVENTWIDGET_H

#include "../ewidget.h"

#include "gameEvents/egodquestevent.h"

class eGodQuestEventWidget : public eWidget {
public:
    using eWidget::eWidget;

    void initialize(eGodQuestEvent* const e);
};

#endif // EGODQUESTEVENTWIDGET_H
