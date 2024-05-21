#ifndef EGODACTION_H
#define EGODACTION_H

#include "egodmonsteraction.h"

#include "characters/gods/egod.h"
#include "engine/egameboard.h"
#include "audio/esounds.h"

class eDestructionTextures;
enum class eGodSound;

enum class eGodActType {
    lookForSoldierAttack,
    lookForBless,
    playMonsterBuildingAttackSound,
    playFightGodHitSoundGodAct,
    lookForAttack,

    provideResource,
    provideAgora,
    provideDrachmas,
    atlasHelp,
    apolloHelp
};

class eGodAct {
public:
    eGodAct(eGameBoard& board, const eGodActType type) :
        mType(type), mBoard(board) {}

    virtual eTile* find(eTile* const t) = 0;
    virtual void act() = 0;

    eGodActType type() const { return mType; }
    eGameBoard& board() { return mBoard; }

    virtual void read(eReadStream& src) = 0;
    virtual void write(eWriteStream& dst) const = 0;

    static stdsptr<eGodAct> sCreate(eGameBoard& board, const eGodActType t);
private:
    const eGodActType mType;
    eGameBoard& mBoard;
};

class ePlayMonsterBuildingAttackSoundGodAct : public eGodAct {
public:
    ePlayMonsterBuildingAttackSoundGodAct(
            eGameBoard& board, eBuilding* const b) :
        eGodAct(board, eGodActType::playMonsterBuildingAttackSound),
        mBuilding(b) {}
    ePlayMonsterBuildingAttackSoundGodAct(eGameBoard& board) :
        ePlayMonsterBuildingAttackSoundGodAct(board, nullptr) {}

    eTile* find(eTile* const t) {
        (void)t;
        return nullptr;
    }

    void act() {
        if(!mBuilding) return;
        const auto b = mBuilding.get();
        auto& board = b->getBoard();
        board.ifVisible(b->centerTile(), [&]() {
            eSounds::playFireballHitSound();
        });
    }

    void read(eReadStream& src) {
        src.readBuilding(&board(), [this](eBuilding* const b) {
            mBuilding = b;
        });
    }

    void write(eWriteStream& dst) const {
        dst.writeBuilding(mBuilding);
    }
private:
    stdptr<eBuilding> mBuilding;
};

class ePlayFightGodHitSoundGodAct : public eGodAct {
public:
    ePlayFightGodHitSoundGodAct(eGameBoard& board, eGod* const g) :
        eGodAct(board, eGodActType::playFightGodHitSoundGodAct),
        mG(g) {}
    ePlayFightGodHitSoundGodAct(eGameBoard& board) :
        ePlayFightGodHitSoundGodAct(board, nullptr) {}

    eTile* find(eTile* const t) {
        (void)t;
        return nullptr;
    }

    void act() {
        if(!mG) return;
        board().ifVisible(mG->tile(), [&]() {
            eSounds::playGodSound(mG->type(), eGodSound::hit);
        });
    }

    void read(eReadStream& src) {
        src.readCharacter(&board(), [this](eCharacter* const g) {
            mG = static_cast<eGod*>(g);
        });
    }

    void write(eWriteStream& dst) const {
        dst.writeCharacter(mG);
    }
private:
    stdptr<eGod> mG;
};

class eLookForBlessGodAct : public eGodAct {
public:
    eLookForBlessGodAct(eGameBoard& board, const double bless) :
        eGodAct(board, eGodActType::lookForBless),
        mBless(bless) {}
    eLookForBlessGodAct(eGameBoard& board) :
        eLookForBlessGodAct(board, 0) {}

    eTile* find(eTile* const t) {
        const auto b = t->underBuilding();
        if(!b) return nullptr;
        if(!eBuilding::sBlessable(b->type())) return nullptr;
        if(b->blessed() || b->cursed()) return nullptr;
        mTarget = b;
        return b->centerTile();
    }

    void act() {
        if(mTarget) mTarget->setBlessed(mBless);
    }

    void read(eReadStream& src) {
        src.readBuilding(&board(), [this](eBuilding* const b) {
            mTarget = b;
        });
        src >> mBless;
    }

    void write(eWriteStream& dst) const {
        dst.writeBuilding(mTarget);
        dst << mBless;
    }
private:
    stdptr<eBuilding> mTarget;
    double mBless = 0;
};

class eLookForSoldierAttackGodAct : public eGodAct {
public:
    eLookForSoldierAttackGodAct(eGameBoard& board) :
        eGodAct(board, eGodActType::lookForSoldierAttack) {}

    eTile* find(eTile* const t) {
        const auto& chars = t->characters();
        if(chars.empty()) return nullptr;
        for(const auto& cc : chars) {
            const bool is = cc->isSoldier();
            if(!is) continue;
            const int pid = cc->playerId();
            if(pid == 1) continue;
            mTarget = cc;
            return t;
        }
        return nullptr;
    }

    void act() {
        if(mTarget) mTarget->killWithCorpse();
    }

    void read(eReadStream& src) {
        src.readCharacter(&board(), [this](eCharacter* const c) {
            mTarget = c;
        });
    }

    void write(eWriteStream& dst) const {
        dst.writeCharacter(mTarget);
    }
private:
    stdptr<eCharacter> mTarget;
};

class eLookForAttackGodAct : public eGodAct {
public:
    eLookForAttackGodAct(eGameBoard& board) :
        eGodAct(board, eGodActType::lookForAttack) {}
    eLookForAttackGodAct(eGameBoard& board, eCharacter* const c) :
        eGodAct(board, eGodActType::lookForAttack),
        mCptr(c) {}

    eTile* find(eTile* const t) {
        if(!mCptr) return nullptr;
        if(mCptr->tile() == t) return nullptr;
        const auto b = t->underBuilding();
        if(b && eBuilding::sAttackable(b->type())) {
            mBTarget = b;
            return b->centerTile();
        } else {
            const auto& chars = t->characters();
            if(chars.empty()) return nullptr;
            for(const auto& cc : chars) {
                if(mCptr == cc.get()) continue;
                bool isGod = false;
                eGod::sCharacterToGodType(cc->type(), &isGod);
                if(isGod) continue;
                bool isMonster = false;
                eMonster::sCharacterToMonsterType(cc->type(), &isMonster);
                if(isMonster) continue;
                bool isHero = false;
                eHero::sCharacterToHeroType(cc->type(), &isHero);
                if(isHero) continue;
                mCTarget = cc;
                return t;
            }
            return nullptr;
        }
    }

    void act() {
        if(!mCptr) return;
        if(mBTarget) {
            mBTarget->collapse();
            eSounds::playCollapseSound();
        } else if(mCTarget) {
            mCTarget->killWithCorpse();
        }
    }

    void read(eReadStream& src) {
        src.readCharacter(&board(), [this](eCharacter* const c) {
            mCptr = c;
        });
        src.readCharacter(&board(), [this](eCharacter* const c) {
            mCTarget = c;
        });
        src.readBuilding(&board(), [this](eBuilding* const b) {
            mBTarget = b;
        });
    }

    void write(eWriteStream& dst) const {
        dst.writeCharacter(mCptr);
        dst.writeCharacter(mCTarget);
        dst.writeBuilding(mBTarget);
    }
private:
    stdptr<eCharacter> mCptr;
    stdptr<eCharacter> mCTarget;
    stdptr<eBuilding> mBTarget;
};

class eGodAction : public eGodMonsterAction {
public:
    eGodAction(eCharacter* const c, const eCharActionType type);

    void appear();
    void disappear(const bool die = false,
                   const stdsptr<eCharActFunc>& finish = nullptr);
    void teleport(eTile* const tile);

    void randomPlaceOnBoard();

    using eTexPtr = eTextureCollection eDestructionTextures::*;
    bool lookForRangeAction(const int dtime,
                            int& time, const int freq,
                            const int range,
                            const eCharacterActionType at,
                            const stdsptr<eGodAct>& act,
                            const eCharacterType chart,
                            const eGodSound missileSound);
    bool lookForBlessCurse(const int dtime, int& time,
                           const int freq, const int range,
                           const double bless);

    bool lookForSoldierAttack(const int dtime, int& time,
                              const int freq, const int range);

    void spawnGodMissile(const eCharacterActionType at,
                         const eCharacterType chart,
                         eTile* const target,
                         const eGodSound sound,
                         const stdsptr<eGodAct>& act,
                         const stdsptr<eCharActFunc>& finishAttackA = nullptr);
    void spawnGodMultipleMissiles(
            const eCharacterActionType at,
            const eCharacterType chart,
            eTile* const target,
            const eGodSound sound,
            const stdsptr<eGodAct>& playHitSound,
            const stdsptr<eCharActFunc>& finishA,
            const int nMissiles);
    void spawnGodTimedMissiles(const eCharacterActionType at,
            const eCharacterType chart,
            eTile* const target,
            const eGodSound sound,
            const stdsptr<eGodAct>& playHitSound,
            const stdsptr<eCharActFunc>& finishA,
            const int time);

    void fightGod(eGod* const g, const stdsptr<eCharActFunc>& finishAttackA);

    void goBackToSanctuary();
    void goToTarget();

    eGodType type() const { return mType; }

    void playAppearSound();
    void playDisappearSound();
private:
    void hermesRun(const bool appear);

    const eGodType mType;
};

class eGA_lookForSoldierAttackFinish : public eCharActFunc {
public:
    eGA_lookForSoldierAttackFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::GA_lookForSoldierAttackFinish) {}
    eGA_lookForSoldierAttackFinish(eGameBoard& board, eGodAction* const ca,
                                   eTile* const tile) :
        eCharActFunc(board, eCharActFuncType::GA_lookForSoldierAttackFinish),
        mTptr(ca), mTile(tile) {}

    void call() override {
        if(!mTptr) return;
        const auto t = mTptr.get();
        const auto c = t->character();
        c->changeTile(mTile);
        t->appear();
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eGodAction*>(ca);
        });
        mTile = src.readTile(board());
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
        dst.writeTile(mTile);
    }
private:
    stdptr<eGodAction> mTptr;
    eTile* mTile = nullptr;
};

class eGA_lookForRangeActionFinish : public eCharActFunc {
public:
    eGA_lookForRangeActionFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::GA_lookForRangeActionFinish) {}
    eGA_lookForRangeActionFinish(eGameBoard& board, eGodAction* const ca) :
        eCharActFunc(board, eCharActFuncType::GA_lookForRangeActionFinish),
        mTptr(ca) {}

    void call() override {
        if(!mTptr) return;
        mTptr->resumeAction();
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eGodAction*>(ca);
        });
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
    }
private:
    stdptr<eGodAction> mTptr;
};

class eGA_teleportFinish : public eCharActFunc {
public:
    eGA_teleportFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::GA_teleportFinish) {}
    eGA_teleportFinish(eGameBoard& board, eGodAction* const ca,
                       eTile* const tile) :
        eCharActFunc(board, eCharActFuncType::GA_teleportFinish),
        mTptr(ca), mTile(tile) {}

    void call() override {
        if(!mTptr) return;
        const auto t = mTptr.get();
        const auto c = t->character();
        c->changeTile(mTile);
        t->appear();
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eGodAction*>(ca);
        });
        mTile = src.readTile(board());
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
        dst.writeTile(mTile);
    }
private:
    stdptr<eGodAction> mTptr;
    eTile* mTile = nullptr;
};

class eGA_hermesRunFinish : public eCharActFunc {
public:
    eGA_hermesRunFinish(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::GA_hermesRunFinish) {}
    eGA_hermesRunFinish(eGameBoard& board, eGodAction* const ca,
                        eCharacter* const c, const bool appear) :
        eCharActFunc(board, eCharActFuncType::GA_hermesRunFinish),
        mTptr(ca), mCptr(c), mAppear(appear) {}

    void call() override {
        if(!mTptr || !mCptr) return;
        const auto t = mTptr.get();
        mCptr->setSpeed(1.);
        if(!mAppear) t->playDisappearSound();
    }

    void read(eReadStream& src) override {
        src.readCharacterAction(&board(), [this](eCharacterAction* const ca) {
            mTptr = static_cast<eGodAction*>(ca);
        });
        src.readCharacter(&board(), [this](eCharacter* const c) {
            mCptr = c;
        });

        src >> mAppear;
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacterAction(mTptr);
        dst.writeCharacter(mCptr);

        dst << mAppear;
    }
private:
    stdptr<eGodAction> mTptr;
    stdptr<eCharacter> mCptr;
    bool mAppear;
};

class eGA_spawnGodMissilePlaySound : public eCharActFunc {
public:
    eGA_spawnGodMissilePlaySound(eGameBoard& board) :
        eCharActFunc(board, eCharActFuncType::GA_spawnGodMissilePlaySound) {}
    eGA_spawnGodMissilePlaySound(eGameBoard& board, const eGodSound sound,
                                 eCharacter* const c) :
        eCharActFunc(board, eCharActFuncType::GA_spawnGodMissilePlaySound),
        mCptr(c), mSound(sound) {}

    void call() override {
        if(!mCptr) return;
        const auto c = mCptr.get();
        board().ifVisible(c->tile(), [&]() {
            const auto ct = c->type();
            const auto gt = eGod::sCharacterToGodType(ct);
            eSounds::playGodSound(gt, mSound);
        });
    }

    void read(eReadStream& src) override {
        src.readCharacter(&board(), [this](eCharacter* const c) {
            mCptr = c;
        });

        src >> mSound;
    }

    void write(eWriteStream& dst) const override {
        dst.writeCharacter(mCptr);

        dst << mSound;
    }
private:
    stdptr<eCharacter> mCptr;
    eGodSound mSound;
};

class eGoToTargetTeleport : public eFindFailFunc {
public:
    eGoToTargetTeleport(eGameBoard& board) :
        eFindFailFunc(board, eFindFailFuncType::teleport2) {}
    eGoToTargetTeleport(eGameBoard& board, eGodAction* const ca) :
        eFindFailFunc(board, eFindFailFuncType::teleport2),
        mTptr(ca) {}

    void call(eTile* const tile) {
        if(!mTptr) return;
        mTptr->teleport(tile);
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

#endif // EGODACTION_H
