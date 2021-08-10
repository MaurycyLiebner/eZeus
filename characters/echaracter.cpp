#include "echaracter.h"

#include "engine/egameboard.h"

eCharacter::eCharacter(eGameBoard& board) :
    mBoard(board) {
    mBoard.registerCharacter(this);
}

eCharacter::~eCharacter() {
    if(mTile) mTile->removeCharacter(this);
    mBoard.unregisterCharacter(this);
}

void eCharacter::setTile(eTile* const t) {
    mTile = t;
}

void eCharacter::incTime(const int by) {
    mTime += by;
    if(mCharAction) mCharAction->increment(by);
}

void eCharacter::setOrientation(const eOrientation o) {
    mOrientation = o;
}

void eCharacter::setCharAction(eCharacterAction* const a) {
    mCharAction = a;
}
