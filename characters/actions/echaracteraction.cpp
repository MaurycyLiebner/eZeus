#include "echaracteraction.h"

eCharacterAction::eCharacterAction(eCharacter* const d) :
    mCharacter(d) {

}

void eCharacterAction::setState(const eCharacterActionState state) {
    mState = state;
}
