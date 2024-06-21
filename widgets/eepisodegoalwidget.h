#ifndef EEPISODEGOALWIDGET_H
#define EEPISODEGOALWIDGET_H

#include "eframedwidget.h"

template <class T> using stdsptr = std::shared_ptr<T>;

class eEpisodeGoal;
class eWorldBoard;

class eEpisodeGoalWidget : public eFramedWidget {
public:
    using eFramedWidget::eFramedWidget;

    void initialize(const stdsptr<eEpisodeGoal>& e,
                    eWorldBoard* const board);
};

#endif // EEPISODEGOALWIDGET_H
