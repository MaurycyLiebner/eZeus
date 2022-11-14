#ifndef ECHARACTERACTIONFUNCTION_H
#define ECHARACTERACTIONFUNCTION_H

#include "fileIO/estreams.h"

enum class eCharacterActionFunctionType {
    AWC_goBackFail,
    AWC_goBackFinish,

    AA_patrolFail,
    AA_patrolFinish,

    ArtA_buildFinish,
    ArtA_buildDelete,

    CTA_findTargetFinish,

    CRA_collectFinish,
    CRA_collectFail,
    CRA_callCollectedActionFinish,

    FFA_lookForFireFail,
    FFA_putOutFireFinish,

    GA_patrolFail,
    GA_patrolFailFail,
    GA_patrolFailFinish,
    GA_lookForSoldierAttackFinish,
    GA_teleportFinish,
    GA_hermesRunFinish,

    GAA_loserDisappearFinish,
    GAA_fightFinish
};

using eCharActFuncType = eCharacterActionFunctionType;

class eCharacterActionFunction {
public:
    eCharacterActionFunction(eGameBoard& board,
                             const eCharActFuncType t);

    eCharActFuncType type() const { return mType; }
    eGameBoard& board() { return mBoard; }

    virtual void read(eReadStream& src) = 0;
    virtual void write(eWriteStream& dst) const = 0;

    virtual void call() = 0;

    static stdsptr<eCharacterActionFunction> sCreate(
            eGameBoard& board,
            const eCharActFuncType type);
private:
    eGameBoard& mBoard;
    const eCharActFuncType mType;
};

using eCharActFunc = eCharacterActionFunction;


#endif // ECHARACTERACTIONFUNCTION_H
