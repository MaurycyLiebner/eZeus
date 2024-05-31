#include "echaracterbase.h"

#include "actions/edieaction.h"

#include "gods/egod.h"
#include "heroes/ehero.h"
#include "monsters/emonster.h"

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

bool eCharacterBase::isSoldier() const {
    const auto t = type();
    const int min = static_cast<int>(eCharacterType::rockThrower);
    const int max = static_cast<int>(eCharacterType::greekHorseman);
    const int bi = static_cast<int>(t);
    if(bi >= min && bi <= max) return true;
    return false;
}

bool eCharacterBase::isGod() const {
    bool result;
    eGod::sCharacterToGodType(type(), &result);
    return result;
}

bool eCharacterBase::isHero() const {
    bool result;
    eHero::sCharacterToHeroType(type(), &result);
    return result;
}

bool eCharacterBase::isMonster() const {
    bool result;
    eMonster::sCharacterToMonsterType(type(), &result);
    return result;
}

bool eCharacterBase::isImmortal() const {
    return isGod() || isHero() || isMonster();
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
