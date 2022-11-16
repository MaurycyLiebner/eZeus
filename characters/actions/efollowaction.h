#ifndef EFOLLOWACTION_H
#define EFOLLOWACTION_H

#include <deque>

#include "ecomplexaction.h"

#include "engine/eorientation.h"

#include "pointers/estdpointer.h"

class eTile;

class eFollowAction : public eComplexAction {
public:
    eFollowAction(eCharacter* const f,
                  eCharacter* const c);
    eFollowAction(eCharacter* const c);

    void setDistance(const int d);

    bool decide() override { return false; }

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    void increment(const int by) override;

    stdptr<eCharacter> mFollow;

    struct ePathNode {
        eTile* fTile;
        eOrientation fO;
    };

    std::deque<ePathNode> mTiles;

    int mDistance = 1;
};


#endif // EFOLLOWACTION_H
