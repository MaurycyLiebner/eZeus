#ifndef EHEROSOUNDS_H
#define EHEROSOUNDS_H

#include "esoundvector.h"

#include "characters/heroes/ehero.h"

enum class eHeroSound {
    arrived,
    attack,
    hit,
    die
};

class eHeroSounds {
public:
    eHeroSounds(const std::string& shortName,
                const std::string& longName);

    void play(const eHeroSound s);

    void playArrival() {
        fArrival->playRandomSound();
    }

    void playAttack() {
        fAttack->playRandomSound();
    }

    void playHit() {
        fHit->playRandomSound();
    }

    void playDie() {
        fDie->playRandomSound();
    }

    const std::string fShortName;
    const std::string fLongName;

    std::shared_ptr<eSoundVector> fArrival = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> fAttack = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> fHit = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> fDie = std::make_shared<eSoundVector>();
};

#endif // EHEROSOUNDS_H
