#include "emonsterinvasioneventbase.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "characters/actions/emonsteraction.h"
#include "emonsterinvasionevent.h"
#include "eiteratesquare.h"

eMonsterInvasionEventBase::eMonsterInvasionEventBase(const eGameEventType type,
        const eGameEventBranch branch) :
    eGameEvent(type, branch) {}


void eMonsterInvasionEventBase::setType(const eMonsterType type) {
    mType = type;
    const auto& ws = warnings();
    for(const auto& w : ws) {
        const auto& ws = w.second;
        const auto iw = dynamic_cast<eMonsterInvasionWarningEvent*>(ws.get());
        if(!iw) continue;
        iw->setMonster(type);
    }
}

void eMonsterInvasionEventBase::setPointId(const int p) {
    mPointId = p;
}

void eMonsterInvasionEventBase::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mType;
    dst << mPointId;
}

void eMonsterInvasionEventBase::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mType;
    src >> mPointId;
}

eMonster* eMonsterInvasionEventBase::triggerBase() const {
    const auto board = gameBoard();
    if(!board) return nullptr;
    const auto monster = eMonster::sCreateMonster(mType, *board);
    board->registerMonster(monster.get());
    monster->setPlayerId(2);

    const auto a = e::make_shared<eMonsterAction>(monster.get());
    monster->setAction(a);
    auto tile = board->monsterTile(mPointId);
    if(tile) {
        const int tx = tile->x();
        const int ty = tile->y();
        const auto placeMonster = [board, monster, tx, ty](
                                  const int dx, const int dy) {
            const int ttx = tx + dx;
            const int tty = ty + dy;
            const auto tile = board->tile(ttx, tty);
            if(!tile) return false;
            if(const auto ub = tile->underBuilding()) {
                const auto type = ub->type();
                const bool w = eBuilding::sWalkableBuilding(type);
                if(!w) {
                    const bool a = eBuilding::sAttackable(type);
                    if(a) {
                        ub->collapse();
                    } else {
                        return false;
                    }
                }
            }
            monster->changeTile(tile);
            return true;
        };
        int k = 0;
        while(!monster->tile()) {
            eIterateSquare::iterateSquare(k++, placeMonster);
        }
    }
    a->increment(1);

    return monster.get();
}
