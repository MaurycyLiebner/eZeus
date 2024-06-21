#include "egodquesteventbase.h"

void eGodQuestEventBase::setGod(const eGodType g) {
    mQuest.fGod = g;
}

void eGodQuestEventBase::setId(const eGodQuestId id) {
    mQuest.fId = id;
}

void eGodQuestEventBase::setHero(const eHeroType h) {
    mQuest.fHero = h;
}

void eGodQuestEventBase::write(eWriteStream& dst) const {
    eGameEvent::write(dst);
    mQuest.write(dst);
}

void eGodQuestEventBase::read(eReadStream& src) {
    eGameEvent::read(src);
    mQuest.read(src);
}
