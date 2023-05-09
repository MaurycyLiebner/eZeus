#include "egodquestevent.h"

#include "engine/egameboard.h"
#include "engine/eeventdata.h"
#include "engine/eevent.h"
#include "elanguage.h"
#include "emessages.h"

eGodQuestEvent::eGodQuestEvent(eGameBoard& board) :
    eGameEvent(eGameEventType::godQuest, board) {}

void eGodQuestEvent::setGod(const eGodType g) {
    mGod = g;
}

void eGodQuestEvent::setId(const eGodQuestId id) {
    mId = id;
}

void eGodQuestEvent::setHero(const eHeroType h) {
    mHero = h;
}

void eGodQuestEvent::trigger() {
    eEventData ed;
    ed.fHero = mHero;
    ed.fQuestId = mId;
    ed.fGod = mGod;
    auto& board = getBoard();
    board.event(eEvent::godQuest, ed);
    const auto& inst = eMessages::instance;
    const auto gm = inst.godMessages(mGod);
    if(!gm) return board.allowHero(mHero);
    const eQuestMessages* qm = nullptr;
    switch(mId) {
    case eGodQuestId::godQuest1:
        qm = &gm->fQuest1;
        break;
    case eGodQuestId::godQuest2:
        qm = &gm->fQuest2;
        break;
    }
    const auto reason = qm->fQuest.fReason;
    board.allowHero(mHero, reason);
}

std::string eGodQuestEvent::longName() const {
    return eLanguage::text("god_quest");
}

void eGodQuestEvent::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    dst << mGod;
    dst << mId;
    dst << mHero;
}

void eGodQuestEvent::read(eReadStream& src) {
    eGameEvent::read(src);
    src >> mGod;
    src >> mId;
    src >> mHero;
}

stdsptr<eGameEvent> eGodQuestEvent::makeCopy(const std::string& reason) const {
    const auto c = e::make_shared<eGodQuestEvent>(getBoard());
    c->setReason(reason);
    c->mGod = mGod;
    c->mId = mId;
    c->mHero = mHero;
    return c;
}
