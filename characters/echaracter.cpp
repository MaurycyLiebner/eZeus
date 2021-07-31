#include "echaracter.h"

eCharacter::eCharacter() {

}

void eCharacter::setTile(eTile* const t) {
    mTile = t;
}

void eCharacter::incTime() {
    mTime++;
    if(mCharAction) mCharAction->increment();
}

void eCharacter::setOrientation(const eOrientation o) {
    mOrientation = o;
}

void eCharacter::setCharAction(eCharacterAction* const a) {
    mCharAction = a;
}
