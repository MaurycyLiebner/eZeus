#include "echaracter.h"

#include "engine/egameboard.h"

#include "actions/edieaction.h"
#include "actions/efightaction.h"
#include "actions/earcheraction.h"

#include "gods/egod.h"
#include "heroes/ehero.h"
#include "audio/esounds.h"

#include "esoldier.h"

eCharacter::eCharacter(eGameBoard& board,
                       const eCharacterType type) :
    eObject(board), eCharacterBase(type) {
    getBoard().registerCharacter(this);
}

eCharacter::~eCharacter() {
    getBoard().unregisterCharacter(this);
}

bool eCharacter::canFight(eCharacter* const c) {
    if(dead()) return false;
    if(playerId() == c->playerId()) return false;
    if(attack() == 0 && c->attack() == 0) return false;
    const auto at = actionType();
    if(at == eCharacterActionType::fight ||
       at == eCharacterActionType::fight2) return false;
    const auto ct = c->type();
    const auto t = type();
    if(t == eCharacterType::disgruntled) {
        if(ct == eCharacterType::watchman) return true;
        else if(rand() % 10) return false;
    }
    if(ct == eCharacterType::boar ||
       ct == eCharacterType::deer) {
        const bool h = t == eCharacterType::hunter;
        if(!h) return false;
        return at != eCharacterActionType::carry;
    }
    bool isGod;
    eGod::sCharacterToGodType(t, &isGod);
    if(isGod) return false;
    bool isHero = false;
    eHero::sCharacterToHeroType(t, &isHero);
    if(isHero) return false;
    bool isMonster1;
    eMonster::sCharacterToMonsterType(t, &isMonster1);
    bool isMonster2;
    eMonster::sCharacterToMonsterType(ct, &isMonster2);
    if(isMonster1 && isMonster2) return false;
    return true;
}

void eCharacter::provideToBuilding(eBuilding* const b) {
    const int r = b->provide(mProvide, mProvideCount);
    mProvideCount -= r;
}

void eCharacter::fight(eCharacter* const c) {
    pauseAction();
    const auto ff = std::make_shared<eChar_fightFinish>(
                        getBoard(), this);
    const auto fa = e::make_shared<eFightAction>(this, c);
    fa->setFailAction(ff);
    fa->setFinishAction(ff);
    setAction(fa);
}

void eCharacter::kill() {
    changeTile(nullptr);
}

void eCharacter::killWithCorpse() {
    beingKilled();
    const stdptr<eCharacter> c(this);
    const auto finish = std::make_shared<eChar_killWithCorpseFinish>(
                            getBoard(), this);
    auto& board = getBoard();
    board.ifVisible(tile(), [&]() {
        eSounds::playDieSound(this);
    });
    const auto a = e::make_shared<eDieAction>(this);
    a->setFailAction(finish);
    a->setFinishAction(finish);
    setAction(a);
}

double eCharacter::absX() const {
    if(!mTile) return mX;
    return mX + mTile->x();
}

double eCharacter::absY() const {
    if(!mTile) return mY;
    return mY + mTile->y();
}

void eCharacter::changeTile(eTile* const t, const bool prepend) {
    const auto tsptr = ref<eCharacter>();
    if(mTile) mTile->removeCharacter(tsptr);
    mTile = t;
    if(t) t->addCharacter(tsptr, prepend);
    else deleteLater();
    if(t && mProvide != eProvide::none && mProvideCount > 0) {
        for(const int x : {-1, 0, 1}) {
            for(const int y : {-1, 0, 1}) {
                const auto tt = t->tileRel<eTile>(x, y);
                if(!tt) continue;
                if(const auto b = tt->underBuilding()) {
                    provideToBuilding(b);
                    if(mProvideCount <= 0) return;
                }
            }
        }
    }
}

void eCharacter::incTime(const int by) {
    mTime += by;
    const auto at = actionType();
    if(at == eCharacterActionType::fight ||
       at == eCharacterActionType::fight2) {
        mSoundPlayTime += by;
        const int soundPlayTime = 500;
        if(mSoundPlayTime > soundPlayTime) {
            mSoundPlayTime -= soundPlayTime;
            auto& board = getBoard();
            board.ifVisible(tile(), [&]() {
                if(rand() % 2) {
                    eSounds::playHitSound(this);
                } else {
                    eSounds::playAttackSound(this);
                }
            });
        }
    }
    if(mAction) {
        if(mAction->state() != eCharacterActionState::running) {
            mAction.reset();
            changeTile(nullptr);
        } else {
            mAction->increment(by);
        }
    } else {
        changeTile(nullptr);
    }
}

void eCharacter::setOrientation(const eOrientation o) {
    mOrientation = o;
}

void eCharacter::setAction(const stdsptr<eCharacterAction>& a) {
    mAction = a;
}

void eCharacter::setActionType(const eCharacterActionType t) {
    mActionStartTime = textureTime();
    eCharacterBase::setActionType(t);
}

void eCharacter::setHasSecondaryTexture(const bool st) {
    mHasSecondaryTexture = st;
}

void eCharacter::setProvide(const eProvide p, const int n) {
    mProvide = p;
    mProvideCount = n;
}

bool eCharacter::isSoldier() const {
    const auto t = type();
    const int min = static_cast<int>(eCharacterType::rockThrower);
    const int max = static_cast<int>(eCharacterType::greekHorseman);
    const int bi = static_cast<int>(t);
    if(bi >= min && bi <= max) return true;
    return false;
}

bool eCharacter::defend(const double a) {
    if(dead()) return true;

    bool isMonster = false;
    eMonster::sCharacterToMonsterType(type(), &isMonster);
    if(isMonster) return false;
    bool isGod = false;
    eGod::sCharacterToGodType(type(), &isGod);
    if(isGod) return false;
    bool isHero = false;
    eHero::sCharacterToHeroType(type(), &isHero);
    if(isHero) return false;

    setHP(hp() - a);
    if(hp() <= 0) {
        killWithCorpse();
        return true;
    } else {
        return false;
    }
    return dead();
}

void eCharacter::pauseAction() {
    const auto ca = mAction;
    if(!ca) return;
    auto& p = mPausedActions.emplace_back();
    p.fA = ca->ref<eCharacterAction>();
    p.fAt = actionType();
    p.fO = orientation();
}

void eCharacter::resumeAction() {
    if(mPausedActions.empty()) return;
    const auto p = mPausedActions.back();
    mPausedActions.pop_back();
    setAction(p.fA);
    setActionType(p.fAt);
}

void eCharacter::read(eReadStream& src) {
    eCharacterBase::read(src);
    src >> mIOID;
    src >> mVisible;
    src >> mProvide;
    src >> mProvideCount;
    const auto tile = src.readTile(getBoard());
    changeTile(tile);
    src >> mOrientation;
    src >> mX;
    src >> mY;
    src >> mSoundPlayTime;
    src >> mTime;
    src >> mHasSecondaryTexture;
    bool hasAction;
    src >> hasAction;
    if(hasAction) {
        eCharActionType type;
        src >> type;
        mAction = eCharacterAction::sCreate(this, type);
        mAction->read(src);
    }
    src >> mActionStartTime;

    int s;
    src >> s;
    for(int i = 0; i < s; i++) {
        auto& a = mPausedActions.emplace_back();
        src >> a.fAt;
        bool hasAction;
        src >> hasAction;
        if(hasAction) {
            eCharActionType type;
            src >> type;
            a.fA = eCharacterAction::sCreate(this, type);
            a.fA->read(src);
        }
        src >> a.fO;
    }
}

void eCharacter::write(eWriteStream& dst) const {
    eCharacterBase::write(dst);
    dst << mIOID;
    dst << mVisible;
    dst << mProvide;
    dst << mProvideCount;
    dst.writeTile(mTile);
    dst << mOrientation;
    dst << mX;
    dst << mY;
    dst << mSoundPlayTime;
    dst << mTime;
    dst << mHasSecondaryTexture;
    dst << (mAction != nullptr);
    if(mAction) {
        dst << mAction->type();
        mAction->write(dst);
    }
    dst << mActionStartTime;

    dst << mPausedActions.size();
    for(const auto& a : mPausedActions) {
        dst << a.fAt;
        dst << (a.fA != nullptr);
        if(a.fA) {
            dst << a.fA->type();
            a.fA->write(dst);
        }
        dst << a.fO;
    }
}
