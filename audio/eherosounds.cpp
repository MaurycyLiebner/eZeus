#include "eherosounds.h"

#include "audio/esounds.h"
#include "egamedir.h"

eHeroSounds::eHeroSounds(const std::string& shortName,
                         const std::string& longName) :
    fShortName(shortName), fLongName(longName) {}

eHeroSounds::~eHeroSounds() {
    Mix_FreeChunk(fArrival);
    for(const auto a : fAttack) {
        Mix_FreeChunk(a);
    }
    Mix_FreeChunk(fHit);
}

void eHeroSounds::load() {
    const std::string voiceDir{eGameDir::path("Audio/Voice/Walker/")};
    const std::string wavsDir{eGameDir::path("Audio/Wavs/")};

    fArrival = eSounds::loadSoundBase(voiceDir + fShortName + "_ev_1.mp3");
    for(const auto& s : {"H_" + fLongName + "_atk1.wav",
                         "H_" + fLongName + "_atk2.wav"}) {
        const auto r = eSounds::loadSoundBase(wavsDir + s);
        if(r) fAttack.push_back(r);
    }
    fHit = eSounds::loadSoundBase(wavsDir + "H_" + fLongName + "_hit.wav");
    fDie = eSounds::loadSoundBase(wavsDir + "H_" + fLongName + "_die.wav");
}

void eHeroSounds::play(const eHeroSound s) {
    switch(s) {
    case eHeroSound::arrived:
        playArrival();
        break;
    case eHeroSound::attack:
        playAttack();
        break;
    case eHeroSound::hit:
        playHit();
        break;
    case eHeroSound::die:
        playDie();
        break;
    }
}
