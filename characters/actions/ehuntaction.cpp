#include "ehuntaction.h"

#include "engine/epathfinder.h"

#include "emovetoaction.h"
#include "ewaitaction.h"

#include "characters/eboar.h"
#include "characters/edeer.h"

#include "buildings/ehuntinglodge.h"

eHuntAction::eHuntAction(
        eHuntingLodge* const b,
        eHunter* const c,
        const eAction& failAction,
        const eAction& finishAction) :
    eActionWithComeback(c, failAction, finishAction),
    mLodge(b),
    mHunter(c) {}

bool hasAnimal(eTileBase* const tile, eCharacterType& type) {
    return tile->hasCharacter([&type](const eCharacterBase& c) {
        const bool b = c.type() == eCharacterType::boar && !c.fighting();
        if(b) {
            type = eCharacterType::boar;
            return true;
        }
        const bool d = c.type() == eCharacterType::deer && !c.fighting();
        if(d) {
            type = eCharacterType::deer;
            return true;
        }
        return false;
    });
}

bool tryToCollect(eTile* const tile) {
    const auto cs = tile->characters();
    for(const auto& c : cs) {
        const auto t = c->type();
        if(t == eCharacterType::boar) {
            const auto b = static_cast<eBoar*>(c.get());
            if(b->dead()) {
                b->setActionType(eCharacterActionType::none);
                return true;
            }
        } else if(t == eCharacterType::deer) {
            const auto d = static_cast<eDeer*>(c.get());
            if(d->dead()) {
                d->setActionType(eCharacterActionType::none);
                return true;
            }
        }
    }
    return false;
}

bool eHuntAction::decide() {
    const bool r = eActionWithComeback::decide();
    if(r) return r;

    const auto t = mHunter->tile();

    if(tryToCollect(t)) mHunter->incCollected(1);
    const int coll = mHunter->collected();

    const SDL_Point p{t->x(), t->y()};
    const auto rect = mLodge->tileRect();
    const bool inLodge = SDL_PointInRect(&p, &rect);

    if(coll > 0) {
        if(inLodge) {
            mLodge->add(eResourceType::meat, coll);
            mHunter->incCollected(-coll);
            waitDecision();
        } else {
            goBackDecision();
        }
    } else {
        if(inLodge) {
            const int res = mLodge->resource();
            if(res >= mLodge->maxResource() ||
               !mLodge->enabled()) {
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
            findResourceDecision();
        }
    }
    return true;
}

void eHuntAction::resume() {
    if(mHunter) {
        const auto t = mHunter->tile();
        if(t && tryToCollect(t)) {
            setCurrentAction(nullptr);
            return;
        }
    }
    eActionWithComeback::resume();
}

void eHuntAction::findResourceDecision() {
    const auto c = character();

    const stdptr<eHuntAction> tptr(this);

    auto aType = std::make_shared<eCharacterType>();

    const auto hha = [aType](eTileBase* const tile) {
        eCharacterType type;
        const bool r = hasAnimal(tile, type);
        if(r) *aType = type;
        return r;
    };

    const auto a = e::make_shared<eMoveToAction>(c, [](){}, [](){});
    a->setFoundAction([this, c, aType]() {
        if(*aType == eCharacterType::deer) {
            mHunter->setDeerHunter(true);
        }
        c->setActionType(eCharacterActionType::walk);
    });
    const auto findFailFunc = [tptr]() {
        if(tptr) tptr->mNoResource = true;
    };
    a->setFindFailAction(findFailFunc);
    a->start(hha);
    setCurrentAction(a);
}

void eHuntAction::goBackDecision() {
    mHunter->setActionType(eCharacterActionType::carry);
    const auto rect = mLodge->tileRect();
    eActionWithComeback::goBack(rect, eWalkableObject::sCreateDefault());
}

void eHuntAction::waitDecision() {
    const auto w = e::make_shared<eWaitAction>(
                       mHunter, [](){}, [](){});
    w->setTime(5000);
    setCurrentAction(w);
}
