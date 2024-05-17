#include "egodquestfulfilledevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "elanguage.h"
#include "emessages.h"

#include "buildings/eheroshall.h"

eGodQuestFulfilledEvent::eGodQuestFulfilledEvent(
        const eGameEventBranch branch,
        eGameBoard& board) :
    eGodQuestEventBase(eGameEventType::godQuestFulfilled, branch, board) {}

void eGodQuestFulfilledEvent::trigger() {
    eEventData ed;
    ed.fHero = hero();
    ed.fQuestId = id();
    ed.fGod = god();
    auto& board = getBoard();
    board.event(eEvent::godQuestFulfilled, ed);
    board.allow(eBuildingType::godMonument, static_cast<int>(god()));
    const auto hh = board.heroHall(hero());
    if(hh) hh->setHeroOnQuest(false);
}

std::string eGodQuestFulfilledEvent::longName() const {
    return eLanguage::text("god_quest_fulfilled");
}

stdsptr<eGameEvent> eGodQuestFulfilledEvent::makeCopy(
        const std::string& reason) const {
    const auto c = e::make_shared<eGodQuestFulfilledEvent>(
                       branch(), getBoard());
    c->setReason(reason);
    c->setGod(god());
    c->setId(id());
    c->setHero(hero());
    return c;
}
