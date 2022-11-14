#include "echaracterbase.h"

#include "actions/edieaction.h"

eCharacterBase::eCharacterBase(const eCharacterType type) :
    mType(type) {

}

void eCharacterBase::setAttack(const double a) {
    mAttack = a;
}

void eCharacterBase::setHP(const double hp) {
    mHP = hp;
}

bool eCharacterBase::fighting() const {
    return mActionType == eCharacterActionType::fight ||
           mActionType == eCharacterActionType::fight2;
}

void eCharacterBase::setActionType(const eCharacterActionType t) {
    mActionType = t;
}

void eCharacterBase::read(eReadStream& src) {
    src >> mActionType;
    src >> mPlayerId;
    src >> mBusy;
    src >> mHP;
    src >> mAttack;
    src >> mSpeed;
}

void eCharacterBase::write(eWriteStream& dst) const {
    dst << mActionType;
    dst << mPlayerId;
    dst << mBusy;
    dst << mHP;
    dst << mAttack;
    dst << mSpeed;
}
