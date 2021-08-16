#include "echaracterbase.h"

eCharacterBase::eCharacterBase(const eCharacterType type) :
    mType(type) {

}

bool eCharacterBase::defend(const int a) {
    mHP -= a;
    return dead();
}

void eCharacterBase::setAttack(const int a) {
    mAttack = a;
}

void eCharacterBase::setHP(const int hp) {
    mHP = hp;
}

bool eCharacterBase::fighting() const {
    return mActionType == eCharacterActionType::fight;
}

void eCharacterBase::setActionType(const eCharacterActionType t) {
    mActionType = t;
}
