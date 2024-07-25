#include "egodquestevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "elanguage.h"
#include "emessages.h"
#include "egodquestfulfilledevent.h"
#include "buildings/eheroshall.h"
#include "estringhelpers.h"

eGodQuestEvent::eGodQuestEvent(const eGameEventBranch branch) :
    eGodQuestEventBase(eGameEventType::godQuest, branch) {
    const auto e4 = eLanguage::text("fulfilled_trigger");
    mFulfilledTrigger = e::make_shared<eEventTrigger>(e4);

    addTrigger(mFulfilledTrigger);
}

eGodQuestEvent::~eGodQuestEvent() {
    const auto board = gameBoard();
    if(board) board->removeGodQuest(this);
}

void eGodQuestEvent::trigger() {
    const auto board = gameBoard();
    if(!board) return;
    board->addGodQuest(this);
    eEventData ed;
    ed.fHero = hero();
    ed.fQuestId = id();
    ed.fGod = god();
    board->event(eEvent::godQuest, ed);
    const auto& inst = eMessages::instance;
    const auto gm = inst.godMessages(god());
    if(!gm) return board->allowHero(hero());
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
    board->allowHero(hero(), reason);
}

std::string eGodQuestEvent::longName() const {
    return eLanguage::text("god_quest");
}

bool eGodQuestEvent::finished() const {
    return mFulfilled;
}

void eGodQuestEvent::read(eReadStream& src) {
    eGodQuestEventBase::read(src);
    src >> mFulfilled;
}

void eGodQuestEvent::write(eWriteStream& dst) const {
    eGodQuestEventBase::write(dst);
    dst << mFulfilled;
}

void eGodQuestEvent::fulfill() {
    const auto board = gameBoard();
    if(!board) return;
    const auto hh = board->heroHall(hero());
    if(!hh) return;
    const auto s = hh->stage();
    if(s != eHeroSummoningStage::arrived) return;
    hh->sendHeroOnQuest();
    board->removeGodQuest(this);

    const auto e = e::make_shared<eGodQuestFulfilledEvent>(
                       eGameEventBranch::child);
    const auto boardDate = board->date();
    const int period = 150;
    const auto date = boardDate + period;
    e->initializeDate(date, period, 1);
    e->setGod(god());
    e->setHero(hero());
    e->setId(id());
    addConsequence(e);
}

void eGodQuestEvent::fulfilled() {
    const auto board = gameBoard();
    if(!board) return;
    const auto date = board->date();
    const auto& msgs = eMessages::instance;
    const auto godMsgs = msgs.godMessages(god());
    const eQuestMessages* qMsgs = nullptr;
    switch(id()) {
    case eGodQuestId::godQuest1:
        qMsgs = &godMsgs->fQuest1;
        break;
    case eGodQuestId::godQuest2:
        qMsgs = &godMsgs->fQuest2;
        break;
    }
    auto rFull = qMsgs->fFulfilled.fReason;
    const auto heroName = eHero::sHeroName(hero());
    eStringHelpers::replaceAll(rFull, "[hero_needed]", heroName);
    mFulfilledTrigger->trigger(*this, date, rFull);
    mFulfilled = true;
}
