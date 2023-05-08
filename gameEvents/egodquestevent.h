#ifndef EGODQUESTEVENT_H
#define EGODQUESTEVENT_H

#include "egameevent.h"

#include "characters/gods/egod.h"
#include "characters/heroes/ehero.h"

class eGodQuestEvent : public eGameEvent {
public:
    eGodQuestEvent(eGameBoard& board);

    eGodType god() const { return mGod; }
    void setGod(const eGodType g);

    eGodQuestId id() const { return mId; }
    void setId(const eGodQuestId id);

    eHeroType hero() const { return mHero; }
    void setHero(const eHeroType h);

    void trigger() override;
    std::string longName() const override;

    void write(eWriteStream& dst) const override ;
    void read(eReadStream& src) override;
private:
    eGodType mGod = eGodType::zeus;
    eGodQuestId mId = eGodQuestId::godQuest1;
    eHeroType mHero = eHeroType::hercules;
};

#endif // EGODQUESTEVENT_H
