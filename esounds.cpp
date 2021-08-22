#include "esounds.h"

eSounds eSounds::sInstance;

eSounds::eSounds() {

}

void eSounds::load() {
    sInstance.loadImpl();
}

bool eSounds::loaded() {
    return sInstance.mLoaded;
}

Mix_Chunk* loadSoundBase(const std::string& path) {
    const auto wav = Mix_LoadWAV(path.c_str());
    if(!wav) {
        printf("Failed to load sound '%s'!\n SDL_mixer Error: %s\n",
               path.c_str(), Mix_GetError());
        return nullptr;
    }
    return wav;
}

void eSounds::loadImpl() {
    if(mLoaded) return;
    mLoaded = true;

    const std::string dir{"../Audio/Ambient/Layer2/"};

    for(const auto& s : {"maintenance1.wav",
                         "maintenance2.wav",
                         "maintenance3.wav",
                         "maintenance4.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mMaintenance.push_back(r);
    }

    for(const auto& s : {"wagon1.wav",
                         "wagon2.wav",
                         "wagon3.wav",
                         "city1.wav",
                         "city3.wav",
                         "city4.wav",
                         "city5.wav",
                         "city8.wav",
                         "city9.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mCommonHousing.push_back(r);
    }

    for(const auto& s : {"elite1.wav",
                         "elite2.wav",
                         "city2.wav",
                         "city7.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mEliteHousing.push_back(r);
    }

    for(const auto& s : {"dig3.wav",
                         "dig4.wav",
                         "dig5.wav",
                         "dig6.wav",
                         "dig7.wav",
                         "dig8.wav",
                         "bird1.wav",
                         "bird2.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mFarming.push_back(r);
    }

    for(const auto& s : {"rustling1.wav",
                         "rustling2.wav",
                         "orchard1.wav",
                         "orchard2.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mOrchard.push_back(r);
    }

    for(const auto& s : {"shearing1.wav",
                         "shearing2.wav",
                         "shearing3.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mSheepFarm.push_back(r);
    }

    for(const auto& s : {"goatherd1.wav",
                         "goatherd2.wav",
                         "goatherd3.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mGoatFarm.push_back(r);
    }

    for(const auto& s : {"dock1.wav",
                         "dock2.wav",
                         "dock3.wav",
                         "urchin1.wav",
                         "urchin2.wav",
                         "urchin3.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mSea.push_back(r);
    }

    for(const auto& s : {"trireme1.wav",
                         "trireme2.wav",
                         "trireme3.wav",
                         "trireme4.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mTriremeWharf.push_back(r);
    }

    for(const auto& s : {"hunting1.wav",
                         "hunting2.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mHunting.push_back(r);
    }

    for(const auto& s : {"timber_mill1.wav",
                         "timber_mill2.wav",
                         "timber_mill3.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mTimberMill.push_back(r);
    }

    for(const auto& s : {"marble1.wav",
                         "marble2.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mMarble.push_back(r);
    }

    for(const auto& s : {"mint1.wav",
                         "mint2.wav",
                         "mint3.wav",
                         "mint4.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mMint.push_back(r);
    }

    for(const auto& s : {"foundry1.wav",
                         "foundry2.wav",
                         "foundry3.wav",
                         "foundry4.wav",
                         "foundry5.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mFoundry.push_back(r);
    }

    for(const auto& s : {"wagon4.wav",
                         "wagon5.wav",
                         "wagon6.wav",
                         "wagon7.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mWorkshops.push_back(r);
    }

    for(const auto& s : {"chest1.wav",
                         "chest2.wav",
                         "chest3.wav",
                         "shovel.wav",
                         "drop_wood.wav",
                         "storage_cart1.wav",
                         "warehouse.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mStorage.push_back(r);
    }

    for(const auto& s : {"agora_food1.wav",
                         "agora_food2.wav",
                         "agora_food3.wav",
                         "agora_food4.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mAgoraFood.push_back(r);
    }

    for(const auto& s : {"agora_fleece1.wav",
                         "agora_fleece2.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mAgoraFleece.push_back(r);
    }

    for(const auto& s : {"agora_fleece1.wav",
                         "agora_fleece2.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mAgoraFleece.push_back(r);
    }

    for(const auto& s : {"agora_oil.wav",
                         "agora_gen1.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mAgoraOil.push_back(r);
    }

    for(const auto& s : {"agora_wine1.wav",
                         "agora_wine2.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mAgoraWine.push_back(r);
    }

    for(const auto& s : {"agora_arms1.wav",
                         "agora_arms2.wav",
                         "agora_gen2.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mAgoraArms.push_back(r);
    }

    for(const auto& s : {"agora_horse1.wav",
                         "agora_horse2.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mAgoraHorse.push_back(r);
    }

    for(const auto& s : {"trade1.wav",
                         "trade2.wav",
                         "trade3.wav",
                         "trade4.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mTrade.push_back(r);
    }

    for(const auto& s : {"tax1.wav",
                         "tax2.wav",
                         "tax3.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mTaxes.push_back(r);
    }

    for(const auto& s : {"palace1.wav",
                         "palace2.wav",
                         "palace3.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mPalace.push_back(r);
    }

    for(const auto& s : {"defensive1.wav",
                         "defensive2.wav",
                         "defensive3.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mDefensive.push_back(r);
    }

    for(const auto& s : {"infirmary1.wav",
                         "infirmary2.wav",
                         "infirmary3.wav",
                         "infirmary4.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mInfirmary.push_back(r);
    }

    for(const auto& s : {"drama1.wav",
                         "flying.wav",
                         "thtr_spear1.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mTheatre.push_back(r);
    }

    for(const auto& s : {"thtr_mumbl1.wav",
                         "thtr_mumbl2.wav",
                         "thtr_mumbl3.wav",
                         "thtr_spear2.wav",
                         "thtr_spin1.wav",
                         "thtr_spin2.wav",
                         "thtr_women.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mDrama.push_back(r);
    }

    for(const auto& s : {"Plato.wav",
                         "Aristotle.wav",
                         "Socrates.wav",
                         "college.wav",
                         "college2.wav",
                         "podium1.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mPhilosophy.push_back(r);
    }

    for(const auto& s : {"gym1.wav",
                         "gym2.wav",
                         "gym3.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mGymnasium.push_back(r);
    }

    for(const auto& s : {"cheer.wav",
                         "javelin.wav",
                         "wrestling.wav",
                         "cheer2.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mStadium.push_back(r);
    }

    for(const auto& s : {"sanctuary1.wav",
                         "sanctuary2.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mSanctuary.push_back(r);
    }

    for(const auto& s : {"armory1.wav",
                         "armory2.wav",
                         "armory3.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mArmory.push_back(r);
    }

    for(const auto& s : {"horse1.wav",
                         "horse2.wav",
                         "horse3.wav",
                         "horse4.wav",
                         "horse5.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mHorseRanch.push_back(r);
    }

    for(const auto& s : {"win_chime1.wav",
                         "win_chime2.wav",
                         "recreation1.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mBeautification.push_back(r);
    }

    for(const auto& s : {"fountain1.wav",
                         "fountain2.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mFountain.push_back(r);
    }

    for(const auto& s : {"artisan_guild1.wav",
                         "artisan_guild2.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mArtisan.push_back(r);
    }




    for(const auto& s : {"bird7.wav",
                         "finch2.wav",
                         "sparrow1.wav",
                         "bird3.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mMeadow.push_back(r);
    }

    for(const auto& s : {"bird1.wav",
                         "bird2.wav",
                         "bird4.wav",
                         "rustling1.wav",
                         "rustling2.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mFarmland.push_back(r);
    }

    for(const auto& s : {"wave1.wav",
                         "wave2.wav",
                         "wave3.wav",
                         "wave4.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mBeach.push_back(r);
    }

    for(const auto& s : {"rumble.wav",
                         "rockslide1.wav",
                         "rockslide2.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mRocky.push_back(r);
    }

    for(const auto& s : {"bird3.wav",
                         "bird4.wav",
                         "bird5.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mVegetation.push_back(r);
    }

    for(const auto& s : {"water_space1.wav",
                         "water_space2.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mWater.push_back(r);
    }



    for(const auto& s : {"boar1.wav",
                         "boar2.wav",
                         "boar3.wav",
                         "boar4.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mBoar.push_back(r);
    }

    for(const auto& s : {"goat1.wav",
                         "goat2.wav",
                         "goat3.wav",
                         "goat4.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mGoat.push_back(r);
    }

    for(const auto& s : {"wolf1.wav",
                         "wolf2.wav",
                         "wolf3.wav",
                         "wolf4.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mWolf.push_back(r);
    }

    for(const auto& s : {"sheep1.wav",
                         "sheep2.wav",
                         "sheep3.wav",
                         "sheep4.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mSheep.push_back(r);
    }

    for(const auto& s : {"cattle1.wav",
                         "cattle2.wav",
                         "cattle3.wav",
                         "cattle4.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mCattle.push_back(r);
    }

    for(const auto& s : {"deer1.wav",
                         "deer2.wav",
                         "deer3.wav",
                         "deer4.wav"}) {
        const auto r = loadSoundBase(dir + s);
        if(r) mDeer.push_back(r);
    }
}
