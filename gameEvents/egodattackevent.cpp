#include "egodattackevent.h"

#include "engine/egameboard.h"
#include "engine/eevent.h"
#include "engine/eeventdata.h"
#include "characters/actions/egodattackaction.h"
#include "egodtraderesumesevent.h"

eGodAttackEvent::eGodAttackEvent(const eGameEventBranch branch) :
    eGameEvent(eGameEventType::godAttack, branch) {}

void eGodAttackEvent::setTypes(const std::vector<eGodType>& types) {
    mTypes = types;
    const int nTypes = mTypes.size();
    if(mNextId >= nTypes) mNextId = 0;
}

void eGodAttackEvent::setRandom(const bool r) {
    mRandom = r;
}

void eGodAttackEvent::trigger() {
    if(mTypes.empty()) return;
    const auto board = gameBoard();
    if(!board) return;
    int tid;
    const int nTypes = mTypes.size();
    if(mRandom) {
        tid = rand() % mTypes.size();
    } else {
        tid = mNextId;
        if(++mNextId >= nTypes) mNextId = 0;
    }
    const auto t = mTypes.at(tid);
    const auto god = eGod::sCreateGod(t, *board);

    const auto a = e::make_shared<eGodAttackAction>(god.get());
    god->setAttitude(eGodAttitude::hostile);
    god->setAction(a);
    a->increment(1);
    eEventData ed;
    ed.fChar = god.get();
    ed.fTile = god->tile();
    ed.fGod = t;
    board->registerAttackingGod(god.get());
    board->event(eEvent::godInvasion, ed);
    if(t == eGodType::zeus) {
        board->setLandTradeShutdown(true);
        board->setSeaTradeShutdown(true);
    } else if(t == eGodType::poseidon) {
        board->setSeaTradeShutdown(true);
    } else if(t == eGodType::hermes) {
        board->setLandTradeShutdown(true);
    }
    if(t == eGodType::zeus ||
       t == eGodType::poseidon ||
       t == eGodType::hermes) {
        const auto e = e::make_shared<eGodTradeResumesEvent>(
                           eGameEventBranch::child);
        e->setGod(t);
        e->initializeDate(board->date() + 365);
        addConsequence(e);
    }
}

std::string eGodAttackEvent::longName() const {
    return eLanguage::text("god_attack");
}

void eGodAttackEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mTypes.size();
    for(const auto t : mTypes) {
        dst << t;
    }
    dst << mRandom;
    dst << mNextId;
}

void eGodAttackEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    int n;
    src >> n;
    for(int i = 0; i < n; i++) {
        eGodType t;
        src >> t;
        mTypes.push_back(t);
    }
    src >> mRandom;
    src >> mNextId;
}
