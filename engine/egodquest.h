#ifndef EGODQUEST_H
#define EGODQUEST_H

#include "characters/gods/egod.h"
#include "characters/heroes/ehero.h"

struct eGodQuest {
    static eHeroType sDefaultHero(
            const eGodType gt, const eGodQuestId gqi);

    void write(eWriteStream& dst) const {
        dst << fGod;
        dst << fId;
        dst << fHero;
    }

    void read(eReadStream& src) {
        src >> fGod;
        src >> fId;
        src >> fHero;
    }

    bool operator==(const eGodQuest& o) {
        return fGod == o.fGod &&
               fId == o.fId &&
               fHero == o.fHero;
    }

    eGodType fGod = eGodType::zeus;
    eGodQuestId fId = eGodQuestId::godQuest1;
    eHeroType fHero = eGodQuest::sDefaultHero(fGod, fId);
};

#endif // EGODQUEST_H
