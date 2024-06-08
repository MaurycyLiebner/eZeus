#ifndef EGODSOUNDS_H
#define EGODSOUNDS_H

#include "esoundvector.h"

#include "characters/gods/egod.h"

enum class eGodSound {
    wooing0,
    jealousy1,
    jealousy2,
    invade,
    monster,
    quest,
    questFinished,
    help,
    appear,
    disappear,
    attack,
    curse,
    hit,
    santcify
};

struct eGodSounds {
    eGodSounds(const std::string& shortName,
               const std::string& longName);

    void load();

    void play(const eGodSound s);

    void playWooing0() {
        fWooing0->playRandomSound();
    }

    void playJealousy1() {
        fJealousy1->playRandomSound();
    }

    void playJealousy2() {
        fJealousy2->playRandomSound();
    }

    void playInvade() {
        fInvade->playRandomSound();
    }

    void playMonster() {
        fMonster->playRandomSound();
    }

    void playQuest() {
        fQuest->playRandomSound();
    }

    void playQuestFinished() {
        fQuestFinished->playRandomSound();
    }

    void playHelp() {
        fHelp->playRandomSound();
    }

    void playAppear() {
        fAppear->playRandomSound();
    }

    void playDisappear() {
        fDisappear->playRandomSound();
    }

    void playAttack() {
        fAttack->playRandomSound();
    }

    void playCurse() {
        fCurse->playRandomSound();
    }

    void playHit() {
        fHit->playRandomSound();
    }

    void playSanctify() {
        fSanctify->playRandomSound();
    }

    const std::string fShortName;
    const std::string fLongName;

    bool fFirstVisit = true;

    std::shared_ptr<eSoundVector> fWooing0 = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> fJealousy1 = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> fJealousy2 = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> fInvade = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> fMonster = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> fQuest = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> fQuestFinished = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> fHelp = std::make_shared<eSoundVector>();

    std::shared_ptr<eSoundVector> fAppear = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> fDisappear = std::make_shared<eSoundVector>();

    std::shared_ptr<eSoundVector> fAttack = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> fCurse = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> fHit = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> fSanctify = std::make_shared<eSoundVector>();
private:
    bool mLoaded = false;
};

#endif // EGODSOUNDS_H
