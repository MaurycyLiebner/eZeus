#include "emonsterinvasionevent.h"

#include "elanguage.h"
#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "emessages.h"

eMonsterInvasionWarningEvent::eMonsterInvasionWarningEvent(
        const eGameEventBranch branch, eGameBoard& board) :
    eGameEvent(eGameEventType::monsterInvasionWarning, branch, board) {}

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
    auto& board = getBoard();
    eEventData ed;
    ed.fMonster = mMonster;
    switch(mType) {
    case eMonsterInvasionWarningType::warning24: {
        board.event(eEvent::monsterInvasion24, ed);
    } break;
    case eMonsterInvasionWarningType::warning12: {
        board.event(eEvent::monsterInvasion12, ed);
    } break;
    case eMonsterInvasionWarningType::warning6: {
        board.event(eEvent::monsterInvasion6, ed);
    } break;
    case eMonsterInvasionWarningType::warning1: {
        board.event(eEvent::monsterInvasion1, ed);
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

stdsptr<eGameEvent> eMonsterInvasionWarningEvent::makeCopy(
        const std::string& reason) const {
    const auto c = e::make_shared<eMonsterInvasionWarningEvent>(
                       branch(), getBoard());
    c->setReason(reason);
    c->mType = mType;
    c->mMonster = mMonster;
    return c;
}

eMonsterInvasionEvent::eMonsterInvasionEvent(
        const eGameEventBranch branch, eGameBoard& board) :
    eMonsterInvasionEventBase(eGameEventType::monsterInvasion,
                              branch, board) {
    const auto warnTypes = {
        eMonsterInvasionWarningType::warning24,
        eMonsterInvasionWarningType::warning12,
        eMonsterInvasionWarningType::warning6,
        eMonsterInvasionWarningType::warning1
    };
    for(const auto w : warnTypes) {
        int months;
        switch(w) {
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
                           eGameEventBranch::child, board);
        e->initialize(w, type());
        addWarning(daysBefore, e);
    }
}

void eMonsterInvasionEvent::trigger() {
    auto& board = getBoard();

    const auto monster = triggerBase();

    eEventData ed;
    ed.fChar = monster;
    ed.fTile = monster->tile();
    ed.fMonster = type();
    board.event(eEvent::monsterInvasion, ed);

    const auto& inst = eMessages::instance;
    const auto gm = inst.monsterMessages(type());
    const auto& m = gm->fToSlainReason;
    const auto heroType = eMonster::sSlayer(type());
    board.allowHero(heroType, m);
}

std::string eMonsterInvasionEvent::longName() const {
    return eLanguage::text("monster_invasion_long_name");
}

stdsptr<eGameEvent> eMonsterInvasionEvent::makeCopy(const std::string& reason) const {
    const auto c = e::make_shared<eMonsterInvasionEvent>(branch(), getBoard());
    c->setType(type());
    c->setPointId(pointId());
    c->setReason(reason);
    return c;
}
