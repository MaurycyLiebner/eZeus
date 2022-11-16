#ifndef EACTIONWITHCOMEBACK_H
#define EACTIONWITHCOMEBACK_H

#include "ecomplexaction.h"
#include "emovepathaction.h"
#include "engine/emovedirection.h"
#include "walkable/ewalkableobject.h"

#include <SDL2/SDL_rect.h>

class eBuilding;

using eWalkable = std::function<bool(eTileBase*)>;

class eActionWithComeback : public eComplexAction {
    friend class eAWC_goBackFail;
public:
    eActionWithComeback(eCharacter* const c,
                        const eCharActionType type);
    eActionWithComeback(eCharacter* const c,
                        eTile* const startTile,
                        const eCharActionType type);

    bool decide() override;

    void setFinishOnComeback(const bool b)
    { mFinishOnComeback = b; }

    void read(eReadStream& src) override;
    void write(eWriteStream& dst) const override;

    void goBack(const stdsptr<eWalkableObject>& walkable);
    void goBack(eBuilding* const b,
                const stdsptr<eWalkableObject>& walkable);
    void goBack(const SDL_Rect& rect,
                const stdsptr<eWalkableObject>& walkable);

    eTile* startTile() const { return mStartTile; }
private:
    void teleportDecision();

    eTile* mStartTile = nullptr;

    SDL_Rect mGoBackRect{0, 0, 0, 0};

    bool mFinishOnComeback = false;
    bool mDefaultTry = false;
    bool mGoBackFail = false;
};

class eAWC_goBackFail : public eCharActFunc {
public:
    eAWC_goBackFail(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::AWC_goBackFail) {}
    eAWC_goBackFail(eGameBoard& board,
                    eActionWithComeback* const t,
                    const stdsptr<eWalkableObject>& walkable) :
        eCharActFunc(board, eCharActFuncType::AWC_goBackFail),
        mTptr(t), mWalkable(walkable) {}

    void call() override {
        if(!mTptr) return;
        const auto t = mTptr.get();
        t->goBack(mWalkable);
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eActionWithComeback*>(ca);
        });
        mWalkable = src.readWalkable();
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
        dst.writeWalkable(mWalkable.get());
    }
private:
    stdptr<eActionWithComeback> mTptr;
    stdsptr<eWalkableObject> mWalkable;
};

class eAWC_goBackFinish : public eCharActFunc {
public:
    eAWC_goBackFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::AWC_goBackFinish) {}
    eAWC_goBackFinish(eGameBoard& board, eActionWithComeback* const t) :
        eCharActFunc(board, eCharActFuncType::AWC_goBackFinish),
        mTptr(t) {}

    void call() override {
        if(!mTptr) return;
        const auto t = mTptr.get();
        t->setState(eCharacterActionState::finished);
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eActionWithComeback*>(ca);
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
    }
private:
    stdptr<eActionWithComeback> mTptr;
};

#endif // EACTIONWITHCOMEBACK_H
