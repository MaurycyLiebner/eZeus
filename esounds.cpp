#include "esounds.h"

#include "engine/etile.h"
#include "buildings/ebuilding.h"
#include "characters/echaracter.h"

eSounds eSounds::sInstance;

Mix_Chunk* loadSoundBase(const std::string& path) {
    const auto wav = Mix_LoadWAV(path.c_str());
    if(!wav) {
        printf("Failed to load sound '%s'!\n SDL_mixer Error: %s\n",
               path.c_str(), Mix_GetError());
        return nullptr;
    }
    return wav;
}

eSounds::eSounds() {

}

void deleteSounds(const std::vector<Mix_Chunk*>& sounds) {
    for(const auto s : sounds) {
        Mix_FreeChunk(s);
    }
}

eSounds::~eSounds() {
    Mix_FreeChunk(mButton);

    deleteSounds(mEnvironment);

    deleteSounds(mMaintenance);
    deleteSounds(mCommonHousing);
    deleteSounds(mEliteHousing);
    deleteSounds(mFarming);
    deleteSounds(mOrchard);
    deleteSounds(mSheepFarm);
    deleteSounds(mGoatFarm);
    deleteSounds(mSea);
    deleteSounds(mTriremeWharf);
    deleteSounds(mHunting);
    deleteSounds(mTimberMill);
    deleteSounds(mMarble);
    deleteSounds(mMint);
    deleteSounds(mFoundry);
    deleteSounds(mWorkshops);
    deleteSounds(mStorage);
    deleteSounds(mAgoraFood);
    deleteSounds(mAgoraFleece);
    deleteSounds(mAgoraOil);
    deleteSounds(mAgoraWine);
    deleteSounds(mAgoraArms);
    deleteSounds(mAgoraHorse);
    deleteSounds(mTrade);
    deleteSounds(mTaxes);
    deleteSounds(mPalace);
    deleteSounds(mDefensive);
    deleteSounds(mInfirmary);
    deleteSounds(mTheatre);
    deleteSounds(mDrama);
    deleteSounds(mPhilosophy);
    deleteSounds(mGymnasium);
    deleteSounds(mStadium);
    deleteSounds(mSanctuary);
    deleteSounds(mArmory);
    deleteSounds(mHorseRanch);
    deleteSounds(mBeautification);
    deleteSounds(mFountain);
    deleteSounds(mArtisan);

    // terrain
    deleteSounds(mMeadow);
    deleteSounds(mFarmland);
    deleteSounds(mBeach);
    deleteSounds(mRocky);
    deleteSounds(mVegetation);
    deleteSounds(mWater);
    // animals
    deleteSounds(mBoar);
    deleteSounds(mGoat);
    deleteSounds(mWolf);
    deleteSounds(mSheep);
    deleteSounds(mCattle);
    deleteSounds(mDeer);

    // events
    Mix_FreeChunk(mFire);
    Mix_FreeChunk(mCollapse);
}

void eSounds::loadButtonSound() {
    const std::string wavsDir{"../Audio/Wavs/"};
    sInstance.mButton = loadSoundBase(wavsDir + "button.wav");
}

void eSounds::load() {
    sInstance.loadImpl();
}

bool eSounds::loaded() {
    return sInstance.mLoaded;
}

void eSounds::playButtonSound() {
    Mix_PlayChannel(-1, sInstance.mButton, 0);
}

void eSounds::playSoundForTile(eTile* const tile) {
    if(tile->onFire()) return eSounds::playFireSound();
    if(const auto b = tile->underBuilding()) {
        switch(b->type()) {
        case eBuildingType::commonHouse:
            return eSounds::playCommonHousingSound();
        case eBuildingType::theater:
            return eSounds::playTheatreSound();
        case eBuildingType::dramaSchool:
            return eSounds::playDramaSound();
        case eBuildingType::timberMill:
            return eSounds::playTimberMillSound();
        case eBuildingType::warehouse:
        case eBuildingType::granary:
            return eSounds::playStorageSound();
        case eBuildingType::foundry:
            return eSounds::playFoundrySound();
        case eBuildingType::mint:
            return eSounds::playMintSound();
        case eBuildingType::maintenanceOffice:
            return eSounds::playMaintananceSound();
        case eBuildingType::taxOffice:
            return eSounds::playTaxesSound();
        case eBuildingType::palace1:
        case eBuildingType::palace2:
            return eSounds::playPalaceSound();
        case eBuildingType::podium:
        case eBuildingType::college:
            return eSounds::playPhilosophySound();
        case eBuildingType::gymnasium:
            return eSounds::playGymnasiumSound();
        case eBuildingType::stadium1:
        case eBuildingType::stadium2:
            return eSounds::playStadiumSound();
        case eBuildingType::fountain:
            return eSounds::playFountainSound();
        case eBuildingType::armory:
            return eSounds::playArmorySound();
        case eBuildingType::foodVendor:
            return eSounds::playFoodVendorSound();
        case eBuildingType::fleeceVendor:
            return eSounds::playFleeceVendorSound();
        case eBuildingType::oilVendor:
            return eSounds::playOilVendorSound();
        case eBuildingType::wineVendor:
            return eSounds::playWineVendorSound();
        case eBuildingType::armsVendor:
            return eSounds::playArmsVendorSound();
        case eBuildingType::horseTrainer:
            return eSounds::playHorseTrainerSound();
        default: break;
        }
    }

    for(const auto& c : tile->characters()) {
        switch(c->type()) {
        case eCharacterType::hunter:
            return eSounds::playHuntingSound();
        case eCharacterType::silverMiner:
            return eSounds::playMintSound();
        case eCharacterType::lumberjack:
            return eSounds::playTimberMillSound();
        case eCharacterType::boar:
            return eSounds::playBoarSound();
        case eCharacterType::deer:
            return eSounds::playDeerSound();
        case eCharacterType::wolf:
            return eSounds::playWolfSound();
        case eCharacterType::sheep:
            return eSounds::playSheepSound();
        case eCharacterType::goat:
            return eSounds::playGoatSound();
        case eCharacterType::cattle:
            return eSounds::playCattleSound();
        case eCharacterType::cartTransporter:
            return eSounds::playStorageSound();
        default: break;
        }
    }

    switch(tile->terrain()) {
    case eTerrain::beach:
        return eSounds::playBeachSound();
    case eTerrain::water:
        return eSounds::playWaterSound();
    case eTerrain::silver:
    case eTerrain::copper:
    case eTerrain::flatStones:
    case eTerrain::tallStones:
        return eSounds::playRockySound();
    default: break;
    }

    eSounds::playEnvironmentSound();
}

void playRandomSound(const std::vector<Mix_Chunk*>& sounds) {
    if(sounds.empty()) return;
    const int id = rand() % sounds.size();
    Mix_PlayChannel(-1, sounds[id], 0);
}

void eSounds::playEnvironmentSound() {
    playRandomSound(sInstance.mEnvironment);
}

void eSounds::playBeachSound() {
    playRandomSound(sInstance.mBeach);
}

void eSounds::playWaterSound() {
    playRandomSound(sInstance.mWater);
}

void eSounds::playRockySound() {
    playRandomSound(sInstance.mRocky);
}

void eSounds::playCommonHousingSound() {
    playRandomSound(sInstance.mCommonHousing);
}

void eSounds::playTheatreSound() {
    playRandomSound(sInstance.mTheatre);
}

void eSounds::playDramaSound() {
    playRandomSound(sInstance.mDrama);
}

void eSounds::playPhilosophySound() {
    playRandomSound(sInstance.mPhilosophy);
}

void eSounds::playGymnasiumSound() {
    playRandomSound(sInstance.mGymnasium);
}

void eSounds::playStadiumSound() {
    playRandomSound(sInstance.mStadium);
}

void eSounds::playFountainSound() {
    playRandomSound(sInstance.mFountain);
}

void eSounds::playTaxesSound() {
    playRandomSound(sInstance.mTaxes);
}

void eSounds::playPalaceSound() {
    playRandomSound(sInstance.mPalace);
}

void eSounds::playMaintananceSound() {
    playRandomSound(sInstance.mMaintenance);
}

void eSounds::playFoundrySound() {
    playRandomSound(sInstance.mFoundry);
}

void eSounds::playMintSound() {
    playRandomSound(sInstance.mMint);
}

void eSounds::playTimberMillSound() {
    playRandomSound(sInstance.mTimberMill);
}

void eSounds::playArmorySound() {
    playRandomSound(sInstance.mArmory);
}

void eSounds::playHuntingSound() {
    playRandomSound(sInstance.mHunting);
}

void eSounds::playBoarSound() {
    playRandomSound(sInstance.mBoar);
}

void eSounds::playDeerSound(){
    playRandomSound(sInstance.mDeer);
}

void eSounds::playWolfSound() {
    playRandomSound(sInstance.mWolf);
}

void eSounds::playSheepSound() {
    playRandomSound(sInstance.mSheep);
}

void eSounds::playGoatSound() {
    playRandomSound(sInstance.mGoat);
}

void eSounds::playCattleSound() {
    playRandomSound(sInstance.mCattle);
}

void eSounds::playStorageSound() {
    playRandomSound(sInstance.mStorage);
}

void eSounds::playFoodVendorSound() {
    playRandomSound(sInstance.mAgoraFood);
}

void eSounds::playFleeceVendorSound() {
    playRandomSound(sInstance.mAgoraFleece);
}

void eSounds::playOilVendorSound() {
    playRandomSound(sInstance.mAgoraOil);
}

void eSounds::playWineVendorSound() {
    playRandomSound(sInstance.mAgoraWine);
}

void eSounds::playArmsVendorSound() {
    playRandomSound(sInstance.mAgoraArms);
}

void eSounds::playHorseTrainerSound() {
    playRandomSound(sInstance.mAgoraHorse);
}

void eSounds::playFireSound() {
    Mix_PlayChannel(-1, sInstance.mFire, 0);
}

void eSounds::playCollapseSound() {
    Mix_PlayChannel(-1, sInstance.mCollapse, 0);
}

void eSounds::playGodSound(const eGodType g, const eGodSound s) {
    eGodSounds* god = nullptr;
    switch(g) {
    case eGodType::aphrodite:
        god = &sInstance.mAphrodite; break;
    case eGodType::apollo:
        god = &sInstance.mApollo; break;
    case eGodType::ares:
        god = &sInstance.mAres; break;
    case eGodType::artemis:
        god = &sInstance.mArtemis; break;
    case eGodType::athena:
        god = &sInstance.mAthena; break;
    case eGodType::atlas:
        god = &sInstance.mAtlas; break;
    case eGodType::demeter:
        god = &sInstance.mDemeter; break;
    case eGodType::dionysus:
        god = &sInstance.mDionysus; break;
    case eGodType::hades:
        god = &sInstance.mHades; break;
    case eGodType::hephaestus:
        god = &sInstance.mHephaestus; break;
    case eGodType::hera:
        god = &sInstance.mHera; break;
    case eGodType::hermes:
        god = &sInstance.mHermes; break;
    case eGodType::poseidon:
        god = &sInstance.mPoseidon; break;
    case eGodType::zeus:
        god = &sInstance.mZeus; break;
    }
    god->play(s);
}

void eSounds::loadImpl() {
    if(mLoaded) return;
    mLoaded = true;

    {
        const std::string layer1Dir{"../Audio/Ambient/Layer1/"};
        for(const auto& s : {"wind1.wav",
                             "wind2.wav",
                             "wind3.wav",
                             "wind4.wav",
                             "wind5.wav",
                             "wind6.wav",
                             "wind7.wav",
                             "shimmer3.wav",
                             "wind_sparkle2.wav",
                             "dark2.wav",
                             "bells.wav",
                             "space_bells7.wav",
                             "space_bells10.wav",
                             "space_bells12.wav",
                             "space_bells13.wav",
                             "space_bells14.wav",
                             "space_bells4a.wav",
                             "chime2.wav",
                             "voice.wav",
                             "shimmer6.wav",
                             "shimmer7.wav"}) {
            const auto r = loadSoundBase(layer1Dir + s);
            if(r) mEnvironment.push_back(r);
        }
    }

    const std::string layer2Dir{"../Audio/Ambient/Layer2/"};

    for(const auto& s : {"maintenance1.wav",
                         "maintenance2.wav",
                         "maintenance3.wav",
                         "maintenance4.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
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
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mCommonHousing.push_back(r);
    }

    for(const auto& s : {"elite1.wav",
                         "elite2.wav",
                         "city2.wav",
                         "city7.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
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
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mFarming.push_back(r);
    }

    for(const auto& s : {"rustling1.wav",
                         "rustling2.wav",
                         "orchard1.wav",
                         "orchard2.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mOrchard.push_back(r);
    }

    for(const auto& s : {"shearing1.wav",
                         "shearing2.wav",
                         "shearing3.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mSheepFarm.push_back(r);
    }

    for(const auto& s : {"goatherd1.wav",
                         "goatherd2.wav",
                         "goatherd3.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mGoatFarm.push_back(r);
    }

    for(const auto& s : {"dock1.wav",
                         "dock2.wav",
                         "dock3.wav",
                         "urchin1.wav",
                         "urchin2.wav",
                         "urchin3.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mSea.push_back(r);
    }

    for(const auto& s : {"trireme1.wav",
                         "trireme2.wav",
                         "trireme3.wav",
                         "trireme4.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mTriremeWharf.push_back(r);
    }

    for(const auto& s : {"hunting1.wav",
                         "hunting2.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mHunting.push_back(r);
    }

    for(const auto& s : {"timber_mill1.wav",
                         "timber_mill2.wav",
                         "timber_mill3.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mTimberMill.push_back(r);
    }

    for(const auto& s : {"marble1.wav",
                         "marble2.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mMarble.push_back(r);
    }

    for(const auto& s : {"mint1.wav",
                         "mint2.wav",
                         "mint3.wav",
                         "mint4.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mMint.push_back(r);
    }

    for(const auto& s : {"foundry1.wav",
                         "foundry2.wav",
                         "foundry3.wav",
                         "foundry4.wav",
                         "foundry5.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mFoundry.push_back(r);
    }

    for(const auto& s : {"wagon4.wav",
                         "wagon5.wav",
                         "wagon6.wav",
                         "wagon7.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mWorkshops.push_back(r);
    }

    for(const auto& s : {"chest1.wav",
                         "chest2.wav",
                         "chest3.wav",
                         "shovel.wav",
                         "drop_wood.wav",
                         "storage_cart1.wav",
                         "warehouse.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mStorage.push_back(r);
    }

    for(const auto& s : {"agora_food1.wav",
                         "agora_food2.wav",
                         "agora_food3.wav",
                         "agora_food4.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mAgoraFood.push_back(r);
    }

    for(const auto& s : {"agora_fleece1.wav",
                         "agora_fleece2.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mAgoraFleece.push_back(r);
    }

    for(const auto& s : {"agora_fleece1.wav",
                         "agora_fleece2.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mAgoraFleece.push_back(r);
    }

    for(const auto& s : {"agora_oil.wav",
                         "agora_gen1.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mAgoraOil.push_back(r);
    }

    for(const auto& s : {"agora_wine1.wav",
                         "agora_wine2.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mAgoraWine.push_back(r);
    }

    for(const auto& s : {"agora_arms1.wav",
                         "agora_arms2.wav",
                         "agora_gen2.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mAgoraArms.push_back(r);
    }

    for(const auto& s : {"agora_horse1.wav",
                         "agora_horse2.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mAgoraHorse.push_back(r);
    }

    for(const auto& s : {"trade1.wav",
                         "trade2.wav",
                         "trade3.wav",
                         "trade4.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mTrade.push_back(r);
    }

    for(const auto& s : {"tax1.wav",
                         "tax2.wav",
                         "tax3.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mTaxes.push_back(r);
    }

    for(const auto& s : {"palace1.wav",
                         "palace2.wav",
                         "palace3.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mPalace.push_back(r);
    }

    for(const auto& s : {"defensive1.wav",
                         "defensive2.wav",
                         "defensive3.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mDefensive.push_back(r);
    }

    for(const auto& s : {"infirmary1.wav",
                         "infirmary2.wav",
                         "infirmary3.wav",
                         "infirmary4.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mInfirmary.push_back(r);
    }

    for(const auto& s : {"drama1.wav",
                         "flying.wav",
                         "thtr_spear1.wav",
                         "thtr_spear2.wav",
                         "thtr_mumbl1.wav",
                         "thtr_mumbl2.wav",
                         "thtr_mumbl3.wav",
                         "thtr_women.wav",
        }) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mTheatre.push_back(r);
    }

    for(const auto& s : {"thtr_spin1.wav",
                         "thtr_spin2.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mDrama.push_back(r);
    }

    for(const auto& s : {"Plato.wav",
                         "Aristotle.wav",
                         "Socrates.wav",
                         "college.wav",
                         "college2.wav",
                         "podium1.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mPhilosophy.push_back(r);
    }

    for(const auto& s : {"gym1.wav",
                         "gym2.wav",
                         "gym3.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mGymnasium.push_back(r);
    }

    for(const auto& s : {"cheer.wav",
                         "javelin.wav",
                         "wrestling.wav",
                         "cheer2.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mStadium.push_back(r);
    }

    for(const auto& s : {"sanctuary1.wav",
                         "sanctuary2.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mSanctuary.push_back(r);
    }

    for(const auto& s : {"armory1.wav",
                         "armory2.wav",
                         "armory3.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mArmory.push_back(r);
    }

    for(const auto& s : {"horse1.wav",
                         "horse2.wav",
                         "horse3.wav",
                         "horse4.wav",
                         "horse5.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mHorseRanch.push_back(r);
    }

    for(const auto& s : {"win_chime1.wav",
                         "win_chime2.wav",
                         "recreation1.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mBeautification.push_back(r);
    }

    for(const auto& s : {"fountain1.wav",
                         "fountain2.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mFountain.push_back(r);
    }

    for(const auto& s : {"artisan_guild1.wav",
                         "artisan_guild2.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mArtisan.push_back(r);
    }




    for(const auto& s : {"bird7.wav",
                         "finch2.wav",
                         "sparrow1.wav",
                         "bird3.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mMeadow.push_back(r);
    }

    for(const auto& s : {"bird1.wav",
                         "bird2.wav",
                         "bird4.wav",
                         "rustling1.wav",
                         "rustling2.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mFarmland.push_back(r);
    }

    for(const auto& s : {"wave1.wav",
                         "wave2.wav",
                         "wave3.wav",
                         "wave4.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mBeach.push_back(r);
    }

    for(const auto& s : {"rumble.wav",
                         "rockslide1.wav",
                         "rockslide2.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mRocky.push_back(r);
    }

    for(const auto& s : {"bird3.wav",
                         "bird4.wav",
                         "bird5.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mVegetation.push_back(r);
    }

    for(const auto& s : {"water_space1.wav",
                         "water_space2.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mWater.push_back(r);
    }



    for(const auto& s : {"boar1.wav",
                         "boar2.wav",
                         "boar3.wav",
                         "boar4.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mBoar.push_back(r);
    }

    for(const auto& s : {"goat1.wav",
                         "goat2.wav",
                         "goat3.wav",
                         "goat4.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mGoat.push_back(r);
    }

    for(const auto& s : {"wolf1.wav",
                         "wolf2.wav",
                         "wolf3.wav",
                         "wolf4.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mWolf.push_back(r);
    }

    for(const auto& s : {"sheep1.wav",
                         "sheep2.wav",
                         "sheep3.wav",
                         "sheep4.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mSheep.push_back(r);
    }

    for(const auto& s : {"cattle1.wav",
                         "cattle2.wav",
                         "cattle3.wav",
                         "cattle4.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mCattle.push_back(r);
    }

    for(const auto& s : {"deer1.wav",
                         "deer2.wav",
                         "deer3.wav",
                         "deer4.wav"}) {
        const auto r = loadSoundBase(layer2Dir + s);
        if(r) mDeer.push_back(r);
    }


    const std::string wavsDir{"../Audio/Wavs/"};
    mFire = loadSoundBase(wavsDir + "Fire.wav");
    mCollapse = loadSoundBase(wavsDir + "collapse.wav");

    mAphrodite.load();
    mApollo.load();
    mAres.load();
    mArtemis.load();
    mAthena.load();
    mAtlas.load();
    mDemeter.load();
    mDionysus.load();
    mHades.load();
    mHephaestus.load();
    mHera.load();
    mHermes.load();
    mPoseidon.load();
    mZeus.load();
}

void eGodSounds::load() {
    const std::string voiceDir{"../Audio/Voice/Walker/"};
    const std::string wavsDir{"../Audio/Wavs/"};

    for(const auto& s : {fShortName + "_ev_1.mp3",
                         fShortName + "_ev_2.mp3",
                         fShortName + "_ev_3.mp3"}) {
        const auto r = loadSoundBase(voiceDir + s);
        if(r) fVisit.push_back(r);
    }

    fInvade = loadSoundBase(voiceDir + fShortName + "_ev_4.mp3");

    fAppear = loadSoundBase(wavsDir + "G_" + fLongName + "_mat.wav");
    fDisappear = loadSoundBase(wavsDir + "G_" + fLongName + "_demat.wav");

    for(const auto& s : {"G_" + fLongName + "_atk1.wav",
                         "G_" + fLongName + "_atk2.wav",
                         "G_" + fLongName + "_atk3.wav",
                         "G_" + fLongName + "_atk4.wav"}) {
        const auto r = loadSoundBase(wavsDir + s);
        if(r) fAttack.push_back(r);
    }

    fCurse = loadSoundBase(wavsDir + "G_" + fLongName + "_curse.wav");
    fHit = loadSoundBase(wavsDir + "G_" + fLongName + "_hit.wav");
    fSanctify = loadSoundBase(wavsDir + "G_" + fLongName + "_sanctify.wav");
}
