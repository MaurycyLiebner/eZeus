#include "emonstersounds.h"


#include "audio/esounds.h"
#include "egamedir.h"

eMonsterSounds::eMonsterSounds(const std::string& shortName,
                               const std::string& longName) :
    fShortName(shortName), fLongName(longName) {}

void eMonsterSounds::load() {
    if(mLoaded) return;
    mLoaded = true;
    const std::string voiceDir{eGameDir::path("Audio/Voice/Walker/")};
    const std::string wavsDir{eGameDir::path("Audio/Wavs/")};

    fVoice->addPath(voiceDir + "M_" + fShortName + ".mp3");

    for(const auto& s : {"M_" + fLongName + "_atk1.wav",
                         "M_" + fLongName + "_atk2.wav",
                         "M_" + fLongName + "_atk3.wav",
                         "M_" + fLongName + "_atk4.wav"}) {
        fAttack->addPath(wavsDir + s);
    }
    fDie->addPath(wavsDir + "M_" + fLongName + "_die.wav");
    fHit->addPath(wavsDir + "M_" + fLongName + "_hit.wav");
}

void eMonsterSounds::play(const eMonsterSound s) {
    switch(s) {
    case eMonsterSound::voice:
        playVoice();
        break;
    case eMonsterSound::attack:
        playAttack();
        break;
    case eMonsterSound::die:
        playDie();
        break;
    case eMonsterSound::hit:
        playHit();
        break;
    }
}
