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
    const auto& brd = c->board();
    const auto tp = brd.threadPool();

    const int tx = t->x();
    const int ty = t->y();

    const auto startTile = [tx, ty](eThreadBoard& board) {
        return board.absTile(tx, ty);
    };
    const auto finalTile = [](eThreadTile* const t) {
        return t->underBuildingType() == eBuildingType::commonHouse &&
               t->houseVacancies() > 0;
    };
    const auto failFunc = [this]() {
        goBack2();
    };
    const auto walkable = [](eTileBase* const t) {
        return t->walkable();
    };
    const auto finishFunc = [this, c, walkable, failFunc](
                            std::vector<eOrientation> path) {
        if(path.empty()) {
            setState(eCharacterActionState::finished);
            return;
        }
        path.erase(path.begin());
        const auto finishAction = [this]() {
            const bool r = enterHouse();
            if(r) {
                setState(eCharacterActionState::finished);
            } else {
                findHouse();
            }
        };

        const auto a  = new eMovePathAction(c, path, walkable,
                                            failFunc, finishAction);
        setCurrentAction(a);
    };

    const auto pft = new ePathFindTask(startTile, walkable,
                                       finalTile, finishFunc,
                                       failFunc, 200);
    tp->queueTask(pft);

    setCurrentAction(new eWaitAction(c, []() {}, []() {}));
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
        if(t != eBuildingType::commonHouse) continue;
        const auto ch = static_cast<eSmallHouse*>(b);
        const int v = ch->vacancies();
        if(v <= 0) continue;
        ch->moveIn(8);
        return true;
    }
    return false;
}
