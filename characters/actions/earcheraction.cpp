#include "earcheraction.h"

#include "epatrolmoveaction.h"

#include "characters/echaracter.h"
#include "buildings/ebuilding.h"
#include "engine/etile.h"

void eArcherAction::increment(const int by) {
    if(!currentAction()) {
        const auto c = character();
        c->setActionType(eCharacterActionType::walk);
        const auto walkable = [](eTileBase* const tile) {
            const auto ut = tile->underBuildingType();
            if(ut == eBuildingType::tower) return true;
            if(ut != eBuildingType::wall) return false;
            const auto bl = tile->tileRel(0, 1);
            if(!bl) return false;
            const auto br = tile->tileRel(1, 0);
            if(!br) return false;
            const auto b = tile->tileRel(1, 1);
            if(!b) return false;
            const auto blt = bl->underBuildingType();
            const auto brt = br->underBuildingType();
            const auto bt = b->underBuildingType();
            if(blt != eBuildingType::wall ||
               brt != eBuildingType::wall ||
               bt != eBuildingType::wall) return false;
            return true;
        };
        const auto fail = [this]() {
            setState(eCharacterActionState::failed);
        };
        const auto finish = [this]() {
            setState(eCharacterActionState::finished);
        };
        const auto a = std::make_shared<ePatrolMoveAction>(
                           c, fail, finish, false, walkable);
        setCurrentAction(a);
    }
    eComplexAction::increment(by);
}
