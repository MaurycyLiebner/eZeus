#ifndef EFOLLOWACTION_H
#define EFOLLOWACTION_H

#include <deque>

#include "ecomplexaction.h"
#include "emovepathaction.h"

#include "engine/eorientation.h"

#include "pointers/estdpointer.h"

class eTile;
class eMovePathAction;

class eFollowAction : public eComplexAction {
protected:
    eFollowAction(eCharacter* const f,
                  eCharacter* const c,
                  const eCharActionType type);
public:
    eFollowAction(eCharacter* const f,
                  eCharacter* const c);
    eFollowAction(eCharacter* const c);

    void setRemainder(const double r);
    void setDistance(const int d);

    bool decide() override { return false; }

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
protected:
    void increment(const int by) override;
private:
    stdptr<eCharacter> mFollow;

    struct ePathNode {
        eTile* fTile;
        eOrientation fO;
    };

    std::deque<ePathNode> mTiles;

    double mRemainder = 0.;
    int mDistance = 1;
};

class eFA_remainderSetterFinish : public eCharActFunc {
public:
    eFA_remainderSetterFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::FA_remainderSetterFinish) {}
    eFA_remainderSetterFinish(eGameBoard& board,
                              eFollowAction* const fa,
                              eMovePathAction* const ma) :
        eCharActFunc(board, eCharActFuncType::FA_remainderSetterFinish),
        mTptr(fa), mMptr(ma) {}

    void call() override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    stdptr<eFollowAction> mTptr;
    stdptr<eMovePathAction> mMptr;
};

#endif // EFOLLOWACTION_H
