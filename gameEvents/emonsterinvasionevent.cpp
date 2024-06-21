#include "emonsterinvasionevent.h"

#include "elanguage.h"
#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "emessages.h"

eMonsterInvasionWarningEvent::eMonsterInvasionWarningEvent(
        const eGameEventBranch branch) :
    eGameEvent(eGameEventType::monsterInvasionWarning, branch) {}

void eMonsterInvasionWarningEvent::initialize(
        const eMonsterInvasionWarningType type,
        const eMonsterType monster) {
    mType = type;
    mMonster = monster;
}

void eMonsterInvasionWarningEvent::setMonster(const eMonsterType m) {
    mMonster = m;
}

void eMonsterInvasionWarningEvent::trigger() {
    const auto board = gameBoard();
    if(!board) return;
    eEventData ed;
    ed.fMonster = mMonster;
    switch(mType) {
    case eMonsterInvasionWarningType::warning36: {
        board->event(eEvent::monsterInvasion36, ed);
    } break;
    case eMonsterInvasionWarningType::warning24: {
        board->event(eEvent::monsterInvasion24, ed);
    } break;
    case eMonsterInvasionWarningType::warning12: {
        board->event(eEvent::monsterInvasion12, ed);
    } break;
    case eMonsterInvasionWarningType::warning6: {
        board->event(eEvent::monsterInvasion6, ed);
    } break;
    case eMonsterInvasionWarningType::warning1: {
        board->event(eEvent::monsterInvasion1, ed);
    } break;
    }
}

std::string eMonsterInvasionWarningEvent::longName() const {
    return eLanguage::text("monster_invasion_long_name");
}

void eMonsterInvasionWarningEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mType;
    dst << mMonster;
}

void eMonsterInvasionWarningEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mType;
    src >> mMonster;
}

eMonsterInvasionEvent::eMonsterInvasionEvent(const eGameEventBranch branch) :
    eMonsterInvasionEventBase(eGameEventType::monsterInvasion,
                              branch) {}

void eMonsterInvasionEvent::pointerCreated() {

    const auto warnTypes = {
        eMonsterInvasionWarningType::warning36,
        eMonsterInvasionWarningType::warning24,
        eMonsterInvasionWarningType::warning12,
        eMonsterInvasionWarningType::warning6,
        eMonsterInvasionWarningType::warning1
    };
    for(const auto w : warnTypes) {
        int months;
        switch(w) {
        case eMonsterInvasionWarningType::warning36:
            months = 36;
            break;
        case eMonsterInvasionWarningType::warning24:
            months = 24;
            break;
        case eMonsterInvasionWarningType::warning12:
            months = 12;
            break;
        case eMonsterInvasionWarningType::warning6:
            months = 6;
            break;
        case eMonsterInvasionWarningType::warning1:
            months = 1;
            break;
        }
        const int daysBefore = 31*months;
        const auto e = e::make_shared<eMonsterInvasionWarningEvent>(
                           eGameEventBranch::child);
        e->initialize(w, type());
        addWarning(daysBefore, e);
    }
}

void eMonsterInvasionEvent::trigger() {
    const auto board = gameBoard();
    if(!board) return;

    const auto monster = triggerBase();

    eEventData ed;
    ed.fChar = monster;
    ed.fTile = monster->tile();
    ed.fMonster = type();
    board->event(eEvent::monsterInvasion, ed);

    const auto& inst = eMessages::instance;
    const auto gm = inst.monsterMessages(type());
    const auto& m = gm->fToSlainReason;
    const auto heroType = eMonster::sSlayer(type());
    board->allowHero(heroType, m);
}

std::string eMonsterInvasionEvent::longName() const {
    return eLanguage::text("monster_invasion_long_name");
}
