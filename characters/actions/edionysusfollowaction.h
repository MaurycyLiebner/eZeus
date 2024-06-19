#ifndef EDIONYSUSFOLLOWACTION_H
#define EDIONYSUSFOLLOWACTION_H

#include "efollowaction.h"

enum class eCharacterType;

class eDionysusFollowAction : public eFollowAction {
public:
    eDionysusFollowAction(eCharacter* const f,
                          eCharacter* const c);
    eDionysusFollowAction(eCharacter* const c);

    void setFollower(eCharacter* const f);

    static bool sShouldFollow(const eCharacterType c);

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:

    void increment(const int by) override;

    stdptr<eCharacter> mFollower;
};

#endif // EDIONYSUSFOLLOWACTION_H
