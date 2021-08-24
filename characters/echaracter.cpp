#include "echaracter.h"

#include "engine/egameboard.h"

#include "actions/edieaction.h"
#include "actions/efightaction.h"

eCharacter::eCharacter(eGameBoard& board, const eCharacterType type) :
    eCharacterBase(type), mBoard(board) {
    mBoard.registerCharacter(this);
}

eCharacter::~eCharacter() {
    if(mAction) delete mAction;
    changeTile(nullptr);
    mBoard.unregisterCharacter(this);
}

bool eCharacter::canFight(eCharacter* const c) {
    if(dead()) return false;
    if(playerId() == c->playerId()) return false;
    return true;
}

void eCharacter::fight(eCharacter* const c) {
    const auto a = takeAction();
    a->pause();
    setAction(new eFightAction(this, c, [this, a]() {
        if(dead()) {
            setAction(new eDieAction(this, [this]() { delete this; }));
            a->setState(eCharacterActionState::failed);
            delete a;
        } else {
            setAction(a);
            a->resume();
        }
    }));
}

void eCharacter::changeTile(eTile* const t) {
    if(mTile) mTile->removeCharacter(this);
    mTile = t;
    if(mTile) mTile->addCharacter(this);
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

void eCharacter::setActionType(const eCharacterActionType t) {
    mActionStartTime = textureTime();
    eCharacterBase::setActionType(t);
}

void eCharacter::setHasSecondaryTexture(const bool st) {
    mHasSecondaryTexture = st;
}
