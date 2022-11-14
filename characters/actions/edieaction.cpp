#include "edieaction.h"

#include "characters/echaracter.h"

eDieAction::eDieAction(eCharacter* const c) :
    eCharacterAction(c, eCharActionType::dieAction) {
    const auto aType = c->actionType();
    if(aType != eCharacterActionType::none) {
        c->setActionType(eCharacterActionType::die);
    }
}

void eDieAction::increment(const int by) {
    mTime += by;
    if(mTime > 1024) setState(eCharacterActionState::finished);
}

void eDieAction::read(eReadStream& src) {
    eCharacterAction::read(src);
    src >> mTime;
}

void eDieAction::write(eWriteStream& dst) const {
    eCharacterAction::write(dst);
    dst << mTime;
}
