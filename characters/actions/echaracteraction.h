#ifndef ECHARACTERACTION_H
#define ECHARACTERACTION_H

#include <functional>

#include "echaracteractiontype.h"
#include "pointers/estdselfref.h"
#include "pointers/estdpointer.h"
#include "echaracteractionfunction.h"

class eCharacter;

enum class eCharacterActionState {
    running, finished, failed
};

enum class eCharActionType {
    animalAction,
    archerAction,
    artisanAction,
    buildAction,
    cartTransporterAction,
    collectAction,
    collectResourceAction,
    dieAction,
    fightAction,
    fireFighterAction,
    followAction,
    godAttackAction,
    godVisitAction,
    godWorshippedAction,
    growerAction,
    heroAction,
    huntAction,
    monsterAction,
    moveAroundAction,
    movePathAction,
    moveToAction,
    patrolAction,
    patrolGuidedMoveAction,
    patrolMoveAction,
    settlerAction,
    shepherdAction,
    soldierAction,
    traderAction,
    waitAction
};

class eCharacterAction : public eStdSelfRef {
public:
    eCharacterAction(eCharacter* const c,
                     const eCharActionType type);
    virtual ~eCharacterAction();

    virtual void increment(const int by) = 0;

    eCharacter* character() const { return mCharacter; }
    eCharacterActionState state() const { return mState; }
    void setState(const eCharacterActionState state);

    eCharActionType type() const { return mType; }

    eGameBoard& board() const { return mBoard; }

    void setFinishAction(const stdsptr<eCharActFunc>& f);
    void setFailAction(const stdsptr<eCharActFunc>& f);
    void setDeleteFailAction(const stdsptr<eCharActFunc>& d);

    static stdsptr<eCharacterAction> sCreate(
            eCharacter* const c,
            const eCharActionType type);

    virtual void read(eReadStream& src);
    virtual void write(eWriteStream& dst) const;

    void setIOID(const int id) { mIOID = id; }
    int ioID() const { return mIOID; }
private:
    eGameBoard& mBoard;
    eCharacter* const mCharacter;
    int mIOID = -1;
    const eCharActionType mType;
    eCharacterActionState mState{eCharacterActionState::running};
    eCharacterActionType mPauseType;

    stdsptr<eCharActFunc> mFinishAction;
    stdsptr<eCharActFunc> mFailAction;
    stdsptr<eCharActFunc> mDeleteFailAction;
};

#endif // ECHARACTERACTION_H
