#include "echaracterbase.h"

eCharacterBase::eCharacterBase(const eCharacterType type) :
    mType(type) {

}

bool eCharacterBase::defend(const double a) {
    mHP -= a;
    return dead();
}

void eCharacterBase::setAttack(const double a) {
    mAttack = a;
}

void eCharacterBase::setHP(const double hp) {
    mHP = hp;
}

bool eCharacterBase::fighting() const {
    return mActionType == eCharacterActionType::fight;
}

void eCharacterBase::setActionType(const eCharacterActionType t) {
    mActionType = t;
}
