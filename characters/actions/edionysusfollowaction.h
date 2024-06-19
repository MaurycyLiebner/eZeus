#ifndef EDIONYSUSFOLLOWACTION_H
#define EDIONYSUSFOLLOWACTION_H

#include "efollowaction.h"

enum class eCharacterType;

class eDionysusFollowAction : public eFollowAction {
public:
    using eFollowAction::eFollowAction;

    void setFollower(eCharacter* const f);
private:
    static bool sShouldFollow(const eCharacterType c);

    void increment(const int by) override;

    stdptr<eCharacter> mFollower;
};

#endif // EDIONYSUSFOLLOWACTION_H
