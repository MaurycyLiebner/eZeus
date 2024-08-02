#ifndef EFOLLOWACTION_H
#define EFOLLOWACTION_H

#include <deque>

#include "emoveaction.h"

#include "engine/eorientation.h"

#include "pointers/estdpointer.h"

class eTile;
class eMovePathAction;

class eFollowAction : public eMoveAction {
protected:
    eFollowAction(eCharacter* const f,
                  eCharacter* const c,
                  const eCharActionType type);
public:
    eFollowAction(eCharacter* const f,
                  eCharacter* const c);
    eFollowAction(eCharacter* const c);

    void catchUp();
    void setDistance(const int d);

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
protected:
    void increment(const int by) override;
private:
    eCharacterActionState nextTurn(eOrientation& turn) override;

    stdptr<eCharacter> mFollow;

    struct ePathNode {
        eTile* fTile;
        eOrientation fO;
    };

    std::deque<ePathNode> mTiles;

    bool mCatchUp = false;
    int mDistance = 1;
};

#endif // EFOLLOWACTION_H
