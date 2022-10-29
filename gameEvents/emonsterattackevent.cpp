#include "emonsterattackevent.h"

#include "engine/egameboard.h"
#include "characters/actions/emonsteraction.h"

eMonsterAttackEvent::eMonsterAttackEvent(eGameBoard& board) :
    eGameEvent(eGameEventType::monsterAttack, board) {}

void eMonsterAttackEvent::setTypes(const std::vector<eMonsterType>& types) {
    mTypes = types;
    const int nTypes = mTypes.size();
    if(mNextId >= nTypes) mNextId = 0;
}

void eMonsterAttackEvent::setRandom(const bool r) {
    mRandom = r;
}

void eMonsterAttackEvent::trigger() {
    if(mTypes.empty()) return;
    auto& board = getBoard();
    int tid;
    const int nTypes = mTypes.size();
    if(mRandom) {
        tid = rand() % mTypes.size();
    } else {
        tid = mNextId;
        if(++mNextId >= nTypes) mNextId = 0;
    }
    const auto t = mTypes.at(tid);
    const auto monster = eMonster::sCreateMonster(t, board);
    eEvent e;
    switch(t) {
    case eMonsterType::calydonianBoar:
        e = eEvent::calydonianBoarInvasion;
        break;
    }

    const auto a = e::make_shared<eMonsterAction>(
                       monster.get(), []() {}, []() {});
    monster->setAction(a);
    a->increment(1);
    board.event(e, monster->tile());
}

void eMonsterAttackEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mTypes.size();
    for(const auto t : mTypes) {
        dst << t;
    }
    dst << mRandom;
    dst << mNextId;
}

void eMonsterAttackEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    int n;
    src >> n;
    for(int i = 0; i < n; i++) {
        eMonsterType t;
        src >> t;
        mTypes.push_back(t);
    }
    src >> mRandom;
    src >> mNextId;
}
