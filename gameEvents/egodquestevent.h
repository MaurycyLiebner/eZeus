#ifndef EGODQUESTEVENT_H
#define EGODQUESTEVENT_H

#include "egameevent.h"

#include "characters/gods/egod.h"
#include "characters/heroes/ehero.h"

namespace eGodQuest {
    eHeroType sDefaultHero(const eGodType gt, const eGodQuestId gqi);
};

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

    void write(eWriteStream& dst) const override;
    void read(eReadStream& src) override;

    stdsptr<eGameEvent> makeCopy(const std::string& reason) const override;
private:
    eGodType mGod = eGodType::zeus;
    eGodQuestId mId = eGodQuestId::godQuest1;
    eHeroType mHero = eGodQuest::sDefaultHero(mGod, mId);
};

#endif // EGODQUESTEVENT_H
