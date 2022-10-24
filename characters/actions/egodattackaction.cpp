#include "egodattackaction.h"

#include "buildings/ebuilding.h"
#include "textures/edestructiontextures.h"
#include "esounds.h"

void eGodAttackAction::increment(const int by) {
    const int lookForCurseCheck = 6000;
    const int lookForAttackCheck = 8000;

    const bool r = lookForBlessCurse(by, mLookForCurse, lookForCurseCheck, 10, -1);
    if(!r) lookForAttack(by, mLookForAttack, lookForAttackCheck, 10);

    eGodAction::increment(by);
}

eGodAction::eTexPtr godMissile(const eGodType gt) {
    switch(gt) {
    case eGodType::aphrodite:
        return &eDestructionTextures::fGodBlueMissile;
    case eGodType::apollo:
        return &eDestructionTextures::fGodOrangeArrow;
    case eGodType::ares:
        return &eDestructionTextures::fGodOrangeMissile;
    case eGodType::artemis:
        return &eDestructionTextures::fGodBlueArrow;
    case eGodType::athena:
        return &eDestructionTextures::fGodRedMissile;
    case eGodType::atlas:
        return &eDestructionTextures::fGodPinkMissile;
    case eGodType::demeter:
        return &eDestructionTextures::fGodGreenMissile;
    case eGodType::dionysus:
        return &eDestructionTextures::fGodPurpleMissile;
    case eGodType::hades:
        return &eDestructionTextures::fGodOrangeMissile;
    case eGodType::hephaestus:
        return &eDestructionTextures::fGodOrangeMissile;
    case eGodType::hera:
        return &eDestructionTextures::fGodRedMissile;
    case eGodType::hermes:
        return &eDestructionTextures::fGodBlueMissile;
    case eGodType::poseidon:
        return &eDestructionTextures::fGodBlueMissile;
    case eGodType::zeus:
        return &eDestructionTextures::fGodBlueMissile;
    }
    return nullptr;
}

bool eGodAttackAction::lookForAttack(const int dtime,
                                     int& time, const int freq,
                                     const int range) {
    const auto cptr = stdptr<eCharacter>(character());
    const auto act = [cptr](eTile* const t) {
        const auto null = static_cast<eTile*>(nullptr);
        if(!cptr) return null;
        if(cptr->tile() == t) return null;
        const auto b = t->underBuilding();
        if(b && eBuilding::sAttackable(b->type())) {
            return b->centerTile();
        } else {
            const auto& chars = t->characters();
            if(chars.empty()) return null;
            return t;
        }
    };

    const auto finishA = [cptr](eTile* const target) {
        if(!cptr) return;
        const auto b = target->underBuilding();
        if(b && eBuilding::sAttackable(b->type())) {
            b->collapse();
            eSounds::playCollapseSound();
        } else {
            const auto& chars = target->characters();
            if(chars.empty()) return;
            const auto chr = chars.front();
            if(cptr != chr.get()) chr->kill();
        }
    };
    const auto at = eCharacterActionType::fight;
    const auto s = eGodSound::attack;
    const auto tex = godMissile(type());

    return lookForRangeAction(dtime, time, freq, range,
                              at, act, tex, s, finishA);
}

bool eGodAttackAction::decide() {
    const auto c = character();
    switch(mStage) {
    case eGodAttackStage::none:
        mStage = eGodAttackStage::appear;
        randomPlaceOnBoard();
        if(!c->tile()) {
            c->kill();
        } else {
            appear();
        }
        break;
    case eGodAttackStage::appear:
        mStage = eGodAttackStage::goTo1;
        goToTarget();
        break;
    case eGodAttackStage::goTo1: {
        mStage = eGodAttackStage::patrol1;
        const auto tile = c->tile();
        if(tile->hasRoad()) patrol();
        else moveAround();
    }   break;
    case eGodAttackStage::patrol1:
        mStage = eGodAttackStage::goTo2;
        goToTarget();
        break;
    case eGodAttackStage::goTo2: {
        mStage = eGodAttackStage::patrol2;
        const auto tile = c->tile();
        if(tile->hasRoad()) patrol();
        else moveAround();
    }   break;
    case eGodAttackStage::patrol2:
        mStage = eGodAttackStage::disappear;
        disappear();
        break;
    case eGodAttackStage::disappear:
        c->kill();
        break;
    }
    return true;
}
