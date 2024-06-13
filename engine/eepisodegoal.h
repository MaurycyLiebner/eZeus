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
    int fEnumInt1 = 0;
    int fEnumInt2 = 0;
    int fRequiredCount = 0;
    int fStatusCount = 0;
    stdsptr<eWorldCity> fCity;

    void read(eWorldBoard* const board, eReadStream& src);
    void write(eWriteStream& dst) const;

    bool met() const;

    static std::string sText(const eEpisodeGoalType type);
    std::string text(const bool colonyEpisode,
                     const bool atlantean) const;

    void update(const eGameBoard* const b);
};

#endif // EEPISODEGOAL_H
