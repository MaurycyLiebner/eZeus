#ifndef EHEROSOUNDS_H
#define EHEROSOUNDS_H

#include <string>
#include <vector>

#include <SDL2/SDL_mixer.h>

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
    ~eHeroSounds();

    void load();

    void play(const eHeroSound s);

    void playArrival() {
        Mix_PlayChannel(-1, fArrival, 0);
    }

    void playAttack() {
        const int id = rand() % fAttack.size();
        Mix_PlayChannel(-1, fAttack[id], 0);
    }

    void playHit() {
        Mix_PlayChannel(-1, fHit, 0);
    }

    void playDie() {
        Mix_PlayChannel(-1, fDie, 0);
    }

    const std::string fShortName;
    const std::string fLongName;

    Mix_Chunk* fArrival = nullptr;
    std::vector<Mix_Chunk*> fAttack;
    Mix_Chunk* fHit = nullptr;
    Mix_Chunk* fDie = nullptr;
};

#endif // EHEROSOUNDS_H
