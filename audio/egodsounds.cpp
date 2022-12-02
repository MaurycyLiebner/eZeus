#include "egodsounds.h"

#include "audio/esounds.h"
#include "egamedir.h"

eGodSounds::eGodSounds(const std::string& shortName,
                       const std::string& longName) :
    fShortName(shortName),
    fLongName(longName) {}

eGodSounds::~eGodSounds() {
    Mix_FreeChunk(fWooing0);
    Mix_FreeChunk(fJealousy1);
    Mix_FreeChunk(fJealousy2);

    Mix_FreeChunk(fInvade);
    Mix_FreeChunk(fAppear);
    Mix_FreeChunk(fDisappear);

    for(const auto a : fAttack) {
        Mix_FreeChunk(a);
    }
    Mix_FreeChunk(fCurse);
    Mix_FreeChunk(fHit);
    Mix_FreeChunk(fSanctify);
}

void eGodSounds::load() {
    if(fLoaded) return;
    fLoaded = true;

    const std::string voiceDir{eGameDir::path("Audio/Voice/Walker/")};
    const std::string wavsDir{eGameDir::path("Audio/Wavs/")};

    fWooing0 = eSounds::loadSoundBase(voiceDir + fShortName + "_ev_3.mp3");
    fJealousy1 = eSounds::loadSoundBase(voiceDir + fShortName + "_ev_2.mp3");
    fJealousy2 = eSounds::loadSoundBase(voiceDir + fShortName + "_ev_1.mp3");

    fInvade = eSounds::loadSoundBase(voiceDir + fShortName + "_ev_4.mp3");

    fMonster = eSounds::loadSoundBase(voiceDir + fShortName + "_ev_5.mp3");
    fQuest = eSounds::loadSoundBase(voiceDir + fShortName + "_ev_6.mp3");
    fQuestFinished = eSounds::loadSoundBase(voiceDir + fShortName + "_ev_7.mp3");
    fPrayer = eSounds::loadSoundBase(voiceDir + fShortName + "_ev_8.mp3");

    fAppear = eSounds::loadSoundBase(wavsDir + "G_" + fLongName + "_mat.wav");
    fDisappear = eSounds::loadSoundBase(wavsDir + "G_" + fLongName + "_demat.wav");

    for(const auto& s : {"G_" + fLongName + "_atk1.wav",
                         "G_" + fLongName + "_atk2.wav",
                         "G_" + fLongName + "_atk3.wav",
                         "G_" + fLongName + "_atk4.wav"}) {
        const auto r = eSounds::loadSoundBase(wavsDir + s);
        if(r) fAttack.push_back(r);
    }

    fCurse = eSounds::loadSoundBase(wavsDir + "G_" + fLongName + "_curse.wav");
    fHit = eSounds::loadSoundBase(wavsDir + "G_" + fLongName + "_hit.wav");
    fSanctify = eSounds::loadSoundBase(wavsDir + "G_" + fLongName + "_sanctify.wav");
}

void eGodSounds::play(const eGodSound s) {
    switch(s) {
    case eGodSound::wooing0:
        playWooing0();
        break;
    case eGodSound::jealousy1:
        playJealousy1();
        break;
    case eGodSound::jealousy2:
        playJealousy2();
        break;
    case eGodSound::invade:
        playInvade();
        break;
    case eGodSound::monster:
        playMonster();
        break;
    case eGodSound::quest:
        playQuest();
        break;
    case eGodSound::questFinished:
        playQuestFinished();
        break;
    case eGodSound::prayer:
        playPrayer();
        break;
    case eGodSound::appear:
        playAppear();
        break;
    case eGodSound::disappear:
        playDisappear();
        break;
    case eGodSound::attack:
        playAttack();
        break;
    case eGodSound::curse:
        playCurse();
        break;
    case eGodSound::hit:
        playHit();
        break;
    case eGodSound::santcify:
        playSanctify();
        break;
    }
}
