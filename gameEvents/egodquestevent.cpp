#include "egodquestevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "elanguage.h"
#include "emessages.h"
#include "egodquestfulfilledevent.h"
#include "buildings/eheroshall.h"

eGodQuestEvent::eGodQuestEvent(const eGameEventBranch branch,
                               eGameBoard& board) :
    eGodQuestEventBase(eGameEventType::godQuest, branch, board) {}

eGodQuestEvent::~eGodQuestEvent() {
    auto& board = getBoard();
    board.removeGodQuest(this);
}

void eGodQuestEvent::trigger() {
    auto& board = getBoard();
    board.addGodQuest(this);
    eEventData ed;
    ed.fHero = hero();
    ed.fQuestId = id();
    ed.fGod = god();
    board.event(eEvent::godQuest, ed);
    const auto& inst = eMessages::instance;
    const auto gm = inst.godMessages(god());
    if(!gm) return board.allowHero(hero());
    const eQuestMessages* qm = nullptr;
    switch(id()) {
    case eGodQuestId::godQuest1:
        qm = &gm->fQuest1;
        break;
    case eGodQuestId::godQuest2:
        qm = &gm->fQuest2;
        break;
    }
    const auto reason = qm->fQuest.fReason;
    board.allowHero(hero(), reason);
}

std::string eGodQuestEvent::longName() const {
    return eLanguage::text("god_quest");
}

stdsptr<eGameEvent> eGodQuestEvent::makeCopy(const std::string& reason) const {
    const auto c = e::make_shared<eGodQuestEvent>(branch(), getBoard());
    c->setReason(reason);
    c->setGod(god());
    c->setId(id());
    c->setHero(hero());
    return c;
}

void eGodQuestEvent::fulfill() {
    auto& board = getBoard();
    const auto hh = board.heroHall(hero());
    if(!hh) return;
    const auto s = hh->stage();
    if(s != eHeroSummoningStage::arrived) return;
    hh->sendHeroOnQuest();
    board.removeGodQuest(this);

    const auto e = e::make_shared<eGodQuestFulfilledEvent>(
                       eGameEventBranch::child, board);
    const auto boardDate = board.date();
    const int period = 150;
    const auto date = boardDate + period;
    e->initializeDate(date, period, 1);
    e->setGod(god());
    e->setHero(hero());
    e->setId(id());
    addConsequence(e);
}
