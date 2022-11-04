#include "esounds.h"

#include "engine/etile.h"
#include "buildings/ebuilding.h"
#include "characters/echaracter.h"

#include "egamedir.h"

eSounds eSounds::sInstance;

Mix_Chunk* eSounds::loadSoundBase(const std::string& path) {
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
    deleteSounds(mArtisansGuild);

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

    // collectors
    deleteSounds(mCopperMiner);
    deleteSounds(mSilverMiner);
    deleteSounds(mTreeCutter);
    deleteSounds(mStoneCutter);

    deleteSounds(mArtisan);

    // events
    Mix_FreeChunk(mFire);
    Mix_FreeChunk(mCollapse);
}

void eSounds::loadButtonSound() {
    const std::string wavsDir{eGameDir::path("Audio/Wavs/")};
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
        case eBuildingType::palace:
            return eSounds::playPalaceSound();
        case eBuildingType::podium:
        case eBuildingType::college:
            return eSounds::playPhilosophySound();
        case eBuildingType::gymnasium:
            return eSounds::playGymnasiumSound();
        case eBuildingType::stadium:
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

void eSounds::playFireballHitSound() {
    Mix_PlayChannel(-1, sInstance.mFireballHit, 0);
}

void eSounds::playCopperMinerSound() {
    playRandomSound(sInstance.mCopperMiner);
}

void eSounds::playSilverMinerSound() {
    playRandomSound(sInstance.mSilverMiner);
}

void eSounds::playStoneCutterSound() {
    playRandomSound(sInstance.mStoneCutter);
}

void eSounds::playTreeCutterSound() {
    playRandomSound(sInstance.mTreeCutter);
}

void eSounds::playArtisanSound() {
    playRandomSound(sInstance.mArtisan);
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

void eSounds::playHeroSound(const eHeroType h, const eHeroSound s) {
    eHeroSounds* hero = nullptr;
    switch(h) {
    case eHeroType::achilles:
        hero = &sInstance.mAchilles; break;
    case eHeroType::atalanta:
        hero = &sInstance.mAtalanta; break;
    case eHeroType::bellerophon:
        hero = &sInstance.mBellerophon; break;
    case eHeroType::hercules:
        hero = &sInstance.mHercules; break;
    case eHeroType::jason:
        hero = &sInstance.mJason; break;
    case eHeroType::odysseus:
        hero = &sInstance.mOdysseus; break;
    case eHeroType::perseus:
        hero = &sInstance.mPerseus; break;
    case eHeroType::theseus:
        hero = &sInstance.mTheseus; break;
    }
    hero->play(s);
}

void eSounds::playAttackSound(eCharacter* const c) {

}

void eSounds::playDieSound(eCharacter* const c) {
    const auto ct = c->type();
    switch(ct) {
    case eCharacterType::actor:
        Mix_PlayChannel(-1, sInstance.mActorDie, 0);
        break;
    case eCharacterType::rockThrower:
        Mix_PlayChannel(-1, sInstance.mRockthrowerDie, 0);
        break;
    case eCharacterType::boar:
        Mix_PlayChannel(-1, sInstance.mBoarDie, 0);
        break;
    case eCharacterType::hunter:
        Mix_PlayChannel(-1, sInstance.mBoarHunterDie, 0);
        break;
    case eCharacterType::deer:
        Mix_PlayChannel(-1, sInstance.mDeerDie, 0);
        break;
    case eCharacterType::hoplite:
        Mix_PlayChannel(-1, sInstance.mHopliteDie, 0);
        break;

    case eCharacterType::calydonianBoar:
        sInstance.mCalydonianBoar.playDie();
        break;
    case eCharacterType::cerberus:
        sInstance.mCerberus.playDie();
        break;
    case eCharacterType::chimera:
        sInstance.mChimera.playDie();
        break;
    case eCharacterType::cyclops:
        sInstance.mCyclops.playDie();
        break;
    case eCharacterType::dragon:
        sInstance.mDragon.playDie();
        break;
    case eCharacterType::echidna:
        sInstance.mEchidna.playDie();
        break;
    case eCharacterType::harpies:
        sInstance.mHarpies.playDie();
        break;
    case eCharacterType::hector:
        sInstance.mHector.playDie();
        break;
    case eCharacterType::hydra:
        sInstance.mHydra.playDie();
        break;
    case eCharacterType::kraken:
        sInstance.mKraken.playDie();
        break;
    case eCharacterType::maenads:
        sInstance.mMaenads.playDie();
        break;
    case eCharacterType::medusa:
        sInstance.mMedusa.playDie();
        break;
    case eCharacterType::minotaur:
        sInstance.mMinotaur.playDie();
        break;
    case eCharacterType::scylla:
        sInstance.mScylla.playDie();
        break;
    case eCharacterType::sphinx:
        sInstance.mSphinx.playDie();
        break;
    case eCharacterType::talos:
        sInstance.mTalos.playDie();
        break;
    default: {
        const int id = rand() % sInstance.mGenDie.size();
        Mix_PlayChannel(-1, sInstance.mGenDie[id], 0);
    } break;
    }
}

void eSounds::playHitSound(eCharacter* const c) {
    const auto ct = c->type();
    switch(ct) {
    case eCharacterType::actor:
        Mix_PlayChannel(-1, sInstance.mActorHit, 0);
        break;
    case eCharacterType::rockThrower:
        Mix_PlayChannel(-1, sInstance.mRockthrowerHit, 0);
        break;
    case eCharacterType::boar:
        Mix_PlayChannel(-1, sInstance.mBoarHit, 0);
        break;
    case eCharacterType::hunter:
        Mix_PlayChannel(-1, sInstance.mBoarHunterHit, 0);
        break;
    case eCharacterType::deer:
        Mix_PlayChannel(-1, sInstance.mDeerHit, 0);
        break;
    case eCharacterType::hoplite:
        Mix_PlayChannel(-1, sInstance.mHopliteHit, 0);
        break;

    case eCharacterType::aphrodite:
        sInstance.mAphrodite.playHit();
        break;
    case eCharacterType::apollo:
        sInstance.mApollo.playHit();
        break;
    case eCharacterType::ares:
        sInstance.mAres.playHit();
        break;
    case eCharacterType::artemis:
        sInstance.mArtemis.playHit();
        break;
    case eCharacterType::athena:
        sInstance.mAthena.playHit();
        break;
    case eCharacterType::atlas:
        sInstance.mAtlas.playHit();
        break;
    case eCharacterType::demeter:
        sInstance.mDemeter.playHit();
        break;
    case eCharacterType::dionysus:
        sInstance.mDionysus.playHit();
        break;
    case eCharacterType::hades:
        sInstance.mHades.playHit();
        break;
    case eCharacterType::hephaestus:
        sInstance.mHephaestus.playHit();
        break;
    case eCharacterType::hera:
        sInstance.mHera.playHit();
        break;
    case eCharacterType::hermes:
        sInstance.mHermes.playHit();
        break;
    case eCharacterType::poseidon:
        sInstance.mPoseidon.playHit();
        break;
    case eCharacterType::zeus:
        sInstance.mZeus.playHit();
        break;

    case eCharacterType::calydonianBoar:
        sInstance.mCalydonianBoar.playHit();
        break;
    case eCharacterType::cerberus:
        sInstance.mCerberus.playHit();
        break;
    case eCharacterType::chimera:
        sInstance.mChimera.playHit();
        break;
    case eCharacterType::cyclops:
        sInstance.mCyclops.playHit();
        break;
    case eCharacterType::dragon:
        sInstance.mDragon.playHit();
        break;
    case eCharacterType::echidna:
        sInstance.mEchidna.playHit();
        break;
    case eCharacterType::harpies:
        sInstance.mHarpies.playHit();
        break;
    case eCharacterType::hector:
        sInstance.mHector.playHit();
        break;
    case eCharacterType::hydra:
        sInstance.mHydra.playHit();
        break;
    case eCharacterType::kraken:
        sInstance.mKraken.playHit();
        break;
    case eCharacterType::maenads:
        sInstance.mMaenads.playHit();
        break;
    case eCharacterType::medusa:
        sInstance.mMedusa.playHit();
        break;
    case eCharacterType::minotaur:
        sInstance.mMinotaur.playHit();
        break;
    case eCharacterType::scylla:
        sInstance.mScylla.playHit();
        break;
    case eCharacterType::sphinx:
        sInstance.mSphinx.playHit();
        break;
    case eCharacterType::talos:
        sInstance.mTalos.playHit();
        break;
    default: {
        const int id = rand() % sInstance.mGenHit.size();
        Mix_PlayChannel(-1, sInstance.mGenHit[id], 0);
    } break;
    }
}

void eSounds::loadImpl() {
    if(mLoaded) return;
    mLoaded = true;

    {
        const std::string layer1Dir{eGameDir::path("Audio/Ambient/Layer1/")};
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
    const std::string layer2Dir{eGameDir::path("Audio/Ambient/Layer2/")};

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
        if(r) mArtisansGuild.push_back(r);
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


    const std::string wavsDir{eGameDir::path("Audio/Wavs/")};
    mFire = loadSoundBase(wavsDir + "Fire.wav");
    mCollapse = loadSoundBase(wavsDir + "collapse.wav");

    mFireballHit = loadSoundBase(wavsDir + "Fireball_hit.wav");


    for(const auto& s : {"copperminer1.wav",
                         "copperminer2.wav"}) {
        const auto r = loadSoundBase(wavsDir + s);
        if(r) mCopperMiner.push_back(r);
    }

    for(const auto& s : {"silverminer1.wav",
                         "silverminer2.wav"}) {
        const auto r = loadSoundBase(wavsDir + s);
        if(r) mSilverMiner.push_back(r);
    }

    for(const auto& s : {"treecutter1.wav",
                         "treecutter2.wav"}) {
        const auto r = loadSoundBase(wavsDir + s);
        if(r) mTreeCutter.push_back(r);
    }

    for(const auto& s : {"stonecutter1.wav",
                         "stonecutter2.wav"}) {
        const auto r = loadSoundBase(wavsDir + s);
        if(r) mStoneCutter.push_back(r);
    }

    for(const auto& s : {"artisan1.wav",
                         "artisan2.wav"}) {
        const auto r = loadSoundBase(wavsDir + s);
        if(r) mArtisan.push_back(r);
    }

    mActorDie = loadSoundBase(wavsDir + "actor_die.wav");
    mActorHit = loadSoundBase(wavsDir + "actor_hit.wav");

    for(const auto& s : {"am_warr_atk1.wav",
                         "am_warr_atk2.wav"}) {
        const auto r = loadSoundBase(wavsDir + s);
        if(r) mRockthrowerAttack.push_back(r);
    }
    mRockthrowerDie = loadSoundBase(wavsDir + "am_warr_die.wav");
    mRockthrowerHit = loadSoundBase(wavsDir + "am_warr_hit.wav");

    mBoarAttack = loadSoundBase(wavsDir + "boar_attack.wav");
    mBoarDie = loadSoundBase(wavsDir + "boar_die.wav");
    mBoarHit = loadSoundBase(wavsDir + "boar_hit.wav");

    mDeerAttack = loadSoundBase(wavsDir + "deer_attack.wav");
    mDeerDie = loadSoundBase(wavsDir + "deer_die.wav");
    mDeerHit = loadSoundBase(wavsDir + "deer_hit.wav");

    for(const auto& s : {"gen_die1.wav",
                         "gen_die2.wav",
                         "gen_die3.wav",
                         "gen_die4.wav",
                         "gen_die5.wav",
                         "gen_die6.wav",
                         "gen_die7.wav",
                         "gen_die8.wav"}) {
        const auto r = loadSoundBase(wavsDir + s);
        if(r) mGenDie.push_back(r);
    }

    for(const auto& s : {"gen_hit1.wav",
                         "gen_hit2.wav",
                         "gen_hit3.wav",
                         "gen_hit4.wav",
                         "gen_hit5.wav",
                         "gen_hit6.wav",
                         "gen_hit7.wav",
                         "gen_hit8.wav"}) {
        const auto r = loadSoundBase(wavsDir + s);
        if(r) mGenHit.push_back(r);
    }

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

    mAchilles.load();
    mAtalanta.load();
    mBellerophon.load();
    mHercules.load();
    mJason.load();
    mOdysseus.load();
    mPerseus.load();
    mTheseus.load();

    mCalydonianBoar.load();
    mCerberus.load();
    mChimera.load();
    mCyclops.load();
    mDragon.load();
    mEchidna.load();
    mHarpies.load();
    mHector.load();
    mHydra.load();
    mKraken.load();
    mMaenads.load();
    mMedusa.load();
    mMinotaur.load();
    mScylla.load();
    mSphinx.load();
    mTalos.load();
}
