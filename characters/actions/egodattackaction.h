#ifndef EGODATTACKACTION_H
#define EGODATTACKACTION_H

#include "egodaction.h"
#include "elanguage.h"
#include "walkable/eobsticlehandler.h"
#include "etilehelper.h"

enum class eGodAttackStage {
    none, appear, goTo1, patrol1, goTo2, patrol2, disappear
};

class eGodAttackAction : public eGodAction {
    friend class eGodObsticleHandler;
public:
    eGodAttackAction(eCharacter* const c);

    void increment(const int by) override;
    bool decide() override;

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;
private:
    void initialize();

    bool lookForAttack(const int dtime, int& time,
                       const int freq, const int range);
    bool lookForTargetedAttack(const int dtime, int& time,
                               const int freq, const int range);

    bool lookForGodAttack(const int dtime, int& time,
                          const int freq, const int range);
    void goToTarget();
    stdsptr<eObsticleHandler> obsticleHandler();
    void destroyBuilding(eBuilding* const b);

    eGodAttackStage mStage{eGodAttackStage::none};

    int mLookForCurse = rand() % 2000;
    int mLookForTargetedCurse = rand() % 2000;
    int mLookForAttack = rand() % 2000;
    int mLookForTargetedAttack = rand() % 2000;
    int mLookForGod = rand() % 2000;
    int mLookForSpecial = rand() % 2000;
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
        auto& board = this->board();
        if(mWinnerPtr) mWinnerPtr->resumeAction();
        if(mLoserPtr) {
            const auto loser = mLoserPtr->character();
            const auto loserGod = static_cast<eGod*>(loser);
            const auto att = loserGod->attitude();
            if(att == eGodAttitude::worshipped) {
                const auto type = loserGod->type();
                const auto s = board.sanctuary(type);
                if(s) s->setSpawnWait(20000);
            }
            const auto finish = std::make_shared<eGAA_loserDisappearFinish>(
                                    board, mLoserPtr);
            mLoserPtr->disappear(true, finish);
        }
        const auto tip = eGod::sFightResultString(mWt, mLt);
        board.showTip(tip);
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

class eGAA_destroyBuildingFinish : public eCharActFunc {
public:
    eGAA_destroyBuildingFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::GAA_destroyBuildingFinish) {}
    eGAA_destroyBuildingFinish(eGameBoard& board,
                               eGodAttackAction* const tptr,
                               eBuilding* const b) :
        eCharActFunc(board, eCharActFuncType::GAA_destroyBuildingFinish),
        mTptr(tptr), mBptr(b) {}

    void call() override {
        if(!mTptr) return;
        mTptr->resumeAction();
        if(!mBptr) return;
        mBptr->collapse();
        eSounds::playCollapseSound();
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eGodAttackAction*>(ca);
        });
        src.readBuilding(&board(), [this](eBuilding* const b) {
            mBptr = b;
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
        dst.writeBuilding(mBptr);
    }
private:
    stdptr<eGodAttackAction> mTptr;
    stdptr<eBuilding> mBptr;
};

class eTeleportFindFailFunc : public eFindFailFunc {
public:
    eTeleportFindFailFunc(eGameBoard& board) :
        eFindFailFunc(board, eFindFailFuncType::teleport) {}
    eTeleportFindFailFunc(eGameBoard& board, eGodAction* const ca) :
        eFindFailFunc(board, eFindFailFuncType::teleport),
        mTptr(ca) {}

    void call(eTile* const tile) {
        if(!mTptr) return;
        const auto c = mTptr->character();
        auto& board = c->getBoard();
        const auto r = eTileHelper::closestRoad(tile->x(), tile->y(), board);
        mTptr->teleport(r);
    }

    void read(eReadStream& src) {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eGodAction*>(ca);
        });
    }

    void write(eWriteStream& dst) const {
        dst.writeCharacterAction(mTptr);
    }
private:
    stdptr<eGodAction> mTptr;
};

class eGodObsticleHandler : public eObsticleHandler {
public:
    eGodObsticleHandler(eGameBoard& board) :
        eObsticleHandler(board, eObsticleHandlerType::god) {}
    eGodObsticleHandler(eGameBoard& board,
                        eGodAttackAction* const t) :
        eObsticleHandler(board, eObsticleHandlerType::god),
        mTptr(t) {}

    bool handle(eTile* const tile) override {
        if(!mTptr) return false;
        const auto ub = tile->underBuilding();
        if(!ub) return false;
        const auto ubt = ub->type();
        const bool r = eBuilding::sWalkableBuilding(ubt);
        if(r) return false;
        mTptr->destroyBuilding(ub);
        return true;
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eGodAttackAction*>(ca);
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
    }
private:
    stdptr<eGodAttackAction> mTptr;
};

#endif // EGODATTACKACTION_H
