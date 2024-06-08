#ifndef EMONSTERSOUNDS_H
#define EMONSTERSOUNDS_H

#include "esoundvector.h"

#include "characters/monsters/emonster.h"

enum class eMonsterSound {
    voice,
    attack,
    die,
    hit
};

class eMonsterSounds {
public:
    eMonsterSounds(const std::string& shortName,
                   const std::string& longName);

    void load();

    void play(const eMonsterSound s);

    void playVoice() {
        fVoice->playRandomSound();
    }

    void playAttack() {
        fAttack->playRandomSound();
    }

    void playDie() {
        fDie->playRandomSound();
    }

    void playHit() {
        fHit->playRandomSound();
    }

    const std::string fShortName;
    const std::string fLongName;

    std::shared_ptr<eSoundVector> fVoice = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> fAttack = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> fDie = std::make_shared<eSoundVector>();
    std::shared_ptr<eSoundVector> fHit = std::make_shared<eSoundVector>();
private:
    bool mLoaded = false;
};

#endif // EMONSTERSOUNDS_H
