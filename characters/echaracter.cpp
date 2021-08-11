#include "echaracter.h"

#include "engine/egameboard.h"

#include "actions/edieaction.h"
#include "actions/efightaction.h"

eCharacter::eCharacter(eGameBoard& board) :
    mBoard(board) {
    mBoard.registerCharacter(this);
}

eCharacter::~eCharacter() {
    if(mAction) delete mAction;
    if(mTile) mTile->removeCharacter(this);
    mBoard.unregisterCharacter(this);
}

bool eCharacter::canFight(eCharacter* const c) {
    if(dead()) return false;
    if(playerId() == c->playerId()) return false;
    return true;
}

void eCharacter::fight(eCharacter* const c) {
    const auto a = takeAction();
    setAction(new eFightAction(this, c, [this, a]() {
        mFighting = false;
        if(dead()) {
            setAction(new eDieAction(this, [this]() { delete this; }));
            delete a;
        } else {
            setAction(a);
            a->resume();
        }
    }));
    mFighting = true;
}

void eCharacter::setTile(eTile* const t) {
    mTile = t;
}

void eCharacter::incTime(const int by) {
    mTime += by;
    if(mAction) mAction->increment(by);
}

void eCharacter::setOrientation(const eOrientation o) {
    mOrientation = o;
}

void eCharacter::setAction(eCharacterAction* const a) {
    mAction = a;
}

eCharacterAction* eCharacter::takeAction() {
    const auto a = mAction;
    mAction = nullptr;
    return a;
}

bool eCharacter::defend(const int a) {
    mHP -= a;
    return dead();
}

void eCharacter::setAttack(const int a) {
    mAttack = a;
}

void eCharacter::setHP(const int hp) {
    mHP = hp;
}
