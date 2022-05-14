﻿#include "eshepherdaction.h"

#include "characters/esheep.h"
#include "characters/egoat.h"

#include "ewaitaction.h"
#include "emovetoaction.h"

eShepherdAction::eShepherdAction(eShepherBuildingBase* const shed,
        eResourceCollectorBase* const c,
        const eCharacterType animalType,
        const eAction& failAction,
        const eAction& finishAction) :
    eActionWithComeback(c, failAction, finishAction),
    mAnimalType(animalType),
    mCharacter(c),
    mShed(shed) {}

bool hasAnimal(eTileBase* const tile, const eCharacterType type) {
    return tile->hasCharacter([&type](const eCharacterBase& c) {
        if(rand() % 2) return false;
        return c.type() == type && !c.busy();
    });
}

enum class eCollectType {
    groom,
    collect
};

eDomesticatedAnimal* tryToCollect(eTile* const tile,
                                  const eCharacterType type,
                                  eCollectType& collType) {
    const auto cs = tile->characters();
    for(const auto& c : cs) {
        const auto t = c->type();
        if(t != type) continue;
        const auto s = static_cast<eDomesticatedAnimal*>(c.get());
        if(s->busy()) return nullptr;
        if(s->canCollect()) {
            collType = eCollectType::collect;
        } else {
            collType = eCollectType::groom;
        }
        return s;
    }
    return nullptr;
}

bool eShepherdAction::decide() {
    const bool r = eActionWithComeback::decide();
    if(r) return r;

    const auto t = mCharacter->tile();

    const int coll = mCharacter->collected();

    const SDL_Point p{t->x(), t->y()};
    const auto rect = mShed->tileRect();
    const bool inShed = SDL_PointInRect(&p, &rect);

    if(coll > 0) {
        if(inShed) {
            const auto rType = mShed->resourceType();
            mShed->add(rType, coll);
            mCharacter->incCollected(-coll);
            waitDecision();
        } else {
            goBackDecision();
        }
    } else {
        eCollectType collType;
        if(const auto a = tryToCollect(t, mAnimalType, collType)) {
            switch(collType) {
            case eCollectType::collect:
                collectDecision(a);
                break;
            case eCollectType::groom:
                groomDecision(a);
                break;
            }
        } else if(inShed) {
            const int res = mShed->resource();
            if(res >= mShed->maxResource() ||
               !mShed->enabled()) {
                waitDecision();
            } else {
                if(mNoResource) {
                    mNoResource = false;
                    waitDecision();
                } else {
                    findResourceDecision();
                }
            }
        } else if(mNoResource) {
            mNoResource = false;
            goBackDecision();
        } else {
            if(mGroomed > 20) {
                mGroomed = 0;
                goBackDecision();
            } else {
                findResourceDecision();
            }
        }
    }
    return true;
}

bool eShepherdAction::findResourceDecision() {
    const auto c = character();

    const stdptr<eShepherdAction> tptr(this);

    const auto aType = mAnimalType;
    const auto hha = [aType](eTileBase* const tile) {
        return hasAnimal(tile, aType);
    };

    const auto a = e::make_shared<eMoveToAction>(c, [](){}, [](){});
    a->setFoundAction([c]() {
        c->setActionType(eCharacterActionType::walk);
    });
    const auto findFailFunc = [tptr, this]() {
        if(tptr) mNoResource = true;
    };
    a->setFindFailAction(findFailFunc);
    a->start(hha);
    setCurrentAction(a);
    return true;
}

void eShepherdAction::collectDecision(eDomesticatedAnimal* const a) {
    a->setBusy(true);
    a->setVisible(false);
    mCharacter->setActionType(eCharacterActionType::collect);
    const stdptr<eCharacterAction> tptr(this);
    const stdptr<eDomesticatedAnimal> aa(a);
    const auto finish = [tptr, this, aa]() {
        int c = 0;
        if(aa) {
            c = aa->collect();
            aa->setBusy(false);
            aa->setVisible(true);
        }
        if(!tptr) return;
        mCharacter->incCollected(c);
    };
    const auto wait = e::make_shared<eWaitAction>(mCharacter, finish, finish);
    wait->setTime(2000);
    setCurrentAction(wait);
}

void eShepherdAction::groomDecision(eDomesticatedAnimal* const a) {
    a->setBusy(true);
    mCharacter->setActionType(eCharacterActionType::fight);
    const stdptr<eCharacterAction> tptr(this);
    const stdptr<eDomesticatedAnimal> aa(a);
    const auto finish = [tptr, this, aa]() {
        if(aa) {
            aa->groom();
            aa->setBusy(false);
        }
        if(!tptr) return;
        mGroomed++;
    };
    const auto wait = e::make_shared<eWaitAction>(mCharacter, finish, finish);
    wait->setTime(1000);
    setCurrentAction(wait);
}

void eShepherdAction::goBackDecision() {
    if(mCharacter->collected()) {
        mCharacter->setActionType(eCharacterActionType::carry);
    } else {
        mCharacter->setActionType(eCharacterActionType::walk);
    }
    const auto rect = mShed->tileRect();
    eActionWithComeback::goBack([rect](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        const bool r = SDL_PointInRect(&p, &rect);
        if(r) return true;
        return t->walkable();
    });
}

void eShepherdAction::waitDecision() {
    const auto w = e::make_shared<eWaitAction>(
                       mCharacter, [](){}, [](){});
    w->setTime(5000);
    setCurrentAction(w);
}
