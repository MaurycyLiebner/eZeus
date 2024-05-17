#ifndef EGODQUESTEVENTBASE_H
#define EGODQUESTEVENTBASE_H

#include "egameevent.h"

#include "engine/egodquest.h"

class eGodQuestEventBase : public eGameEvent {
public:
    using eGameEvent::eGameEvent;

    const eGodQuest& godQuest() const { return mQuest; }

    eGodType god() const { return mQuest.fGod; }
    void setGod(const eGodType g);

    eGodQuestId id() const { return mQuest.fId; }
    void setId(const eGodQuestId id);

    eHeroType hero() const { return mQuest.fHero; }
    void setHero(const eHeroType h);

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;
private:
    eGodQuest mQuest;
};

#endif // EGODQUESTEVENTBASE_H
