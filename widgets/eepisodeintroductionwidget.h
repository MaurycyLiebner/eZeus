#ifndef EEPISODEINTRODUCTIONWIDGET_H
#define EEPISODEINTRODUCTIONWIDGET_H

#include "elabel.h"

class eCampaign;
class eEpisodeGoal;
enum class eEpisodeType;

enum class eEpisodeIntroType {
    intro,
    goals,
    victory,
    campaingVictory
};

class eEpisodeIntroductionWidget : public eLabel {
public:
    using eLabel::eLabel;

    using eGoals =  std::vector<std::shared_ptr<eEpisodeGoal>>;
    void initialize(const std::shared_ptr<eCampaign>& c,
                    const std::string& title,
                    const std::string& text,
                    const eGoals& goals,
                    const eAction& proceedA,
                    const eEpisodeIntroType type);
};

#endif // EEPISODEINTRODUCTIONWIDGET_H
