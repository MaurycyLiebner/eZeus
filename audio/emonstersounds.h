#ifndef EMONSTERSOUNDS_H
#define EMONSTERSOUNDS_H

#include <string>
#include <vector>

#include <SDL2/SDL_mixer.h>

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
    ~eMonsterSounds();

    void load();

    void play(const eMonsterSound s);

    void playVoice() {
        load();
        Mix_PlayChannel(-1, fVoice, 0);
    }

    void playAttack() {
        load();
        const int id = rand() % fAttack.size();
        Mix_PlayChannel(-1, fAttack[id], 0);
    }

    void playDie() {
        load();
        Mix_PlayChannel(-1, fDie, 0);
    }

    void playHit() {
        load();
        Mix_PlayChannel(-1, fHit, 0);
    }

    const std::string fShortName;
    const std::string fLongName;

    bool fLoaded = false;

    Mix_Chunk* fVoice = nullptr;
    std::vector<Mix_Chunk*> fAttack;
    Mix_Chunk* fDie = nullptr;
    Mix_Chunk* fHit = nullptr;
};

#endif // EMONSTERSOUNDS_H
