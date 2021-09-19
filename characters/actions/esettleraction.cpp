#include "esettleraction.h"

#include "engine/etile.h"
#include "characters/echaracter.h"
#include "engine/ethreadpool.h"
#include "emovetoaction.h"
#include "buildings/esmallhouse.h"
#include "buildings/eelitehousing.h"

eSettlerAction::eSettlerAction(eCharacter* const c,
                               const eAction& failAction,
                               const eAction& finishAction) :
    eActionWithComeback(c, failAction, finishAction) {

}

void eSettlerAction::increment(const int by) {
    if(!currentAction()) findHouse();
    eActionWithComeback::increment(by);
}

void eSettlerAction::findHouse() {
    const auto c = character();

    const auto finalTile = [](eThreadTile* const t) {
        const auto ut = t->underBuildingType();
        const bool h = ut == eBuildingType::commonHouse ||
                       ut == eBuildingType::eliteHousing;
        return h && t->houseVacancies() > 0;
    };
    const stdptr<eCharacterAction> tptr(this);
    const auto failFunc = [tptr, this]() {
        if(tptr) goBack2();
    };

    const auto finishAction = [tptr, this]() {
        if(!tptr) return;
        const bool r = enterHouse();
        if(r) {
            setState(eCharacterActionState::finished);
        } else {
            findHouse();
        }
    };

    c->setActionType(eCharacterActionType::walk);

    const auto a = e::make_shared<eMoveToAction>(c, failFunc, finishAction);
    a->setRemoveLastTurn(true);
    a->start(finalTile);
    setCurrentAction(a);
}

void eSettlerAction::goBack2() {
    eActionWithComeback::goBack([](eTileBase* const t) {
        return t->walkable();
    });
}

bool eSettlerAction::enterHouse() {
    const auto c = character();
    const auto t = c->tile();
    if(!t) {
        setState(eCharacterActionState::failed);
        return false;
    }
    for(const auto n : {eOrientation::topRight,
                        eOrientation::right,
                        eOrientation::bottomRight,
                        eOrientation::bottom,
                        eOrientation::bottomLeft,
                        eOrientation::left,
                        eOrientation::topLeft,
                        eOrientation::top}) {
        const auto nn = t->neighbour<eTile>(n);
        if(!nn) continue;
        const auto b = nn->underBuilding();
        if(!b) continue;
        const auto t = b->type();
        if(t == eBuildingType::commonHouse) {
            const auto ch = static_cast<eSmallHouse*>(b);
            const int v = ch->vacancies();
            if(v <= 0) continue;
            ch->moveIn(8);
            return true;
        } else if(t == eBuildingType::eliteHousing) {
            const auto ch = static_cast<eEliteHousing*>(b);
            const int v = ch->vacancies();
            if(v <= 0) continue;
            ch->moveIn(8);
            return true;
        }
    }
    return false;
}
