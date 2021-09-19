#include "ehuntaction.h"

#include "engine/epathfinder.h"

#include "emovetoaction.h"

#include "characters/eboar.h"
#include "characters/edeer.h"

eHuntAction::eHuntAction(
        const SDL_Rect& buildingRect,
        eHunter* const c,
        const eAction& failAction,
        const eAction& finishAction) :
    eActionWithComeback(c, failAction, finishAction),
    mCharacter(c),
    mBuildingRect(buildingRect) {}

bool hasAnimal(eTileBase* const tile,
                       eCharacterType& type) {
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

void eHuntAction::increment(const int by) {
    if(!currentAction()) findResource();
    else eActionWithComeback::increment(by);
}

void eHuntAction::resume() {
    eActionWithComeback::resume();
    const auto tile = mCharacter->tile();
    if(tryToCollect(tile)) collect();
}

bool eHuntAction::findResource() {
    const auto c = character();

    const stdptr<eCharacterAction> tptr(this);
    const auto failFunc = [tptr]() {
        if(tptr) tptr->setState(eCharacterActionState::failed);
    };

    auto aType = std::make_shared<eCharacterType>();

    const auto finishAction = [tptr, this, c]() {
        if(!tptr) return;
        const auto tile = c->tile();
        if(tryToCollect(tile)) collect();
        else findResource();
    };

    const auto hha = [aType](eTileBase* const tile) {
        eCharacterType type;
        const bool r = hasAnimal(tile, type);
        if(r) *aType = type;
        return r;
    };

    const auto a = e::make_shared<eMoveToAction>(c, failFunc, finishAction);
    a->setFoundAction([this, c, aType]() {
        if(*aType == eCharacterType::deer) {
            mCharacter->setDeerHunter(true);
        }
        c->setActionType(eCharacterActionType::walk);
    });
    a->start(hha);
    setCurrentAction(a);

    return true;
}

bool eHuntAction::collect() {
    mCharacter->incCollected(1);
    goBack2();
    return true;
}

void eHuntAction::goBack2() {
    mCharacter->setActionType(eCharacterActionType::carry);
    const auto rect = mBuildingRect;
    eActionWithComeback::goBack([rect](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        const bool r = SDL_PointInRect(&p, &rect);
        if(r) return true;
        return t->walkable();
    });
}
