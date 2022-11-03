#ifndef EGODSOUNDS_H
#define EGODSOUNDS_H

#include <string>
#include <vector>

#include <SDL2/SDL_mixer.h>

#include "characters/gods/egod.h"

enum class eGodSound {
    wooing0,
    jealousy1,
    jealousy2,
    invade,
    monster,
    quest,
    questFinished,
    prayer,
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
    ~eGodSounds();

    void load();

    void play(const eGodSound s);

    void playWooing0() {
        Mix_PlayChannel(-1, fWooing0, 0);
    }

    void playJealousy1() {
        Mix_PlayChannel(-1, fJealousy1, 0);
    }

    void playJealousy2() {
        Mix_PlayChannel(-1, fJealousy2, 0);
    }

    void playInvade() {
        Mix_PlayChannel(-1, fInvade, 0);
    }

    void playMonster() {
        Mix_PlayChannel(-1, fMonster, 0);
    }

    void playQuest() {
        Mix_PlayChannel(-1, fQuest, 0);
    }

    void playQuestFinished() {
        Mix_PlayChannel(-1, fQuestFinished, 0);
    }

    void playPrayer() {
        Mix_PlayChannel(-1, fPrayer, 0);
    }

    void playAppear() {
        Mix_PlayChannel(-1, fAppear, 0);
    }

    void playDisappear() {
        Mix_PlayChannel(-1, fDisappear, 0);
    }

    void playAttack() {
        const int id = rand() % fAttack.size();
        Mix_PlayChannel(-1, fAttack[id], 0);
    }

    void playCurse() {
        Mix_PlayChannel(-1, fCurse, 0);
    }

    void playHit() {
        Mix_PlayChannel(-1, fHit, 0);
    }

    void playSanctify() {
        Mix_PlayChannel(-1, fSanctify, 0);
    }

    const std::string fShortName;
    const std::string fLongName;

    bool fFirstVisit = true;

    Mix_Chunk* fWooing0 = nullptr;
    Mix_Chunk* fJealousy1 = nullptr;
    Mix_Chunk* fJealousy2 = nullptr;
    Mix_Chunk* fInvade = nullptr;
    Mix_Chunk* fMonster = nullptr;
    Mix_Chunk* fQuest = nullptr;
    Mix_Chunk* fQuestFinished = nullptr;
    Mix_Chunk* fPrayer = nullptr;

    Mix_Chunk* fAppear = nullptr;
    Mix_Chunk* fDisappear = nullptr;

    std::vector<Mix_Chunk*> fAttack;
    Mix_Chunk* fCurse = nullptr;
    Mix_Chunk* fHit = nullptr;
    Mix_Chunk* fSanctify = nullptr;
};

#endif // EGODSOUNDS_H
