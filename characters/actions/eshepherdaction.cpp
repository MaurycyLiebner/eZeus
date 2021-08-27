#include "eshepherdaction.h"

#include "engine/epathfinder.h"

#include "epathfindtask.h"
#include "engine/ethreadpool.h"
#include "characters/actions/ewaitaction.h"

#include "characters/esheep.h"
#include "characters/egoat.h"

eShepherdAction::eShepherdAction(
        const SDL_Rect& buildingRect,
        eResourceCollector* const c,
        const eCharacterType animalType,
        const eAction& failAction,
        const eAction& finishAction) :
    eActionWithComeback(c, failAction, finishAction),
    mAnimalType(animalType),
    mCharacter(c),
    mBuildingRect(buildingRect) {}

bool hasAnimal(eTileBase* const tile, const eCharacterType type) {
    return tile->hasCharacter([&type](const eCharacterBase& c) {
        const auto aType = c.actionType();
        if(aType == eCharacterActionType::lay) return false;
        return c.type() == type;
    });
}

eDomesticatedAnimal* tryToCollect(eTile* const tile, const eCharacterType type) {
    const auto cs = tile->characters();
    for(const auto& c : cs) {
        const auto t = c->type();
        if(t != type) continue;
        const auto s = static_cast<eDomesticatedAnimal*>(c.get());
        if(!s->busy() && s->canCollect()) {
            return s;
        }
        s->groom();
        return nullptr;
    }
    return nullptr;
}

void eShepherdAction::increment(const int by) {
    if(!currentAction()) findResource();
    else eActionWithComeback::increment(by);
}

bool eShepherdAction::findResource() {
    const auto c = character();
    const auto t = c->tile();
    const auto& brd = c->board();
    const auto tp = brd.threadPool();

    const int tx = t->x();
    const int ty = t->y();

    const auto startTile = [tx, ty](eThreadBoard& board) {
        return board.absTile(tx, ty);
    };
    const auto rect = mBuildingRect;
    const auto tileWalkable = [rect](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        const bool r = SDL_PointInRect(&p, &rect);
        if(r) return true;
        return t->walkable();
    };

    const stdptr<eCharacterAction> tptr(this);
    const auto failFunc = [tptr]() {
        if(tptr) tptr->setState(eCharacterActionState::failed);
    };

    const auto finishFunc = [tptr, this, c, tileWalkable, failFunc](
                            const std::vector<eOrientation>& path) {
        if(!tptr) return;
        const auto finishAction = [tptr, this, c]() {
            if(!tptr) return;
            const auto tile = c->tile();
            if(const auto a = tryToCollect(tile, mAnimalType)) {
                collect(a);
            } else findResource();
        };

        c->setActionType(eCharacterActionType::walk);
        const auto a  = e::make_shared<eMovePathAction>(
                            c, path, tileWalkable,
                            failFunc, finishAction);
        setCurrentAction(a);
    };

    const auto aType = mAnimalType;
    const auto hha = [aType](eTileBase* const tile) {
        return hasAnimal(tile, aType);
    };

    const auto pft = new ePathFindTask(startTile, tileWalkable,
                                       hha, finishFunc,
                                       failFunc, false, 50);
    tp->queueTask(pft);

    setCurrentAction(e::make_shared<eWaitAction>(c, []() {}, []() {}));

    return true;
}

bool eShepherdAction::collect(eDomesticatedAnimal* const a) {
    a->setBusy(true);
    mCharacter->setActionType(eCharacterActionType::collect);
    const stdptr<eCharacterAction> tptr(this);
    const stdptr<eDomesticatedAnimal> aa(a);
    const auto finish = [tptr, this, aa](){
        if(tptr) {
            mCharacter->incCollected(1);
            goBack2();
        } if(aa) aa->setBusy(false);
    };
    const auto wait = e::make_shared<eWaitAction>(mCharacter, finish, finish);
    wait->setTime(2000);
    setCurrentAction(wait);
    return true;
}

void eShepherdAction::goBack2() {
    if(mCharacter->collected()) {
        mCharacter->setActionType(eCharacterActionType::carry);
    } else {
        mCharacter->setActionType(eCharacterActionType::walk);
    }
    const auto rect = mBuildingRect;
    eActionWithComeback::goBack([rect](eTileBase* const t) {
        const SDL_Point p{t->x(), t->y()};
        const bool r = SDL_PointInRect(&p, &rect);
        if(r) return true;
        return t->walkable();
    });
}
