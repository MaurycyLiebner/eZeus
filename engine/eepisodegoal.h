#ifndef EEPISODEGOAL_H
#define EEPISODEGOAL_H

#include "fileIO/ereadstream.h"
#include "fileIO/ewritestream.h"

enum class eEpisodeGoalType {
    population,
    treasury,
    sanctuary,
    support,
    quest,
    slay,
    rule,
    housing,
    setAsideGoods
};

struct eEpisodeGoal {
    eEpisodeGoalType fType;
    int fEnumInt1;
    int fEnumInt2;
    int fRequiredCount;
    int fStatusCount = 0;
    stdsptr<eWorldCity> fCity;

    void read(eReadStream& src);
    void write(eWriteStream& dst) const;

    bool met() const;

    std::string text(const bool colonyEpisode,
                     const bool atlantean) const;

    void update(eGameBoard* const b);
};

#endif // EEPISODEGOAL_H
