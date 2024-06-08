#include "eherosounds.h"

#include "audio/esounds.h"
#include "egamedir.h"

eHeroSounds::eHeroSounds(const std::string& shortName,
                         const std::string& longName) :
    fShortName(shortName), fLongName(longName) {
    const std::string voiceDir{eGameDir::path("Audio/Voice/Walker/")};
    const std::string wavsDir{eGameDir::path("Audio/Wavs/")};

    fArrival->addPath(voiceDir + fShortName + "_ev_1.mp3");
    for(const auto& s : {"H_" + fLongName + "_atk1.wav",
                         "H_" + fLongName + "_atk2.wav"}) {
        fAttack->addPath(wavsDir + s);
    }
    fHit->addPath(wavsDir + "H_" + fLongName + "_hit.wav");
    fDie->addPath(wavsDir + "H_" + fLongName + "_die.wav");
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
