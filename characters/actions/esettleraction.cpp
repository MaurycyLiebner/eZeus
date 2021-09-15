#include "esettleraction.h"

#include "engine/etile.h"
#include "epathfindtask.h"
#include "characters/echaracter.h"
#include "engine/ethreadpool.h"
#include "ewaitaction.h"
#include "buildings/esmallhouse.h"

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
    const auto t = c->tile();
    const auto& brd = c->getBoard();
    const auto tp = brd.threadPool();

    const int tx = t->x();
    const int ty = t->y();

    const auto startTile = [tx, ty](eThreadBoard& board) {
        return board.absTile(tx, ty);
    };
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
    const auto walkable = [](eTileBase* const t) {
        return t->walkable();
    };
    const auto finishFunc = [tptr, this, c, walkable, failFunc](
                            std::vector<eOrientation> path) {
        if(!tptr) return;
        if(path.empty()) {
            setState(eCharacterActionState::finished);
            return;
        }
        path.erase(path.begin());
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
        const auto a  = e::make_shared<eMovePathAction>(
                            c, path, walkable,
                            failFunc, finishAction);
        setCurrentAction(a);
    };

    const auto pft = new ePathFindTask(startTile, walkable,
                                       finalTile, finishFunc,
                                       failFunc, false, 200);
    tp->queueTask(pft);

    setCurrentAction(e::make_shared<eWaitAction>(c, []() {}, []() {}));
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
        if(t != eBuildingType::commonHouse &&
           t != eBuildingType::eliteHousing) continue;
        const auto ch = static_cast<eSmallHouse*>(b);
        const int v = ch->vacancies();
        if(v <= 0) continue;
        ch->moveIn(8);
        return true;
    }
    return false;
}
