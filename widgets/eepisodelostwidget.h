#ifndef EEPISODELOSTWIDGET_H
#define EEPISODELOSTWIDGET_H

#include "elabel.h"

class eEpisodeLostWidget : public eLabel {
public:
    using eLabel::eLabel;

    void initialize(const eAction& proceedA);
};

#endif // EEPISODELOSTWIDGET_H
