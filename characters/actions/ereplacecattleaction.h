#ifndef EREPLACECATTLEACTION_H
#define EREPLACECATTLEACTION_H

#include "eactionwithcomeback.h"

#include "characters/echaracter.h"
#include "characters/actions/eanimalaction.h"
#include "buildings/eanimalbuilding.h"

class eReplaceCattleAction : public eActionWithComeback {
public:
    eReplaceCattleAction(eCharacter* const c,
                         eCharacter* const cc = nullptr);

    bool decide() override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    void goCattle();

    stdptr<eCharacter> mCattle;
};

class eRC_finishAction : public eCharActFunc {
public:
    eRC_finishAction(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::RC_finishAction) {}
    eRC_finishAction(eGameBoard& board,
                     eReplaceCattleAction* const a,
                     eCharacter* const c,
                     eCharacter* const cc) :
        eCharActFunc(board, eCharActFuncType::RC_finishAction),
        mButcherA(a), mButcher(c), mCattle(cc) {}

    void call() override;

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const a) {
            mButcherA = static_cast<eReplaceCattleAction*>(a);
        });
        src.readCharacter(&board(), [this](eCharacter* const c) {
            mButcher = c;
        });
        src.readCharacter(&board(), [this](eCharacter* const c) {
            mCattle = c;
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mButcherA);
        dst.writeCharacter(mButcher);
        dst.writeCharacter(mCattle);
    }
private:
    stdptr<eReplaceCattleAction> mButcherA;
    stdptr<eCharacter> mButcher;
    stdptr<eCharacter> mCattle;
};

class eRC_finishWalkingAction : public eCharActFunc {
public:
    eRC_finishWalkingAction(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::RC_finishWalkingAction) {}
    eRC_finishWalkingAction(eGameBoard& board,
                            eCharacter* const c) :
        eCharActFunc(board, eCharActFuncType::RC_finishWalkingAction),
        mCattle(c) {}

    void call() override;

    void read(eReadStream& src) override {
        src.readCharacter(&board(), [this](eCharacter* const c) {
            mCattle = c;
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacter(mCattle);
    }
private:
    stdptr<eCharacter> mCattle;
};

#endif // EREPLACECATTLEACTION_H
