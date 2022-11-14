#ifndef EGODATTACKACTION_H
#define EGODATTACKACTION_H

#include "egodaction.h"
#include "elanguage.h"

enum class eGodAttackStage {
    none, appear, goTo1, patrol1, goTo2, patrol2, disappear
};

class eGodAttackAction : public eGodAction {
public:
    using eGodAction::eGodAction;

    void increment(const int by);
    bool decide();
private:

    bool lookForAttack(const int dtime, int& time,
                       const int freq, const int range);

    bool lookForGodAttack(const int dtime, int& time,
                          const int freq, const int range);
    void goToTarget();
    std::function<bool(eTile* const)> obsticleHandler();
    void destroyBuilding(eBuilding* const b);

    eGodAttackStage mStage{eGodAttackStage::none};

    int mLookForCurse = 0;
    int mLookForAttack = 0;
    int mLookForGod = 0;
};

class eGAA_loserDisappearFinish : public eCharActFunc {
public:
    eGAA_loserDisappearFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::GAA_loserDisappearFinish) {}
    eGAA_loserDisappearFinish(eGameBoard& board, eGodAction* const ca) :
        eCharActFunc(board, eCharActFuncType::GAA_loserDisappearFinish),
        mLoserPtr(ca) {}

    void call() override {
        if(!mLoserPtr) return;
        const auto t = mLoserPtr.get();
        const auto c = t->character();
        c->kill();
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mLoserPtr = static_cast<eGodAction*>(ca);
        });;
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mLoserPtr);
    }
private:
    stdptr<eGodAction> mLoserPtr;
};

class eGAA_fightFinish : public eCharActFunc {
public:
    eGAA_fightFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::GAA_fightFinish) {}
    eGAA_fightFinish(eGameBoard& board, eGodAction* const winnerA,
                     eGodAction* const loserA, const eGodType wt,
                     const eGodType lt) :
        eCharActFunc(board, eCharActFuncType::GAA_fightFinish),
        mWinnerPtr(winnerA), mLoserPtr(loserA),
        mWt(wt), mLt(lt) {}

    void call() override {
        if(mWinnerPtr) mWinnerPtr->resumeAction();
        if(mLoserPtr) {
            const auto finish = std::make_shared<eGAA_loserDisappearFinish>(
                                    board(), mLoserPtr);
            mLoserPtr->disappear(true, finish);
        }
        const auto wn = eGod::sGodName(mWt);
        const auto ln = eGod::sGodName(mLt);
        board().showTip(wn + eLanguage::text("overpowers") + ln);
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mWinnerPtr = static_cast<eGodAction*>(ca);
        });;
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mLoserPtr = static_cast<eGodAction*>(ca);
        });;
        src >> mWt;
        src >> mLt;
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mWinnerPtr);
        dst.writeCharacterAction(mLoserPtr);
        dst << mWt;
        dst << mLt;
    }
private:
    stdptr<eGodAction> mWinnerPtr;
    stdptr<eGodAction> mLoserPtr;
    eGodType mWt;
    eGodType mLt;
};

#endif // EGODATTACKACTION_H
