#include "echaracter.h"

eCharacter::eCharacter() {

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
