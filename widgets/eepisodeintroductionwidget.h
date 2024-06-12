#ifndef EEPISODEINTRODUCTIONWIDGET_H
#define EEPISODEINTRODUCTIONWIDGET_H

#include "elabel.h"

class eCampaign;

class eEpisodeIntroductionWidget : public eLabel {
public:
    using eLabel::eLabel;

    void initialize(const std::shared_ptr<eCampaign>& c);
};

#endif // EEPISODEINTRODUCTIONWIDGET_H
